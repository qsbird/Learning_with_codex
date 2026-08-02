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

### 2026-07-20 — P2.3: 函数、宏与参数

- 目标：理解 `function()` 与 `macro()` 的作用域差异，以及两者的固定/可变参数。
- 本课讲解：函数创建局部变量作用域，宏近似文本展开并影响调用者；两者均可声明形参并通过 `ARGC`、`ARGV`、`ARGN` 读取参数。
- 我的问题与答案：询问函数和宏是否只能固定展开；已用带命名参数与 `ARGN` 的示例说明两者均能接收可变参数。
- 我做了什么：完成函数、宏、作用域和参数机制的讲解。
- 证据：本次对话中的概念确认；未修改项目。
- 我能解释：优先用函数来封装可复用且不泄漏变量副作用的逻辑。
- 卡点或误解：无。
- 下一步：学习 `if()` 的真假值、条件组合与构建配置分支。

### 2026-07-20 — P2.4: 条件判断

- 目标：理解 CMake 的条件分支与一致的布尔值约定。
- 本课讲解：`if`/`elseif`/`else` 可表达组件开关、平台和字符串条件；推荐用 `ON`/`OFF`，并直接写 `if(VARIABLE)` 而非预先展开变量。
- 我的问题与答案：无；学习者确认可继续。
- 我做了什么：完成条件判断、布尔值、字符串比较与平台条件的讲解。
- 证据：本次对话中的概念确认；未修改项目。
- 我能解释：条件分支应只表达真实构建差异，且应避免不必要复杂度。
- 卡点或误解：无。
- 下一步：学习 `option()` 与 cache 变量，创建由构建者控制的项目开关。

### 2026-07-20 — P2.5: 用户可配置选项

- 目标：区分普通变量与面向构建者的布尔 cache 选项。
- 本课讲解：`option()` 创建带说明和默认值的 BOOL cache 条目；`-D` 可覆盖它；现有 cache 值会在同一构建目录中保留。
- 我的问题与答案：无；学习者确认可继续。
- 我做了什么：完成 `option()`、cache 持久性和项目名前缀约定的讲解。
- 证据：本次对话中的概念确认；未修改项目。
- 我能解释：用户可配置构建开关应使用 `option()`，而不是普通 `set()`。
- 卡点或误解：无。
- 下一步：加入 `HELLO_BUILD_APP`，并分别验证 ON/OFF 配置下的 target 图。

### 2026-07-21 — 学习记录自动同步

- 目标：让已验证的学习进度持续同步到私有 GitHub 仓库。
- 我做了什么：在仓库约定与学习 Skill 中加入会话结束时的检查、Lore 提交与 `main` 推送流程。
- 证据：`AGENTS.md` 的 End-of-session GitHub sync 规则，以及 `learning-coach` 的同步步骤。
- 约束：不提交构建产物、IDE 本地状态、`.DS_Store` 或 `.omx/` 状态；无变更时不创建空提交。
- 下一步：继续 P2.5 的 `HELLO_BUILD_APP` 练习。

### 2026-07-21 — P2.5: 应用构建开关练习完成

- 目标：用 `option()` 和 `if()` 让构建者控制是否创建 `hello` 应用 target。
- 本课讲解：布尔 cache 选项由 `-D` 覆盖；条件成立时才处理 `app/` 子目录；独立构建目录保留各自的 cache 值。
- 我的问题与答案：学习者的终端未识别 `rg`；已说明其为 ripgrep，并用系统自带 `grep` 完成等价 cache 检查。
- 我做了什么：检查根 CMake 配置，并分别配置、构建、运行 ON/OFF 两个构建树。
- 证据：`HELLO_BUILD_APP:BOOL=ON` 的构建树生成 `app/hello` 并输出 `Hello World from program input`；`HELLO_BUILD_APP:BOOL=OFF` 的构建树仅生成 `src/libgreeting.a`，不存在 `app/hello`。
- 我能解释：`option()` 将用户选择持久化在各自的构建目录 cache 中，`if()` 决定目标是否进入构建图。
- 卡点或误解：无。
- 下一步：学习 `include()`，将可复用 CMake 配置移动到独立 `.cmake` 模块。

### 2026-07-22 — P2.6: `include()` 与选项模块

- 目标：将应用构建开关提取为可复用模块，并理解模块查找与变量可见性。
- 本课讲解：`include()` 可按明确路径加载文件，或按模块名依次搜索 `CMAKE_MODULE_PATH` 和 CMake 内置模块目录；它在调用者的普通变量作用域中执行，不等同于 `add_subdirectory()`。
- 我的问答与答案：学习者正确定位了 `include(cmake)` 误载内置 `CMake.cmake` 的原因；已纠正“未加引号参数是变量”的表述，它实际是模块名字符串。也已区分 `option()` 的默认值、已有 cache 值和 `-D` 显式覆盖。
- 我做了什么：创建 `cmake/HelloOptions.cmake` 存放 `HELLO_BUILD_APP` 选项；在顶层追加项目模块目录并以 `include(HelloOptions)` 加载。
- 证据：在已激活的 MSVC 开发环境中，使用 Ninja 分别执行 `cmake -S exercises/p0-hello -B <temp>/on -G Ninja && cmake --build <temp>/on`，运行 `<temp>/on/app/hello.exe` 成功；再执行 `cmake -S exercises/p0-hello -B <temp>/off -G Ninja -DHELLO_BUILD_APP=OFF && cmake --build <temp>/off` 成功。两份 cache 分别为 `HELLO_BUILD_APP:BOOL=ON` 与 `OFF`，OFF 构建未生成 `app/hello.exe`。
- 我能解释：项目模块目录应通过 `CMAKE_MODULE_PATH` 显式加入搜索路径；`option()` 只提供 cache 不存在时的默认值，使用者的 `-D` 选择会被保留。
- 卡点或误解：`include(cmake)` 在 Windows 上会因大小写不敏感而意外加载 CMake 内置 `CMake.cmake`，因此“未报错”不代表加载了预期模块。
- 下一步：学习 `CMakePresets.json`，将默认与关闭应用的构建入口命名为可复现的 preset。

### 2026-07-23 — P2.7: CMakePresets.json

- 目标：为默认构建和关闭应用的构建创建可复现、具名的配置与构建入口。
- 本课要点：配置 preset 保存生成器、构建目录和 cache 变量；构建 preset 通过 `configurePreset` 关联一份配置。不同配置必须使用独立的 `binaryDir`，避免 cache 和生成的构建图互相污染。
- 我做了什么：创建 `CMakePresets.json`，定义 `default` 和继承它的 `no-app` 配置 preset；分别定义同名 build preset。将 Ninja 目录加入用户级 `PATH`，并在临时加载 MSVC 开发环境后完成验证。
- 证据：`cmake --preset default`、`cmake --build --preset default` 成功，运行 `out/cmake/p0-hello/default/app/hello.exe` 输出 `Hello World from program input`；`cmake --preset no-app`、`cmake --build --preset no-app` 成功，且 `out/cmake/p0-hello/no-app/app/hello.exe` 不存在。
- 我能解释：`no-app` 设置 `HELLO_BUILD_APP=OFF`，使顶层 `if(HELLO_BUILD_APP)` 跳过 `app/`；两份 preset 不能共用构建目录，因为它们的 CMake 配置与构建产物不同。
- 卡点或误解：当前普通 PowerShell 不会自动加载 MSVC 的 `cl`；需要使用 Visual Studio Developer PowerShell，或在当前会话加载开发环境后构建。
- 下一步：学习 preset 的继承、隐藏 preset 与条件，并为 Debug/Release 等不同构建入口建模。

### 2026-07-23 — P2.8: 隐藏的基础 preset

- 目标：用隐藏 preset 提取公共配置，并通过继承链表达配置之间的共性与差异。
- 本课要点：`hidden: true` 的 preset 不能直接调用，也不会出现在 `cmake --list-presets` 中；它可不提供 `binaryDir`。可调用的 preset 必须通过自身或继承链获得有效的构建目录。
- 我做了什么：新增隐藏的 `base` preset，承载 `Ninja` generator；让 `default` 继承 `base`，让 `no-app` 继承 `default` 并仅覆盖专属构建目录与 `HELLO_BUILD_APP`。
- 证据：`cmake --list-presets` 仅显示 `default` 与 `no-app`；两份 preset 均成功重新配置与构建，Ninja 报告无额外工作。
- 我能解释：`base` 只是复用配置的模板，不能被直接配置，因此不需要 `binaryDir`；`default` 和 `no-app` 可直接作为 CMake 入口，必须各自拥有隔离的构建树。
- 卡点或误解：无。
- 下一步：学习 CMake 的条件 preset 与 `condition`，让不适用当前环境的配置入口自动隐藏。

### 2026-07-23 — P2.9: 条件 preset

- 目标：让仅适用于 Windows 的构建入口根据宿主环境自动可用或禁用。
- 本课要点：`condition` 根据环境判断可调用性；`hidden: true` 是结构上仅供继承的模板，而 condition 用于在不兼容环境中禁用本可调用的入口。
- 我做了什么：新增 `windows-default` configure/build preset，继承 `default`，提供专属 `binaryDir`，并以 `${hostSystemName} == Windows` 作为条件；删除了误加的 `HELLO_BUILD_APP=OFF` 覆盖，使其保留默认应用构建行为。
- 证据：当前 Windows 环境的 `cmake --list-presets` 显示 `windows-default`；`cmake --preset windows-default` 与 `cmake --build --preset windows-default` 成功，运行 `out/cmake/p0-hello/windows-default/app/hello.exe` 输出 `Hello World from program input`。
- 我能解释：hidden preset 不可用是因为它承担公共配置模板的职责；条件 preset 在环境不匹配时不可用，是为了避免用户选择不兼容的构建入口。
- 卡点或误解：首次创建时误将关闭应用的 cache 覆盖复制到 `windows-default`；已删除，因为它应继承默认应用构建行为。
- 下一步：为 Debug 与 Release 创建可复现的 preset，并理解单配置生成器中 `CMAKE_BUILD_TYPE` 的作用。

### 2026-07-23 — P2.10: Debug 与 Release preset

- 目标：为 Ninja 单配置生成器创建隔离、可复现的 Debug 与 Release 构建入口。
- 本课要点：Ninja 的 `CMAKE_BUILD_TYPE` 在配置阶段固定并写入 cache；不同构建类型必须使用独立的 `binaryDir`，不能在同一构建树中来回切换。
- 我做了什么：新增继承 `default` 的 `debug` 与 `release` configure/build preset；分别设置独立构建目录，并通过 `cacheVariables` 设置 `CMAKE_BUILD_TYPE` 为 `Debug` 和 `Release`。首次将该变量误放在 preset 顶层，依据 CMake 的 `Invalid extra field` 错误修正为 `cacheVariables` 成员。
- 证据：两个 preset 均成功配置、构建，且均生成 `app/hello.exe`；`out/cmake/p0-hello/debug/CMakeCache.txt` 记录 `CMAKE_BUILD_TYPE:STRING=Debug`，release 构建树记录 `CMAKE_BUILD_TYPE:STRING=Release`。
- 我能解释：`CMAKE_BUILD_TYPE` 作为 configure preset 的 cache variable 传入，等价于配置时的 `-DCMAKE_BUILD_TYPE=...`；build preset 只构建已经生成的构建树，不能改变其配置。
- 卡点或误解：无。
- 下一步：对比 Ninja 的单配置行为与 Visual Studio 等多配置生成器，并理解 `--config` 的适用场景。

### 2026-07-23 — P2.11: Visual Studio 多配置 preset

- 目标：用一棵 Visual Studio 构建树分别构建 Debug 与 Release，并与 Ninja 单配置行为对比。
- 本课要点：多配置生成器在同一构建树中为不同 configuration 生成独立规则与输出目录；build preset 的 `configuration` 等价于构建时的 `--config`。Ninja 默认只生成一套由 configure cache 固定的规则。
- 我做了什么：新增独立的 `vs-multi` configure preset，使用 `Visual Studio 18 2026` 与 `x64`；新增 `vs-debug`、`vs-release` build preset，分别设为 `Debug`、`Release`。未让其继承 Ninja preset，避免生成器冲突。
- 证据：`cmake --preset vs-multi`、`cmake --build --preset vs-debug`、`cmake --build --preset vs-release` 成功；同一构建树同时生成并运行 `app/Debug/hello.exe` 与 `app/Release/hello.exe`，均输出 `Hello World from program input`。
- 我能解释：Visual Studio 为每个 configuration 维护独立规则与子目录，因此可共享 binaryDir；Ninja 的单配置构建树只保存一套规则，重新配置 Debug/Release 会替换 cache 与构建图。
- 卡点或误解：Codex 命令环境同时包含 `PATH` 和 `Path`，使 MSBuild 启动编译器时因重复环境变量键失败；在验证命令中临时移除重复项后构建成功，preset 无需修改。
- 下一步：复盘 P2 的变量、option、模块和 preset，确认能独立为新项目设计可复现的配置入口。

### 2026-07-23 — P2: 阶段复盘通过

- 目标：确认能够独立选择变量、option、模块和 preset 的配置入口，并复现开发与发布构建。
- 我的回答：`base` 是仅供继承的隐藏模板而 `default` 是可调用入口；Ninja 的 `--config Release` 不会切换构建类型；Release 且不构建应用的 Ninja preset 可继承 `no-app`，覆盖独立 `binaryDir` 和 `CMAKE_BUILD_TYPE=Release`。
- 证据：此前已成功使用 `debug`/`release` preset 配置、构建隔离的 Ninja 构建树，且能够解释 Visual Studio 多配置的 `configuration` 与 Ninja 的 `CMAKE_BUILD_TYPE` 的不同职责。
- 我能解释：普通变量受目录/函数作用域限制，cache variable 为可持久化的配置入口；`option()` 表达布尔开关，`include()` 加载模块；preset 将生成器、构建树和 cache 配置命名为可复现入口。
- 卡点或误解：无。
- 下一步：进入 P3，学习 target usage requirements，以及 `PRIVATE`、`PUBLIC` 与 `INTERFACE` 的选择原则。

### 2026-07-25 — P3.1: 公开与私有编译定义

- 目标：按“谁需要使用该信息”选择 `target_compile_definitions` 的 `PRIVATE`、`PUBLIC` 与 `INTERFACE` 作用域。
- 本课讲解：`PUBLIC` 同时服务 target 自身与消费者；`PRIVATE` 仅服务 target 自身；`INTERFACE` 仅向消费者传播。接口库没有自身编译阶段，因而只能声明 `INTERFACE` usage requirements。
- 我的问题与答案：学习者正确预测：将库内部宏改为 `INTERFACE` 时，`greeting.cpp` 会因看不到宏而触发 `#error`；也正确说明公开宏改为 `PRIVATE` 时会使 `main.cpp` 失败。
- 我做了什么：为 `greeting` 添加 `PRIVATE` 的 `GREETING_IMPLEMENTATION=1`，并在 `greeting.cpp` 中用预处理器检查其可见性。
- 证据：在 `topics/cmake/exercises/p0-hello/` 执行 `cmake --preset debug` 与 `cmake --build --preset debug --clean-first --verbose` 成功；`greeting.cpp` 的编译命令包含 `-DGREETING_HAS_LIBRARY=1 -DGREETING_IMPLEMENTATION=1`，`main.cpp` 的编译命令仅包含 `-DGREETING_HAS_LIBRARY=1`。运行 `out/cmake/p0-hello/debug/app/hello` 输出 `Hello World from program input` 与 `text.h welcome`。
- 我能解释：编译定义的作用域取决于该信息是 target 的实现细节、公开接口要求，还是仅消费者的要求。
- 卡点或误解：首次从仓库根目录执行 preset 失败；`CMakePresets.json` 位于练习目录，需在该目录运行 `cmake --preset ...`。
- 下一步：学习 `target_compile_features`，把 C++ 语言标准要求作为可传播的 target usage requirement。

### 2026-07-25 — P3.2: 公开接口的 C++17 要求

- 目标：将公开接口使用的 C++ 语言特性作为 target usage requirement 传递给消费者。
- 本课讲解：`target_compile_features` 使用 CMake 的抽象编译特性名称表达最低语言版本；当公开头文件使用 `std::string_view` 时，`cxx_std_17` 必须为 `PUBLIC`，使库和消费者均以至少 C++17 编译。
- 我的问题与答案：学习者正确预测：若将该要求错误标为 `PRIVATE`，库可编译但包含公开头文件的 `main.cpp` 会在低于 C++17 的环境失败。
- 我做了什么：将 `Greeting::printGreeting` 改为接收 `std::string_view`，并为 `greeting` 添加 `target_compile_features(greeting PUBLIC cxx_std_17)`。
- 证据：在 `topics/cmake/exercises/p0-hello/` 执行 `cmake --preset debug` 与 `cmake --build --preset debug --verbose` 成功；`greeting.cpp` 与 `main.cpp` 的实际编译命令均包含 `-std=gnu++17`。运行 `out/cmake/p0-hello/debug/app/hello` 输出 `Hello World from program input` 与 `text.h welcome`。
- 我能解释：语言标准要求应附着在使用该特性的 target 上；公开接口中的要求必须向消费者传播。
- 卡点或误解：清理旧练习目录后，终端仍停留在已删除目录会导致 `Current working directory cannot be established`；应切换至 `topics/cmake/exercises/p0-hello/`。
- 下一步：学习 `target_compile_options`，区分编译器选项与可移植的 CMake 编译特性。

### 2026-07-25 — P3.3: target-local 编译器警告选项

- 目标：区分可移植的 `target_compile_features` 与具体编译器参数的 `target_compile_options`，并避免将库的诊断策略传播给消费者。
- 本课讲解：编译特性表达“代码需要的能力”，由 CMake 映射到当前工具链；编译选项直接传递工具链参数。`-Wall`、`-Wextra` 或 `/W4` 是库实现的质量检查策略，应保持 `PRIVATE`。
- 我的问题与答案：学习者正确说明：若将警告选项标为 `PUBLIC`，`hello` 也会收到这些参数，造成不必要的消费者编译策略污染。
- 我做了什么：按编译器分支为 `greeting` 添加私有警告选项：Apple Clang、Clang、GNU 使用 `-Wall -Wextra`，MSVC 使用 `/W4`。
- 证据：在 `topics/cmake/exercises/p0-hello/` 执行 `cmake --preset debug`、`cmake --build --preset debug --clean-first --verbose` 成功；`greeting.cpp` 编译命令包含 `-Wall -Wextra`，`main.cpp` 编译命令没有这两个参数。运行 `out/cmake/p0-hello/debug/app/hello` 成功。
- 我能解释：具体编译器选项通常属于 target 自身的构建质量策略；只有确属公开使用要求时才考虑向消费者传播。
- 卡点或误解：无。
- 下一步：学习静态库、共享库、接口库和对象库的输出与使用场景。

### 2026-07-25 — P3.4: 静态库与共享库

- 目标：理解 `STATIC` 与 `SHARED` 的链接产物、运行时依赖和 target 依赖图差异。
- 本课讲解：target 依赖使用 target 名而不依赖库类型；静态库代码在链接时并入消费者，共享库在运行时由可执行程序加载，因此部署时必须考虑动态库定位。
- 我的问题与答案：学习者正确说明：将 `greeting` 从 `STATIC` 改为 `SHARED` 后，`hello` 仍会由 `target_link_libraries` 正确链接；新增风险发生在动态库未能加载的运行阶段。
- 我做了什么：将 `greeting` 切换为 `SHARED`，并观察生成的动态库。
- 证据：在 `topics/cmake/exercises/p0-hello/` 执行 `cmake --preset debug` 与 `cmake --build --preset debug --clean-first` 成功，生成 `out/cmake/p0-hello/debug/src/libgreeting.dylib`。`otool -L out/cmake/p0-hello/debug/app/hello` 显示 `@rpath/libgreeting.dylib`，运行程序输出 `Hello World from program input` 与 `text.h welcome`。
- 我能解释：库类型改变的是产物和运行时分发模型；`PUBLIC`/`PRIVATE` usage requirements 与 target 链接关系不因静态或共享库而改变。
- 卡点或误解：从静态库切换后，旧 `libgreeting.a` 不再属于当前构建图却仍留在构建目录；已删除该可再生产物，避免误判当前库类型。
- 下一步：学习 header-only 接口库与对象库，并比较它们为何不等同于静态或共享库。

### 2026-07-25 — P3.5: 独立 header-only 接口库

- 目标：让 `INTERFACE` target 传播独有的 header-only 使用要求，而非重复已有库的 include 路径。
- 本课讲解：接口库不编译 `.cpp` 或产出传统库文件；它可将自己的公开 include 路径、编译特性、定义或依赖传递给消费者。target 若不提供独有构建信息，就只是多余的抽象。
- 我的问题与答案：学习者起初预测删除 `greeting_headers` 会导致找不到原 `greeting/text.h`；已澄清该路径此前也由 `greeting` 的 `PUBLIC` include 路径提供，因此接口库当时没有实际贡献。
- 我做了什么：将 header-only 代码移至 `header_only/include/greeting_text/text.h`，使 `greeting_headers` 以 `INTERFACE` 传播独有的 `header_only/include` 路径；`hello` 同时包含 `<greeting/greeting.h>` 与 `<greeting_text/text.h>`。
- 证据：在 `topics/cmake/exercises/p0-hello/` 执行 `cmake --preset debug`、`cmake --build --preset debug --verbose` 成功；`main.cpp` 编译命令同时包含项目 `include` 与 `header_only/include`，随后运行 `out/cmake/p0-hello/debug/app/hello` 输出 `Hello World from program input` 与 `text.h welcome`。
- 我能解释：`greeting` 负责提供有编译实现的 API；`greeting_headers` 负责提供独立 header-only API 的使用要求。消费者链接两个 target，分别获得两套接口。
- 卡点或误解：移动头文件时一度遗漏 `<greeting/greeting.h>`，导致 `Greeting` 未声明；恢复两个 include 后构建通过。已移除新目录中的 `.DS_Store` 元数据文件。
- 下一步：学习对象库（`OBJECT`）如何复用编译后的对象文件，以及它为何不同于链接库。

### 2026-07-25 — P3.6: 对象库复用

- 目标：理解 `OBJECT` 库复用对象文件的方式，并将同一份源码组装为静态库与共享库。
- 本课讲解：对象库编译源码却不生成传统库文件；`$<TARGET_OBJECTS:...>` 取用已经编译的对象文件。将对象库用于共享库时，需要位置无关代码。
- 我的问题与答案：学习者正确说明：若静态库和共享库各自直接列出同一个 `.cpp`，源码会编译两次；对象库消除的是该重复编译步骤。
- 我做了什么：创建独立的 `p3-object-library` 练习，定义 `message_objects`、`message_static` 与 `message_shared`，并为对象库设置 `POSITION_INDEPENDENT_CODE ON`。
- 证据：`cmake -S topics/cmake/exercises/p3-object-library -B out/cmake/p3-object-library -G Ninja` 与 `cmake --build out/cmake/p3-object-library --clean-first --verbose` 成功；`message.cpp` 仅编译为一次 `message.cpp.o`，随后分别生成 `libmessage_static.a` 和 `libmessage_shared.dylib`。
- 我能解释：对象库是编译结果的复用节点，而静态库/共享库是将对象文件打包或链接后的最终库产物。
- 卡点或误解：无。
- 下一步：复盘 P3 的 usage requirements 与库类型选择，并决定是否需要在当前 `greeting` 项目中采用对象库结构。

### 2026-07-25 — P3: 阶段复盘通过

- 目标：确认能独立选择 target usage requirements 与库 target 类型。
- 我的回答：公开头文件使用的语言标准应为 `PUBLIC` compile feature，库实现的跟踪宏应为 `PRIVATE` compile definition；header-only 日志库应使用 `INTERFACE` target 与 `INTERFACE` include 路径；要同时生成静态库和共享库并避免重复编译时，应让对象库编译源码一次，再以 `$<TARGET_OBJECTS:math_objects>` 组装两个最终库。
- 反馈：三项判断均正确。术语微调：最终静态库与共享库通常把对象库产物作为 sources 使用，而不是以普通依赖库的方式链接对象库。
- 证据：此前已验证编译定义、C++17 编译特性、私有警告选项、共享库运行时依赖、独立接口库和对象库的构建行为；本次三项复盘回答正确。
- 我能解释：使用要求的作用域由“当前 target、消费者、或两者谁需要”决定；库类型由产物、运行时分发与对象复用需求决定。
- 卡点或误解：无阻塞；注意对象库不直接代表传统链接库。
- 下一步：进入 P4，学习系统能力探测、生成文件与 CTest。

### 2026-07-31 — P4.1: 系统能力探测与配置头文件

- 目标：在配置阶段探测可选系统能力，并把探测结果安全地交给 C++ 源码。
- 本课讲解：`check_include_file_cxx()` 只检查头文件可用性；`check_cxx_source_compiles()` 编译一段最小源码，因此可确认 `getpid()` 在当前项目配置中实际可用。`configure_file()` 从模板生成随环境变化的配置头文件。
- 我的问题与答案：学习者正确说明：当 `unistd.h` 或 `getpid()` 不可用时，对应宏不会定义/为 0；受条件编译保护的代码会在预处理阶段被排除，而不是等到链接阶段失败。
- 我做了什么：增加 `HAVE_UNISTD_H` 与 `HAVE_GETPID` 探测；由 `greeting_config.h.in` 生成 `generated/greeting_config.h`，并在 `greeting.cpp` 中以该配置决定是否调用 `getpid()`。
- 证据：`cmake --preset default` 成功；生成文件位于 `out/cmake/p0-hello/default/src/generated/greeting_config.h`，当前构建与运行均可通过。
- 我能解释：配置结果属于当前构建树，而非跨机器共享的固定结论；配置头文件让 C++ 编译看到 CMake 已探测到的能力。
- 卡点或误解：最初区分了“检查头文件存在”与“编译最小调用验证函数可用”的粒度差异。
- 下一步：将生成文件作为构建图的显式输入，并验证增量更新。

### 2026-07-31 — P4.2: 自定义命令、生成文件与 IPO 回退

- 目标：让自定义生成的头文件在依赖变化时可靠地参与构建，并按工具链能力启用 IPO。
- 本课讲解：`add_custom_command(OUTPUT ...)` 声明生成文件和依赖；将输出加入 `target_sources()` 后，CMake 才能把生成、重新编译与重新链接串进构建图。`check_ipo_supported()` 应在创建使用它的 target 前探测，而 `set_property(TARGET ...)` 必须在 `add_library(greeting ...)` 后执行。
- 我的问题与答案：学习者正确说明：先探测可避免编译失败；探测结果只影响本机构建配置；target 需要先被声明，才可设置其 property。
- 我做了什么：由 `greeting_banner.h.in` 通过 `copy_if_different` 生成 `generated/greeting_banner.h`；使用 `CheckIPOSupported` 探测后，仅在支持时给 `greeting` 设置 `INTERPROCEDURAL_OPTIMIZATION TRUE`，不支持时输出诊断并正常回退。
- 证据：`cmake --preset default` 显示 `GREETING_IPO_SUPPORTED=NO`，当前 MinGW 的 LTO 测试报 `LTO support has not been enabled in this configuration`；主项目仍可 `cmake --build --preset default` 成功。
- 我能解释：生成文件若未声明为 target 输入，构建器无法知道何时必须先生成它；能力探测的结果与 target 属性设置分别发生在配置阶段的不同正确时机。
- 卡点或误解：曾把 `include(CheckIPOSupported)` 放在 `check_ipo_supported()` 之后，导致命令未知；已修正为先 include、后调用。
- 下一步：为可执行产物注册 CTest，并辨析测试失败是项目行为还是进程环境问题。

### 2026-07-31 — P4.3: CTest、共享库运行时与测试环境

- 目标：注册并运行最小 smoke test，定位共享库程序在 Windows 下的运行时依赖。
- 本课讲解：`enable_testing()` 开启测试；`add_test(NAME ... COMMAND ...)` 注册实际二进制命令；CTest 对进程退出码和输出断言负责，不替代单元测试框架。Windows 的共享库 DLL 需要在可执行文件同目录或系统搜索路径中可见。
- 我的问题与答案：学习者正确说明：CTest 执行实际编译后的二进制产物；测试通过来自程序返回 0 与预期输出，而不是 CMake 自身“编译成功”。
- 我做了什么：注册 `hello_smoke` 并用 `PASS_REGULAR_EXPRESSION` 断言输出；为 `hello` 添加 POST_BUILD 复制，使 `libgreeting.dll` 位于 `hello.exe` 同目录。
- 证据：`ctest --test-dir out/cmake/p0-hello/default --output-on-failure` 在未设置 MinGW 运行时路径时以 `0xC0000135` 失败；把 `C:\Users\Qs\CLion 2025.3.3\bin\mingw\bin` 加到 PATH 后，测试通过 `1/1`。当前复验同样通过。
- 我能解释：`libgreeting.dll` 的部署正确并不保证进程所有依赖都可加载；CTest 是否通过也取决于它启动进程时继承的环境。
- 卡点或误解：原计划的 `HELLO_BUILD_APP=OFF` 边界 CTest 因本机 Ninja PATH 问题跳过，P4 暂不按阶段完成标记。
- 下一步：把库产物与公开头文件安装到一个独立前缀。

### 2026-08-01 — P5.1: 安装规则与可移动的使用接口

- 目标：把共享库、导入库和两套公开头文件安装到独立前缀，并使将来导出的 target 不泄漏源码绝对路径。
- 本课讲解：`install(TARGETS ...)` 按产物类型安装：Windows DLL 为 `RUNTIME`，导入库为 `ARCHIVE`，Unix 共享库为 `LIBRARY`；`install(DIRECTORY ...)` 复制公开头文件目录内容。`BUILD_INTERFACE` 与 `INSTALL_INTERFACE` 让同一 target 在源码树与安装树中使用不同 include 路径。
- 我的问题与答案：学习者正确判断 DLL 安装到 `bin`、导入库安装到 `lib`、两套公开头文件安装到 `<prefix>/include`；也正确说明安装接口的相对路径可随前缀移动，而源码绝对路径不可。
- 我做了什么：安装 `greeting` 到 `bin`/`lib`，把 `include/` 与 `header_only/include/` 的内容安装到同一 `include` 目录；为 `greeting` 和 `greeting_headers` 分别使用 `$<BUILD_INTERFACE:...>` 与 `$<INSTALL_INTERFACE:include>`。
- 证据：`cmake --install C:\Users\Qs\Documents\Cmake-learn\out\cmake\p0-hello\default --prefix C:\Users\Qs\Documents\Cmake-learn\out\cmake\p0-hello\install` 成功；安装树含 `bin/libgreeting.dll`、`lib/libgreeting.dll.a`、`include/greeting/greeting.h`、`include/greeting_text/text.h`。
- 我能解释：源码内部的 `header_only/include` 不应成为消费者 include 路径；安装接口应表达安装前缀下稳定且可迁移的布局。
- 卡点或误解：首次从练习目录执行相对 `cmake --install out/...`，路径被解析到源码目录内；改用仓库根目录相对路径或绝对路径后成功。
- 下一步：将 `greeting` 与 `greeting_headers` 导出为 targets 文件，生成包配置文件，并用独立 consumer 通过 `find_package()` 验证；P5 尚未完成。
