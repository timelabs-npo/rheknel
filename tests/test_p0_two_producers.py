#!/usr/bin/env python3
from __future__ import annotations

import argparse
import importlib.util
import json
import pathlib
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]

def load_module(name: str, path: pathlib.Path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)
    return module

ADC = load_module("adc_to_rheknel", ROOT / "tools" / "adc_to_rheknel.py")
OMNIA = load_module("omnia_to_rheknel", ROOT / "tools" / "omnia_to_rheknel.py")

class TwoProducerTests(unittest.TestCase):
    omnia_root: pathlib.Path

    @classmethod
    def setUpClass(cls):
        cls.adc_contract = json.loads(
            (ROOT / "tests" / "fixtures" / "adc-file-replace.json").read_text(
                encoding="utf-8"
            )
        )

    def test_same_effect_and_authority_without_core_special_case(self):
        adc = ADC.adapt(self.adc_contract)
        omnia = OMNIA.adapt(
            self.omnia_root,
            pathlib.Path("bus/fixtures/p0-replace-file.bundle.json"),
            1790640000,
        )

        self.assertEqual(adc["rheknel_ir_version"], "0.1")
        self.assertEqual(omnia["rheknel_ir_version"], "0.1")
        self.assertEqual(adc["effect"], omnia["effect"])
        self.assertEqual(adc["authority"], omnia["authority"])
        self.assertEqual(adc["source"]["format"], "adc")
        self.assertEqual(omnia["source"]["format"], "omnia")

    def test_stale_omnia_contract_fails_closed(self):
        with self.assertRaises(OMNIA.ContractError):
            OMNIA.adapt(
                self.omnia_root,
                pathlib.Path("bus/fixtures/p0-replace-file.bundle.json"),
                1793232001,
            )

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--omnia-root", type=pathlib.Path, required=True)
    args = parser.parse_args()

    TwoProducerTests.omnia_root = args.omnia_root.resolve()
    suite = unittest.defaultTestLoader.loadTestsFromTestCase(TwoProducerTests)
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    raise SystemExit(0 if result.wasSuccessful() else 1)

if __name__ == "__main__":
    main()
