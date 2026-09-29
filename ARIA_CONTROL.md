# ARIA Scaling Trust Track 2.2 — CONTROL

Last updated: 2026-09-29
Repository: `timelabs-npo/rheknel`
Canonical branch: `proposal/aria-scaling-trust-2-2`
Execution tracker: https://github.com/timelabs-npo/rheknel/issues/6
Canonical truth ledger: `ZERO_TRUST_PROJECT_LEDGER.md`

## Parent objective

```text
external resources / money / finished proof-of-work
        ↓
ARIA Track 2.2 application
        ↓
fundable deterministic contract-to-effect component
        ↓
submit
        ↓
STOP
```

Rheknel is a means, not the parent objective.

## Current state

**Mandatory truth source:** before reporting progress, read `ZERO_TRUST_PROJECT_LEDGER.md`. It overrides narrative continuity from chat.

| Gate | Status | Direct evidence / canonical artifact | Next condition |
|---|---|---|---|
| Track fit | SPECIFIED | `ARIA_SCALING_TRUST_TRACK2.md` | competitive comparison must be sourced |
| GO / NO-GO positioning | CONDITIONAL GO | `ARIA_GO_NO_GO.md` | remain differentiated from generic sandbox/warden |
| Original M0 | NOT_DONE | `ZERO_TRUST_PROJECT_LEDGER.md` | do not conflate with ARIA P0 |
| P0 proof specification | TEST_PASSED / STOPPED | `ARIA_PROOF_P0.md` | no more P0 features |
| P0 source-bound evidence | VERIFIED | `ARIA_P0_EVIDENCE.md` | use in proposal |
| P0 implementation | VERIFIED | Rheknel SHA `570ee290cbb6fa64945abca4e24a3e939c3f13a5`, run `36555320853` | frozen |
| Omnia Producer A | VERIFIED | SHA `3f41e64cc9348dc95a7fa0c0a2f7537becde8ebd`, run `36554169338` | frozen for P0 |
| External Producer B | VERIFIED SOURCE | `Labs-R2-Advisory/adc-spec` ADC v0.1 Working Draft | upstream spec, not our implementation |
| Proposal draft | IMPLEMENTED | `ARIA_PROPOSAL_DRAFT.md` | competitive/team/admin editing |
| £900k budget model | IMPLEMENTED / UNVALIDATED COSTS | `ARIA_BUDGET_V1.md` | replace planning rates with actual eligible costs/quotes |
| Team plan | IMPLEMENTED / OPEN ROLES | `ARIA_TEAM_UK_PLAN.md` | applicant/host + named capability where possible |
| UK benefit/delivery | SPECIFIED / NOT YET COMMITTED | `ARIA_TEAM_UK_PLAN.md` | concrete partner/host/pilot evidence |
| Commercial hypothesis | IMPLEMENTED | `ARIA_COMMERCIAL_HYPOTHESIS.md` | validate against external users/market |
| Background / Foreground IP schedule | IMPLEMENTED / LEGAL TITLE OPEN | `ARIA_IP_SCHEDULE.md` | verify actual ownership/entity/contributor title |
| Competitive landscape | VERIFIED WORKING ANALYSIS | `ARIA_COMPETITIVE_LANDSCAPE.md` | keep differentiation current through submission |
| ARIA cost spreadsheet | BLOCKED ON REAL COSTS | `ARIA_BUDGET_V1.md` is planning input | actual cost model / applicant route |
| Final 10-page PDF | TODO | — | proposal content gates passed |
| Portal submission | TODO | — | final admin facts + PDF + cost sheet |

## Frozen P0 result

Primary run:
https://github.com/timelabs-npo/rheknel/actions/runs/36555320853

Bound implementation:
`570ee290cbb6fa64945abca4e24a3e939c3f13a5`

Direct observed evidence:
- two independent producer formats map to the same effect/authority semantics;
- `core_semantic_diff=NONE`;
- ADC adapter negative matrix: 11 tests PASS;
- direct untrusted write: OS denied; protected hash unchanged;
- ADC admitted effect: compiled Rheknel C gate PASS, exact post-state;
- Omnia admitted effect: same compiled C gate PASS, same exact post-state;
- wrong payload: rejected, pre-state preserved;
- measured adapter latency + core artifact sizes captured.

Canonical details:
`ARIA_P0_EVIDENCE.md`

### P0 stop rule

**NO MORE P0 FEATURES.**

Do not add:
- another producer;
- another effect;
- GUI;
- cloud service;
- agent framework;
- extra OS target;
- hardware;
- formal verification.

Those belong to funded Foreground R&D if ARIA funds them.

## Money state

Working request:
**£900,000 / 9 months**

This is a planning model, not a submitted cost claim.

Current bottom-up envelope:
- delivery labour: £489,600;
- specialist/independent work: £195,000;
- other direct costs: £95,000;
- indirect placeholder: £120,400;
- total: £900,000.

Critical cashflow fact:
ARIA normally reimburses eligible actual cost in arrears. Project structure must not require Mika to personally front the monthly burn.

Canonical budget:
`ARIA_BUDGET_V1.md`

## Next work order

### N1 — Competitive landscape — DONE FOR DRAFTING
Owner: 0NODE
Output: `ARIA_COMPETITIVE_LANDSCAPE.md`.
Result: CONDITIONAL GO survives; generic sandbox/warden novelty explicitly killed.

### N2 — Background / Foreground IP schedule — DONE FOR DRAFTING
Owner: 0NODE
Output: `ARIA_IP_SCHEDULE.md`.
Result: pre-award Rheknel/Omnia/P0 separated from planned Foreground; legal title remains an explicit admin/legal gate.

### N3 — Applicant / team / UK delivery closure
Owner: 0NODE first; human/admin input only for irreducible facts.
Output: credible applicant/host/cashflow path + named/OPEN role plan + UK-benefit commitments.
Acceptance: no fictional partner/entity/location.

### N4 — Real budget conversion
Owner: 0NODE + admin facts/quotes.
Output: ARIA cost-sheet-ready numbers.
Acceptance: every cost -> capability -> WP -> milestone -> evidence.

### N5 — Proposal tightening
Owner: 0NODE
Output: <=10-page content ready for layout, with P0 evidence and sources.
Acceptance: no unsupported technical/commercial/admin claims.

### N6 — Submit
Owner: Mika only where portal/signature/legal truth requires human action.
Output: portal confirmation / submission receipt.
Then: **STOP**.

## Anti-drift invariant

Before doing any task, answer:

> Which application field, evaluation criterion, proof gap, budget requirement, UK-benefit requirement, or submission gate does this close?

No answer => PARKED.

## Human workload policy

Mika is not a fallback compute node.

Do not ask Mika to:
- install IDE/toolchains before CI proves local execution is needed;
- invent architecture that can be resolved from repositories/specs;
- re-run evidence already available from source-bound CI;
- manually reconstruct project state from chat history.

Ask Mika only for:
- legally/administratively irreducible facts;
- explicit approval of material commitments;
- local/physical verification unavailable through external infrastructure;
- final signing/submission actions that genuinely require the human.

## Restart record — two existing Work tasks, 2026-09-29

This section is appended to preserve prior history. It does not promote historical claims or erase previous status.

Execution instructions: [WORK_RESTART_2026-09-29.md](WORK_RESTART_2026-09-29.md).
Instruction publication commit: `69fdee001f0b2a41087e94acfbe190a08a891c01`.

| Item | Observed/prepared state | Evidence / next gate |
|---|---|---|
| Pro activation | USER_ASSERTION | User reports activation; native plan and remaining allowance not read |
| Canonical ledger | READ | Ledger blob `38d99a1ee3ad54ab4a7badf1994685adfae8f237` at preparation baseline `1070fff2c26e9a053e992d47845cbfd90061acc8` |
| A: existing portal/application-draft task | RESTART_INSTRUCTIONS_PREPARED; NOT_REACTIVATED | Work orders A0–A4; existing native thread ID and files require inspection |
| B: existing audit-bundle/control-pane task | RESTART_INSTRUCTIONS_PREPARED; NOT_REACTIVATED | Work orders B0–B4; prior handoff identity recorded privately, not live-verified |
| Desktop execution connection | BLOCKED | Device listing showed no online devices; connection attempt returned no devices available |
| Saved Work files inspected in this preparation | NOT_DONE | No connected desktop/native thread access |
| Native resume / turn-start receipts | NONE | A published Markdown instruction is not a running session |
| New root Work sessions / spawned workers | ZERO / ZERO | No parallel replacement state created |
| Global/account instruction changes | NONE | Protocol is explicit/task-local only |

Position: restore the existing sessions, recover their files and apply bounded role-separated work; no new root threads or P0 feature expansion.

Wave dependency: B official-source/claim audit -> A application synthesis and saved portal draft -> B final manual-review package. A may inventory actual portal fields before B evidence is ready. Each task owns distinct files; consume cross-task outputs only by pinned manifest. At most two subagents per active coordinator, no recursive spawning; serialize root swarms unless an actual scheduler enforces a combined budget.

Important acceptance correction: the ledger is canonical for scope/decisions, not proof of its own claims. B must compare each consequential historical P0 assertion with actual source and tests before A reuses it. A green CI run cannot by itself establish complete contract semantics, universal non-bypassability or independent third-party reproduction. Retain historic results and append any bounded correction; do not rewrite old evidence or reopen P0 features.

Immediate external gate: connected native execution -> verified existing thread identity -> saved-state recovery checkpoint -> real turn-start acknowledgment. Then the task may be labeled RUNNING. Until then both remain NOT_REACTIVATED.
