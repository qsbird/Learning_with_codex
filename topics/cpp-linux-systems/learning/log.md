# C++ Linux Systems 学习日志

完成一个有证据的练习后追加一项。规划、阅读或脚手架准备不标记为课程完成。

```md
### YYYY-MM-DD — M<N>.<N>: <主题>

- 目标：
- 新知识讲解：
- 理解检查：
- 我独立完成了什么：
- AI/提示使用位置：
- 证据：`<配置、构建、测试、sanitizer 或 benchmark 命令>` => <结果>
- 我能解释：
- 卡点或误解：
- 下一步：
```

## 初始记录

### 2026-09-16 — 路线准备：建立 C++ Linux Systems 主题

- 目标：把 2026-09-14 的职业画像和年度路线转换为仓库内可执行、可验证的主题计划。
- 已完成：建立主题说明、学习档案、里程碑路线、日志格式，并将跨主题时间线放入共享年度计划。
- 当前状态：所有本主题里程碑均未开始；先完成年度计划中的 C0 仓库收口，再进行 M0 无 AI 基线。
- 证据：`topics/cpp-linux-systems/` 与 `learning/cpp-career-plan-2026-2027.md` 可审查；尚未执行本主题代码练习。
- 下一步：在 C0 达标后为 M0 准备最小 RAII 资源包装练习脚手架。

### 2026-10-03 — 计划核对：撤下 LLM 前置条件，保留 C++ 工程收口门槛

- Entry ID: cpp-linux-systems.plan.2026-10-03
- 依据：学习者明确停止 LLM；核对 CMake、Qt 与本主题日志和现有源码。
- 决定：M0 不再依赖 llm.M3.4；该项是学习范围调整，不等价于 LLM 完成。
- 当前进度：M0～M6 均未完成；尚无无 AI RAII 基线、具名 Linux 环境和本主题练习验证记录。
- 保留门槛：cmake.P4.4、cmake.P5.2、qt.P4.3 的收口证据。C0 原定 09-27 尚未通过，近期顺序与 10-11 复查窗口见共享年度计划。
- 下一步：现有 CMake/Qt 收口后准备 M0，先取得 90 分钟独立编码、测试和解释证据，再推进所有权与智能指针。
- 验证范围：记录和源码审查，未执行新课程或把计划准备计作学习完成。

### 2026-10-17 — 按停课决定撤下 CMake P5.2 前置条件

- Entry ID: cpp-linux-systems.plan.2026-10-17
- 依据：学习者停止 CMake 与 LLM 课程；CMake P5.2 尚未完成，不能继续作为自动恢复的必修门槛。
- 调整：M0 保留已完成的 cmake.P4.4 与待收口的 qt.P4.3 前置条件，移除 cmake.P5.2；LLM 继续不作为前置条件。对应年度 C0 同步缩小范围。
- 当前状态：M0 尚未开始，无新增独立编码或工具链证据。今天恢复 Qt P4.3 的通知范围解释；该课达到出口后再准备 M0 的 90 分钟无 AI RAII 基线与具名 Linux 环境。
- 验证范围：仅调整计划和记录，不将撤下课程要求计作能力达标。


### 2026-10-31 — 按课选择 macOS 与 Linux 开发环境

- Entry ID: cpp-linux-systems.platform-plan.2026-10-31
- Lesson ID: cpp-linux-systems.M0（环境与学习计划，非完成证据）
- 学习者决定：先选择本机 Colima，了解 macOS 与 Linux 差异后明确要求“当章节中出现mac和linux可能有差异的地方时，提醒我切换环境；如果完全一致，就在mac本机开发”。
- 安排：默认使用 Mac 本机；每节备课核对与目标有关的语义、接口、工具和验收行为。已知相关差异或查证后仍无法确认一致时，练习前说明原因、提醒切换，并准备验证 Linux 环境；不凭相似命令推断平台行为相同。
- M0 调整：先在 macOS 进行可移植文件资源 RAII 的独立编码、测试和解释，先检查本机工具链。Linux 环境与 GDB/perf 等专属工具检查移至首次相关练习前；撤销先前会话中“通用 M0 编码必须先启动/验证 Linux”的安排，不降低后续 Linux 课和年度 C1/C2 的实际平台证据要求。
- 课程安排：M0/M1 通用部分默认 Mac；M2 Linux 资源与诊断用 Linux；M3 通用并发按小课核对；M4 的 epoll、M5 的 Linux 性能分析用 Linux，其他部分按本课接口和工具决定。跨环境构建目录及验证结果分别记录，不跨平台直接比较性能数字。
- 教练已做：将规则写入主题 AGENTS、README、路线、档案、年度计划和会话；没有代写 RAII 解法、启动 Colima 或记录学习者掌握。
- 环境观察：此前只读检查得到 Colima 0.10.1，default 在沙箱列表中显示 Broken；尚未权限充分诊断、启动、重建或删除，Linux 可用性仍待验证，保留已有实例和数据。
- 下一步：准备 Mac 本机 M0 独立基线的非目标脚手架与工具检查，必要时先诊断未有证据的前置概念；编码目标仍交给学习者。M0 保持 planned，课程未完成。


### 2026-10-31 — M0: Mac 本机独立基线脚手架已准备

- Entry ID: cpp-linux-systems.M0.scaffold.2026-10-31
- Lesson ID: cpp-linux-systems.M0
- 本节环境：macOS / Darwin 25.6.0 arm64，Apple Clang 21.0.0 (clang-2100.1.1.101)，CMake 4.3.0，Ninja 1.13.2，LLDB 2100.0.17.203（仅查询版本，未做调试运行）。C++20，Debug。未启动 Colima，Linux 尚未验证。
- 教练准备：exercises/m0-raii-file，独立 CMake/CTest 入口，support/file_api 创建真实 stdio 临时文件并统计打开、关闭、无效关闭、关闭错误与活动资源；support/fixture_check 仅手动调用接口验证环境。目标 file_owner.h/.cpp 仍为空类与 TODO，tests.cpp 仍为返回 1 的占位程序，未代写 RAII 或目标测试。临时文件由标准库管理，不写入源目录。
- 来源：重查 Core Guidelines R.1/特殊成员函数入口、标准库 cstdio 草案、Clang ASan/UBSan 说明并登记 checked_at。基线前不要求阅读完整 RAII 实现；若诊断发现陌生概念则先教学并记录实际帮助。
- 普通基线（仓库根目录）：`cmake -S topics/cpp-linux-systems/exercises/m0-raii-file -B out/cpp-linux-systems/m0/macos -G Ninja -DCMAKE_BUILD_TYPE=Debug -DM0_SANITIZER=none`、`cmake --build out/cpp-linux-systems/m0/macos` 均返回 0；`ctest --test-dir out/cpp-linux-systems/m0/macos --output-on-failure` 返回 8，m0.environment 通过，m0.raii 按空目标预期失败。这不是学习者的故障制造或代码完成证据。
- Sanitizer 环境：在 macos-asan、macos-ubsan 独立构建目录分别用 M0_SANITIZER=address/undefined 配置、构建 m0_fixture_check，再用 CTest 仅运行 m0.environment，全部返回 0。只证明辅助程序在本机相应配置下可构建运行；未注入内存错误/UB 验证检测器，尚未测试学习者目标。
- 交付准备：README.md 写明正式 90 分钟基线的行为、辅助 API 和验证方式；准备不等于开始计时。接口和存储设计、释放责任、移动策略及独立测试均留给学习者。
- 当前问题：用自己的话说明 RAII 如何处理函数提前 return，以及异常被调用者捕获时的资源释放；不确定可直接说明。先收集已有知识，再决定进入独立基线或先讲解；本轮尚未收集实际答案。
- 状态：prepared，非完成、非独立编码证据，不创建完成提交。Qt 通知11-01/模型契约11-07复习保持。此前已有跨主题工作保留，main 与已获取 upstream 为 0/0。


### 2026-10-31 — M0.1: RAII 不熟悉，先进入阅读教学

- Entry ID: cpp-linux-systems.M0.1.reading-start.2026-10-31
- Lesson ID: cpp-linux-systems.M0.1
- 诊断问题：RAII 怎样保证中途 return 或抛出的异常被调用者捕获时释放已取得资源？学习者实际回复“不熟悉”。仅记自报和教学选择，不推断其他 C++ 知识，不标为独立基线失败或已理解。
- 调整：原 M0 90 分钟独立基线未开始，先拆出 M0.1：RAII 与作用域资源释放。按阅读→讨论→本人实践推进；复制、移动等后续知识再诊断/教学，日后用不同条件做独立变体。M0 阶段目标未撤销，M0.1 不代表整个 M0 完成。
- 材料：learning/materials/cpp-linux-systems.M0.1.md，约 8～12 分钟；解释资源与释放责任、局部对象构造/析构、三条退出路径、逆序析构、标准文件流示例和边界。已交付阅读，等待学习者确认阅读完成或提出疑问，位置与耗时未知。本轮没有下发概念测验或编码任务。
- 示例与帮助：ScopeTrace 只打印对象生命周期日志，std::ofstream 片段使用标准库现成管理类型；未实现目标 FileOwner，未编写其目标测试。资料与示例交付不作为独立掌握证据。
- 来源：核对 Core Guidelines R.1，以及 C++ 工作草案 stmt.dcl/class.dtor/except.ctor/filebuf.cons/except.terminate，并登记 sources。使用 C++20 已有规则，不将滚动草案新增内容当作当前编译器能力。
- 教练演示验证（macOS，本日工具链）：`cmake --build out/cpp-linux-systems/m0/macos --target m0_scope_demo` 返回 0；`out/cpp-linux-systems/m0/macos/m0_scope_demo` 返回 0。普通路径输出 enter outer、enter inner、body、leave inner、after inner、leave outer；return 路径先 enter outer/inner，再 leave inner/outer；异常路径先 enter outer/inner，再 leave inner/outer，最后 caught: demo。仅验证教练示例，不重测未修改的文件辅助层。
- 下一步：等待阅读确认；先答疑，再讨论一个目标场景，理解后安排单一作用域文件实践。RAII 能力仍 unknown，材料交付不升级为 explained；课程未完成，不创建完成提交。环境仍 macOS，不启动 Colima。


### 2026-11-01 — M0.1: 阅读确认，进入概念讨论

- Entry ID: cpp-linux-systems.M0.1.reading-confirmed.2026-11-01
- Lesson ID: cpp-linux-systems.M0.1
- 学习者原话：“阅读完成，可以接续”。确认 learning/materials/cpp-linux-systems.M0.1.md 已读完，实际耗时未知；阅读确认不作为理解或独立实践证据。
- 每日核对：当前 11-01，年度 10-31～11-06 窗口继续 M0.1 的阅读、讨论、实践；不因进入 11 月跳到 M1。C0 课次前置完成证据保持，main 与已获取 upstream 引用 0/0、无冲突；已有学习记录和跨主题改动保留。Qt 通知短复习今日到期、模型契约11-07复习保持，均不冒记为完成，先接续当前 RAII 会话。
- 当前源码：FileOwner 与目标测试仍为空。没有重跑昨天的环境检查或把其成功当作今天新机器验证，环境选择继续 macOS，本轮只做概念讨论。
- 本轮问题：已在材料定义的 ScopeTrace 对象 A、B 在嵌套代码块内构造，随后 return 离开整个函数；判断 enter/leave 的输出顺序和末尾 end 是否执行。等待实际答案后再决定下一步；尚无概念理解证据，RAII 能力保持 unknown。


### 2026-11-01 — M0.1: 提前返回的析构顺序预测

- Entry ID: cpp-linux-systems.M0.1.nested-return-answer.2026-11-01
- Lesson ID: cpp-linux-systems.M0.1
- 学习者最终回答：enter A、enter B、leave B、leave A；end 不会出现。
- 过程：第一条回答将 leave A 放在 leave B 前，随后学习者在教练尚未反馈或提示前主动修正为 B 先析构。保留自我纠正过程，不把最终正确顺序记为教练提示后的结果。
- 评估：提前 return 不跳过已成功构造的局部对象析构，逆序析构及跳过后续 end 的预测正确（explanation assistance: none）。这是阅读后的控制流理解检查，未构成文件资源管理实践。
- 教练反馈：后构造的 B 先析构，再析构 A。下一步用普通 std::FILE* 局部变量作对照，检查能否区分变量自身生命结束与文件关闭责任；等待实际答案后再评估 RAII 理解。


### 2026-11-01 — M0.1: 裸指针变量与文件流生命周期的区分

- Entry ID: cpp-linux-systems.M0.1.raw-handle-clarification.2026-11-01
- Lesson ID: cpp-linux-systems.M0.1
- 学习者回答：不确定；认为 std::FILE* 是指针，指针变量销毁不影响所指内容，文件很可能仍打开；同时怀疑 FILE 自身销毁可能关闭文件，并指出那不是指针变量能承担的操作。
- 评估：已抓住指针变量不承担所指资源清理这一关键区别，但对是否取决于 FILE 内部实现仍有疑问。本次回答未事先追加提示，记录为部分理解，不能据此认定已完全解释 RAII 释放责任。
- 教练澄清：题设下指针变量离开作用域不销毁其指向的文件流，也不会自动调用 fclose。没有其他拥有者或关闭代码时文件仍打开；此结论不依赖 FILE 的内部表示。资源拥有者需要明确调用关闭接口；在本课辅助层中通过 file_api::close 观察实际释放。
- 教学方式：换成两个普通指针指向同一流的具体对照，确认指针变量与被管理资源的生命周期不是同一件事。下一问：成功打开后 a 保存句柄，内层块的 b 复制 a 的指针值；内层块结束时会因 b 离开作用域而关闭文件吗？
- 证据边界：本轮澄清已给出原问题答案，相关解释为教练帮助，不新增独立掌握或目标实践。未运行泄漏程序、未修改 FileOwner。等待下一真实回答再安排有界实践。


### 2026-11-01 — M0.1: 指针对照确认，进入作用域释放实践

- Entry ID: cpp-linux-systems.M0.1.scope-practice-start.2026-11-01
- Lesson ID: cpp-linux-systems.M0.1
- 学习者原话：“显然不会”，回答普通指针 b 复制 a 的句柄值后，b 离开内层作用域是否自动关闭文件。
- 评估：正确，属于前轮澄清后的理解检查（explanation assistance: hint）。结合此前逆序析构预测与关于指针不承担资源清理的本人解释，结束文字题循环，进入有界实践；不以此宣称独立代码能力。
- 脚手架：教练提供 FileOwner 构造/析构声明、空句柄成员 handle_、禁止复制的声明；只留 file_owner.cpp 两个函数体 TODO。补充接口含义：file_api::Handle 等同 std::FILE*，nullptr 为空；file_api::close 实际关闭并计数。explicit 用于避免隐式转换；= delete 禁止复制，避免重复释放责任。本课不实现移动。
- 教练检查程序：check_scope.cpp / m0_scope_check，四项 CTest 覆盖 normal、return、exception、empty；观察拥有期间保持打开、离开后关闭计数、无无效关闭、活动资源归零。检查与接口由教练提供，不计学习者设计或实践证据；目标构造与析构逻辑未代写，tests.cpp 后续综合占位仍保留。
- 本日验证（现有 macOS 构建树）：`cmake --build out/cpp-linux-systems/m0/macos --target m0_scope_check` 返回 0（handle_ 未使用警告符合空实现）；`ctest --test-dir out/cpp-linux-systems/m0/macos -R '^m0.scope[.]' --output-on-failure` 返回 8。normal/return/exception 均 opened=1、closed=0、live=1，按预期失败；empty 通过，符合两个目标函数体为空。未重跑未改的辅助 smoke 或完整 sanitizer 测试。
- 下发任务：按 exercises/m0-raii-file/M0.1-task.md，只实现构造时保存并接管句柄、析构时释放有效文件且空对象不关闭。目标四项通过，再由本人解释资源关闭与析构的联系。这是教学实践，非原 90 分钟独立基线。
- 当前：实践已下发，等待学习者真实修改；本课未完成，不创建完成提交。环境 macOS，Qt 到期复习未冒记为完成。


### 2026-11-01 — M0.1: 定位关闭接口的编译错误

- Entry ID: cpp-linux-systems.M0.1.compile-api-debug.2026-11-01
- Lesson ID: cpp-linux-systems.M0.1
- 学习者请求调查本人实现的问题。源码：构造函数已写 handle_ = handle；析构函数写 handle_.close()，两处还保留 return。
- 复现：`cmake --build out/cpp-linux-systems/m0/macos --target m0_scope_check` 返回 1。file_owner.cpp:13 编译器报告 Handle（__sFILE*）为指针，以及 __sFILE 没有 close 成员，Ninja 停止；尚未产生可用于当前修改的运行结果。
- 原因：混淆对象成员方法与辅助层命名空间函数。Handle 是 std::FILE*，file_api::close 接收句柄参数。仅将点换成箭头不能提供 FILE 本身不存在的成员函数。
- 指导：构造函数保存句柄这一处符合目标；析构应先区分空/有效句柄，再通过 file_api 的 close 函数传入有效句柄。空句柄不调用关闭接口，以满足 empty 检查。未代写或修改学习者目标代码。
- 调试方式：已读 clion-debugger 技能并先做静态/构建分诊；实际问题是编译错误，运行时调试前提未满足，因此未启动调试会话或添加断点，不宣称取得运行时证据。
- 状态：等待学习者修正析构调用方式与空句柄边界后重建，随后运行四项 m0.scope 检查。课程未完成，未将构造赋值或构建失败记为完整实践成功。


### 2026-11-01 — M0.1: 移除错误 delete 后四项检查通过

- Entry ID: cpp-linux-systems.M0.1.scope-check-passed.2026-11-01
- Lesson ID: cpp-linux-systems.M0.1
- 本轮起始实现：构造保存 handle_；析构判空后先 file_api::close(handle_)，随后 delete handle_。构建通过，但普通 m0.scope.normal 运行以 Subprocess aborted 中止（CTest 返回8）。
- 调查：辅助层 file_api::close 内部已调用 std::fclose 关闭文件流；额外 delete 与 tmpfile 的资源获取方式不配对，并在 fclose 后再次错误释放。已说明“文件获取/关闭接口配对；delete 应与 new 配对”。未修改学习者源码。
- IDE 尝试：CLion router 状态起初无会话，已有运行配置仅 hello/greeting/所有CTest。按测试 main 文件启动失败，报告 Process not started / probably build process failed；没有取得 debugger 栈或变量，也没有设置/修改断点。转用 ASan 构建作替代运行验证。
- 并发编辑观察：在 ASan 构建前后检查到最新源码已移除 delete。故此次 ASan 正常结果属于修正后版本，不能作为错误 delete 版本的 ASan 报错证据；原问题的动态证据限于普通构建中止。
- 最新本人实现：构造 handle_ = handle；析构仅在非空时调用 file_api::close(handle_)。构造/析构末尾 return 和原 TODO 注释不影响本课行为。目标修改由学习者完成；关闭接口及错误 delete 的定位受教练指导，practice assistance: hint，不宣称从零独立实现。
- 验证：普通 `cmake --build out/cpp-linux-systems/m0/macos --target m0_scope_check` 返回0；`ctest --test-dir out/cpp-linux-systems/m0/macos -R '^m0.scope[.]' --output-on-failure` 返回0，normal/return/exception/empty 四项全通过。
- ASan：`cmake --build out/cpp-linux-systems/m0/macos-asan --target m0_scope_check` 返回0；同目录 CTest 用相同正则四项全部通过、返回0。仅证明这些用例无 ASan 报告，不扩大为所有资源/平台验证；验证结束后重新读取源文件仍为不含 delete 的正确版本。
- 下一步：进入反思/独立迁移：外层和内层各自管理一个不同的文件，内层代码块结束、外层未结束时，几个文件仍打开，为什么？本题不提示答案，等待真实作答。尚未关闭课次，不作完成提交。


### 2026-11-01 — M0.1: RAII 作用域释放小课完成

- Entry ID: cpp-linux-systems.M0.1.completed.2026-11-01
- Lesson ID: cpp-linux-systems.M0.1
- 结果：本小课退出证据齐全，已完成；整个 M0 阶段仍未完成，复制/移动及后续独立变体尚未验证。
- 所教知识：已成功构造的局部对象在普通结束、提前 return、向外层 catch 退栈时自动析构；后构造的先析构。对象析构与具体资源清理通过类型实现连接，普通 FILE* 变量不承担关闭责任；文件获取/关闭接口应配对，不能在 fclose 后追加 delete。
- 本人实践：构造保存传入句柄；析构判空后通过 file_api::close 关闭。接口、成员、禁止复制声明与检查由教练提供。close 调用和多余 delete 的纠正有教练帮助，practice assistance: hint；未将接口设计、测试设计或故障定位冒记为本人独立完成。
- 验证命令：`cmake --build out/cpp-linux-systems/m0/macos --target m0_scope_check` 与 `ctest --test-dir out/cpp-linux-systems/m0/macos -R '^m0.scope[.]' --output-on-failure` 均返回0，normal/return/exception/empty 四项全通过。ASan 目录 macos-asan 中同名构建及相同四项 CTest 也返回0。对应最后实现源码已核对，未增加新代码后重复测试。详细错误到通过过程见 cpp-linux-systems.M0.1.scope-check-passed.2026-11-01。
- 误解与修正：从把 FILE* 当作有 close 成员的对象，到正确调用命名空间函数；随后曾额外 delete 文件指针造成普通用例中止，已移除。ASan 仅运行了修正后版本，不宣称捕获错误版调用栈。
- 独立迁移问题：外层和内层两个 FileOwner 各自拥有不同文件，内层块结束、外层尚未结束时还有几个文件打开，为什么？本题未追加提示。
- 学习者原话：“外层文件保持打开，内层因为析构，自动调用 了close关闭了文件”。正确说明只剩外层一个文件打开，体现从一个拥有者到两个不同文件与嵌套作用域的应用（transfer assistance: none）。这份迁移和先前本人实现、行为验证共同满足本小课出口，不据一句话升级从零独立编码能力。
- 能力与复习：RAII 作用域资源管理保持 assisted，另记录本次无提示迁移；11-02 安排一次短复习，检查资源配对、提前返回/异常析构、不同作用域释放时机。尚无延迟保持结果。
- 下一步：先检查复制/移动的已有理解，必要时准备 M0.2 小课，再安排不同条件的无 AI 独立变体。11-01 到期的 Qt 通知复习仍待做，不在本条冒记通过。macOS 为通用练习默认环境，Linux 相关差异课前再提醒切换，Colima 仍未实际验证。
- 记录与仓库范围：先持久化证据和复习安排，再清除已结束会话。只提交本课 Systems 源码、材料、记录与相关主题指导；跨主题和共享工具改动保留，不混合提交。不把整个 M0 标完成。
