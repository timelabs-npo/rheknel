# ARIA Scaling Trust — Background / Foreground IP Schedule v1

Status: WORKING SCHEDULE — LEGAL REVIEW REQUIRED BEFORE SUBMISSION
Date: 2026-09-29

Purpose:
prevent two opposite errors:
1. presenting pre-existing work as ARIA-funded novelty;
2. accidentally treating third-party/open-source material as applicant-owned Background IP.

## 1. Background IP — Timelabs pre-award work

Everything listed here exists before any ARIA award and should be disclosed as Background IP / pre-existing work where relevant.

### Rheknel baseline and Omnia integration

Repository:
`timelabs-npo/rheknel`

Relevant pre-award implementation:
- main historical deterministic dispatcher;
- PR #4 — Omnia ABI 1.0 fail-closed integration;
- PR #4 evidence tip: `009545681da7ad4dfb7580f584642faf7f0a6a5d`.

Observed license at that exact revision:
- `LICENSE` blob `de00ae746c6aebb7176dea00ff1f252854ca546f`;
- **MIT License**;
- copyright notice: Timelabs NPO, 2026.

Existing capabilities include:
- fixed-capacity C core;
- typed dispatch;
- Omnia ABI 1.0 consumer;
- canonical encoding/integrity validation;
- freshness/provenance/evidence handling;
- fail-closed integration path;
- existing adversarial tests and CI evidence.

These are NOT ARIA Foreground novelty.

### P0 pre-proposal validation prototype

Repository:
`timelabs-npo/rheknel`

Sealed P0 implementation:
`570ee290cbb6fa64945abca4e24a3e939c3f13a5`

P0 evidence:
`ARIA_P0_EVIDENCE.md`

Pre-award P0 work includes:
- strict ADC -> canonical IR adapter prototype;
- Omnia -> canonical IR adapter prototype;
- P0 canonical effect shape;
- one `replace_file` effect harness;
- P0-specific compiled C dispatch gate;
- Linux permission-separation CI experiment;
- P0 receipts;
- proposal benchmark harness.

These artifacts are also pre-award work.

ARIA Foreground must therefore **generalise, productionise, evaluate and externally integrate beyond P0** rather than claiming to fund P0 retroactively.

### Omnia Producer A

Repository:
`timelabs-npo/omnia-playbook`

P0 producer revision:
`3f41e64cc9348dc95a7fa0c0a2f7537becde8ebd`

Observed license:
- `LICENSE` blob `90f9790126ce93579070e75812337e790e8be4f4`;
- **BSD 3-Clause License**;
- copyright notice in current file: Timelabs non-profit corp, 2026.

Pre-existing Omnia compiler/codec/schema/evidence work remains Background IP.

## 2. Third-party material — NOT applicant-owned Background IP

### Agent Delegation Contract (ADC)

Repository:
`Labs-R2-Advisory/adc-spec`

Public v0.1 Working Draft used as P0 Producer B.

Observed license:
- `LICENSE` blob `261eeb9e9f8b2b4b0d119366dda99c6fd7d35c64`;
- **Apache License 2.0**.

ADC is third-party open-source specification material.

The proposal must say:
- Rheknel interoperates with / consumes ADC semantics in the P0 prototype;
- Timelabs does NOT own ADC;
- ADC is NOT ARIA Foreground;
- any included/derived material must respect Apache-2.0 attribution/license obligations.

The same rule applies to future third-party producers, policy engines, agent frameworks and Arena components.

## 3. Proposed ARIA Foreground

Subject to the final award agreement, the funded work should be defined as new post-award deliverables such as:

### FG1 — Canonical contract-to-effect IR v1

New stable specification beyond the P0 prototype:
- explicit authority narrowing rules;
- versioning/compatibility semantics;
- reversible/irreversible effect semantics;
- no-silent-widening conformance rules;
- producer-independent contract.

### FG2 — Adapter / conformance interface

Reusable producer adapter SDK/API:
- strict lowering interface;
- compatibility test suite;
- producer conformance fixtures;
- error semantics;
- measured integration contract.

P0 ADC/Omnia scripts are Background prototypes.
The production/reusable adapter layer is Foreground.

### FG3 — Production authority boundary

New runtime work beyond P0:
- production process/IPC model;
- explicit capability binding;
- bounded executor interface;
- safe lifecycle/failure semantics;
- platform-specific isolation where scoped;
- production-quality integration with the deterministic core.

The P0 Python effect harness is NOT the Foreground final runtime.

### FG4 — Effect receipt / replay specification

Production receipt schema and verifier:
- admitted contract identity;
- canonical IR identity;
- effect identity;
- pre/post-state evidence;
- failure/partial-effect semantics;
- replay/audit verification.

P0 receipts are Background prototype evidence.

### FG5 — Adversarial benchmark

New funded benchmark/evaluation corpus:
- multiple producer formats;
- realistic agent stacks;
- authority-widening attempts;
- malformed/stale/tampered cases;
- bypass testing;
- Utility/Security/Efficiency metrics;
- Arena-compatible evaluation.

### FG6 — Arena / ecosystem integration

New adapters, packaging and interfaces required to make the component consumable by external Track 2/Arena systems.

### FG7 — Documentation / release / adoption material

New funded:
- integration documentation;
- threat model;
- conformance guides;
- reproducibility package;
- release packaging;
- external pilot/adoption artefacts.

## 4. Licensing boundary

ARIA's Track 2 licensing requirements must be applied to funded Foreground as required by the final solicitation/award terms.

Current planning assumption:
**Foreground software will be released under the required permissive Track 2 licensing terms (MIT + Apache-2.0 where the solicitation requires dual licensing).**

Do NOT silently relicense third-party ADC material.
Do NOT assume BSD/MIT Background ownership is sufficient without verifying copyright/title.

## 5. Ownership facts requiring legal/admin verification

Before submission/award, verify:

1. who legally owns copyright in the Rheknel commits;
2. who legally owns copyright in Omnia-playbook commits;
3. whether “Timelabs NPO” / “timelabs non-profit corp” copyright notices correspond to an existing legal entity or are project labels;
4. contributor ownership/assignments for any non-Mika contributions;
5. whether any employer/institution agreement creates claims over relevant code;
6. third-party dependency/license notices;
7. whether the planned applicant has the legal right to grant/use the required Background IP rights.

Until verified, these are OPEN LEGAL FACTS, not narrative assumptions.

## 6. Novelty/accounting rule

Every proposal work package must label its deliverables:

```text
BACKGROUND INPUT
    -> NEW FUNDED TRANSFORMATION / R&D
    -> FOREGROUND OUTPUT
```

Example:

```text
P0 ADC/Omnia prototype adapters (Background)
    -> producer-independent adapter architecture + conformance R&D
    -> stable reusable adapter SDK + >=3 integrations (Foreground)
```

If the middle transformation cannot be stated clearly, the deliverable is probably pre-existing work and must not be billed as Foreground novelty.

## 7. Current IP gate status

- Rheknel technical baseline identified: YES
- P0 pre-award prototype identified: YES
- Omnia pre-award producer identified: YES
- ADC marked third-party: YES
- observed repository licenses captured: YES
- legal ownership/title verified: **NO — ADMIN/LEGAL BLOCKER**
- final award-license interpretation verified: **NO — CONTRACT-STAGE CHECK**

This schedule is sufficient for proposal drafting.
It is not legal advice or final IP diligence.
