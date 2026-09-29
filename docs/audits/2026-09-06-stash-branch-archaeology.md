# Stash propagation and branch archaeology: rheknel

This documentation-only record routes archival evidence to its relevant repository. Snapshot: **2026-09-06, Europe/Moscow**, before the documentation branches created by this pass. Every comparison below uses fixed commit IDs.

The canonical archive is [rhea-project/stash](https://github.com/timelabs-npo/rhea-project/blob/3316bae0770744238099c25ae34e76e7ad4af8b4/stash/README.md). It is a normal Git branch named `stash`, separate from local `refs/stash`. Its 37 archive files total **361,824 bytes**; this pass reconstructed their UTF-8 bytes locally, verified each Git blob SHA-1 and size, and verified SHA-256 after disk readback. The four content-addressed original reports also match the SHA-256 encoded in their paths and total **115,053 bytes**.

The [original collection manifest](https://github.com/timelabs-npo/rhea-project/blob/3316bae0770744238099c25ae34e76e7ad4af8b4/stash/runs/2026-09-06-cloud-001/manifest.json) still records **41 pending items/groups** and `PARTIAL_WD_UNAVAILABLE`. That is the original cloud capture's state, not a statement that this Windows host lacks filesystem access. Mirroring the published archive does not collect the binaries, source trees, VM disks or histories merely named in those reports. Those pending artifacts were not captured in this pass.

At the six inspected main tips, no blob matches any of the 37 `stash/` archive blobs. This is exact-content evidence, not proof that no paraphrases, links or equivalent implementation exist. The propagation proposed here is a pinned documentation pointer and repository-specific findings; implementation adoption remains a separate change.

## Repository findings and routing

[PR #4](https://github.com/timelabs-npo/rheknel/pull/4), `integration/rhea-link-v1@009545681da7ad4dfb7580f584642faf7f0a6a5d`, is **5 ahead / 2 behind** main. Its paired producer is [Omnia Playbook #7](https://github.com/timelabs-npo/omnia-playbook/pull/7), `7a233147423dd350fcdcc8aa2709c0091df5bb02`. Both PRs remain open.

The six `.omnb` consumer fixtures, `tests/fixtures/OMNIA_SHA256SUMS`, and `tests/fixtures/omnia-manifest.json` have the same Git blobs as their eight producer counterparts under `artifacts/omnia-bus-v1/`. That establishes exact repository object identity across the pair. It does not establish that the judge ran, that a platform passed, or that v2 admits the legacy ABI.

Current main `c07ca8384259b613f81cba197fb749f52b86d10f` differs from the local historical `6e605c5077b561c5330b505fef3e6654fbb852dd` by two README/artwork commits only. [PR #1](https://github.com/timelabs-npo/rheknel/pull/1) has one unique commit but zero branch-side changed files against its merge base; the commit count alone is not a security implementation. [PR #2](https://github.com/timelabs-npo/rheknel/pull/2) contains one changed path, `rhea`, and its own title says no dashboard implementation was found. No binary was executed in this pass.

Use the [stash compatibility record](https://github.com/timelabs-npo/rhea-project/blob/3316bae0770744238099c25ae34e76e7ad4af8b4/stash/memory/COMPATIBILITY.md) to preserve the distinction between the legacy judge chain and clean-slate v2. Any actual legacy integration should review producer and consumer together on exact SHAs. Do not infer present-day authority or v2 compatibility from a historical component name.

## Branch ledger

Pinned main: `c07ca8384259b613f81cba197fb749f52b86d10f`. Ahead/behind counts measure commit ancestry relative to that main. They do not measure missing patches, successful tests or merge readiness. Historical merged PRs can refer to older heads, or contain content integrated without the original ancestry.

| Branch | Pinned head | Ahead / behind main | PR evidence |
| --- | --- | --- | --- |
| `copilot/build-binary-from-rheknel-c` | [`b10c19a1c9fa`](https://github.com/timelabs-npo/rheknel/commit/b10c19a1c9fa72b0a1cd68847389bb4bea88a8a5) | 1 / 2 | [#2](https://github.com/timelabs-npo/rheknel/pull/2) open draft |
| `copilot/implement-rhea-kernel-security` | [`80af27349dcf`](https://github.com/timelabs-npo/rheknel/commit/80af27349dcfbbe214d89d1c0fed90b115c589eb) | 1 / 5 | [#1](https://github.com/timelabs-npo/rheknel/pull/1) open draft |
| `integration/rhea-link-v1` | [`009545681da7`](https://github.com/timelabs-npo/rheknel/commit/009545681da7ad4dfb7580f584642faf7f0a6a5d) | 5 / 2 | [#4](https://github.com/timelabs-npo/rheknel/pull/4) open |
| `main` | [`c07ca8384259`](https://github.com/timelabs-npo/rheknel/commit/c07ca8384259b613f81cba197fb749f52b86d10f) | 0 / 0 | none in retrieved PR history |

## Verification limits

All branch lists and PR lists fit within the 100-item first page. Comparisons cover every non-main branch. The checkpoint branch's explicit no-common-ancestor response is recorded as unrelated history. Recursive trees used for content identity checks were not truncated. GitHub comparison file lists can stop at 300 files; a 300-entry list is not a complete large-branch diff. No broad patch-equivalence analysis of the older Rhea histories was performed.

This pass used GitHub metadata, pinned trees, selected documents and local archive hashing. Component tests, builds, deployment checks, production runtime checks and pending WD artifact collection were not run. The archive's published Drive and scheduler receipts were read as historical records; those external states were not reverified or changed.
