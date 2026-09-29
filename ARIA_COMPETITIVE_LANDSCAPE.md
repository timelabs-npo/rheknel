# ARIA Scaling Trust Track 2.2 — Competitive Landscape v1

Status: SOURCE-BOUND WORKING ANALYSIS
Date: 2026-09-29
Purpose: test whether the Rheknel proposal is actually differentiated enough to deserve funding.

## 1. Decision

**Generic runtime governance / agent sandbox / external policy gate = NO-GO positioning.**

That category is already occupied by substantial open-source and commercial work.

**Current viable differentiation hypothesis:**

> Rheknel is a small producer-independent deterministic contract-to-effect TCB that preserves semantics from independently defined machine-readable authority/coordination contracts to bounded real effects, while binding admission to post-state evidence.

This remains a hypothesis to test during proposal review, not a monopoly claim.

## 2. NVIDIA OpenShell

Official source:
https://www.nvidia.com/en-us/ai/openshell/

Observed current claims:
- security enforcement outside the agent process;
- nothing permitted by default;
- sandboxed agents without direct network access;
- kernel/system-call mediation;
- a single secured channel to supervisor approval;
- policy verification/prover;
- auditable allow/deny;
- model/harness/agent agnostic positioning.

### Consequence for Rheknel

We CANNOT claim novelty from:
- “policy outside the model”;
- “agent cannot prompt away enforcement”;
- deny-by-default runtime isolation;
- OS/kernel-mediated sandboxing;
- generic agent-agnostic runtime controls.

### Remaining distinction to test

OpenShell's public positioning is primarily a secure runtime/sandbox and policy-control environment.

Rheknel must instead demonstrate value in the **semantic handoff from independently authored machine-readable contracts/protocols into exact bounded effect capabilities and post-state receipts**, without requiring adoption of a larger sandbox/control plane.

If that distinction is not materially useful to users, Rheknel loses.

## 3. Microsoft Agent Governance Toolkit / Agent Control Specification

Official/open-source sources:
- https://opensource.microsoft.com/blog/2026/04/02/introducing-the-agent-governance-toolkit-open-source-runtime-security-for-ai-agents/
- https://github.com/microsoft/agent-governance-toolkit/blob/main/docs/packages/agent-control-specification.md
- https://github.com/microsoft/agent-governance-toolkit/blob/main/policy-engine/README.md

Observed current properties:
- stateless deterministic fail-closed policy runtime;
- host enforcement points across agent lifecycle;
- Rust core with C ABI and multiple language bindings;
- framework-agnostic integration;
- policy manifests plus Rego/Cedar support;
- identity, isolation, audit, runtime rings and broader governance stack;
- sub-millisecond policy-enforcement claims.

### Consequence for Rheknel

We CANNOT claim novelty from:
- deterministic fail-closed agent policy evaluation;
- C ABI / multi-language policy runtime;
- generic pre-tool interception;
- “kernel for agents” rhetoric;
- runtime privilege separation;
- audit evidence by itself.

### Remaining distinction to test

ACS returns a policy verdict that a host enforces.

Rheknel's useful thesis must be stronger/different:

1. an external negotiated/security **contract is itself source evidence**;
2. strict adapters lower multiple independent contract languages into one canonical authority IR;
3. lowering must never silently widen authority;
4. the bounded effect and post-state are part of the proof object, not merely a host obligation after a verdict;
5. the TCB remains intentionally tiny and deployable close to effectors.

If Microsoft ACS can already express and verify this full contract-to-effect semantic preservation with comparable evidence and lower adoption cost, Rheknel's thesis must pivot.

## 4. Open Policy Agent (OPA)

Official sources:
- https://www.openpolicyagent.org/docs
- https://www.openpolicyagent.org/docs/integration
- https://www.openpolicyagent.org/docs/deploy
- https://www.openpolicyagent.org/docs/management-decision-logs

Observed properties:
- mature general-purpose policy engine;
- domain-agnostic structured inputs;
- declarative Rego policy;
- explicit separation of Policy Decision Point from Policy Enforcement Point;
- distributed/sidecar deployment;
- decision IDs and decision logs for audit.

### Consequence for Rheknel

We CANNOT claim novelty from:
- separating policy decision from enforcement;
- generic structured policy evaluation;
- sidecar/local policy engine;
- decision logging;
- language-independent policy APIs.

### Remaining distinction to test

Rheknel does not aim to become a general policy language.

The hypothesis is that there is value in a **small effect-oriented lowering/authority substrate** that consumes the result of policy/negotiation systems — including potentially OPA — and binds the allowed semantic object to the exact effect + post-state receipt.

OPA can be an upstream producer/decision system rather than a competitor if the boundary is real.

## 5. Keel / governed agent harnesses

Representative open-source source:
https://github.com/keel-harness/keel

Observed current positioning:
- agent operates behind a separate warden;
- agent cannot directly execute governed actions through the governed path;
- hash-pinned policy;
- warden owns policy evaluation / sandbox launch / authoritative audit;
- tamper-evident action records;
- explicit assumption that kernel/OS user are not compromised.

### Consequence for Rheknel

We CANNOT claim novelty from:
- separate warden process;
- “the model cannot talk its way through the boundary”;
- governed actions + tamper-evident audit;
- separation between model requests and authoritative execution.

### Remaining distinction to test

Keel is a governed agent harness/session architecture.

Rheknel must remain a **small reusable component beneath arbitrary harnesses**, centered on contract semantics and effect authority rather than session orchestration.

If Rheknel grows into an agent harness, it enters Keel's territory and loses the ARIA 2.2 “specific component” advantage.

## 6. Agent Delegation Contract (ADC)

External source:
https://github.com/Labs-R2-Advisory/adc-spec

Verified current source:
- README blob SHA: `1535c745eaf902f27a1416d592b4f7030d0451d1`;
- ADC identifies itself as an open machine-readable AI-agent authorization specification;
- v0.1 Working Draft;
- Apache 2.0;
- explicitly says it is a **specification, not an implementation** and that any runtime may evaluate ADCs;
- defines authority, constraints, delegation, escalation, binding and connectivity semantics.

### Consequence for Rheknel

ADC is NOT something Rheknel should replace.

It is evidence for the component thesis:
independent authority languages already exist, and they need runtime/effect-boundary implementations.

P0 successfully used ADC as an external producer and Omnia as another producer, mapping both to the same canonical effect/authority semantics with no Rheknel core semantic changes.

## 7. Competitive matrix

| Capability / claim | NVIDIA OpenShell | Microsoft AGT/ACS | OPA | Keel | ADC | Rheknel proposal |
|---|---|---|---|---|---|---|
| enforcement outside model | strong | host/runtime controls | PDP/PEP split | separate warden | spec only | yes, targeted |
| deterministic fail-closed policy | policy/runtime | strong | strong/general | governed policy | semantics only | existing baseline |
| OS/sandbox isolation | strong | available in broader toolkit | external PEP | yes | no | targeted effect boundary |
| generic policy language | policy system | manifests/Rego/Cedar | Rego | project policy | delegation contract | **no** |
| external contract language input | policy configs | manifests/policies | arbitrary structured input | policy | **yes** | **yes: multiple independent producers** |
| semantic lowering to canonical effect IR | not core public claim | not core public claim | not core function | not core focus | no runtime | **central hypothesis** |
| effect-specific before/post-state receipt | audit controls | audit/evidence | decision logs | action audit | audit-required semantics | **central hypothesis** |
| tiny C-oriented TCB close to effector | no | Rust multi-runtime | Go/general engine | harness/warden | n/a | **target** |
| producer-independent contract compatibility metric | not observed as core metric | not observed as core metric | arbitrary inputs but no effect-IR metric | not focus | n/a | **explicit metric** |

“Not observed as core metric” means only that the reviewed public material did not establish it as the central claim; it is NOT a claim that the system cannot do it.

## 8. Proposal differentiation sentence

Use:

> Existing agent-security runtimes already provide sandboxing, deterministic policy evaluation and external enforcement. Rheknel targets the narrower semantic boundary those systems can consume or complement: lowering independently produced coordination/authorization contracts into a small canonical effect authority, proving that the lowering does not widen permission, and binding the admitted effect to independently checkable post-state evidence.

Do NOT use:

> Rheknel is the first deterministic policy runtime / first external agent gate / first secure sandbox / first auditable agent runtime.

Those statements are not defensible.

## 9. Competitive proof required during funded project

Rheknel should be evaluated in at least two modes:

1. **standalone effect-boundary mode** — contract producer -> Rheknel -> effect;
2. **composed mode** — existing policy/runtime (e.g. OPA/agent governance system) -> Rheknel effect boundary.

Success criterion:
Rheknel adds a measurable property — semantic preservation + effect/post-state binding — without requiring replacement of the upstream governance system.

## 10. Kill conditions

The proposal should pivot or die if reviewers/users establish that:
- OpenShell/AGT/another incumbent already provides producer-independent contract lowering + equivalent post-state effect binding with lower integration cost;
- the canonical IR is just another unnecessary policy language;
- adapters become bespoke per-customer glue with no reusable semantics;
- post-state receipts add little beyond existing audit records;
- the small-TCB advantage disappears after realistic effect support is added.

## 11. Current conclusion

**CONDITIONAL GO remains justified after competitive review.**

Why:
- generic runtime-governance novelty is dead and explicitly removed from the pitch;
- P0 now demonstrates the narrower two-producer semantic-lowering + effect-boundary thesis;
- the remaining differentiation is falsifiable and can be compared directly against incumbent systems.

This is not proof of market demand or award-worthiness.
It is sufficient to continue the ARIA application rather than continue P0 engineering.
