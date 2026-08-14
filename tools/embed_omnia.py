#!/usr/bin/env python3
"""Convert a compact Omnia bundle into a deterministic C byte array."""

from __future__ import annotations

import argparse
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--symbol", default="omnia_embedded_bundle")
    args = parser.parse_args()
    data = args.input.read_bytes()
    rows = []
    for offset in range(0, len(data), 12):
        rows.append("    " + ", ".join(f"0x{value:02x}" for value in data[offset : offset + 12]) + ",")
    guard = (args.symbol + "_H").upper()
    content = "\n".join(
        [
            f"#ifndef {guard}",
            f"#define {guard}",
            "",
            f"static const unsigned char {args.symbol}[] = {{",
            *rows,
            "};",
            f"static const size_t {args.symbol}_size = sizeof({args.symbol});",
            "",
            f"#endif /* {guard} */",
            "",
        ]
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(content, encoding="ascii")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
