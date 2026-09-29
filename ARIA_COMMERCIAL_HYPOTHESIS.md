# ARIA Scaling Trust — Commercial Hypothesis v1

Status: WORKING DRAFT
Date: 2026-09-29
Project: Rheknel — Deterministic Contract-to-Effect Runtime for Untrusted Agents

## 1. Hypothesis

The commercial value is not the act of selling a proprietary agent firewall.

The hypothesis is:

> As organisations delegate consequential actions to heterogeneous AI agents, they will pay for integration, assurance and operational support around a small vendor-neutral contract-to-effect boundary that lets them keep model choice flexible while making effect authority deterministic and auditable.

The open-source core is the adoption mechanism.
Revenue, if demand exists, comes from difficult integration and assurance work around real systems.

## 2. Buyer/problem hypotheses

### Buyer A — enterprises deploying tool-using agents

Problem:
agent policies exist at prompt/framework level but must ultimately map to IAM, APIs, files, databases, workflows or other effects.

Potential paid need:
- integration of existing policy/contract sources;
- high-assurance effect adapters;
- deployment architecture;
- audit/incident evidence;
- long-term support.

### Buyer B — agent-platform / framework vendors

Problem:
they do not want every framework to invent a bespoke low-level policy/effect layer.

Potential paid need:
- maintained adapters/conformance;
- enterprise deployment support;
- jointly supported integrations;
- benchmark/evaluation engineering.

### Buyer C — regulated / high-assurance operators

Problem:
they need explicit authority boundaries, reproducible evidence and deterministic failure semantics around selected effects.

Potential paid need:
- threat modelling;
- deployment engineering;
- independent conformance/evaluation;
- platform-specific capability isolation.

### Buyer D — research/evaluation infrastructure

Problem:
multi-agent security research needs reproducible effect-boundary experiments rather than only model-output evaluation.

Potential paid need:
- benchmark infrastructure;
- custom effect environments;
- evaluation campaigns;
- Arena/pilot engineering.

These are hypotheses, not existing customers.

## 3. Open-source / value-capture boundary

### Open-source Foreground

Expected ARIA-funded reusable software:
- canonical authority IR/specification;
- deterministic core and public APIs required by the project;
- producer adapter SDK/examples;
- reference effectors;
- receipts/replay tooling;
- conformance and adversarial benchmark suite;
- Arena integration surface;
- documentation.

Licensing must follow ARIA's required permissive terms for Track 2 software.

### Potential paid layer after/alongside grant

Do not create artificial proprietary lock-in.

Potential services:
- integration with proprietary enterprise systems;
- supported long-term release branches;
- deployment/hardening;
- independent conformance/evaluation engagements;
- custom high-assurance effectors;
- training / architecture review;
- managed support/SLA if market demand appears.

Future hosted services or proprietary modules are optional hypotheses and should not be required for the open-source core to work.

## 4. Why someone pays if the code is free

Because the expensive part in high-assurance agent deployment is not downloading a C library.

It is:
- mapping organisation-specific authority to exact effects;
- proving the mapping does not widen permissions;
- integrating OS/cloud/enterprise capabilities;
- adversarial testing;
- maintaining evidence across upgrades;
- operating the system under audit/security requirements;
- responding when real infrastructure changes.

The business model therefore resembles security/infrastructure open source more than a per-token AI API.

## 5. Adoption funnel

```text
ARIA open-source proof
        ↓
Arena + public conformance
        ↓
external framework integrations
        ↓
pilot deployments
        ↓
paid integration / assurance / support
        ↓
only if demand is real:
repeatable product/company structure
```

Do not create a company because the grant asks for a commercial hypothesis.
Create/scale a commercial vehicle only when external demand supports it.

## 6. Commercial validation during the 9-month project

Commercial hypothesis is considered stronger if the project obtains:

- >=3 external technical integration conversations;
- >=2 independent framework/contract integrations;
- >=1 UK-based pilot/adoption candidate;
- explicit records of integration pain/time;
- at least one written indication that support/integration/evaluation has budget value;
- zero requirement that users replace their existing agent framework.

These are targets, not current claims.

## 7. Pricing hypotheses — for validation, not proposal promises

Possible post-grant service shapes:

- bounded architecture/security assessment;
- fixed-scope integration package;
- independent conformance/evaluation engagement;
- annual enterprise support;
- custom effect-adapter engineering.

No pricing is frozen yet.
The project should learn what buyers value before inventing a SaaS tariff.

## 8. Competitive boundary

Rheknel should not attempt to monetise generic features already available from:
- agent sandboxes/wardens;
- OPA-style policy engines;
- framework-specific permission systems;
- generic audit logging.

The value proposition must remain:
**producer-independent semantic preservation from machine-readable authority contract to bounded real effect, with a small inspectable TCB and source-bound receipts.**

If buyers see no material value beyond a generic sandbox/policy engine, the commercial hypothesis FAILS and should be reported as such.

## 9. Commercial kill conditions

Do not spin this into a company/product story if:
- external integrations require replacing the buyer's agent stack;
- adapters are bespoke consulting with no reusable substrate;
- the deterministic boundary does not reduce audit/security/integration burden;
- buyers value only free benchmark code and show no willingness to pay for surrounding work;
- incumbents already provide equivalent producer-independent semantics at lower integration cost.

## 10. Current commercial status

- open-source technical Background IP exists;
- pre-proposal P0 technical proof = TEST_PASSED;
- no customer revenue is claimed from this project;
- no signed pilot is claimed;
- no company valuation, market size or sales forecast is claimed;
- commercial validation is a funded/adoption workstream, not a fabricated precondition.
