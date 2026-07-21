# CMake 长期学习路线

## 目标与使用方式

目标：能为中小型 C++ 项目设计和维护现代、target-based 的 CMake 构建；能阅读开源项目的构建逻辑；能交付可测试、可安装、可被其他项目消费的软件包。

本路线以 [CMake 官方 Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) 为唯一主线；官方练习是逐步递进的，每一步都包含前一步的完整解答。路线将其 12 个步骤编排成 6 个可验证阶段，避免在未掌握 target 基础前过早进入高级主题。

开始前填写 [profile.md](profile.md)。每次学习后追加 [log.md](log.md)，并以可复现的命令、测试输出、提交或笔记作为完成证据。不要因“读完”而勾选阶段。

完成的学习会话会同步到本仓库的私有 GitHub `main` 分支；仅同步源码、Skill 与学习资料，不同步构建产物或 IDE 本地状态。

## 每课学习方式

每一个新主题都按固定顺序进行：

1. **讲解**：先说明它解决什么问题、核心术语、运行时或构建时发生了什么，以及最小示例。
2. **问答**：你可以随时要求换一种解释、追问细节或提出反例；未澄清的概念不强行推进。
3. **引导练习**：在理解后完成一个小改动；教练按“问题 → 概念提示 → 局部提示”提供帮助。
4. **小测与复盘**：最后才用少量解释、预测或调试题检查理解，并将结果写进学习记录。

测试用于发现下一步要补的知识，不作为新主题的起点，也不以分数评判学习速度。

## 里程碑总览

| 阶段 | 官方 Tutorial 对应 | 建议时长 | 产出 | 完成门槛 |
|---|---|---:|---|---|
| P0：环境与工作流 | Step 0 | 1 次 | 可复现的构建命令 | 能解释生成器与构建目录 |
| P1：项目与 target 基础 | Step 1 | 1–2 周 | 可执行程序 + 库 + 子目录 | 能从零构建并拆分小项目 |
| P2：CMake 语言与配置 | Steps 2–3 | 2 周 | 选项、模块、Presets | 能为不同配置写可复现入口 |
| P3：target 与库设计 | Steps 4–5 | 2–3 周 | 可配置库项目 | 能正确传播 usage requirements |
| P4：工程化构建 | Steps 6–8 | 2–3 周 | 探测、生成文件、测试 | 能定位平台差异并验证构建 |
| P5：发布、依赖与进阶 | Steps 9–11 | 3–4 周 | 可安装、可消费的包 + 结业项目 | 能让另一个项目 `find_package` 并使用它 |

时长以每周 3–5 小时估算；证据不足时延长阶段，而不是跳过。

---

## P0 — 环境与构建工作流

官方对应：[Step 0: Before You Begin](https://cmake.org/cmake/help/latest/guide/tutorial/Step0/index.html)。

学习内容：教程练习获取方式、CMake 版本、生成器、单配置与多配置生成器、`cmake -S/-B` 与 `cmake --build`。

练习：在空的 `build/` 目录完成配置、构建、运行；分别记录所用生成器和构建工具。

验证：从删除后的构建目录重新执行：

```sh
cmake -S . -B build
cmake --build build
```

退出标准：能解释源码树与构建树为何分离，以及配置阶段和构建阶段的职责。

## P1 — 项目与 target 基础

官方对应：[Step 1: Getting Started with CMake](https://cmake.org/cmake/help/latest/guide/tutorial/Step1/index.html)：可执行程序、库、链接、子目录。

学习内容：`cmake_minimum_required`、`project`、`add_executable`、`add_library`、`target_sources`、`target_link_libraries`、`add_subdirectory`、`target_compile_features`。

练习：实现一个两目录小项目：`MathFunctions` 库 + 使用它的命令行程序。将一个原先直接放在可执行程序中的计算函数移动到库。

验证：

- 从空构建目录构建并运行；
- 列出每个源文件所属 target；
- 不看资料解释可执行程序如何获得库的符号。

退出标准：独立创建一个“库 + 应用 + 子目录”的 CMake 项目，且不使用全局 `include_directories` 或全局编译选项。

## P2 — CMake 语言与配置入口

官方对应：[Step 2: CMake Language Fundamentals](https://cmake.org/cmake/help/latest/guide/tutorial/Step2/index.html) 与 [Step 3: Configuration and Cache Variables](https://cmake.org/cmake/help/latest/guide/tutorial/Step3/index.html)。

学习内容：变量、列表、函数与宏、条件与循环、`include()`；`option()`、普通变量与 cache 变量；`CMakePresets.json`。

练习：

1. 将一段重复的配置提取为函数；
2. 用 option 控制一个可见功能；
3. 写最少两个 preset（开发与发布），并通过 preset 完成 configure/build。

验证：改变 option 或 preset 后，只影响预期的配置；在日志中解释变量作用域和 cache 的用途。

退出标准：能在没有命令行记忆负担的情况下，使用 preset 复现开发与发布构建。

## P3 — target usage requirements 与库类型

官方对应：[Step 4: In-Depth CMake Target Commands](https://cmake.org/cmake/help/latest/guide/tutorial/Step4/index.html) 与 [Step 5: In-Depth CMake Library Concepts](https://cmake.org/cmake/help/latest/guide/tutorial/Step5/index.html)。

学习内容：`target_compile_features`、`target_compile_definitions`、`target_compile_options`、`target_link_options`、`target_include_directories`、`PRIVATE`/`PUBLIC`/`INTERFACE`；静态库、动态库、接口库与对象库。

练习：扩展 P1 的库，使其对消费者公开 header 与一个编译定义，同时保留实现细节。创建一个 header-only 接口库；可选地比较静态与共享库。

验证：

- 消费者不需要手工复制 include 路径、编译定义或依赖；
- 故意把一个应公开的 requirement 改为 `PRIVATE`，观察并解释失败；
- 画出 target 依赖图。

退出标准：能以“谁需要使用该信息”为准则选择 `PRIVATE`、`PUBLIC` 或 `INTERFACE`。

## P4 — 探测、生成与测试

官方对应：[Step 6: In-Depth System Introspection](https://cmake.org/cmake/help/latest/guide/tutorial/Step6/index.html)、[Step 7: Custom Commands and Generated Files](https://cmake.org/cmake/help/latest/guide/tutorial/Step7/index.html) 与 [Step 8: Testing and CTest](https://cmake.org/cmake/help/latest/guide/tutorial/Step8/index.html)。

学习内容：检查头文件、检查源代码是否能编译、IPO 检查；`add_custom_command`、生成文件及其依赖；`enable_testing`、`add_test`、CTest。

练习：

1. 为一个可选能力增加编译期探测与明确的回退行为；
2. 用一个小生成器产生 header 或源文件，并将其作为 target 输入；
3. 为正常路径与边界条件各写一个 CTest。

验证：

```sh
ctest --test-dir build --output-on-failure
```

退出标准：能解释生成文件为什么必须被声明为构建图的一部分，且能在失败测试中定位问题。

## P5 — 安装、包、依赖与高级表达

官方对应：[Step 9: Installation Commands and Concepts](https://cmake.org/cmake/help/latest/guide/tutorial/Step9/index.html)、[Step 10: Finding Dependencies](https://cmake.org/cmake/help/latest/guide/tutorial/Step10/index.html) 与 [Step 11: Miscellaneous Features](https://cmake.org/cmake/help/latest/guide/tutorial/Step11/index.html)。

学习内容：`install()`、导出 targets、版本文件、`find_package()`、传递依赖、查找非包文件、target alias、generator expressions。

练习（结业项目）：将 P3/P4 的库安装到独立前缀；新建 `consumer/` 项目，仅用 `find_package()` 找到并链接它；为 Debug/Release 或不同平台条件使用一个最小 generator expression。

验证：

```sh
cmake --install build --prefix _install
cmake -S consumer -B consumer/build -DCMAKE_PREFIX_PATH="$PWD/_install"
cmake --build consumer/build
```

退出标准：在新的构建树中，消费者无需引用原项目源码路径即可配置、构建并运行。

---

## 长期节奏与复习规则

每个学习单元遵循：阅读官方对应章节 → 完成最小改动 → 运行验证 → 用自己的话解释 → 记录证据。每周至少安排一次 20 分钟复习：从空构建目录复现前一个阶段的核心命令，或故意制造一个小错误再排查。

完成 P5 后的下一周期，不再按教程逐行推进；改为选择一个真实 CMake 开源项目，写出其 target 图、构建选项、测试入口、安装/包策略，并提交一个小的文档、测试或构建改进。

## 进度状态

| 阶段 | 状态 | 首次开始 | 完成证据 | 下次复习 |
|---|---|---|---|---|
| P0 | 已完成 | 2026-07-18 | 最小项目以 Ninja + Apple Clang 成功 configure、build、run；完成概念问答 | 2026-07-26 |
| P1 | 已完成 | 2026-07-19 | 分目录 `greeting` 静态库与 `hello` 可执行程序成功构建运行；完成复盘小测 | 2026-07-26 |
| P2 | 进行中 | 2026-07-19 | 开始学习普通变量与目录作用域 | 完成变量、列表、函数与模块练习后安排 |
| P3 | 未开始 |  |  |  |
| P4 | 未开始 |  |  |  |
| P5 | 未开始 |  |  |  |

## 暂不学习

在完成 P3 前，不把全局 include 路径、全局编译选项、复杂 FetchContent 链、交叉编译工具链或平台分支作为主学习任务。它们不是不重要，而是需要建立在 target usage requirements 之上。
