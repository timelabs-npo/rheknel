#!/usr/bin/env python3
"""Strict ADC v0.1 -> Rheknel P0 canonical effect adapter.

P0 deliberately supports exactly one external semantic:
authority.decisions[].decision_type == "replace_file"

Security rule: unknown or ambiguous semantics fail closed.
No model inference, fuzzy matching, or permissive defaults.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
from pathlib import Path

HEX64 = re.compile(r"^[0-9a-f]{64}$")
REQUIRED_THRESHOLD_FIELDS = (
    "replace_file.target",
    "replace_file.expected_old_sha256",
    "replace_file.expected_new_sha256",
)

class ContractError(ValueError):
    pass

def _require_dict(value, name):
    if not isinstance(value, dict):
        raise ContractError(f"{name}: expected object")
    return value

def _require_string(value, name):
    if not isinstance(value, str) or not value:
        raise ContractError(f"{name}: expected non-empty string")
    return value

def _extract_eq_thresholds(decision):
    thresholds = decision.get("thresholds")
    if not isinstance(thresholds, list):
        raise ContractError("authority.decisions[].thresholds: expected array")

    values = {}
    for item in thresholds:
        item = _require_dict(item, "threshold")
        field = _require_string(item.get("field"), "threshold.field")
        operator = _require_string(item.get("operator"), "threshold.operator")
        if field not in REQUIRED_THRESHOLD_FIELDS:
            raise ContractError(f"{field}: unsupported threshold field in P0")
        if operator != "eq":
            raise ContractError(f"{field}: only operator=eq is accepted in P0")
        if field in values:
            raise ContractError(f"{field}: duplicate threshold")
        values[field] = item.get("value")

    missing = [name for name in REQUIRED_THRESHOLD_FIELDS if name not in values]
    if missing:
        raise ContractError("missing required threshold(s): " + ", ".join(missing))
    return values

def adapt(contract):
    root = _require_dict(contract, "contract")

    if root.get("adc_version") != "0.1":
        raise ContractError("adc_version: P0 requires exactly 0.1")

    contract_id = _require_string(root.get("contract_id"), "contract_id")
    agent = _require_dict(root.get("agent"), "agent")
    agent_id = _require_string(agent.get("agent_id"), "agent.agent_id")

    binding = _require_dict(root.get("binding"), "binding")
    if binding.get("enforcement_mode") != "infrastructure":
        raise ContractError("binding.enforcement_mode: must be infrastructure")
    if binding.get("audit_required") is not True:
        raise ContractError("binding.audit_required: must be true")
    if binding.get("on_violation") not in ("deny_and_halt", "deny_and_escalate"):
        raise ContractError("binding.on_violation: unsupported fail-closed behavior")

    authority = _require_dict(root.get("authority"), "authority")
    decisions = authority.get("decisions")
    if not isinstance(decisions, list) or not decisions:
        raise ContractError("authority.decisions: expected non-empty array")

    matches = []
    for decision in decisions:
        decision = _require_dict(decision, "authority.decisions[]")
        if decision.get("decision_type") == "replace_file":
            matches.append(decision)

    if len(matches) != 1:
        raise ContractError("authority.decisions: require exactly one replace_file decision")

    decision = matches[0]
    if decision.get("autonomous") is not True:
        raise ContractError("replace_file.autonomous: must be true")

    values = _extract_eq_thresholds(decision)
    target = _require_string(values["replace_file.target"], "replace_file.target")
    old_hash = _require_string(
        values["replace_file.expected_old_sha256"],
        "replace_file.expected_old_sha256",
    )
    new_hash = _require_string(
        values["replace_file.expected_new_sha256"],
        "replace_file.expected_new_sha256",
    )

    if not target.startswith("/"):
        raise ContractError("replace_file.target: must be absolute")
    if not HEX64.fullmatch(old_hash):
        raise ContractError("replace_file.expected_old_sha256: expected lowercase sha256")
    if not HEX64.fullmatch(new_hash):
        raise ContractError("replace_file.expected_new_sha256: expected lowercase sha256")

    source_bytes = json.dumps(root, sort_keys=True, separators=(",", ":")).encode("utf-8")
    source_sha256 = hashlib.sha256(source_bytes).hexdigest()

    return {
        "rheknel_ir_version": "0.1",
        "source": {
            "format": "adc",
            "version": "0.1",
            "contract_id": contract_id,
            "agent_id": agent_id,
            "canonical_sha256": source_sha256,
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
    parser.add_argument("contract", type=Path)
    parser.add_argument("-o", "--output", type=Path)
    args = parser.parse_args(argv)

    try:
        contract = json.loads(args.contract.read_text(encoding="utf-8"))
        result = adapt(contract)
    except (OSError, json.JSONDecodeError, ContractError) as exc:
        print(f"adc_to_rheknel: reject: {exc}", file=sys.stderr)
        return 2

    payload = json.dumps(result, sort_keys=True, separators=(",", ":")) + "\n"
    if args.output:
        args.output.write_text(payload, encoding="utf-8")
    else:
        sys.stdout.write(payload)
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
