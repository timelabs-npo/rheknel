# ARIA Scaling Trust Track 2.2 — Proposal Draft v0

Status: WORKING DRAFT
Current rolling cut-off: 31 October 2026, 14:00 GMT
Track: 2.2 Components
Working title: **Rheknel — Deterministic Contract-to-Effect Runtime for Untrusted Agents**

> This draft follows ARIA's indicative proposal outline. It is not yet the submission PDF.
> Technical claims must be replaced by source-bound evidence before submission.

## Section 0 — Summary (<=500 words)

AI agents can increasingly negotiate policies, select protocols and invoke tools, but the final transition from a machine-readable agreement to a real digital or physical effect remains a trust bottleneck. If the same probabilistic agent that interprets an agreement also owns the capability to execute the effect, persuasive or compromised behaviour can silently widen authority at exactly the point where the agreement is meant to bind it.

We propose **Rheknel**, a small deterministic contract-to-effect component for untrusted agents. Rheknel sits after requirement capture, negotiation and security reasoning. It consumes machine-readable contracts produced by independent upstream systems, translates them into a canonical typed authority representation, admits or rejects a bounded capability deterministically, executes only through a constrained effect interface, and emits a machine-verifiable receipt tied to real post-state evidence.

The project builds on pre-existing Background IP: an allocation-free C99 Rheknel/Omnia admission path with exact-version ABI validation, provenance/freshness handling, fail-closed verdicts and multi-platform CI evidence. ARIA funding would not rebuild that work. The Foreground programme would make the boundary producer-independent, bind contract semantics to effect capabilities, build reusable adapters and receipt formats, and evaluate the component under adversarial multi-agent conditions.

Our first pre-proposal proof uses two independently defined contract sources: the existing Omnia ABI and the external Agent Delegation Contract (ADC) v0.1 Working Draft. Both are required to map to identical effect semantics without modifying the Rheknel C core. A Linux authority-separation test gives the untrusted proposer no OS permission to modify the protected resource, while a separate authority identity may perform one hash-bound replace-file effect. The current evidence package is being frozen separately in `ARIA_P0_EVIDENCE.md`.

The funded project would generalise this into an open-source Track 2.2 component with: producer adapters; explicit capability binding; bounded effect contracts; execution receipts; replay/audit tooling; an adversarial benchmark harness; and an Arena integration surface. Evaluation will measure Utility/Security impact, generality across producers/tasks, validation latency and resource cost, false rejection, unauthorised-effect rate, and external integration effort.

The goal is not another agent sandbox or another model-side safety policy. The goal is a small, inspectable semantic boundary that preserves an agreement all the way to the effect it authorises.

## Section 1 — Programme & Technical

### 1.1 Track fit

**Track 2.2 — Components.**

Rheknel is a specific reusable tool intended to be consumed by many agent stacks rather than a complete Arena participant.

Direct programme mapping:

| ARIA component area | Rheknel contribution |
|---|---|
| Contracting languages | consumes externally defined machine-readable agreements without owning the language |
| Negotiation safety | prevents the executor from silently widening negotiated authority |
| Security reasoner output | turns final protocol/authority output into deterministic bounded capabilities |
| Protocol implementation | provides a small typed execution substrate for approved effects |
| Security auditing/report | emits receipts tied to contract identity and real post-state |

### 1.2 Technical hypothesis

**H1 — Producer independence.** A single deterministic core can enforce semantically equivalent authority from independently developed contract producers without producer-specific changes to the core.

**H2 — Authority separation.** An untrusted agent can retain proposal capability while lacking direct OS capability to create the protected effect.

**H3 — Semantic preservation.** Translation from external contract to effect capability can fail closed on unknown, stale, malformed or ambiguous semantics rather than inventing permission.

**H4 — Low overhead.** The deterministic boundary can add bounded latency, memory and integration cost relative to the value of the protected operation.

### 1.3 Architecture

```text
 requirements / negotiators / security reasoners
                 |
                 | independent machine-readable contracts
                 v
        producer-specific strict adapters
                 |
                 v
         canonical authority IR
                 |
                 v
      +--------------------------+
      | Rheknel deterministic TCB|
      | validate / admit / reject|
      +--------------------------+
                 |
          bounded capability
                 |
                 v
           effect executor
                 |
                 v
          real post-state
                 |
                 v
       verifiable execution receipt
```

Probabilistic agents are outside the authority TCB.

### 1.4 Background IP

Pre-existing work includes:
- Rheknel fixed-capacity C core;
- Omnia ABI 1.0 consumer;
- exact-version and canonical-encoding checks;
- provenance/evidence and freshness semantics;
- fail-closed typed dispatch on the integration branch;
- adversarial fixture suite;
- recorded macOS, Linux, Windows and OpenBSD build/runtime evidence.

This work is Background IP and will not be represented as ARIA-funded novelty.

### 1.5 Foreground R&D

WP1 — Canonical contract/effect semantics
- freeze the canonical authority IR;
- define explicit narrowing rules;
- define reversible/irreversible effect semantics;
- specify receipt invariants.

WP2 — Producer-independent ingress
- support multiple independent contracting/security-reasoner formats;
- build strict adapters and conformance tests;
- measure integration effort and core-change rate.

WP3 — Authority/effect boundary
- isolate the deterministic authority plane from agent runtimes;
- bind selected OS/process capabilities;
- build bounded executor interfaces;
- prove direct bypass denial for supported effects.

WP4 — Receipts and audit
- bind source contract hash/version, admitted capability, before-state and post-state;
- support deterministic replay and external verification.

WP5 — Adversarial evaluation
- malformed/stale/contradictory/tampered contracts;
- authority-widening adapter attempts;
- direct bypass attempts;
- Utility/Security and efficiency measurements.

WP6 — Arena and ecosystem integration
- package a minimal component interface;
- expose benchmark-compatible harnesses;
- integrate with external agent stacks without model/provider dependency.

### 1.6 Current pre-proposal evidence

P0 acceptance requires:
- two independent producers reach the same canonical effect semantics;
- the external producer requires no Rheknel core semantic change;
- valid contracts create exactly the intended effect;
- invalid contracts create zero unauthorised effects;
- direct proposer bypass is denied by the OS;
- receipts match real post-state;
- benchmark measurements are captured.

**Do not mark P0 complete in this document until `ARIA_P0_EVIDENCE.md` is sealed.**

### 1.7 Differentiation

Rheknel is not positioned as a generic agent sandbox, warden, policy proxy or generic receipt system.

The differentiated R&D question is whether a **small producer-independent TCB can preserve the semantics of negotiated/security contracts at the effect boundary**, across independently developed upstream languages and agent stacks, while keeping the authority surface inspectable and cheap.

The proposal must compare this claim directly against current agent sandboxes/wardens, generic policy engines, capability systems and agent-contract runtimes before submission.

### 1.8 Metrics

Security:
- unauthorised-effect rate;
- bypass success rate;
- malformed/stale/tampered escape rate;
- provenance/receipt mismatch rate.

Utility:
- valid task completion rate;
- false rejection rate;
- contract compatibility rate.

Generality:
- independent producers integrated without core semantic changes;
- supported effect classes;
- external agent stacks integrated.

Efficiency:
- p50/p95 validation latency;
- CPU time;
- peak memory;
- binary size;
- adapter/integration LOC;
- cost per protected operation where relevant.

Adoption:
- external integrations;
- Arena usage;
- downstream contributors;
- pilot organisations.

### 1.9 Technical risks / unknowns

1. Contract languages may not expose enough semantics for safe lossless lowering.
2. A canonical IR may accidentally become a lowest-common-denominator language.
3. OS-level authority separation may be expensive or platform-specific.
4. Strong fail-closed behaviour may reduce Utility through false rejection.
5. Receipts may prove post-state without proving broader causal correctness.
6. Current P0 uses one deliberately small file effect and must not be over-generalised.
7. A competing runtime may already occupy the useful semantic boundary; differentiation must be continuously re-tested.

### 1.10 Milestones / stage gates

**M1 — Contract boundary frozen.**
PASS: canonical IR + narrowing rules + threat model reviewed against >=2 independent producer formats.
KILL: semantics require permissive inference.

**M2 — Reusable ingress demonstrated.**
PASS: >=3 independent producer adapters with zero core semantic changes.
KILL: producer-specific logic leaks into core.

**M3 — Effect authority demonstrated.**
PASS: >=2 effect classes with direct bypass tests and post-state receipts.
KILL: agent can reach protected effect outside the authority boundary.

**M4 — Adversarial benchmark.**
PASS: quantified Security/Utility/Efficiency baseline and failure taxonomy.
KILL/REDESIGN: security gain is negligible or utility penalty is unacceptable.

**M5 — Arena/external integration.**
PASS: external stacks use component through documented interface with bounded integration effort.

**M6 — Release/adoption package.**
PASS: dual MIT + Apache-2.0 Foreground release, benchmark suite, docs, external adoption evidence.

## Section 2 — Team

### Lead

**Mika IO / Timelabs NPO** — project originator and existing Rheknel/Omnia implementation owner.

Planned lead commitment: **[FREEZE BEFORE SUBMISSION: target 80% FTE]**.

Relevant evidence:
- authored/maintains current Rheknel and Omnia work;
- existing low-level C / systems and deterministic-interface work;
- existing external technical review/public contribution history.

### Team gaps to fund rather than pretend away

- security/formal methods reviewer;
- agent-framework / Arena integration engineer;
- independent adversarial evaluator;
- UK programme/adoption collaborator;
- project administration/accounting capacity for ARIA reimbursement and reporting.

Final proposal will state named people where available and explicitly identify planned hires/subcontracts otherwise.

### Management

Small work packages with explicit PASS/KILL gates.
Quarterly programme milestones mapped to ARIA Arena metrics.
Technical claims accepted only with source-bound test evidence.
Negative results retained and reported rather than narratively converted into success.

## Section 3 — Administrative Response

### Funding request

Working envelope: **£900,000 / 9 months**.

This is not final. It must be replaced by ARIA's cost spreadsheet and bottom-up work-package costing.

### Background IP

Yes.
Background IP includes existing Rheknel/Omnia source, ABI work, tests and evidence produced before the ARIA-funded project. Timelabs must confirm ownership/licensing status before submission.

Foreground deliverables funded by ARIA will follow the required permissive open-source licensing terms.

### Other funding

No ARIA cost may be double-funded.
OpenSats and other funding applications, if pursued, will be scoped to distinct deliverables and disclosed where the portal requires.

### Freedom to operate

**[ADMIN PASS REQUIRED]**
State current applicant/legal structure, banking/payment feasibility, sanctions/export-control considerations, and any restrictions accurately at submission time.

### UK benefit

Working plan:
- establish a material UK delivery footprint during the project;
- budget for UK build weeks and programme participation;
- recruit/subcontract relevant UK expertise;
- make the reusable tooling available to UK Arena participants and companies;
- pursue UK-based pilot/adoption relationships.

The final response must be concrete enough to satisfy ARIA's non-UK benefit criterion and must not promise an entity/location structure that has not been secured.

### Commercial hypothesis

Open-source core; value capture through:
- integration/support for high-assurance agent deployments;
- enterprise/edge deployment engineering;
- conformance/evaluation services;
- future funded Track 2.3 adoption/pilots;
- potential new-company formation only if evidence of demand emerges.

A separate portal commercial-hypothesis response will be prepared before submission.

---

## Submission gate

Do not submit until:
- P0 evidence is sealed;
- current competitive landscape comparison is sourced;
- budget spreadsheet is bottom-up;
- team/FTE and gaps are explicit;
- Background/Foreground IP is checked;
- UK benefit plan is concrete;
- commercial hypothesis is complete;
- PDF <=10 pages, Arial >=11 pt, >=0.5 inch margins.
