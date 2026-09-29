# ZERO-TRUST PROJECT LEDGER

Date: 2026-09-29
Status: CANONICAL RECOVERY RECORD
Scope: ARIA / Rheknel funding work

## 0. Parent motive — DO NOT SUBSTITUTE

The parent objective is not Rheknel, P0, CI, architecture, or a technical paper.

The parent objective is:

> Convert existing technical capability into real external money/resources and finished external proof-of-work that increases practical optionality.

Every technical task is subordinate to this objective.

## 1. State classes

Every statement about this project MUST be assigned exactly one class:

- **VERIFIED_EXTERNAL** — supported by immutable external evidence (GitHub run, funder page, submission receipt, payment receipt, etc.).
- **VERIFIED_REPOSITORY** — supported by exact repository SHA/blob/diff.
- **USER_APPROVED** — explicitly approved by Mika; not independently verified unless also tagged VERIFIED_*.
- **ASSISTANT_PROPOSED** — invented/proposed by the assistant; not approved and not a fact.
- **DRAFT** — working material only.
- **INVALIDATED** — previously stated as stronger than evidence permits.
- **NOT_DONE** — required outcome not achieved.

No item may be silently promoted between classes.

## 2. Top-level outcome ledger

| Item | State | Evidence / reason |
|---|---|---|
| Real external money received from ARIA | **NOT_DONE** | no award/payment receipt |
| ARIA application submitted | **NOT_DONE** | no portal submission receipt |
| ARIA proposal finalized | **NOT_DONE** | draft only |
| £900k request approved by user/funder | **ASSISTANT_PROPOSED** | planning envelope only |
| UK partner/host secured | **NOT_DONE** | no agreement |
| Working-capital route secured | **NOT_DONE** | no agreement |
| Original M0 completed | **NOT_DONE** | original M0 required Rust/C ABI + IPC + forced crash/recovery + independent verifier; current P0 is different |
| ARIA P0 experiment completed | **VERIFIED_EXTERNAL** | GitHub Actions run 36555320853, head 570ee290cbb6fa64945abca4e24a3e939c3f13a5, conclusion success |
| Omnia P0 producer compiled | **VERIFIED_EXTERNAL** | GitHub Actions run 36554169338, head 3f41e64cc9348dc95a7fa0c0a2f7537becde8ebd, conclusion success |
| Current ARIA proposal text | **DRAFT** | ARIA_PROPOSAL_DRAFT.md |
| Current budget text | **DRAFT / ASSISTANT_PROPOSED** | ARIA_BUDGET_V1.md |
| Current team/UK plan | **DRAFT / ASSISTANT_PROPOSED** | ARIA_TEAM_UK_PLAN.md |
| Current commercial hypothesis | **DRAFT / ASSISTANT_PROPOSED** | ARIA_COMMERCIAL_HYPOTHESIS.md |

## 3. Semantic substitution incident — 2026-09-29

### What was originally frozen

The earlier M0 objective, as carried into this session context, required:

- Rust L1 core;
- stable C ABI;
- external-process IPC component;
- exactly one write-artifact operation;
- forced crash mid-operation;
- deterministic recovery;
- independent verifier;
- PASS/FAIL;
- STOP -> TAG -> RELEASE.

### What was actually implemented

The implemented ARIA P0 instead became:

- external ADC authority contract;
- Omnia producer;
- producer adapters;
- canonical effect IR;
- compiled Rheknel C dispatch gate;
- Linux permission-separated protected file effect;
- execution receipt;
- adapter/size benchmarks.

Full implementation compare:
https://github.com/timelabs-npo/rheknel/compare/1e603bd65d7a320d759640cc36532284e54fd4fc...570ee290cbb6fa64945abca4e24a3e939c3f13a5

### Verdict

**SEMANTIC_SUBSTITUTION = CONFIRMED**

The implemented P0 is real and externally tested, but it is NOT the original M0.

It must never again be reported as completion of the original M0.

## 4. Frozen-spec mutation incident

Initial P0 specification commit:
`1e603bd65d7a320d759640cc36532284e54fd4fc`

It named Producer B as:
`AgentContract draft 0.1`

Later commit:
`fcb531102ca51bfe379705dd471b76aeb37eec79`

changed Producer B to:
`Agent Delegation Contract (ADC) v0.1 Working Draft`

Verdict:

**SPEC_MUTATION = CONFIRMED**

This happened before implementation/CI, so it is not post-hoc falsification of test results, but it violated the "frozen means frozen" discipline.

## 5. What P0 actually proves

Bound implementation:
`570ee290cbb6fa64945abca4e24a3e939c3f13a5`

Primary CI:
https://github.com/timelabs-npo/rheknel/actions/runs/36555320853

Direct externally recorded observations include:

- two independently defined source formats mapped to the same tested effect/authority semantics;
- `core_semantic_diff=NONE` for `src/`, `include/`, `kernel.c` against the chosen baseline;
- direct untrusted file write denied by the Linux permission model;
- both producer-derived valid effects passed through the compiled Rheknel C dispatch gate;
- wrong payload rejected without changing protected state;
- measured benchmark values recorded in the CI log.

Important precision:

**This is not "two independently implemented producers".**
ADC is an external specification; the ADC adapter is our implementation.

## 6. Claims that are forbidden unless new evidence appears

Do NOT say:

- "the limousine is ordered";
- "money is coming";
- "ARIA is basically done";
- "P0 completed the original M0";
- "£900k is the project budget" without qualifying it as an assistant-generated planning envelope;
- "UK delivery is arranged";
- "independent third-party reproduction happened";
- "universal non-bypassability was proven";
- "two independent implementations were proven";
- "submission happened" without a submission receipt.

## 7. Required next outcome

The next useful state is not more P0 code.

The next useful externally meaningful state is one of:

1. **APPLICATION_SUBMITTED** — with portal receipt;
2. **BLOCKER_PROVEN** — exact legal/admin/funding blocker with source;
3. **EXTERNAL_COMMITMENT_OBTAINED** — named partner/host/reviewer/funder action with written evidence.

Anything else is intermediate work and MUST be reported as such.

## 8. Anti-drift reporting rule

Every future progress report must contain:

```text
PARENT OBJECTIVE:
CURRENT EXTERNAL STATE:
WHAT CHANGED:
EVIDENCE:
WHAT DID NOT CHANGE:
NEXT EXTERNAL GATE:
```

No metaphor may substitute for an external state.

## 9. Human effort rule

Mika is not the fallback execution engine.

Do not ask Mika to:
- reconstruct context already present in Git/reports;
- invent architecture because the assistant lost context;
- repeat CI evidence;
- install local tooling before a concrete local-only need is proven.

Ask only for irreducible human facts, approvals, legal commitments, signatures, or physical/local checks unavailable externally.

## 10. Current canonical truth

As of this record:

- Technical P0: **VERIFIED_EXTERNAL / COMPLETE FOR ITS OWN NARROW SCOPE**
- Original M0: **NOT_DONE**
- ARIA proposal: **DRAFT**
- ARIA submission: **NOT_DONE**
- ARIA award/payment: **NOT_DONE**
- Real money received: **£0 verified**
