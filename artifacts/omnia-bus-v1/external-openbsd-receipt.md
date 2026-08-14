# Live OpenBSD ABI verification receipt

## Bound source

- repository: `timelabs-npo/rheknel`
- branch: `integration/rhea-link-v1`
- source commit: `f1cafe4b1efb7773a7b7b7aed549a8e30b49d089`
- ABI: `1.0`
- fixture SHA-256: `c84075b7c8b28b16e3a97fa48b858a67530f42f55a5c4c051f9ad3e0f2b3c729`

## Live OpenBSD run

- workflow run: [31809158269](https://github.com/timelabs-npo/rheknel/actions/runs/31809158269)
- job: [94795291175](https://github.com/timelabs-npo/rheknel/actions/runs/31809158269/job/94795291175)
- conclusion: `success`
- run created: `2026-08-14T14:22:14Z`
- job completed: `2026-08-14T14:23:31Z`
- guest: `OpenBSD openbsd.my.domain 7.9 GENERIC.MP#4 amd64`
- compiler: `OpenBSD clang version 19.1.7`
- compiler target: `amd64-unknown-openbsd7.9`
- checkout action: `actions/checkout@11d5960a326750d5838078e36cf38b85af677262`
- VM action: `vmactions/openbsd-vm@c30f6df85ed7db55c714ea9c354d00747d10481d`

Observed output:

```text
omnia_bus: all adversarial and boundary checks passed
status=OK verdict=0 records_applicable=2 action_count=1 now=1786665600
SHA256 (tests/fixtures/omnia-dns-macos.omnb) = c84075b7c8b28b16e3a97fa48b858a67530f42f55a5c4c051f9ad3e0f2b3c729
```

## Hosted cross-platform run

[CMake run 31809158065](https://github.com/timelabs-npo/rheknel/actions/runs/31809158065)
completed successfully at the same source commit for Linux GCC, Linux Clang,
and Windows MSVC, including build and CTest execution for every matrix entry.

## Evidence boundary

This is live execution in an OpenBSD 7.9 amd64 VM launched by a pinned GitHub
Action on GitHub-hosted infrastructure. It is not an independent third-party
reproduction. It does not establish OpenBSD arm64 or physical-hardware runtime
behavior. The inspected MBSD repository targets OpenWrt 23.05.4 Linux on MT7981,
not OpenBSD, and neither MBSD firmware nor Beryl hardware was built or mutated.
