<p align="center">
  <img src="docs/readme/hero.svg" alt="Rheknel — The Stone Cronus Cannot Digest" width="100%" />
</p>

<h1 align="center">RHEKNEL</h1>
<p align="center"><strong>THE STONE CRONUS CANNOT DIGEST.</strong></p>
<p align="center"><em>Probabilistic systems may advise. The invariant gate gets the last word.</em></p>

<p align="center">
  <a href="https://blueshoes.space/rhea/">Rhea Pantheon</a> ·
  <a href="SAFETY_Manifesto.en.md">Safety Manifesto</a> ·
  <a href="decisions.md">Decisions</a> ·
  <a href="0protocol.ru.md">Protocol 0</a>
</p>

---

An AI model can be brilliant, persuasive, statistically calibrated—and still have **no authority to mutate reality**.

Rheknel explores the smallest possible boundary between *advice* and *effect*: a deterministic C dispatcher where registered judges evaluate a context and return one of three verdicts before actions are emitted.

```text
        untrusted / probabilistic proposal
                     │
                     ▼
             ┌──────────────┐
             │   RHEKNEL    │
             │ invariant gate│
             └──────┬───────┘
                    │
         ┌──────────┼──────────┐
         ▼          ▼          ▼
        OK       REJECT     ESCALATE
         │
         ▼
   tagged action dispatch
```

## Why the stone?

Rhea saves Zeus from Cronus by handing Cronus a **stone wrapped as the child he intended to swallow**. Cronus accepts the substitution; succession survives.

Rheknel takes the stone as its emblem because a useful invariant sometimes has to be a categorical object the surrounding probabilistic machinery **cannot negotiate into something else**.

> **ΚΡΟΝΟΣ ≠ ΧΡΟΝΟΣ.** Cronus is not Chronos. A myth can tolerate centuries of conflation. A control boundary cannot.

## What exists in this repository

The current `kernel.c` is a **small C prototype**, not a certified safety kernel and not proof of autonomous-system correctness.

It currently provides:

- bounded static action and judge registries;
- tagged callback registration;
- `RHEA_OK`, `RHEA_REJECT`, and `RHEA_ESCALATE` verdicts;
- deterministic judge iteration with short-circuit on the first non-OK verdict;
- action dispatch only after the caller accepts the verdict;
- no heap allocation in the demonstrated registry/dispatch path.

The included `aletheia_judge_string()` is a **demo heuristic** that rejects a couple of literal strings. It is not a semantic truth oracle, not a prompt-injection proof, and not an independently validated safety policy.

That distinction matters more than the slogan.

## The invariant shape

```c
typedef enum {
    RHEA_OK = 0,
    RHEA_REJECT = 1,
    RHEA_ESCALATE = 2
} RheaVerdict;
```

The architectural idea is deliberately boring:

1. **Observation/proposal enters as data.**
2. **Judges evaluate it under bounded code paths.**
3. **Any reject/escalate stops the optimistic path.**
4. **Actions are separate callbacks, not model prose interpreted as capabilities.**

The interesting work begins only when real invariants, typed contexts, evidence identities, failure semantics, and independent tests replace demonstration callbacks.

## Build the prototype

The repository currently uses a build file named `Make`:

```bash
make -f Make build
make -f Make run
```

The target is compiled from `kernel.c` with GCC using C11 flags.

## What Rheknel refuses to claim

A README cannot certify itself.

This repository does **not** currently establish:

- formal verification;
- constant-time or `O(1)` end-to-end enforcement guarantees;
- sub-millisecond hardware response guarantees;
- L4 autonomous-vehicle certification;
- prompt-injection immunity;
- production OpenBSD kernel integration;
- safety certification of any physical actuator.

Those may be research targets or integration directions. They become claims only when accompanied by executable evidence and an explicit qualification boundary.

## The family contract

Rheknel is not the whole system. It is the **NO-shaped object** inside a larger architecture.

| Relative | Relationship to Rheknel |
|---|---|
| **Rhea Project** | defines staged authority boundaries and evidence contracts |
| **Omnia Playbook** | supplies typed invariants, diagnostics, and procedures—not execution authority |
| **Omnia Vault** | preserves immutable state/evidence and causal history |
| **Blueshoes** | may propose/admit network mutations; actual effects require their own executor and receipts |

Public family map: **https://blueshoes.space/rhea/**

## Protocol 0

> *It's dangerous to go alone.*

Human and machine reasoning can collaborate. Neither gets to erase the invariant merely because the current answer is inconvenient.

## License

MIT. Timelabs NPO research project.

---

<p align="center"><strong>ADVICE IS CHEAP. AUTHORITY IS TYPED. NO MEANS NO.</strong></p>
