# ARIA Scaling Trust Track 2.2 — Team + UK Delivery Plan v1

Status: WORKING PLAN
Date: 2026-09-29

## 1. Team architecture

The proposal should not pretend that one person is simultaneously:
- lead systems architect;
- full-time C/runtime engineer;
- security/formal reviewer;
- Arena/evaluation engineer;
- independent red team;
- grants administrator;
- UK adoption lead.

That is not lean. It is non-independent and operationally brittle.

### Core roles

| Role | Planned commitment | Employment route | Current status | Primary proof responsibility |
|---|---:|---|---|---|
| Lead / systems architect — Mika IO | 0.80 FTE x 9 months | applicant/core team | identified | technical thesis, canonical semantics, scope gates, final integration |
| Senior systems/runtime engineer | 1.00 FTE x 9 months | hire or named contractor | OPEN | production C runtime, capability boundary, portability |
| Security/formal-methods engineer | 0.80 FTE x 8 months | hire or named contractor | OPEN | threat model, narrowing invariants, fail-closed review |
| Evaluation / Arena engineer | 1.00 FTE x 7 months | hire/contract | OPEN | benchmark design, Utility/Security metrics, Arena integration |
| Integration / release engineer | 0.60 FTE x 6 months | hire/contract | OPEN | external producers/stacks, packaging, release/conformance |
| Project admin / compliance | 0.40 FTE x 9 months | part-time hire/service | OPEN | cost evidence, claims, reporting, procurement/admin |

Independent review/red-team stays outside the core implementation team.

## 2. Independence rule

The same person/team that implements a security property MUST NOT be the sole acceptor of that property.

Minimum separation:
- implementation team produces code/tests;
- independent security/formal reviewer challenges model/invariants;
- independent red-team produces adversarial cases;
- CI/evidence binds the exact source revision;
- proposal/report distinguishes developer verification from independent reproduction.

P0 is developer-run external CI evidence, **not independent third-party reproduction**.

## 3. Lead commitment

Planning assumption:
**Mika IO = 80% FTE for the 9-month project.**

This is intentionally high because the project is a technical R&D programme, not a passive PI grant.

Before submission, replace this planning statement with:
- exact contractual/employment relationship to applicant;
- exact project start availability;
- any concurrent funded commitments;
- legally accurate applicant/residence/payment details.

Do not invent these facts in the proposal.

## 4. UK delivery problem

ARIA allows non-UK applicants, but the project must articulate concrete UK benefit/delivery.

The UK plan also solves a second problem: ARIA normally reimburses actual expenditure in arrears, so the delivery structure must have working capital and grant administration capacity.

### Preferred structure to investigate first

**UK delivery/host partner + Mika as technical lead.**

Desired properties:
- can sign ARIA agreement and receive/reconcile reimbursements;
- can employ/contract the lead and core team lawfully;
- has project working capital;
- can host UK build weeks;
- provides accounting/procurement infrastructure without controlling technical scope;
- accepts the required open-source/IP structure.

This is a target structure, not an existing partnership.

### Fallback structure

Non-UK lead/applicant with:
- named UK subcontractors/researchers;
- UK Arena integration;
- UK build weeks;
- UK pilot/adoption relationships;
- clear UK expenditure/benefit;
- a separate credible working-capital mechanism.

## 5. Concrete UK-benefit package

The proposal can credibly promise deliverables rather than vague “ecosystem benefit”:

1. **UK build weeks**
   - two in-person engineering/evaluation weeks during the 9-month project;
   - budgeted under project travel;
   - tied to M2/M5 integration gates.

2. **UK security/formal review**
   - procure at least one material independent review from UK-based capability where technically competitive and compliant;
   - deliver public/non-sensitive review findings where possible.

3. **Arena integration**
   - make Rheknel usable by UK-based Arena participants through documented adapter/conformance interfaces;
   - publish integration fixtures and benchmark procedures.

4. **UK pilot/adoption**
   - target at least one UK-based external integration/pilot candidate before M5;
   - pilot is a target/KPI, not a fact until a partner exists.

5. **Open-source public goods**
   - permissively licensed Foreground software and benchmark tooling available to UK researchers/companies without vendor lock-in.

## 6. Recruitment / contracting order

Do not recruit six people before award.

Pre-award:
1. identify 2–3 credible security/formal reviewers or organisations;
2. identify 2–3 Arena/agent integration candidates;
3. identify one grant-admin/host structure capable of cashflow;
4. obtain budgetary quotes / letters of interest where useful;
5. name only people who actually consent.

Post-award:
1. lead + senior runtime engineer;
2. security/formal engineer;
3. evaluation/Arena engineer;
4. integration/release role;
5. admin/compliance support;
6. independent red-team at the appropriate milestone.

## 7. Team evidence needed for submission

For each named key person:
- role;
- FTE%;
- relevant track record;
- why they are uniquely/usefully positioned;
- current affiliation / contractual path;
- location relevant to delivery;
- conflicts/other commitments.

For OPEN roles:
- capability specification;
- hiring/subcontract route;
- budget envelope;
- latest date by which role must be filled;
- contingency if recruitment fails.

## 8. Team kill conditions

Redesign before submission if:
- no credible working-capital/grant-admin structure exists;
- lead cannot commit the declared FTE;
- independent review is merely another Timelabs-controlled model/agent;
- UK benefit is only travel with no delivery/adoption substance;
- team budget is defended by titles rather than work packages;
- critical role remains “Mika will do it somehow”.

## 9. Facts still requiring administrative confirmation

These are the only human-origin facts the proposal must eventually get from Mika or a legal/admin source:

- exact applicant legal entity / individual route;
- exact country of contracting/payment at award time;
- bank/payment capability;
- lead employment/contract relationship;
- confirmed 80% FTE availability for project dates;
- existing IP ownership/licensing conflicts, if any;
- named UK partner/host, if one is secured.

Until verified, these remain **OPEN**, not guessed.
