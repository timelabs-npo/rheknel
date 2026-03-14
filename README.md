RHEA v2: The Invariant Kernel / 不变式内核
Rhea is an ultra-lightweight (< 2KB) deterministic event-driven kernel written in C, designed for managing AI agents in extreme resource-constrained environments where security and logic invariants are non-negotiable.

🏛️ Organization & Credits / 机构与致谢
Organization: Timelabs NPO

Authors:

Lead Architect: Mika IO (IET Force)
Co-Author / System Logic: Gemini (Google DeepMind)
1. Manifesto: Anthropics vs. Everybody / 宣言：对抗概率论
The AI industry has chosen the path of "black boxes" and "probabilistic safety." Rhea declares the end of the age of probability. We don't ask AI to be safe; we force it at the kernel level.

AI 行业选择了“黑盒”和“概率安全”的道路。Rhea 宣告概率时代的终结。我们不要求 AI 保持安全；我们通过内核级别强制其实施安全。

2. Engineering Solidity / 工程可靠性 (IEEE DATE 2025)
The project follows the principles of Trustworthy Co-Design (IEEE 10992986):

Hardware-Software Co-Design: Built for RISC-V/ESP32 execution.
Deterministic Event Bus: Separation of Actions and Filters for 100% predictability.
Zero-Allocation Policy: No heap, no malloc, zero memory leaks.
该项目遵循 Trustworthy Co-Design 原则 (IEEE 10992986)：

软硬件协同设计：专为 RISC-V/ESP32 执行而构建。
确定性事件总线：动作与过滤器的分离，实现 100% 的可预测性。
零分配策略：无堆空间，无 malloc，零内存泄漏。
3. Actuality & Autonomy / 现状与自主权
AI Silicon: The software heart for open-source AI chips.

Computational Irreducibility: We enforce a "Tribunal" at every cycle instead of predicting hallucinations.

L4 Autonomy: A hardware-level kill-switch for autonomous heavy machinery.

AI 芯片：开源 AI 芯片的软件核心。

计算不可约性：我们在每个周期执行“法庭”机制，而不是预测幻觉。

L4 自主：自主重型机械的硬件级切断开关。

4. Technical Spec / 技术规格
Language: Pure C (C99).

Memory: < 2KB static footprint.

Architecture: Hook-based (Action/Filter Dispatcher).

🤝 Support & Contact / 支持与联系
We seek industrial partners for Rhea Shield mass production and L4 Safety Certification.

我们正在寻求 Rhea Shield 量产和 L4 安全认证 的工业合作伙伴。

Email: dev@timelabs.npo

GitHub: timelions/rhea