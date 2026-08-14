# Rheknel ABI 1.0 verification artifacts

- `receipts/macos-arm64-host.log`: host build, CTest, ASan/UBSan, static-analysis, positive action, stale no-action, sizes, hashes, and explicit portability boundary.
- `external-openbsd-receipt.md`: added only after a GitHub OpenBSD VM run actually completes; absence means no live OpenBSD claim.
- consumer fixtures and their producer manifest are in `tests/fixtures/`.

Producer commit: `timelabs-npo/omnia-playbook@7a233147423dd350fcdcc8aa2709c0091df5bb02`.

Current measured host artifacts are not committed as binaries: the static library was 15,816 bytes and the host CLI was 35,736 bytes. Those sizes are macOS arm64 observations, not cross-platform invariants.
