# C++ Linux Systems 学习路线

## 目标与使用方式

本路线服务于“工业软件/CAE 平台”和“Linux C++ 服务/中间件”共同需要的系统能力。每个里程碑只在独立实现、可重复验证和正确解释同时满足时完成。时间安排由 [年度总计划](../../../learning/cpp-career-plan-2026-2027.md) 协调；本文件只定义本主题的学习顺序和退出证据。

## M0 — 无 AI 基线与可重复工具链

- **Starting point：** 有大型 C++ 工程经验，但现代 C++、Linux 工具和独立实现能力缺少统一基线。
- **New hinge：** 把“能完成需求”转换为可复现的独立编码、测试和解释证据。
- **Practice：** 90 分钟无 AI 实现一个拥有文件或句柄资源的 RAII 类型，覆盖成功、移动、错误和提前返回。
- **Verify：** CMake configure/build、CTest；至少一次故意失败；记录编译器和 sanitizer 可用性。
- **Exit：** 能解释构造、析构、拷贝/移动和异常路径；测试证明资源只释放一次；记录独立完成比例和卡点。
- **Review：** M1 结束后从空目录重做一个不同资源类型。
- **Not now：** 模板炫技、复杂框架、网络或并发。

## M1 — 所有权、值语义与泛型基础

- **Starting point：** M0 的单一 RAII 类型。
- **New hinge：** 用类型语义表达所有权、复制成本、移动和异常保证，而不是依赖调用者记忆。
- **Practice：** Rule of Zero/Five、`unique_ptr`/`shared_ptr` 边界、强/基本异常保证、容器选型、lambda、函数/类模板、type traits 与基础 concepts。
- **Verify：** 单元测试覆盖复制、移动、自赋值、异常注入和容器边界；ASan/UBSan 分别运行；做一个 vector/deque/list/unordered_map 数据布局实验。
- **Exit：** 能独立选择值、独占、共享或观察关系；能说明异常保证与 STL 选型；ASan/UBSan 无已知错误。
- **Review：** M2 中把一个 Linux 资源封装为 Rule-of-Zero 上层类型。
- **Not now：** 表达式模板、模板元编程技巧、定制 allocator 和 ABI 深水区。

## M2 — Linux 资源、进程与故障定位

- **Starting point：** 能安全封装资源并写测试。
- **New hinge：** 把 C++ 生命周期连接到 Linux 文件描述符、进程和动态链接行为，并用调试器而非猜测定位问题。
- **Practice：** 文件 I/O、文件描述符、进程、信号、管道、权限、动态库；GDB 断点、条件断点、调用栈和 core dump。
- **Verify：** 在明确记录的 Linux 环境中独立定位一个崩溃；用 ASan/UBSan 复测 M0/M1；保留故障复现与修复命令。
- **Exit：** 能解释进程/线程、文件描述符所有权、信号边界和动态库查找；GDB 定位过程可重复。
- **Review：** M4 网络练习中再次使用 GDB 或 strace 定位一次 I/O 故障。
- **Not now：** 内核开发、eBPF 深入、容器编排和系统管理认证路线。

## M3 — 并发组件、取消与关闭

- **Starting point：** 生命周期与 Linux 诊断基础已验证。
- **New hinge：** 并发正确性来自共享状态协议、happens-before 和完整关闭路径，而不是“加一把锁”。
- **Practice：** `std::thread`、mutex、condition_variable、atomic、future；有界队列、线程池、取消、超时、错误传播和优雅退出。
- **Verify：** 单元测试覆盖队列满/空、虚假唤醒、关闭、异常和窗口期；压力测试；在支持环境中单独运行 TSan。
- **Exit：** 有界队列和线程池具备可重复测试；TSan 无已知数据竞争或记录明确限制；能解释 worker 生命周期和关闭顺序。
- **Review：** M4 的连接处理复用队列或调度器；与 Qt P8 worker-object 做一次概念对照。
- **Not now：** lock-free 容器、无等待算法和复杂 memory_order 优化。

## M4 — TCP、epoll 与 Boost.Asio

- **Starting point：** 能实现可关闭的并发组件。
- **New hinge：** TCP 是无消息边界的字节流；正确服务需要 framing、部分读写、生命周期、超时和背压协议。
- **Practice：** 阻塞 Socket client/server、非阻塞 I/O、epoll LT/ET、Boost.Asio `io_context`/handler/executor、异步 echo、版本化 framing。
- **Verify：** 测试拆包/粘包、部分读写、断线、半关闭、超时、队列满和优雅退出；端到端测试可重复运行。
- **Exit：** 异步 TCP 服务正确处理 framing、超时、断线和背压；能画出连接与 handler 生命周期。
- **Review：** M5 压测时制造慢客户端和突发流量。
- **Not now：** HTTP 框架、RPC 框架、TLS 细节和分布式一致性。

## M5 — 性能测量与质量闭环

- **Starting point：** 已有真实的并发/网络组件可测量。
- **New hinge：** 优化结论必须建立在固定负载、可重复基线和同环境复测之上。
- **Practice：** benchmark 设计、吞吐、p50/p95、峰值内存、perf、火焰图、锁竞争、缓存与数据布局；故障注入和可靠性测试。
- **Verify：** 至少完成一次完整“基线—定位—单一修改—复测”报告；固定数据、硬件、编译模式和命令。
- **Exit：** 形成第一份可复现性能报告，并能区分 CPU、I/O、锁和内存问题；后续在旗舰项目累计三次闭环。
- **Review：** 旗舰项目每个性能结论必须复用同一报告模板。
- **Not now：** 没有测量依据的微优化、极致低延迟交易技巧和平台不可复现的跑分。

## M6 — 旗舰项目移交准备

- **Starting point：** 现代 C++、Linux、并发、网络和性能的最小组件均有证据。
- **New hinge：** 把练习能力组合成清晰边界、可测试指标和可回退阶段，而不是继续堆练习。
- **Practice：** 为独立仓库 `engineering-data-lab` 定义用户场景、工程数据格式、非目标、target 图、协议、测试数据、性能指标和 v0.1 阶段。
- **Verify：** 设计评审能追踪每项需求到测试或 benchmark；不含公司代码、格式、数据或内部设计。
- **Exit：** 独立仓库范围获批准，可从空目录 configure/build/test；本学习仓库只保留兼容性小实验和学习证据。
- **Review：** 年度 C3/C5 检查点评估项目 v1.0/v1.1。
- **Not now：** 未经测量的大规模架构、插件生态、求解器、计算几何和纯渲染算法。

## 进度状态

| 阶段 | 状态 | 首次开始 | 完成证据 | 下次复习 |
|---|---|---|---|---|
| M0 | 未开始 |  |  |  |
| M1 | 未开始 |  |  |  |
| M2 | 未开始 |  |  |  |
| M3 | 未开始 |  |  |  |
| M4 | 未开始 |  |  |  |
| M5 | 未开始 |  |  |  |
| M6 | 未开始 |  |  |  |

## 明确暂缓

- CAE 求解器、有限元算法、CAD 几何内核、计算几何和纯图形渲染算法。
- AI Infra、编译器、操作系统内核和极致低延迟交易。
- 系统性重学高数、线代和概率论；只在项目需要时补向量、矩阵、坐标变换、包围盒和空间索引。
- 在 M4 前引入大型服务框架，在 M5 前声称性能优化，在 M6 前创建旗舰项目远程仓库。
