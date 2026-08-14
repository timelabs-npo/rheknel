# Rheknel ABI 1.0 verification artifacts

- `receipts/macos-arm64-host.log`: host build, CTest, ASan/UBSan, static-analysis, positive action, stale no-action, sizes, hashes, and explicit portability boundary.
- `external-openbsd-receipt.md`: immutable receipt for the successful GitHub CI run inside an OpenBSD 7.9 amd64 VM.
- consumer fixtures and their producer manifest are in `tests/fixtures/`.

Producer commit: `timelabs-npo/omnia-playbook@7a233147423dd350fcdcc8aa2709c0091df5bb02`.

Current measured host artifacts are not committed as binaries: the static library was 15,848 bytes and the host CLI was 35,672 bytes. Those sizes are macOS arm64 observations, not cross-platform invariants.

The OpenBSD receipt proves execution in the named CI VM for the recorded source
commit. It is not independent third-party reproduction and does not cover
OpenBSD arm64, physical OpenBSD hardware, MBSD/OpenWrt, or Beryl hardware.
