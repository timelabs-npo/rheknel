#!/usr/bin/env python3
"""Strict Omnia ABI 1.0 -> Rheknel P0 canonical effect adapter.

The Omnia producer remains external. This adapter imports the pinned producer's
reference codec, compiles the declared source manifest, decodes the exact OMNA
bundle, and maps one bounded replace_file authority contract into Rheknel IR.

Security rule: ambiguous or unsupported semantics fail closed.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

HEX64 = re.compile(r"^[0-9a-f]{64}$")

class ContractError(ValueError):
    pass

def _load_codec(omnia_root: Path):
    tools_dir = omnia_root / "tools"
    sys.path.insert(0, str(tools_dir))
    try:
        import omnia_bus_codec
    except Exception as exc:
        raise ContractError(f"cannot import Omnia codec from {tools_dir}: {exc}") from exc
    return omnia_bus_codec

def _require_exact_keys(value, expected, name):
    if not isinstance(value, dict):
        raise ContractError(f"{name}: expected object")
    keys = set(value)
    expected = set(expected)
    if keys != expected:
        raise ContractError(
            f"{name}: expected keys {sorted(expected)}, got {sorted(keys)}"
        )
    return value

def _require_string(value, name):
    if not isinstance(value, str) or not value:
        raise ContractError(f"{name}: expected non-empty string")
    return value

def adapt(omnia_root: Path, manifest: Path, now_epoch_s: int):
    codec = _load_codec(omnia_root)
    manifest_path = manifest if manifest.is_absolute() else omnia_root / manifest

    try:
        encoded = codec.compile_bundle(omnia_root, manifest_path)
        decoded = codec.decode_bundle(encoded)
    except Exception as exc:
        raise ContractError(f"Omnia compile/decode rejected input: {exc}") from exc

    if decoded.get("abi") != "1.0":
        raise ContractError("omnia.abi: P0 requires exactly 1.0")
    if decoded.get("target_platform") != "rheknel-p0":
        raise ContractError("omnia.target_platform: expected rheknel-p0")

    created_at = decoded.get("created_at")
    fresh_until = decoded.get("fresh_until")
    if not isinstance(created_at, int) or not isinstance(fresh_until, int):
        raise ContractError("omnia freshness: expected integer epoch bounds")
    if now_epoch_s < created_at or now_epoch_s > fresh_until:
        raise ContractError("omnia bundle: not currently valid for supplied P0 clock")

    records = decoded.get("records")
    if not isinstance(records, list) or len(records) != 1:
        raise ContractError("omnia records: P0 requires exactly one record")

    record = records[0]
    if record.get("kind") != "invariant":
        raise ContractError("omnia record: P0 requires invariant kind")
    if record.get("states") != {
        "consistency": "pass",
        "applicability": "applicable",
        "verifiability": "verified",
        "reliability": "reliable",
    }:
        raise ContractError("omnia record: authority state is not fully admissible")

    assessed_at = record.get("assessed_at")
    record_fresh_until = record.get("fresh_until")
    if (
        not isinstance(assessed_at, int)
        or not isinstance(record_fresh_until, int)
        or now_epoch_s < assessed_at
        or now_epoch_s > record_fresh_until
    ):
        raise ContractError("omnia record: stale or not-yet-valid")

    metadata = record.get("metadata")
    if not isinstance(metadata, dict):
        raise ContractError("omnia metadata: expected object")
    check = _require_exact_keys(
        metadata.get("check"),
        (
            "audit_required",
            "autonomous",
            "enforcement_mode",
            "expected_new_sha256",
            "expected_old_sha256",
            "target",
            "type",
        ),
        "omnia.metadata.check",
    )

    if check.get("type") != "replace_file":
        raise ContractError("omnia check.type: unsupported effect")
    if check.get("enforcement_mode") != "infrastructure":
        raise ContractError("omnia check.enforcement_mode: must be infrastructure")
    if check.get("audit_required") is not True:
        raise ContractError("omnia check.audit_required: must be true")
    if check.get("autonomous") is not True:
        raise ContractError("omnia check.autonomous: must be true")

    target = _require_string(check.get("target"), "omnia check.target")
    old_hash = _require_string(
        check.get("expected_old_sha256"), "omnia check.expected_old_sha256"
    )
    new_hash = _require_string(
        check.get("expected_new_sha256"), "omnia check.expected_new_sha256"
    )

    if not target.startswith("/"):
        raise ContractError("omnia check.target: must be absolute")
    if not HEX64.fullmatch(old_hash):
        raise ContractError("omnia check.expected_old_sha256: invalid lowercase sha256")
    if not HEX64.fullmatch(new_hash):
        raise ContractError("omnia check.expected_new_sha256: invalid lowercase sha256")

    return {
        "rheknel_ir_version": "0.1",
        "source": {
            "format": "omnia",
            "version": "1.0",
            "bundle_id": decoded["bundle_id"],
            "frame_sha256": decoded["frame_sha256"],
            "source_sha256": decoded["source_sha256"],
        },
        "effect": {
            "type": "replace_file",
            "target": target,
            "expected_old_sha256": old_hash,
            "expected_new_sha256": new_hash,
        },
        "authority": {
            "autonomous": True,
            "enforcement_mode": "infrastructure",
            "audit_required": True,
        },
    }

def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--omnia-root", type=Path, required=True)
    parser.add_argument(
        "--manifest",
        type=Path,
        default=Path("bus/fixtures/p0-replace-file.bundle.json"),
    )
    parser.add_argument("--now", type=int, default=1790640000)
    parser.add_argument("-o", "--output", type=Path)
    args = parser.parse_args(argv)

    try:
        result = adapt(args.omnia_root.resolve(), args.manifest, args.now)
    except (OSError, ContractError) as exc:
        print(f"omnia_to_rheknel: reject: {exc}", file=sys.stderr)
        return 2

    payload = json.dumps(result, sort_keys=True, separators=(",", ":")) + "\n"
    if args.output:
        args.output.write_text(payload, encoding="utf-8")
    else:
        sys.stdout.write(payload)
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
