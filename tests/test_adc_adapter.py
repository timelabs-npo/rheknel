#!/usr/bin/env python3
from __future__ import annotations

import copy
import importlib.util
import json
import pathlib
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]
ADAPTER = ROOT / "tools" / "adc_to_rheknel.py"
FIXTURE = ROOT / "tests" / "fixtures" / "adc-file-replace.json"

spec = importlib.util.spec_from_file_location("adc_to_rheknel", ADAPTER)
module = importlib.util.module_from_spec(spec)
assert spec.loader is not None
spec.loader.exec_module(module)

class AdcAdapterTests(unittest.TestCase):
    def load(self):
        return json.loads(FIXTURE.read_text(encoding="utf-8"))

    def test_valid_contract_maps_to_canonical_effect(self):
        result = module.adapt(self.load())
        self.assertEqual(result["rheknel_ir_version"], "0.1")
        self.assertEqual(result["source"]["format"], "adc")
        self.assertEqual(result["source"]["version"], "0.1")
        self.assertEqual(
            result["effect"]["target"],
            "/var/lib/rheknel-protected/result.bin",
        )
        self.assertEqual(result["effect"]["type"], "replace_file")
        self.assertTrue(result["authority"]["audit_required"])
        self.assertEqual(
            result["authority"]["enforcement_mode"],
            "infrastructure",
        )

    def test_missing_audit_requirement_fails_closed(self):
        contract = self.load()
        contract["binding"]["audit_required"] = False
        with self.assertRaises(module.ContractError):
            module.adapt(contract)

    def test_native_enforcement_mode_fails_closed_for_p0(self):
        contract = self.load()
        contract["binding"]["enforcement_mode"] = "native"
        with self.assertRaises(module.ContractError):
            module.adapt(contract)

    def test_missing_required_threshold_fails_closed(self):
        contract = self.load()
        contract["authority"]["decisions"][0]["thresholds"] = [
            item
            for item in contract["authority"]["decisions"][0]["thresholds"]
            if item["field"] != "replace_file.expected_new_sha256"
        ]
        with self.assertRaises(module.ContractError):
            module.adapt(contract)

    def test_duplicate_security_threshold_fails_closed(self):
        contract = self.load()
        duplicate = copy.deepcopy(
            contract["authority"]["decisions"][0]["thresholds"][0]
        )
        contract["authority"]["decisions"][0]["thresholds"].append(duplicate)
        with self.assertRaises(module.ContractError):
            module.adapt(contract)

    def test_unknown_adc_version_fails_closed(self):
        contract = self.load()
        contract["adc_version"] = "0.2"
        with self.assertRaises(module.ContractError):
            module.adapt(contract)

    def test_non_absolute_target_fails_closed(self):
        contract = self.load()
        for item in contract["authority"]["decisions"][0]["thresholds"]:
            if item["field"] == "replace_file.target":
                item["value"] = "relative/result.bin"
        with self.assertRaises(module.ContractError):
            module.adapt(contract)

if __name__ == "__main__":
    unittest.main()
