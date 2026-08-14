# Rheknel

Rheknel is a fixed-capacity, fail-closed C99 dispatch kernel plus an allocation-free consumer for Omnia's compact invariant/check bundle.

The integration boundary is deliberately direct:

```text
Omnia YAML/JSON + assurance metadata
                ↓ deterministic compiler
          OMNA binary ABI 1.0
                ↓ zero-copy validation
          Rheknel deterministic judge
                ↓
       OK / REJECT / ESCALATE / ERROR
                ↓ only OK reaches action
```

There is no RPC service, daemon, broker, natural-language authority, or extra coordination component.

## What is implemented

- exact-version ABI 1.0 with strict rejection of every other version or unknown flag;
- frame and source SHA-256, evidence IDs, provenance IDs, and deterministic freshness evaluation from caller-supplied epoch seconds;
- compact exact encodings for states, kinds, integers, strings, arrays, and maps; floats are rejected rather than rounded;
- consistency, applicability, verifiability, and reliability state handling with explicit verdict mapping;
- allocation-free, endian-independent parsing with checked offsets, canonical ULEB128, UTF-8 validation, depth/size/count limits, and duplicate-ID contradiction detection;
- fail-closed dispatch: unknown judges, malformed typed input, unsupported ABI, stale data, and direct `rhea_emit()` cannot run actions;
- portable C99 build/test path and an OpenBSD path that uses `pledge(2)` in the CLI;
- embedded C-header fixture and binary-file consumption paths.

The normative encoding and loss guarantees are in [`docs/OMNIA_RHEKNEL_ABI.md`](docs/OMNIA_RHEKNEL_ABI.md). Omnia owns the compiler and source fixtures in its separate repository; the byte-identical test vectors here pin the consumer boundary.

## Build and test

```sh
make test
make sanitize
make embed-check
```

Run the host CLI with an explicit clock input:

```sh
./build/rhea tests/fixtures/omnia-dns-macos.omnb 1786665600
```

The golden result is `OK` with one action. At `1789257601` the same artifact is stale, returns `ESCALATE`, and executes zero actions.

`make openbsd-test` is dependency-light and uses the platform `cc`; GitHub CI also executes it inside a pinned OpenBSD VM. A successful cross-compile or static analysis is not described as a live OpenBSD run—see [`docs/PORTABILITY.md`](docs/PORTABILITY.md).

## MBSD boundary

`timelabs-npo/mbsd@a970e76ee41104e80aea8a1782a8053da2a3e116` identifies MBSD as OpenWrt 23.05.4/Linux on MediaTek MT7981 and records its prior OpenBSD direction as superseded. Rheknel therefore does not invent an MBSD/OpenBSD target. An MBSD claim requires an actual OpenWrt SDK/toolchain build and remains separate from OpenBSD verification.

## Safety boundary

Rheknel evaluates already-typed data. It does not prove source truth, execute Omnia checks, grant mutation authority from text, or make stale/missing evidence current. The fixed registries are process-global and not thread-safe; callers must serialize registration/dispatch or wrap instances externally.
