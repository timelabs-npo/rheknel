#!/usr/bin/env python3
"""P0 bounded effect authority.

Experiment harness only. It executes exactly one effect type against one target.
Before the effect, the canonical typed effect is admitted through the compiled
Rheknel C dispatch gate. Only the OS identity running this process owns write
permission to the protected resource.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import subprocess
import sys
from pathlib import Path

P0_TARGET = Path("/var/lib/rheknel-protected/result.bin")
IR_VERSION = "0.1"
HEX64 = frozenset("0123456789abcdef")

class AuthorityError(RuntimeError):
    pass

def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()

def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        while True:
            chunk = handle.read(65536)
            if not chunk:
                break
            digest.update(chunk)
    return digest.hexdigest()

def require_sha256(value: object, name: str) -> str:
    if (
        not isinstance(value, str)
        or len(value) != 64
        or any(ch not in HEX64 for ch in value)
    ):
        raise AuthorityError(f"{name}: expected lowercase sha256 hex")
    return value

def validate_ir(value: object) -> dict:
    if not isinstance(value, dict):
        raise AuthorityError("IR: expected object")
    if set(value) != {"rheknel_ir_version", "source", "effect", "authority"}:
        raise AuthorityError("IR: unexpected top-level fields")
    if value["rheknel_ir_version"] != IR_VERSION:
        raise AuthorityError("IR: unsupported version")
    if not isinstance(value["source"], dict) or not value["source"]:
        raise AuthorityError("IR.source: expected non-empty object")

    effect = value["effect"]
    if not isinstance(effect, dict) or set(effect) != {
        "type", "target", "expected_old_sha256", "expected_new_sha256"
    }:
        raise AuthorityError("IR.effect: unexpected fields")
    if effect["type"] != "replace_file":
        raise AuthorityError("IR.effect.type: unsupported")
    if effect["target"] != str(P0_TARGET):
        raise AuthorityError("IR.effect.target: outside P0 capability")
    require_sha256(effect["expected_old_sha256"], "IR.effect.expected_old_sha256")
    require_sha256(effect["expected_new_sha256"], "IR.effect.expected_new_sha256")

    authority = value["authority"]
    if not isinstance(authority, dict) or set(authority) != {
        "autonomous", "enforcement_mode", "audit_required"
    }:
        raise AuthorityError("IR.authority: unexpected fields")
    if authority["autonomous"] is not True:
        raise AuthorityError("IR.authority.autonomous: must be true")
    if authority["enforcement_mode"] != "infrastructure":
        raise AuthorityError("IR.authority.enforcement_mode: must be infrastructure")
    if authority["audit_required"] is not True:
        raise AuthorityError("IR.authority.audit_required: must be true")
    return value

def rheknel_gate(gate_path: Path, ir: dict) -> str:
    effect = ir["effect"]
    try:
        result = subprocess.run(
            [
                str(gate_path),
                effect["target"],
                effect["expected_old_sha256"],
                effect["expected_new_sha256"],
            ],
            check=False,
            capture_output=True,
            text=True,
        )
    except OSError as exc:
        raise AuthorityError(f"Rheknel C gate could not execute: {exc}") from exc

    stdout = result.stdout.strip()
    if result.stderr:
        print(result.stderr, file=sys.stderr, end="")
    if stdout:
        print(stdout)
    if result.returncode != 0 or "rheknel_gate=PASS" not in stdout:
        raise AuthorityError(
            f"Rheknel C gate denied effect: exit={result.returncode} output={stdout!r}"
        )
    return stdout

def execute(ir_path: Path, payload_path: Path, receipt_path: Path, gate_path: Path) -> dict:
    raw_ir = ir_path.read_bytes()
    try:
        ir = json.loads(raw_ir)
    except json.JSONDecodeError as exc:
        raise AuthorityError(f"IR: malformed JSON: {exc}") from exc
    ir = validate_ir(ir)

    canonical_ir = json.dumps(ir, sort_keys=True, separators=(",", ":")).encode("utf-8")
    ir_sha256 = sha256_bytes(canonical_ir)

    target = P0_TARGET
    if not target.exists() or not target.is_file():
        raise AuthorityError("protected target: missing or not a regular file")

    before_hash = sha256_file(target)
    expected_old = ir["effect"]["expected_old_sha256"]
    if before_hash != expected_old:
        raise AuthorityError(
            f"pre-state mismatch: expected {expected_old}, observed {before_hash}"
        )

    payload = payload_path.read_bytes()
    payload_hash = sha256_bytes(payload)
    expected_new = ir["effect"]["expected_new_sha256"]
    if payload_hash != expected_new:
        raise AuthorityError(
            f"payload mismatch: expected {expected_new}, observed {payload_hash}"
        )

    gate_evidence = rheknel_gate(gate_path, ir)

    temp = target.with_name(f".{target.name}.p0-{os.getpid()}.tmp")
    fd = None
    try:
        fd = os.open(temp, os.O_WRONLY | os.O_CREAT | os.O_EXCL, 0o644)
        with os.fdopen(fd, "wb", closefd=True) as handle:
            fd = None
            handle.write(payload)
            handle.flush()
            os.fsync(handle.fileno())
        os.replace(temp, target)
        dir_fd = os.open(target.parent, os.O_RDONLY)
        try:
            os.fsync(dir_fd)
        finally:
            os.close(dir_fd)
    finally:
        if fd is not None:
            os.close(fd)
        try:
            temp.unlink()
        except FileNotFoundError:
            pass

    after_hash = sha256_file(target)
    if after_hash != expected_new:
        raise AuthorityError(
            f"post-state mismatch: expected {expected_new}, observed {after_hash}"
        )

    receipt = {
        "schema": "rheknel.p0.effect-receipt/v1",
        "result": "PASS",
        "ir_sha256": ir_sha256,
        "source": ir["source"],
        "effect": {
            "type": "replace_file",
            "target": str(target),
            "before_sha256": before_hash,
            "after_sha256": after_hash,
        },
        "authority": ir["authority"],
        "rheknel_gate": gate_evidence,
    }
    receipt_path.write_text(
        json.dumps(receipt, sort_keys=True, separators=(",", ":")) + "\n",
        encoding="utf-8",
    )
    return receipt

def main(argv=None) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--ir", type=Path, required=True)
    parser.add_argument("--payload", type=Path, required=True)
    parser.add_argument("--receipt", type=Path, required=True)
    parser.add_argument("--gate", type=Path, required=True)
    args = parser.parse_args(argv)

    try:
        receipt = execute(args.ir, args.payload, args.receipt, args.gate)
    except (OSError, AuthorityError) as exc:
        print(f"p0_effect_authority: reject: {exc}", file=sys.stderr)
        return 2

    print(json.dumps(receipt, sort_keys=True, separators=(",", ":")))
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
