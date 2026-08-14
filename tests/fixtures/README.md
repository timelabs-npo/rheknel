# Pinned Omnia ABI fixtures

These files are byte-identical copies of `timelabs-npo/omnia-playbook` producer artifacts from commit `7a233147423dd350fcdcc8aa2709c0091df5bb02` on `integration/rhea-link-v1` (PR #7).

The positive golden `omnia-dns-macos.omnb` is SHA-256 `c84075b7c8b28b16e3a97fa48b858a67530f42f55a5c4c051f9ad3e0f2b3c729`. `omnia-manifest.json` records its source YAML baseline, sizes, and every adversarial fixture hash. `OMNIA_SHA256SUMS` is copied unchanged from the producer.

`omnia-dns-macos.h` is deterministically derived from the positive binary by `tools/embed_omnia.py`; `make embed-check` proves the committed header is byte-equivalent.
