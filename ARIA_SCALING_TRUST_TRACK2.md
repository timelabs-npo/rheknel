# ARIA Scaling Trust Track 2.2 — Canonical Proposal Frame

Status: ACTIVE
Repository: timelabs-npo/rheknel
Proposal branch: proposal/aria-scaling-trust-2-2
Technical baseline: PR #4 head 009545681da7ad4dfb7580f584642faf7f0a6a5d
Funding target: ARIA Scaling Trust — Track 2.2 Components
Current batch cutoff: 31 October 2026, 14:00 GMT

## 0. Parent objective

Convert existing technical work into:
1. a finished, externally legible technical artifact;
2. a fundable open-source programme;
3. external cash/resources;
4. increased relocation and career optionality.

Rheknel is a means, not the objective.
No technical task is valid unless it closes a concrete proposal field, evaluation criterion, proof gap, or adoption requirement.

## 1. Funding fit

ARIA Track 2 funds open-source tooling for secure multi-agent coordination.
Track 2.2 is for reusable components that many agents can use.

Relevant programme language includes:
- requirement capture;
- negotiation;
- security reasoning;
- protocol implementation/generation;
- verifiable reporting and auditing.

Projects are expected to be reusable, measurable, efficient, and capable of adoption beyond one agent stack.

## 2. Proposal thesis

### Working title
**Rheknel — Deterministic Contract-to-Effect Runtime for Untrusted Agents**

### One-sentence thesis
Rheknel is a small deterministic authority component that converts already-agreed machine-readable security/coordination contracts into bounded, auditable effects without giving probabilistic agents direct authority over those effects.

### Architecture
```text
untrusted agents / negotiators / security reasoners
                    |
                    | machine-readable contract / protocol
                    v
        +---------------------------+
        | Rheknel deterministic TCB |
        | validate / admit / reject |
        | bind capability / receipt |
        +---------------------------+
                    |
                    | admitted typed effect only
                    v
             external executor
                    |
                    v
             real post-state
                    |
                    v
            evidence receipt
```

The agent is not trusted to self-certify, self-enforce, or self-report success.

## 2.5. Competitive boundary — what NOT to pitch

The generic category "agent runs behind an external policy gate / sandbox / warden and emits receipts" is already crowded in 2026.

Adjacent systems include NVIDIA OpenShell/Sentry, Microsoft Agent Governance Toolkit, Keel, OPA-style policy engines, AgentContract/AgentAssert, proof-of-execution work, action-receipt protocols and bounded-capability proposals.

Therefore the proposal must NOT claim novelty from:
- running policy outside the model process;
- deny-by-default permissions by itself;
- generic sandboxing;
- generic audit receipts;
- "the model cannot talk its way around policy".

The differentiated claim must instead be narrower:

> a small, portable deterministic TCB that preserves the semantics of externally produced negotiation/security contracts all the way to the real effect boundary, with producer-independent typed adapters, explicit capability binding and independently verifiable post-state evidence.

This proposal is a NO-GO if that differentiation cannot be demonstrated against the current landscape.

## 3. Existing Background IP — do not rebuild

The open PR #4 already provides a substantial deterministic admission substrate:

- allocation-free / zero-copy C99 Omnia ABI consumer;
- exact-version typed input;
- canonical ULEB128, UTF-8 and structural validation;
- frame SHA-256;
- provenance/evidence IDs;
- deterministic freshness evaluation;
- explicit OK / REJECT / ESCALATE / ERROR mapping;
- fail-closed behaviour for malformed, stale, unsupported, contradictory and unknown inputs;
- prevention of direct `rhea_emit()` action bypass in that branch;
- portable C99 build path;
- recorded macOS, Linux, Windows and OpenBSD CI/runtime evidence.

This material is Background IP / pre-existing work.
The funded proposal must not pretend these features are new.

## 4. Funded Foreground work

The proposal is NOT "build a firewall for agents".

The funded work should create a reusable contract-to-effect component around the existing deterministic core:

1. **Generic contract ingress**
   - stable typed schema for external protocol/security-reasoner outputs;
   - adapters for at least two independent producers;
   - canonicalisation and version negotiation.

2. **Authority separation**
   - deterministic authority process isolated from probabilistic agent runtimes;
   - explicit capability binding;
   - no direct effect authority for untrusted agents.

3. **Effect execution contract**
   - bounded executor interface;
   - before/after state evidence;
   - reversible/irreversible effect classification;
   - deterministic failure semantics.

4. **Verifiable receipts**
   - machine-readable reason for admission/rejection;
   - effect identity;
   - input contract hash;
   - source/version metadata;
   - before/post-state evidence;
   - replayable audit record.

5. **Evaluation harness**
   - at least two independent agent/protocol producers;
   - valid, malformed, stale, contradictory and adversarial contracts;
   - direct-bypass attempts;
   - measurable utility/security trade-off.

6. **Arena integration surface**
   - minimal adapter for Scaling Trust Arena-style task execution;
   - no dependence on one proprietary model/provider.

## 5. Falsifiable technical claim

The component succeeds only if all of the following are true:

1. two independent producers can generate compatible contracts without changing Rheknel core;
2. valid contracts produce intended bounded effects;
3. invalid/stale/unsupported contracts produce zero unauthorized effects;
4. untrusted agents cannot bypass the authority boundary to create the same protected effect directly;
5. independent post-state evidence confirms what happened;
6. the component adds bounded latency/CPU/memory overhead.

If the same core cannot be reused across independent producers, the "general component" claim fails.
If the agent can bypass the authority boundary, the security claim fails.

## 6. Evaluation metrics

### Security
- unauthorized-effect rate;
- malformed/stale/unsupported contract escape rate;
- bypass success rate;
- tamper-detection rate;
- provenance loss rate.

### Utility
- valid-task completion rate;
- false-rejection rate;
- end-to-end task success;
- protocol compatibility across producers.

### Efficiency
- p50/p95 admission latency;
- CPU time per decision;
- peak memory;
- binary size;
- integration LOC / adapter complexity.

### Generality
- number of independent producers integrated without core modification;
- number of effect classes supported through the same contract;
- zero vendor-specific model dependency in core.

## 7. Minimal technical proof before proposal submission

Do NOT build a platform.

One proof only:

```text
Producer A ----\
               > contract -> Rheknel -> protected file effect -> receipt
Producer B ----/

Negative cases:
- malformed contract      => zero effect
- stale contract          => zero effect
- unsupported version     => zero effect
- tampered contract       => zero effect
- direct proposer bypass  => OS denied
```

This is sufficient to support the proposal if the measurements are clean.

## 8. Proposed project shape

Working planning assumption:
- duration: 9 months;
- target ask: £900k;
- open-source deliverables;
- small core team plus paid specialist review/validation;
- Background IP retained as pre-existing work;
- ARIA-funded Foreground released under required open-source terms.

The £900k figure is a planning target, not yet a submitted budget.
It should be adjusted only after the work packages, FTEs, subcontracting, hardware/Arena costs and compliance overhead are costed.

## 9. Work packages

### WP1 — Contract model + threat model
Freeze typed contract, authority model, effect semantics and evaluation plan.

### WP2 — Reusable adapters
Integrate two independent protocol/security-reasoner producers.

### WP3 — Authority/effect boundary
Build deterministic broker/executor separation and capability binding.

### WP4 — Receipts + audit
Produce machine-verifiable execution receipts and replay tooling.

### WP5 — Adversarial benchmark
Measure valid/invalid/adversarial cases and bypass attempts.

### WP6 — Arena/adoption integration
Package component for external use, document integration API, and demonstrate Arena-compatible deployment.

## 10. Kill conditions

Stop / redesign if any of the following is true:

- the core only works with one producer;
- the agent can directly create the protected effect;
- the proposal requires pretending PR #4 work is new;
- the component cannot produce measurable security benefit;
- utility loss is so high that the component is unusable;
- integration requires rebuilding an entire agent stack;
- scope expands without closing an ARIA evaluation criterion.

## 11. Immediate next actions

1. Produce one-page ARIA fit memo against official Track 2.2 criteria.
2. Freeze Background IP / Foreground IP split.
3. Specify Producer A and Producer B for the two-source proof.
4. Build only the missing two-producer contract-to-effect proof.
5. Capture measurements.
6. Write budget and milestones.
7. Draft proposal.
8. Submit before 31 October 2026, 14:00 GMT.
9. STOP.

## 12. Parallel money lanes

### OpenSats
Keep separate.
Only pursue with a Bitcoin/Nostr/FOSS-specific proof-of-work.
Do not contaminate the ARIA proposal with unrelated Nostr scope.

### Cohere / FreeBSD
Treat as reputation and collaborator pipelines.
Continue only on concrete external events/reviewer loops.
Do not let them pre-empt the ARIA submission.

---

## Non-negotiable anti-drift rule

Every new task must answer:

> Which ARIA proposal field, evaluation criterion, proof gap, adoption requirement, or submission requirement does this close?

If it cannot answer that question, PARK IT.
