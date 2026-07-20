# 学习记录

每次完成练习后追加一项；只记录能证明学习发生的事实。阶段完成后，同时更新 [roadmap.md](roadmap.md) 的“进度状态”。

## 模板

```md
### YYYY-MM-DD — M<N>: <主题>

- 目标：
- 本课讲解：
- 我的问题与答案：
- 我做了什么：
- 证据：`<运行的命令>` → <结果>
- 我能解释：
- 卡点或误解：
- 下一步：
```

## 状态值

使用：`未开始`、`进行中`、`待复习`、`已完成`、`阻塞`。`已完成` 必须包含可重复运行的验证命令或可审查的产物位置。

### 2026-07-18 — P0: 环境基线

- 目标：确认本机能开始 CMake 学习。
- 我做了什么：检测 CMake 与默认 C++ 编译器。
- 证据：`cmake --version` → 4.3.0；`c++ --version` → Apple Clang 21.0.0（arm64）。
- 我能解释：待首次练习后补充。
- 卡点或误解：尚未在空构建目录中完成最小项目。
- 下一步：创建最小可执行程序并执行 configure、build、run。

### 2026-07-18 — P0.1: CMake、生成器与编译器的分工

- 目标：建立从 CMake 描述到最终二进制文件的构建链心智模型。
- 本课讲解：CMake 负责配置与生成；Ninja 等后端负责调度构建；Clang 等编译器负责编译与链接。
- 我的问题与答案：询问 Ninja 和 Clang 的关系，以及常见构建工具/编译器；已讨论 CMake → Ninja → Clang、CMake → Make → GCC、CMake → MSBuild → MSVC 等组合。
- 我做了什么：完成概念讲解与问答，学习者确认已大概理解。
- 证据：本次对话中的两次概念问答；尚无项目构建产物。
- 我能解释：CMake、构建后端和编译器的职责分工。
- 卡点或误解：尚未学习生成器选择与配置类型。
- 下一步：理解单配置/多配置生成器，再开始第一个最小项目。

### 2026-07-19 — P0.2: 生成器与构建配置

- 目标：理解生成器选择与 Debug/Release 配置的确定时机。
- 本课讲解：普通 Ninja 是单配置生成器，`Ninja Multi-Config` 是多配置生成器；单配置在配置时使用 `CMAKE_BUILD_TYPE`，多配置在构建时使用 `--config`。
- 我的问题与答案：追问多配置生成器为什么不使用 `CMAKE_BUILD_TYPE`，以及 Ninja 是否属于单配置；已解释同一构建目录中规则的生成时机。
- 我做了什么：完成概念讲解与问答，学习者确认可继续。
- 证据：本次对话中的生成器与配置问答；尚无项目构建产物。
- 我能解释：普通 Ninja 与 Ninja Multi-Config 的配置模型不同。
- 卡点或误解：无。
- 下一步：逐行理解最小 `CMakeLists.txt`，再开始第一个最小项目。

### 2026-07-19 — P1.1: 最小 CMakeLists.txt

- 目标：理解最小 CMake 项目如何声明版本、语言、项目与可执行 target。
- 本课讲解：`cmake_minimum_required` 声明兼容性下限；`project(... LANGUAGES CXX)` 启用 C++；`add_executable` 把源码关联到命名 target。
- 我的问题与答案：无；学习者要求继续。
- 我做了什么：完成最小构建描述的逐行讲解；尚未进入练习。
- 证据：本次对话中的概念讲解；尚无项目构建产物。
- 我能解释：CMake 描述 target，而不是直接写编译器命令。
- 卡点或误解：无。
- 下一步：理解 `main.cpp`、源码树与构建树如何在首次配置中连接起来。

### 2026-07-19 — P1.2: 首个练习工作区

- 目标：为最小 CMake 可执行程序准备独立源码目录。
- 本课讲解：源码目录包含 `CMakeLists.txt` 与 C++ 源文件；构建结果将写入单独的 `build/` 目录。
- 我的问题与答案：无；学习者要求创建空工作区。
- 我做了什么：创建 `exercises/p0-hello/`，其中包含空的 `CMakeLists.txt` 与 `main.cpp`。
- 证据：两个练习文件已存在，尚未填写。
- 我能解释：源码树与构建树应分离。
- 卡点或误解：无。
- 下一步：在引导下填写 `main.cpp`，再填写最小 `CMakeLists.txt`。

### 2026-07-19 — P1.3: 第一个可构建 target

- 目标：独立写出最小 C++ 源文件与 CMake target 描述，并完成首次 out-of-source 构建。
- 本课讲解：`add_executable` 将 `main.cpp` 关联到可执行 target；CMake 先生成 Ninja 规则，再由 Ninja 调用 Clang 编译与链接。
- 我的问题与答案：无；学习者完成了两个练习文件。
- 我做了什么：配置、构建并运行 `hello` target。
- 证据：`cmake -G Ninja -S exercises/p0-hello -B build/p0-hello`、`cmake --build build/p0-hello`、`./build/p0-hello/hello` 均成功；程序输出 `Hello, World!`。
- 我能解释：待小测确认 `project` 的默认语言与构建目录职责。
- 卡点或误解：`project(hello)` 默认启用了 C 与 CXX；若项目只使用 C++，可显式指定 `LANGUAGES CXX`。
- 下一步：复盘本次 CMake 输出，完成 P0/P1 的小测，再继续 target 属性与更多源文件。

### 2026-07-19 — P0/P1.3: 理解检查与反馈

- 目标：确认构建目录、默认语言和 target 的基本概念。
- 本课讲解：构建目录容纳生成器相关规则与缓存；`project()` 未指定语言时默认启用 C 与 CXX；项目名与 target 名是不同概念。
- 我的问题与答案：学习者正确说明了构建目录用于生成指定后端的工程文件，且正确指出未指定语言会触发 C/C++ 检测；将 `add_executable(hello main.cpp)` 中的 `hello` 误称为项目名，已澄清为 target 名。
- 我做了什么：完成三项短答复盘。
- 证据：本次对话中的回答与前一项成功构建。
- 我能解释：构建树的用途、`project()` 默认语言，以及 target 与项目名的区别。
- 卡点或误解：同一字符串可以同时被用作项目名与 target 名，但二者语义独立；本练习恰好都写成了 `hello`。
- 下一步：将项目名和 target 名故意命名为不同值，观察它们分别出现在哪里，再学习为 target 增加更多源文件。

### 2026-07-19 — P1.4: 多源文件 target

- 目标：理解多个源文件如何共同构成一个可执行 target。
- 本课讲解：`add_executable` 可直接列出多个源文件；也可用 `target_sources` 将文件关联到既有 target；增量构建只重编译受修改影响的源文件。
- 我的问题与答案：无；学习者确认没有疑问。
- 我做了什么：完成多源文件、目标归属和 `PRIVATE` 初步含义的讲解。
- 证据：本次对话中的概念确认；尚未修改练习源码。
- 我能解释：源文件属于具体 target，而非笼统“属于项目”。
- 卡点或误解：无。
- 下一步：理解头文件的声明与 `.cpp` 实现文件的分工，再完成两源文件练习。

### 2026-07-19 — P1.5: 两源文件练习检查

- 目标：将入口与欢迎功能拆分，并将两个 `.cpp` 文件加入同一 target。
- 本课讲解：头文件声明接口，实现文件提供定义；`target_sources` 的第一个参数是 target 名，作用域关键字为 `PRIVATE`/`PUBLIC`/`INTERFACE`。
- 我的问题与答案：学习者提交代码供检查。
- 我做了什么：在独立的 `build/p0-hello-check` 目录运行 CMake 配置。
- 证据：配置失败：`target_sources` 将小写 `private` 解析为名为 `private` 的 target；当前 `greating.cpp` 仅包含头文件，尚未定义 `Greating::printGreating()`。
- 我能解释：待修正后确认。
- 卡点或误解：遗漏 `target_sources` 的 target 参数；声明不等于定义。
- 下一步：先修正 `target_sources` 调用，再在 `greating.cpp` 定义静态成员函数，重新配置、构建和运行。

### 2026-07-19 — P1.5: 两源文件练习完成

- 目标：使 `main.cpp` 与 `greating.cpp` 成为同一可执行 target 的两个可构建源文件。
- 本课讲解：target 的源文件都要被声明给 CMake；类成员的声明必须在某个翻译单元中有对应定义，链接才会成功。
- 我的问题与答案：学习者提交修正版本供复查。
- 我做了什么：重新配置、构建并运行 `hello`。
- 证据：`cmake -S exercises/p0-hello -B build/p0-hello-check`、`cmake --build build/p0-hello-check`、`./build/p0-hello-check/hello` 均成功；Ninja 分别编译 `main.cpp` 和 `greating.cpp`，程序输出 `Hello World from program input`。
- 我能解释：`target_sources(hello PRIVATE ...)` 将多个 `.cpp` 文件关联到 target；函数声明和定义缺一不可。
- 卡点或误解：无；`#include <ostream>` 在当前实现中是冗余的，且标准库头文件惯例使用尖括号。
- 下一步：了解为什么多个源文件仍只是一个可执行 target，以及何时应将可复用功能提取为库。

### 2026-07-19 — P1.6: 库 target 的概念

- 目标：区分“可执行程序”和 CMake 的通用 target 概念。
- 本课讲解：库是构建图中的 target，可携带源码、属性与依赖；`add_executable` 创建可执行 target，`add_library` 创建库 target；并非每类库 target 都产生传统库文件。
- 我的问题与答案：询问为何强调 `add_library` 声明的是 target 而不是程序；已澄清程序是可执行产物，target 是更通用的构建对象。
- 我做了什么：完成库 target 与依赖图的概念讲解。
- 证据：本次对话中的问答；尚未将练习拆为库 target。
- 我能解释：target 是可配置、可依赖和可链接的构建图节点。
- 卡点或误解：无。
- 下一步：理解静态库与共享库的运行时差别，再把 `greating` 提取为静态库 target。

### 2026-07-19 — P1.7: 静态库与共享库

- 目标：理解静态库和共享库在链接、部署与运行时依赖上的不同。
- 本课讲解：静态库代码在链接时进入可执行程序；共享库在运行时被加载；本阶段显式使用 `STATIC` 以聚焦 target 关系。
- 我的问题与答案：无；学习者确认理解。
- 我做了什么：完成静态库与共享库的概念讲解。
- 证据：本次对话中的概念确认；尚未重构练习项目。
- 我能解释：静态库与共享库的代码进入程序和运行时依赖方式不同。
- 卡点或误解：无。
- 下一步：将 `greating.cpp` 提取为静态库 target，并让 `hello` 显式链接它。

### 2026-07-19 — P1.8: 提取并链接静态库

- 目标：将欢迎功能提取为 `greeting` 库 target，并让 `hello` 通过 target 依赖使用它。
- 本课讲解：`add_library` 创建库 target，`target_sources` 将实现文件归属给库，`target_link_libraries` 让可执行 target 链接库。
- 我的问题与答案：构建失败后分析出 CMake 中的 `greeting.cpp` 与磁盘中的 `greating.cpp` 拼写不一致；学习者已将文件统一重命名。
- 我做了什么：重新配置、构建并运行库化后的项目。
- 证据：`cmake -S exercises/p0-hello -B build/p0-hello-check`、`cmake --build build/p0-hello-check`、`./build/p0-hello-check/hello` 均成功；输出包含 `Linking CXX static library libgreeting.a` 和 `Linking CXX executable hello`，程序输出 `Hello World from program input`。
- 我能解释：库 target 先于链接它的可执行 target 构建，且 CMake 根据 target 依赖自动安排顺序。
- 卡点或误解：`add_library(greeting)` 未显式指定类型，但当前因 `BUILD_SHARED_LIBS` 未启用而生成静态库；后续练习将显式写 `STATIC` 以避免依赖默认值。
- 下一步：理解 `target_link_libraries(hello PRIVATE greeting)` 中依赖方向与 `PRIVATE` 的含义，并为库建立清晰的 public header 边界。

### 2026-07-19 — P1.9: target 依赖的可见性

- 目标：理解 `target_link_libraries` 的依赖方向，以及 `PRIVATE`/`PUBLIC`/`INTERFACE` 的传播语义。
- 本课讲解：`hello` 消费 `greeting`；target 的使用要求可包含头文件路径、编译定义、编译选项与其他依赖；可见性决定这些要求向消费者传播的方式。
- 我的问题与答案：无；学习者确认理解。
- 我做了什么：完成依赖方向与 usage requirements 的概念讲解。
- 证据：本次对话中的概念确认；库与可执行程序已成功链接。
- 我能解释：`PRIVATE` 表示仅当前 target 的构建依赖，`PUBLIC` 同时传播给消费者，`INTERFACE` 只传播给消费者。
- 卡点或误解：无。
- 下一步：理解为什么公开头文件目录是库 target 的 `PUBLIC` usage requirement。

### 2026-07-19 — P1.10: 公开头文件边界

- 目标：理解公开头文件目录为何属于库 target 的 `PUBLIC` usage requirement。
- 本课讲解：当前同目录中的引号 include 依赖编译器的本地查找规则；真实库应在 `include/` 下提供公开头文件，并由 `target_include_directories` 向消费者传播路径。
- 我的问题与答案：无；学习者确认可继续。
- 我做了什么：完成 public header、include 目录与 `CMAKE_CURRENT_SOURCE_DIR` 的概念讲解。
- 证据：本次对话中的概念确认；尚未重组练习目录。
- 我能解释：消费者能找到公开头文件，是库 target 传播 include 路径的结果。
- 卡点或误解：无。
- 下一步：将练习目录重组为 `include/`、`src/`、`app/`，并用 `PUBLIC` include 路径构建验证。

### 2026-07-19 — P1.11: 公开头文件目录练习完成

- 目标：通过 `greeting` target 的 `PUBLIC` include 目录，让分离目录中的消费者找到公开头文件。
- 本课讲解：`CMAKE_CURRENT_SOURCE_DIR` 代表当前处理的源码目录；`target_include_directories(... PUBLIC ...)` 同时为库自身和消费者提供 include 路径。
- 我的问题与答案：询问为何使用 `CMAKE_CURRENT_SOURCE_DIR`，以及相近变量能否替代；已对照官方变量文档解释当前目录、顶层源码目录、当前 list 文件和项目边界的不同。
- 我做了什么：检查 `include/greeting/greeting.h`、`src/greeting.cpp`、`app/main.cpp` 与 CMake target 配置，并重新配置、构建、运行。
- 证据：`cmake -S exercises/p0-hello -B build/p0-hello-check`、`cmake --build build/p0-hello-check`、`./build/p0-hello-check/hello` 均成功；两个翻译单元均能包含 `greeting/greeting.h`，程序输出 `Hello World from program input`。
- 我能解释：公开头文件路径应由提供它的库 target 以 `PUBLIC` usage requirement 传递给消费者。
- 卡点或误解：无；练习源码树中出现了 IDE 生成的 `cmake-build-debug/`，后续应将其视为构建目录而非源码并排除版本控制。
- 下一步：显式声明静态库类型，整理 include 写法与生成目录，然后进入 `add_subdirectory` 的分目录 CMake 组织。

### 2026-07-19 — P1.12: 显式库类型与公开接口整理

- 目标：消除库类型与公开头文件使用方式中的隐式约定。
- 本课讲解：相近目录变量的语义不同，应按目录所有权选择；显式的 `STATIC` 与公开头文件 include 使构建意图更清晰。
- 我的问题与答案：询问 `CMAKE_CURRENT_SOURCE_DIR` 与相近变量的区别；已按当前目录、顶层源码树、项目边界、当前 list 文件和构建目录解释适用场景。
- 我做了什么：复查修改后的 target 配置并重新构建运行。
- 证据：`add_library(greeting STATIC)` 已存在；`app/main.cpp` 与 `src/greeting.cpp` 都包含 `<greeting/greeting.h>`；configure、build、run 成功，输出 `Hello World from program input`。
- 我能解释：公开头文件路径由库 target 传播，且变量选择应反映路径所属边界。
- 卡点或误解：功能无阻塞；`cmake-build-debug/` 仍位于练习源码树中，应继续视为 IDE 构建产物而非源码。
- 下一步：学习 `add_subdirectory` 的目录作用域与子目录 CMake 文件职责。

### 2026-07-19 — P1.13: 分目录 CMake 练习检查

- 目标：将项目级、库级和应用级 CMake 职责拆分到各自目录。
- 本课讲解：根目录用 `add_subdirectory` 组织组件；每个子目录负责创建自己的 target 与相关 usage requirements。
- 我的问题与答案：学习者提交分目录 CMake 配置供检查。
- 我做了什么：检查三个 `CMakeLists.txt`，并重新配置、构建。
- 证据：根目录按 `src` 再 `app` 的顺序添加子目录，且 `greeting`/`hello` 均只定义一次；构建在编译阶段失败，两个翻译单元均报告 `greeting/greeting.h` 未找到。
- 我能解释：待修正后确认。
- 卡点或误解：从根 `CMakeLists.txt` 移动 target 定义时遗漏了 `target_include_directories(greeting PUBLIC ...)`；它应随 `greeting` target 一起放入 `src/CMakeLists.txt`。
- 下一步：在 `src/CMakeLists.txt` 恢复 `greeting` 的 `PUBLIC` include usage requirement，路径需指向项目根的 `include/`，然后重新构建。

### 2026-07-19 — P1.13: include 可见性复查

- 目标：验证公开 include 目录能同时服务库自身和消费者。
- 本课讲解：`INTERFACE` 只传播给消费者，`PUBLIC` 同时适用于当前 target 与消费者。
- 我的问题与答案：学习者补回 include 目录后要求复查。
- 我做了什么：重新配置、构建并比较两个翻译单元的结果。
- 证据：`app/main.cpp` 已成功编译，说明 `INTERFACE` include 目录已传播给 `hello`；`src/greeting.cpp` 编译失败，提示 `greeting/greeting.h` 未找到，说明 `greeting` 自身未获得 include 路径。
- 我能解释：待将 `INTERFACE` 改为 `PUBLIC` 后确认。
- 卡点或误解：库实现文件本身也包含公开头文件，因此这里不能只使用 `INTERFACE`。
- 下一步：仅将 `target_include_directories(greeting ...)` 的作用域从 `INTERFACE` 改为 `PUBLIC`，然后重新构建。

### 2026-07-19 — P1.13: 分目录构建完成

- 目标：以 `PUBLIC` include usage requirement 完成库自身与消费者的头文件可见性。
- 本课讲解：`PUBLIC` 同时服务当前 target 与其消费者；`add_subdirectory` 会为子目录创建对应构建目录。
- 我的问题与答案：学习者将 include 作用域改为 `PUBLIC` 后要求复查。
- 我做了什么：重新配置、构建并运行。
- 证据：configure、build、run 均成功；输出依次包含 `src/libgreeting.a` 和 `app/hello` 的链接，程序输出 `Hello World from program input`。
- 我能解释：库的公开头文件路径既供库实现使用，也通过 `PUBLIC` 传递给可执行消费者。
- 卡点或误解：无。
- 下一步：完成 P1 小测，确认 target、子目录与 usage requirements 的理解后进入 CMake 语言基础。

### 2026-07-19 — P1: 复盘小测通过

- 目标：验证 target 类型、依赖方向、子目录处理顺序与 usage requirements 的理解。
- 本课讲解：复盘静态库与可执行 target、`add_subdirectory`、`PRIVATE`/`PUBLIC`/`INTERFACE` 以及 target 链接传播。
- 我的问题与答案：四题均答对。学习者正确识别 `hello → greeting` 的依赖方向、`src` 先于 `app` 的组织原因、`PUBLIC` 同时服务库自身和消费者，以及测试 target 链接库即可获得公开 include 路径。
- 我做了什么：完成 P1 的理解检查与术语反馈。
- 证据：本次对话中的四项回答，以及此前成功的分目录构建。
- 我能解释：target、库、子目录与公开 usage requirements 如何构成可扩展的 CMake 构建图。
- 卡点或误解：术语微调：源码属于 target 的组成而非另一个“依赖”；测试 target 应写完整依赖声明，例如 `target_link_libraries(tests PRIVATE greeting)`。
- 下一步：开始 P2，学习 CMake 变量、列表、函数与作用域。

### 2026-07-19 — P2.1: 普通变量与目录作用域

- 目标：理解普通变量的定义、展开与子目录作用域。
- 本课讲解：`set()` 在当前目录或函数作用域创建普通变量，`${VAR}` 在命令执行前展开；父目录变量对子目录可见，子目录新变量不自动回传。
- 我的问题与答案：无；学习者确认可继续。
- 我做了什么：完成普通变量、列表的初步表示方式和目录作用域的讲解。
- 证据：本次对话中的概念确认；未修改项目。
- 我能解释：变量应表达可复用构建概念，且变量有效范围受目录/函数作用域约束。
- 卡点或误解：无。
- 下一步：学习列表的分号表示、追加和遍历。

### 2026-07-19 — P2.2: 列表、遍历与命名

- 目标：理解 CMake 列表的表示、追加、遍历与变量命名大小写规则。
- 本课讲解：列表是分号分隔的变量值；`list(APPEND)` 用于安全追加；`foreach(... IN LISTS ...)` 接收列表变量名；命令名不区分大小写而变量名区分大小写。
- 我的问题与答案：询问循环变量能否大写以及 CMake 的大小写规范；已澄清循环变量是自定义普通变量，建议命令小写、关键字大写、局部变量小写、用户配置变量使用带项目名前缀的大写。
- 我做了什么：完成列表与命名约定讲解。
- 证据：本次对话中的概念确认；未修改项目。
- 我能解释：列表变量的展开与遍历，以及 `${SOURCE}` 和 `${source}` 的区别。
- 卡点或误解：无。
- 下一步：学习 `function()` 与 `macro()` 的作用域差异。
