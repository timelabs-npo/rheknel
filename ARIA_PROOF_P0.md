# ARIA Pre-Proposal Proof Spec — P0

Status: FROZEN FOR IMPLEMENTATION
Date: 2026-09-29
Parent: ARIA Scaling Trust Track 2.2
Purpose: produce the minimum new evidence required for the proposal.

## 1. Question

Can the same deterministic Rheknel core consume two independently defined contract sources and enforce the same bounded effect semantics without core changes?

If no, the general reusable-component claim is weak.

## 2. Contract sources

### Producer A — Omnia
Source: existing Omnia -> Rheknel ABI 1.0 path.
Role: Background IP baseline.

### Producer B — AgentContract draft 0.1
Source: external open language-agnostic AI-agent contract specification.
Role: independent external contract source.

Important:
Rheknel does NOT replace AgentContract.
The experiment tests whether an external behavioral contract can be adapted into the same deterministic effect-boundary representation used by existing Omnia data.

## 3. Core invariant

Adapters may translate producer-specific syntax into the canonical Rheknel request/contract IR.

Adapters MUST NOT:
- widen authority;
- invent omitted permissions;
- silently convert unknown values to allow;
- modify Rheknel core semantics;
- contain agent/model inference.

Unknown / unsupported semantics fail closed.

## 4. One protected effect

One effect only:

`replace_file(path, expected_old_hash, new_bytes, expected_new_hash)`

The protected target exists inside a directory writable only by the deterministic authority process.

The untrusted proposer identity cannot directly replace the file.

## 5. Topology

```text
Omnia ABI 1.0 -----\
                    > adapter -> canonical Rheknel IR
AgentContract YAML-/                    |
                                        v
                               deterministic judge
                                        |
                                  OK / deny
                                        |
                                        v
                               bounded file effector
                                        |
                                        v
                               post-state receipt
```

## 6. Positive cases

For each producer:

1. express the same allowed replace-file contract;
2. adapt to canonical IR;
3. verify canonical IR semantics are equivalent;
4. execute through Rheknel;
5. observe exactly one write;
6. verify final hash;
7. record receipt.

## 7. Negative cases

For each applicable producer/adapter:

- malformed syntax -> zero effect;
- missing authority -> zero effect;
- unknown field with security significance -> zero effect;
- stale/expired contract -> zero effect;
- wrong expected_old_hash -> zero effect;
- wrong expected_new_hash -> zero accepted completion;
- direct proposer write bypass -> OS denial;
- adapter attempts authority widening -> conformance test failure.

## 8. Measurements

Record:

- adapter LOC;
- whether Rheknel core changed (must be NO for producer B integration);
- p50/p95 validation latency;
- CPU time;
- peak memory;
- binary size;
- valid-case completion;
- false rejection;
- unauthorized-effect count;
- direct-bypass result.

## 9. PASS

PASS only if:

- both producer sources reach the same canonical effect semantics;
- Producer B requires no Rheknel core semantic change;
- all valid cases complete;
- all negative cases produce zero unauthorized effects;
- direct bypass is OS-denied;
- post-state receipts independently match the real file state.

## 10. FAIL / kill conditions

STOP and revise the ARIA thesis if:

- external Producer B requires special-case changes inside Rheknel core;
- semantics cannot be translated without ambiguity;
- adapters need model inference;
- direct effect bypass succeeds;
- evidence cannot distinguish requested/admitted/executed/post-state values;
- runtime overhead is disproportionate to the tiny effect.

## 11. Deliverables

Only:

- AgentContract adapter;
- Omnia adapter reuse / minimal normalisation if necessary;
- canonical IR definition;
- one bounded file effector;
- conformance tests;
- benchmark script;
- receipt format;
- results table.

No GUI.
No cloud service.
No extra operating systems.
No generic plugin system.
No new agent framework.
No additional effect types before P0 PASS.

## 12. After PASS

Capture results.
Freeze source SHA.
Use measurements in ARIA proposal.
STOP.

Do not turn P0 into the funded project.
