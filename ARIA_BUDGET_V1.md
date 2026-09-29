# ARIA Scaling Trust Track 2.2 — Bottom-Up Budget v1

Status: PLANNING MODEL — NOT YET SUBMITTED
Date: 2026-09-29
Project length: 9 months
Target request: **£900,000**

Official programme boundary:
- Track 2 project range: £200k–£2m;
- project length: 3 months–1 year;
- ARIA reimburses actual eligible expenditure in arrears, normally quarterly, with monthly payments potentially agreed for cashflow;
- eligible labour is actual salary + employer statutory contributions, not an arbitrary contractor/profit rate.

Official sources:
- https://aria.org.uk/opportunity-spaces/trust-everything-everywhere/scaling-trust/funding
- https://aria.org.uk/funding-opportunities/faqs
- https://aria.org.uk/media/qb1lty1w/eligible-expenditure-guidance.pdf

Therefore **the rates below are planning ceilings for capability/cost modelling, not declared salaries and not yet claimed eligible expenditure.**
They MUST be replaced by actual salary/contract quotes and the ARIA cost spreadsheet before submission.

## 1. Delivery labour

| Role / capability | FTE | Months active | Planning loaded cost / active month | Envelope | Why needed |
|---|---:|---:|---:|---:|---|
| Lead / systems architect | 0.80 | 9 | £16,000 | £115,200 | technical ownership, contract/effect semantics, programme decisions |
| Senior systems/runtime engineer | 1.00 | 9 | £14,000 | £126,000 | deterministic runtime, capability boundary, portable implementation |
| Security / formal-methods engineer | 0.80 | 8 | £15,000 | £96,000 | threat models, narrowing rules, adversarial/fail-closed analysis |
| Evaluation / Arena engineer | 1.00 | 7 | £12,000 | £84,000 | benchmark harness, Arena integration, Utility/Security metrics |
| Integration / release engineer | 0.60 | 6 | £10,000 | £36,000 | external producers/stacks, packaging, conformance/release |
| Project admin / compliance | 0.40 | 9 | £9,000 | £32,400 | reimbursement evidence, reporting, procurement/admin controls |
| **Labour subtotal** |  |  |  | **£489,600** | |

The lead allocation intentionally targets 80% FTE, consistent with the programme's preference for substantial lead/key-researcher commitment. It is a planning assumption until the applicant/team structure is frozen.

## 2. Independent/specialist work

| Work | Envelope | Acceptance condition |
|---|---:|---|
| Independent adversarial / red-team review | £60,000 | external report + reproducible attack cases, including negative findings |
| Formal-methods / security design review | £50,000 | review of canonical IR, narrowing invariants and threat model; no certification claim |
| External integration / pilot engineering | £60,000 | at least two external-stack integration attempts with measured effort/results |
| Accounting / legal / IP / grant-compliance support | £25,000 | cost-evidence readiness, IP schedule, contracting/admin support |
| **Specialist subtotal** | **£195,000** | |

## 3. Other direct costs

| Cost | Envelope | Constraint |
|---|---:|---|
| Compute, CI, test hardware / equipment use | £50,000 | only project-necessary infrastructure; final treatment per ARIA eligible-cost rules |
| UK programme travel / build weeks / collaboration | £30,000 | programme participation + concrete UK delivery/adoption work |
| Other project-specific direct costs | £15,000 | only documented eligible costs tied to a WP |
| **Other direct subtotal** | **£95,000** | |

## 4. Indirect cost placeholder

**£120,400**

This is NOT a flat mark-up and MUST NOT be submitted as a generic overhead percentage.

It is a balancing placeholder for eligible indirect/organisation costs pending:
1. final lead-applicant structure;
2. actual employment model;
3. ARIA detailed cost-sheet classification;
4. evidence of the applicant's normal allocation methodology.

If the final eligible indirect cost is lower, the request should fall below £900k or the freed amount must be reallocated only to demonstrably necessary project activity — never to preserve the headline number.

## 5. Total

| Category | Amount |
|---|---:|
| Delivery labour | £489,600 |
| Specialist / independent work | £195,000 |
| Other direct costs | £95,000 |
| Indirect cost placeholder | £120,400 |
| **TOTAL** | **£900,000** |

## 6. Work-package mapping

| WP | Months | Primary spend | Planning allocation |
|---|---|---|---:|
| WP1 Contract model + threat model | 1–2 | lead, systems, security review | £105,000 |
| WP2 Producer-independent ingress | 2–4 | systems, integration, security | £130,000 |
| WP3 Authority/effect boundary | 3–5 | systems, security, test infrastructure | £145,000 |
| WP4 Receipts / replay / audit | 4–6 | systems, evaluation, formal review | £115,000 |
| WP5 Adversarial benchmark | 5–8 | evaluation, red-team, compute | £155,000 |
| WP6 Arena / external adoption | 6–9 | integration, evaluation, pilot work, UK build weeks | £160,000 |
| Cross-project admin / compliance / eligible indirect | 1–9 | admin, accounting/legal, indirect | £90,000 |
| **TOTAL** |  |  | **£900,000** |

This mapping is for proposal planning. No cost may be counted twice in the final ARIA spreadsheet.

## 7. Cash-flow model

ARIA's normal payment mechanism reimburses actual eligible costs **in arrears**. Planning burn profile:

| Month | Planned spend |
|---:|---:|
| 1 | £80,000 |
| 2 | £90,000 |
| 3 | £100,000 |
| 4 | £105,000 |
| 5 | £110,000 |
| 6 | £110,000 |
| 7 | £105,000 |
| 8 | £105,000 |
| 9 | £95,000 |
| **TOTAL** | **£900,000** |

Operational implication:

> The project must not depend on Mika personally fronting ~£100k+ monthly expenditure.

Before award/contract, the delivery structure must establish a working-capital path compatible with reimbursement timing. Preferred request if funded: **monthly reimbursement**, subject to ARIA agreement.

Potential compliant mechanisms to evaluate later:
- lead organisation with adequate working capital;
- supplier/subcontract payment terms aligned with reimbursement cycle;
- staged hiring/start dates;
- other lawful bridge finance if required.

No finance mechanism is assumed or promised here.

## 8. Cost-to-evidence rule

Every final budget line must map to:

```text
cost -> named capability -> work package -> milestone -> externally checkable output
```

Examples:
- security engineer -> WP1/WP3 -> threat model / narrowing invariant tests -> M1/M3;
- red-team subcontract -> WP5 -> independent attack corpus/report -> M4;
- Arena engineer -> WP5/WP6 -> benchmark + external integration -> M4/M5.

If a pound cannot be mapped this way, DELETE IT.

## 9. Budget kill conditions

Reduce/redesign the request if:
- actual eligible labour cost is materially below the planning envelope;
- indirect-cost methodology does not support the placeholder;
- subcontract work duplicates internal team work;
- a cost has no project-specific necessity/evidence;
- working capital cannot sustain the reimbursement cycle;
- £900k can only be defended by adding scope after the technical plan is already sufficient.

The objective is **maximum expected usable funding**, not maximum headline request.
