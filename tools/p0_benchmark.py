#!/usr/bin/env python3
"""Small reproducible P0 adapter benchmark.

Reports measured adapter wall/CPU latency and process peak RSS.
This is proposal evidence, not a real-time guarantee.
"""

from __future__ import annotations

import argparse
import importlib.util
import json
import pathlib
import resource
import statistics
import time

ROOT = pathlib.Path(__file__).resolve().parents[1]

def load_module(name: str, path: pathlib.Path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)
    return module

ADC = load_module("adc_to_rheknel_bench", ROOT / "tools" / "adc_to_rheknel.py")
OMNIA = load_module("omnia_to_rheknel_bench", ROOT / "tools" / "omnia_to_rheknel.py")

def percentile_ns(samples, p):
    ordered = sorted(samples)
    if not ordered:
        raise ValueError("empty sample")
    idx = max(0, min(len(ordered) - 1, round((len(ordered) - 1) * p)))
    return ordered[idx]

def loc(path: pathlib.Path) -> int:
    count = 0
    for line in path.read_text(encoding="utf-8").splitlines():
        stripped = line.strip()
        if stripped and not stripped.startswith("#"):
            count += 1
    return count

def measure(fn, iterations: int):
    walls = []
    cpus = []
    for _ in range(iterations):
        c0 = time.process_time_ns()
        w0 = time.perf_counter_ns()
        fn()
        w1 = time.perf_counter_ns()
        c1 = time.process_time_ns()
        walls.append(w1 - w0)
        cpus.append(c1 - c0)
    return {
        "iterations": iterations,
        "wall_us_p50": percentile_ns(walls, 0.50) / 1000.0,
        "wall_us_p95": percentile_ns(walls, 0.95) / 1000.0,
        "cpu_us_mean": statistics.fmean(cpus) / 1000.0,
    }

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--omnia-root", type=pathlib.Path, required=True)
    parser.add_argument("--iterations", type=int, default=100)
    args = parser.parse_args()
    if args.iterations < 10:
        raise SystemExit("iterations must be >= 10")

    adc_contract = json.loads(
        (ROOT / "tests" / "fixtures" / "adc-file-replace.json").read_text(
            encoding="utf-8"
        )
    )
    omnia_root = args.omnia_root.resolve()
    manifest = pathlib.Path("bus/fixtures/p0-replace-file.bundle.json")

    # Warm both paths before measuring.
    ADC.adapt(adc_contract)
    OMNIA.adapt(omnia_root, manifest, 1790640000)

    adc = measure(lambda: ADC.adapt(adc_contract), args.iterations)
    omnia = measure(
        lambda: OMNIA.adapt(omnia_root, manifest, 1790640000),
        args.iterations,
    )

    rss = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
    # Linux reports KiB; macOS reports bytes. The benchmark CI job is Linux.
    result = {
        "schema": "rheknel.p0.benchmark/v1",
        "host_assumption": "GitHub-hosted Ubuntu runner; values are observations, not guarantees",
        "adc_adapter": adc,
        "omnia_adapter": omnia,
        "adapter_loc": {
            "adc_to_rheknel": loc(ROOT / "tools" / "adc_to_rheknel.py"),
            "omnia_to_rheknel": loc(ROOT / "tools" / "omnia_to_rheknel.py"),
            "p0_effect_authority": loc(ROOT / "tools" / "p0_effect_authority.py"),
        },
        "process_peak_rss_kib": rss,
    }
    print(json.dumps(result, sort_keys=True, indent=2))

if __name__ == "__main__":
    main()
