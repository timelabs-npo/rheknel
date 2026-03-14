Rhea Architectural Decision Records (ADR)
Organization: Timelabs NPO

Project: Rheknel (Rhea v2)

Total Records: 14

[ADR-001] Agent Consolidation (2026-02)
Context: v1 had 10 agents with overlapping competencies.

Decision: Merge Astronomer + Physicist + Mathematician → Agent 1; Chemist + Biologist + Neuroscience → Agent 2. Add Tech Lead (A6), Growth (A7). Preserve Critical Reviewer independence.

Rationale: Eliminates handoff losses; biological systems do not respect disciplinary boundaries.

[ADR-002] Multi-Model Bridge (2026-02)
Context: Need diverse AI perspectives; avoid single-provider lock-in.

Decision: Build rhea_bridge.py with 6 providers and 400+ models with Tribunal mode.

Rationale: 10-100x cost reduction via free tiers. Geographic diversity reduces bias.

[ADR-003] ADHD-Optimized Design (2026-02)
Context: Neurotypical UX fails for executive dysfunction.

Decision: All UX assumes ADHD as default: minimal decision load, passive profiling, body-first morning, no questionnaires.

Rationale: If it works for ADHD users, it works for everyone. (Bruton et al. 2025).

[ADR-004] Model Allocation (2026-02)
Decision: Claude Opus for research/critique (A1, A2, A4, A8); Sonnet for execution (A3, A5, A6, A7).

[ADR-005] Passive Profiling (2026-02)
Decision: Use behavioral signals (sleep, movement, HRV) instead of self-report questionnaires.

Rationale: Reduces onboarding friction and increases reliability.

[ADR-006] Hunter-Gatherer Calibration (2026-02)
Decision: Use Hadza/San/Tsimane daily patterns as the "Calibration Zero" for optimal defaults.

Rationale: The nervous system biology converges on these patterns (Wiessner 2014).

[ADR-007] Three-Tier External Memory (2026-02-13)
Decision: GitHub (state.md ≤ 2KB) for long-term; entire.io for episodic; compact session handoff.

Rationale: Reduces context overhead from 70% to ~5%.

[ADR-008] Tiered Routing (Cheap-First) (2026-02-13)
Decision: 4-tier routing: Cheap, Balanced, Expensive, Reasoning. Default = Cheap.

Rationale: Enforces cost discipline. (Supersedes ADR-004).

[ADR-009] Cost-Aware Agents (2026-02-13)
Decision: Agents self-regulate cost via declared tiers and escalation rationale.

Rationale: Estimated 80% of calls stay on the cheap tier.

[ADR-010] Discomfort Metric (2026-02-13)
Decision: Implement Discomfort function D to trigger auto-compaction and self-improvement loops.

Rationale: Prevents context bloat ("Goldfish failure").

[ADR-011] Self-Upgrade Techniques (2026-02-14)
Decision: Adopt 6 patterns: Reflexion, Tribunal/Debate, Tool-Verification, Eval Sets, Failure Memory, Teacher-Student.

[ADR-012] Manual-Commit Strategy (2026-02-14)
Decision: Maintain manual git commits for provenance (Later Superseded by ADR-014).

[ADR-013] Wrapper Script for Lifecycle (2026-02-14)
Decision: Create scripts/rhea_commit.sh to bridge the gap between Cowork and Entire.io sessions.

[ADR-014] Per-Query Persistence + Auto-Commit (2026-02-14)
Decision: Every query causes a memory update. Switch to auto-commit strategy.

Rationale: Full episodic memory—every interaction leaves a trace.