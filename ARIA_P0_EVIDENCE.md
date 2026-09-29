# ARIA P0 Evidence Record

Status: **TEST_PASSED**
Date: 2026-09-29

This record binds the pre-proposal P0 result to concrete source revisions and external CI runs.

## Bound source

### Rheknel implementation under test

- repository: `timelabs-npo/rheknel`
- implementation branch: `proposal/aria-p0-adc`
- **sealed implementation SHA: `570ee290cbb6fa64945abca4e24a3e939c3f13a5`**
- PR: https://github.com/timelabs-npo/rheknel/pull/7

The evidence document itself is committed after the sealed implementation SHA and is not part of the implementation under test.

### Omnia producer under test

- repository: `timelabs-npo/omnia-playbook`
- branch: `proposal/aria-p0-replace-file`
- **producer SHA: `3f41e64cc9348dc95a7fa0c0a2f7537becde8ebd`**
- PR: https://github.com/timelabs-npo/omnia-playbook/pull/13

### External producer specification

Producer B is the public **Agent Delegation Contract (ADC) v0.1 Working Draft**:
https://github.com/Labs-R2-Advisory/adc-spec

The upstream README describes ADC as an open machine-readable AI-agent authorization specification and explicitly states that ADC is a specification rather than an implementation. P0 therefore treats ADC as an independent contract source, not as Rheknel code.

## External CI result

Primary Rheknel P0 run:

- workflow: `ARIA P0 producer conformance`
- run: **36555320853**
- URL: https://github.com/timelabs-npo/rheknel/actions/runs/36555320853
- event: pull_request
- head SHA: `570ee290cbb6fa64945abca4e24a3e939c3f13a5`
- conclusion: **success**

Jobs:
- `p0-two-producers`: job **109362957904** — success
- `p0-effect-boundary`: job **109362958289** — success
- `p0-adc (ubuntu-latest)`: job **109362958300** — success
- `p0-adc (macos-latest)`: job **109362958224** — success

Current-head OpenBSD regression:

- workflow run: **36555320854**
- URL: https://github.com/timelabs-npo/rheknel/actions/runs/36555320854
- head SHA: `570ee290cbb6fa64945abca4e24a3e939c3f13a5`
- tracked separately from the Linux authority-separation experiment.

Omnia producer compilation:

- workflow: `ARIA P0 Omnia producer`
- run: **36554169338**
- URL: https://github.com/timelabs-npo/omnia-playbook/actions/runs/36554169338
- head SHA: `3f41e64cc9348dc95a7fa0c0a2f7537becde8ebd`
- conclusion: **success**
- compiled OMNA artifact size: **926 bytes**
- compiled package SHA-256: `b57b2dc5420606f565bd0e1ca669f075c3b78222d794818696bf750461f36d7d`
- decoded frame SHA-256: `dd632c2203c40cca2b667451f8f978d7be287670d1b2b676a8a9d391f1499fd4`
- decoded source SHA-256: `360eb27c1ce1f1f7ea5a839fe72e5fe2f298612ca187117152a75ce6bed53a0b`
- exact source evidence binding: **PASS**

## Acceptance evidence

### 1. Two independently defined producers reach the same canonical effect semantics — PASS

Job 109362957904 reports:

`test_same_effect_and_authority_without_core_special_case ... ok`

ADC and Omnia both produced:

```text
effect.type = replace_file
effect.target = /var/lib/rheknel-protected/result.bin
effect.expected_old_sha256 = 2f58779ddbbaf9113f455bc6145e9914a6c3c5bd4009c3ada730403425a47eac
effect.expected_new_sha256 = efceb412448a47a7e85909d3ee3800aea941d9cd8125cce19f8b65ccff8eaf3b

authority.autonomous = true
authority.enforcement_mode = infrastructure
authority.audit_required = true
```

The producer-specific source metadata differs, as intended.

### 2. Producer B integration does not alter Rheknel C core semantics — PASS

The same job executes:

```text
git diff --exit-code 1e603bd65d7a320d759640cc36532284e54fd4fc HEAD -- src include kernel.c
```

and reports:

```text
core_semantic_diff=NONE
```

The P0-specific C gate is an external caller of the existing `rhea_dispatch` API; it does not modify `src/`, `include/`, or `kernel.c`.

### 3. ADC fail-closed adapter conformance — PASS

Ubuntu job 109362958300 reports:

```text
Ran 11 tests in 0.002s
OK
```

The test matrix includes:
- malformed JSON;
- unsupported ADC version;
- missing audit requirement;
- unsupported enforcement mode;
- missing required authority threshold;
- duplicate security threshold;
- unknown security-significant threshold;
- non-autonomous decision;
- invalid SHA-256;
- non-absolute target;
- valid positive mapping.

The same job also reports the existing C regression suite:

```text
100% tests passed, 0 tests failed out of 3
```

including the existing Omnia adversarial test, ADC adapter conformance and Omnia CLI positive path.

### 4. Stale Omnia contract fails closed — PASS

Job 109362957904 reports:

```text
test_stale_omnia_contract_fails_closed ... ok
```

Existing Omnia adversarial fixtures additionally cover contradictory, provenance-missing, unsupported-version, malformed and integrity-tamper cases.

### 5. Untrusted proposer cannot bypass authority — PASS for the tested Linux permission model

Job 109362958289 creates distinct Unix identities:
- `rheknel-agent`
- `rheknel-authority`

The protected resource is:
`/var/lib/rheknel-protected/result.bin`

Initial state:

```text
pre_state_sha256=2f58779ddbbaf9113f455bc6145e9914a6c3c5bd4009c3ada730403425a47eac
```

Direct write under `rheknel-agent` is rejected by the OS:

```text
cannot create /var/lib/rheknel-protected/result.bin: Permission denied
direct_bypass=OS_DENIED status=2
post_attempt_sha256=2f58779ddbbaf9113f455bc6145e9914a6c3c5bd4009c3ada730403425a47eac
```

Thus the bypass attempt did not modify the protected state.

### 6. Both producer-derived effects pass through the compiled Rheknel C dispatch gate — PASS

Before each admitted effect, the authority harness invokes the compiled `p0_gate`, which registers a typed judge/action pair and calls the existing Rheknel `rhea_dispatch` API.

For both ADC-derived and Omnia-derived IRs, job 109362958289 records:

```text
rheknel_gate=PASS verdict=0 action_count=1
```

The receipt includes this gate evidence.

### 7. ADC-derived admitted effect reaches exact expected post-state — PASS

```text
adc_effect=PASS
post_state_sha256=efceb412448a47a7e85909d3ee3800aea941d9cd8125cce19f8b65ccff8eaf3b
```

The execution receipt binds:
- canonical IR SHA-256;
- ADC contract identity/version;
- before-state hash;
- after-state hash;
- exact effect target;
- authority semantics;
- compiled Rheknel gate result.

### 8. Omnia-derived admitted effect reaches the same exact post-state — PASS

```text
omnia_effect=PASS
post_state_sha256=efceb412448a47a7e85909d3ee3800aea941d9cd8125cce19f8b65ccff8eaf3b
```

The receipt binds the Omnia bundle/frame/source identities and the same before/after effect state.

### 9. Wrong payload is rejected without changing protected state — PASS

Job 109362958289 records:

```text
wrong_payload=REJECTED status=2
post_state_sha256=2f58779ddbbaf9113f455bc6145e9914a6c3c5bd4009c3ada730403425a47eac
```

No accepted completion receipt is emitted for the wrong payload.

## Measured efficiency evidence

Source: job 109362957904, 200 iterations on a GitHub-hosted Ubuntu runner.

### Adapter latency

ADC adapter:
- p50 wall: **14.507 µs**
- p95 wall: **24.566 µs**
- mean CPU: **16.797 µs**

Omnia adapter (includes reference producer compile/decode path):
- p50 wall: **513.280 µs**
- p95 wall: **948.896 µs**
- mean CPU: **604.808 µs**

### Process memory

- Python benchmark process peak RSS: **21,472 KiB**

This is the peak RSS of the Python proposal harness, not the memory footprint of the C Rheknel core.

### Code / artifact sizes

Measured adapter/harness nonblank non-comment LOC:
- `adc_to_rheknel.py`: **135**
- `omnia_to_rheknel.py`: **159**
- `p0_effect_authority.py`: **159** at the benchmarked revision

Existing release C artifacts on the Ubuntu runner:
- `librheknel.a`: **26,266 bytes**
- `rhea` CLI: **30,376 bytes**

These are environment-specific observations, not cross-platform size guarantees.

## P0 verdict

Against the frozen `ARIA_PROOF_P0.md` acceptance criteria:

| Criterion | Result |
|---|---|
| two independent producers reach same canonical effect semantics | PASS |
| Producer B integration requires no Rheknel core semantic change | PASS |
| valid ADC contract completes intended bounded effect | PASS |
| valid Omnia contract completes intended bounded effect | PASS |
| negative adapter/contract cases fail closed | PASS for tested matrix |
| direct proposer bypass is OS denied | PASS on GitHub-hosted Ubuntu |
| real post-state independently matches receipt | PASS |
| efficiency measurements captured | PASS |

**P0 = TEST_PASSED.**

## Scope boundary / non-claims

P0 does **not** prove:

- universal non-bypassability;
- security against a compromised kernel, root, or authority process;
- formal verification;
- production daemon/IPC isolation;
- physical hardware isolation;
- independent third-party reproduction;
- generality beyond the two tested producer formats and one `replace_file` effect;
- latency/memory guarantees outside the named CI environment.

The P0 effect authority is an experiment harness. The actual funded proposal must treat productionisation, additional effect classes, Arena integration and independent adversarial review as Foreground R&D.

## Stop rule

P0 technical expansion stops here.

Use this evidence in the ARIA proposal.
Do not add another effect, another producer, a GUI, cloud service, agent framework or platform merely because the current proof works.
