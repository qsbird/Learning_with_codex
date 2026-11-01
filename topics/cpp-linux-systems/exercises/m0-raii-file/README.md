# M0：文件资源 RAII 学习与后续独立变体

课次：`cpp-linux-systems.M0`。准备日期：2026-10-31。

**本节环境：macOS 本机，C++20。** 目标是资源所有权与释放，不涉及 Linux 专属系统调用。`file_api` 只使用 `<cstdio>` 的临时文件接口；Linux 复验另记证据。生成的构建文件在仓库的 `out/cpp-linux-systems/m0/` 下，临时文件由系统创建和关闭删除。

这是基线诊断，正式开始前先确认目标概念是否熟悉。未学过的部分先讲解，再按实际帮助安排实践；不把陌生概念当作失败。下面的计时任务尚未因脚手架准备而自动开始。

## 当前阶段：M0.1 作用域释放实践

2026-10-31 学习者明确表示不熟悉 RAII，11-01 已确认读完 [M0.1 材料](../../learning/materials/cpp-linux-systems.M0.1.md)，并完成析构顺序与裸指针生命周期讨论。现在按 [M0.1 实践说明](M0.1-task.md) 只填写构造/析构两个函数体；接口和四项行为检查已准备。`scope_trace.cpp` 是教练示例，目标函数体仍为 TODO；`tests.cpp` 保留给后续综合变体。

下面完整行为契约留给后续综合独立变体使用，**不是当前 M0.1 的编码任务**。移动构造、移动赋值、自移动等要求在相关概念确认或教学后才安排。先前拟定的学习前独立基线没有启动，不记失败；未来无 AI 变体与有帮助的教学实践分别记录。

## 边界与目标

正式开始后，预留 90 分钟独立完成 `file_owner.h`、`file_owner.cpp` 和 `tests.cpp`。记录实际用时、停下的位置、查阅资料与卡点。首版不使用 AI 生成实现或测试；可查语言/API 参考，先不看同类 RAII 封装的完整解法。需要帮助时保留当前版本，我们再安排有提示的学习。

设计 `m0::FileOwner`，接收 `file_api::open()` 返回的句柄并接管它的释放责任。公开接口和私有状态由你决定。需要的行为：

- 持有有效文件，离开作用域后资源恰好释放一次。
- 拥有单一释放责任，禁止拷贝；支持移动构造、移动赋值。
- 移动到已有资源的对象后，旧资源得到正确处理；自移动仍保持有效、不重复释放。
- 获取失败时处理空句柄；可选择空对象或报告错误，写明约定。
- 提前 `return`，以及异常被外层捕获后，不留下活动资源。

本次练习自己实现资源所有权和特殊成员函数，不用 `unique_ptr`、`shared_ptr` 或另一个现成 RAII 类型代替核心实现。

## 已提供的辅助接口

`support/` 是教练准备，当前练习只使用它的接口：

| 接口 | 输入与输出 |
|---|---|
| `file_api::Handle` | `std::FILE*`，空句柄为 `nullptr` |
| `file_api::open()` | 创建真实临时文件，返回句柄，失败为 `nullptr` |
| `file_api::open(true)` | 模拟获取失败，返回 `nullptr`，不创建文件 |
| `file_api::close(handle)` | 关闭文件，并记录释放次数与无效释放 |
| `file_api::stats()` | 返回本进程累计的 `opened`、`closed`、`invalid_closes`、`close_errors`、当前 `live` 数量 |

所有资源通过这对 `open/close` 管理。不要在目标代码里直接调用 `std::fclose`，否则计数无法观察释放。计数器只用于单线程检查；统计是累计值，每个场景比较前后差值。`close(nullptr)` 也计入无效释放。

临时文件创建失败可能是机器环境问题。先确认 `m0.environment` 通过，再评价学习者实现。`m0.environment` 手动打开和关闭文件，只验证辅助接口和构建环境，不包含目标类的答案。

## 独立检查与解释

由你设计最小测试证明上面的行为：正常作用域、移动构造、移动赋值至已有资源的对象、自移动、获取失败、提前返回、被外层捕获的异常。结合统计值和必要的编译期检查验证，不只打印成功。最后应无新增无效释放/关闭错误，活动资源回到场景开始时的数量。

保留一个你自己发现或制造的失败，再记录修复前后结果。脚手架自带的占位失败属于教练准备，不计作你的故障验证。

结束后说明：谁拥有资源，移动后谁负责释放，为什么提前返回与异常路径不会泄漏。通过命令还需要这份本人解释才能完成课次。

## 命令（从仓库根目录运行）

```sh
cmake -S topics/cpp-linux-systems/exercises/m0-raii-file -B out/cpp-linux-systems/m0/macos -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build out/cpp-linux-systems/m0/macos
ctest --test-dir out/cpp-linux-systems/m0/macos --output-on-failure
```

初始预期：`m0.environment` 通过；`m0.raii` 因未实现而失败。修改目标实现与测试后才评价基线结果。

ASan 和 UBSan 用独立目录；正式实践验证时再使用：

```sh
cmake -S topics/cpp-linux-systems/exercises/m0-raii-file -B out/cpp-linux-systems/m0/macos-asan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DM0_SANITIZER=address
cmake --build out/cpp-linux-systems/m0/macos-asan
ctest --test-dir out/cpp-linux-systems/m0/macos-asan --output-on-failure
cmake -S topics/cpp-linux-systems/exercises/m0-raii-file -B out/cpp-linux-systems/m0/macos-ubsan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DM0_SANITIZER=undefined
cmake --build out/cpp-linux-systems/m0/macos-ubsan
ctest --test-dir out/cpp-linux-systems/m0/macos-ubsan --output-on-failure
```

本辅助层的重复释放检查和 sanitizer 各有作用；sanitizer 无报错不单独证明文件已关闭。

## 复盘资料

这些是教练备课与基线后复盘的来源；本次尚未要求先阅读完整 RAII 解法：

- `cpp-core-guidelines`：[R.1 资源管理、C.21 特殊成员函数](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-raii)。
- `cpp-cstdio`：[标准库 `<cstdio>` 文件接口](https://eel.is/c++draft/c.files)。在线工作草案不是冻结的 C++20 正文；本课仅使用已有文件接口。
- `clang-asan`：[AddressSanitizer 用法](https://clang.llvm.org/docs/AddressSanitizer.html)。
- `clang-ubsan`：[UndefinedBehaviorSanitizer 用法](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)。
