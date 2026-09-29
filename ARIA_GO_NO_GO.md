# ARIA Scaling Trust Track 2.2 — GO / NO-GO Memo

Decision date: 2026-09-29
Status: CONDITIONAL GO
Repository baseline: timelabs-npo/rheknel PR #4 head 009545681da7ad4dfb7580f584642faf7f0a6a5d

## Decision

**GO only if the proposal is positioned as a small, portable contract-to-effect TCB that consumes external negotiation/security outputs and preserves their semantics at the effect boundary.**

**NO-GO if positioned as a generic agent sandbox, warden, policy firewall, receipt system, or “LLM cannot bypass permissions” runtime.**

That generic runtime-security category is already crowded.

## Why generic runtime-security is a NO-GO

Current competing or adjacent systems include:

- NVIDIA OpenShell / Sentry: secure runtime boundaries, out-of-agent enforcement, policy controls, kernel/hardware containment.
- Microsoft Agent Governance Toolkit: deterministic runtime governance for agents.
- Keel: separate warden process, policy enforcement, audit records, agent cannot directly execute governed actions.
- OPA and similar policy engines: mature deny-by-default policy evaluation and service deployment patterns.
- AgentContract / AgentAssert: explicit agent behavioral contracts and runtime enforcement.
- emerging receipt / proof-of-execution / bounded-capability protocols and IETF drafts.

Therefore, “put the model behind an external policy gate” is not a differentiated 2026 thesis.

## Where the remaining opportunity is

ARIA Track 2.2 explicitly calls for reusable components around:
- contracting languages;
- negotiation safety;
- security reasoners;
- protocol implementers;
- security auditing / reports from execution traces.

The gap we can credibly attack is the **semantic handoff between a negotiated/security contract and the real effect boundary**:

```text
negotiator / security reasoner / protocol designer
                    |
                    | external machine-readable contract
                    v
        deterministic contract compiler / TCB
                    |
                    | canonical typed authority
                    v
             bounded real effect
                    |
                    v
       post-state + verifiable receipt
```

The component must be useful even when the upstream producer changes.

## Differentiation target

Rheknel should compete on:

1. **Producer independence**
   - ingest contracts from multiple external policy/protocol producers;
   - no dependency on one model or agent framework.

2. **Small TCB**
   - C99 / allocation-bounded deterministic core;
   - auditable implementation surface;
   - suitable for deployment close to effectors, including constrained/edge settings.

3. **Semantic preservation**
   - explicit mapping from high-level negotiated contract fields to low-level effect capabilities;
   - no silent widening of authority during translation.

4. **Effect-boundary evidence**
   - before-state;
   - admitted contract hash;
   - exact capability/effect identity;
   - post-state;
   - replay/audit material.

5. **Measurable ARIA impact**
   - security: fewer unauthorized effects;
   - utility: low false-reject / preserved task completion;
   - efficiency: bounded latency, CPU, memory;
   - generality: multiple producers/effects without core changes;
   - adoption: documented external integration surface.

## Mandatory pre-proposal proof

The proof should use:

- existing Omnia/Rheknel path as one Background-IP producer;
- at least one truly external producer or policy/protocol format;
- the same deterministic core;
- one protected effect;
- one negative direct-bypass path;
- measurements.

A second producer that requires core changes invalidates the generality claim.

## Budget posture

ARIA Track 2 permits projects from £200k to £2m.

Current planning target: **£900k / 9 months**, subject to bottom-up costing.

Do not ask for £2m merely because it is available.
Do not ask for £200k if the credible delivery plan requires a team, security review, UK travel/events, benchmark work, and adoption engineering.

## Immediate money sequence

1. Freeze this positioning.
2. Choose the independent external producer / format.
3. Produce the smallest compatibility + effect-boundary proof.
4. Capture benchmark numbers.
5. Cost the 9-month work packages.
6. Write 10-page max proposal.
7. Submit before 31 Oct 2026 14:00 GMT.
8. Keep OpenSats separate and opportunistic.
9. Stop technical expansion after the evidence needed for proposal exists.

## Kill conditions

NO-GO / pivot if:
- differentiation collapses into “yet another agent sandbox”;
- generality requires editing core per producer;
- security gain cannot be measured;
- utility cost is unacceptable;
- the existing PR #4 work is doing nearly all of the claimed Foreground work;
- the proposal cannot explain why NVIDIA/OpenShell, Microsoft tooling, Keel, OPA, AgentContract, or receipt protocols do not already solve the same problem.
