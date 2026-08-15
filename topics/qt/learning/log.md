# Qt 学习记录

每次完成练习后追加一项；只记录能证明学习发生的事实。阶段完成时，同时更新 [roadmap.md](roadmap.md) 的进度状态。

## 模板

```md
### YYYY-MM-DD — P<N>.<N>: <主题>

- 目标：
- 新知识讲解：<它解决什么问题；最小形式；关键语法或 API 的作用>
- 理解检查：<我的预测或解释，以及修正>
- 可选项目对照：<独立学习 / 项目名称与只读文件或符号>
- 我做了什么：
- 证据：`<配置、构建、测试或运行命令>` => <结果>
- 我能解释：
- 卡点或误解：
- 下一步：
```

## 状态值

使用：`未开始`、`进行中`、`待复习`、`已完成`、`阻塞`。`已完成` 必须包含可重复运行的命令、测试输出、截图或可审查产物；只读完章节不能标记完成。

## 初始记录

### 2026-07-28 — 路线准备：Qt 学习主题初始化

- 目标：建立可在任意机器克隆后使用的 Qt 学习路线，不把练习绑定到某个外部项目或固定路径。
- 已完成：补齐 Qt 主题说明、学习档案、学习路线和日志格式；默认模式设为独立学习。
- 证据：`topics/qt/README.md`、`topics/qt/AGENTS.md`、`topics/qt/learning/` 已建立；尚未执行 Qt 构建或安装检查。
- 当前状态：所有阶段均为“未开始”。
- 下一步：填写 `profile.md`，定位本机 Qt 6 Kit，再开始 P0 的最小 Widgets 程序。

### 2026-08-09 — P0.1: 环境、Kit 与最小 Widgets 应用

- 目标：从空构建目录配置、构建并运行最小 Qt 6 Widgets 程序，并解释配置、构建与事件循环的边界。
- 新知识讲解：Qt Kit 提供匹配的 Qt 库、工具与编译器；`cmake -S ... -B ...` 配置并生成构建规则，`cmake --build ...` 据此编译和链接；`QApplication::exec()` 运行事件循环，使窗口能持续接收关闭等事件。
- 理解检查：学习者正确预测无效 Widgets 模块会在 `find_package` 的配置阶段失败；正确预测移除 `app.exec()` 后窗口会立即退出。
- 可选项目对照：独立学习。
- 我做了什么：使用 Homebrew Qt 6.11.1 Kit 配置并构建 `p0-hello-widget`，从终端运行 `p0_hello_widget`，确认出现空白窗口。
- 证据：`cmake -S topics/qt/exercises/p0-hello-widget -B out/qt/p0-hello-widget -DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/qtbase/6.11.1` => 配置成功，构建文件生成于 `out/qt/p0-hello-widget`；`cmake --build out/qt/p0-hello-widget` => `Built target p0_hello_widget`；`./out/qt/p0-hello-widget/p0_hello_widget` => 窗口可见，关闭后终端返回。
- 我能解释：关闭最后一个窗口的事件由 `QApplication` 事件循环处理；默认情况下它退出循环，`app.exec()` 返回，随后 `main` 结束。`target_compile_features` 绑定到单个 target，以免未来项目中的其他 target 被不必要地强制使用相同 C++ 标准。
- 卡点或误解：最初按 `.app` 路径运行；但当前 CMake target 没有 `MACOSX_BUNDLE`，实际产物是普通可执行文件。已改用 `./out/qt/p0-hello-widget/p0_hello_widget`。
- 下一步：P1 — 为主窗口引入 `find_package`、`target_link_libraries`、Designer `.ui` 与 qrc 资源。

### 2026-08-09 — P1.1: Designer 表单与 AUTOUIC

- 目标：用 Qt Designer 创建 `QMainWindow` 表单，并由 CMake 自动生成可供 C++ 使用的界面头文件。
- 新知识讲解：`.ui` 是界面描述源文件；`CMAKE_AUTOUIC ON` 在构建阶段调用 `uic` 生成 `ui_*.h`。`.ui` 的 `<class>` 值决定生成的 `Ui::` 类型名；生成的 `Ui` 对象负责组装界面，实际的 `QMainWindow` 负责显示、事件循环参与和控件树根节点职责。
- 理解检查：学习者起初认为修改既有 `.ui` 内容需要重新配置；已修正为只需构建，因为规则和源文件列表未变。能说明新增 `.ui` 并加入 target 时必须重新配置，以将新文件加入构建依赖图。
- 可选项目对照：独立学习。
- 我做了什么：用 Designer 创建 `mainwindow.ui`，设置窗口标题为 `P1 Widget Shell`；将表单、`main.cpp` 和 `CMakeLists.txt` 组成 `p1_widget_shell` target；按生成的 `Ui::P1WidgetShell` 类型修正了 C++ 端的类型名。
- 证据：`cmake -S topics/qt/exercises/p1-widget-shell -B out/qt/p1-widget-shell -DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/qtbase/6.11.1` => 配置成功；`cmake --build out/qt/p1-widget-shell` => 输出 `Built target p1_widget_shell_autogen` 与 `Built target p1_widget_shell`；`./out/qt/p1-widget-shell/p1_widget_shell` => 显示标题为 `P1 Widget Shell` 的窗口。
- 我能解释：`Ui::P1WidgetShell` 是 Qt 根据 `.ui` 生成的界面组装器，会创建和配置子控件；`QMainWindow window` 才是实际显示、接收事件并作为控件树根节点的窗口对象。
- 卡点或误解：最初将 `.ui` 的 `<class>P1WidgetShell</class>` 与示例中的 `Ui::MainWindow` 混用，导致编译找不到类型；通过读取 `uic` 生成头文件并使用 `Ui::P1WidgetShell` 修正。
- 下一步：P1.2 — 添加一个 qrc 图标，学习 `AUTORCC` 的输入和生成资源路径。

### 2026-08-09 — P1.2: qrc 图标与 AUTORCC

- 目标：用 `.qrc` 把图标嵌入可执行文件，并用 `:/...` 路径在界面中加载。
- 新知识讲解：`.qrc` 是资源清单；`CMAKE_AUTORCC ON` 在构建阶段调用 `rcc`，把清单及其中文件编进二进制。运行时路径由 `prefix` 与 `<file>` 拼接而成，不是磁盘目录的镜像。macOS 上 `setWindowIcon` 往往看不到标题栏小图标，尤其从终端启动时；可用窗口内 `QLabel`/`QPixmap` 验证资源是否真的加载。
- 理解检查：正确说明运行时从嵌入资源读取；只改图片内容、路径不变时只需重建。能解释 `:/icons/icons/icon.png` 来自 `prefix="/icons"` + `<file>icons/icon.png</file>` 的拼接，而非磁盘上存在 `:/icons/icons/`。
- 可选项目对照：独立学习。
- 我做了什么：启用 `CMAKE_AUTORCC`，添加 `icons.qrc` 与 `icons/icon.png`；用 `QLabel` 显示 `:/icons/icons/icon.png` 以在 macOS 上获得可见证据。
- 证据：`cmake -S topics/qt/exercises/p1-widget-shell -B out/qt/p1-widget-shell -DCMAKE_PREFIX_PATH=/opt/homebrew/Cellar/qtbase/6.11.1` => 配置成功；`cmake --build out/qt/p1-widget-shell` => 出现 `Automatic RCC for icons.qrc` 与 `qrc_icons.cpp.o`，`Built target p1_widget_shell`；运行后窗口中央显示资源图标。
- 我能解释：AUTORCC 的输入是 `.qrc` 及清单中的文件；构建时按拼接后的逻辑路径打包进可执行文件；运行时通过 `prefix` + `file` 形成的 `:/...` 路径读取。
- 卡点或误解：起初未开启 `CMAKE_AUTORCC`；`<file>` 相对路径与磁盘位置不一致导致 make 找不到 `icon.png`；`QIcon(":/...")` 与 `.qrc` 路径一度错位；误以为 macOS 标题栏应像 Windows 一样显示 `setWindowIcon`。
- 下一步：P1.3 — 引入需要 `Q_OBJECT` 的主窗口类，学习 `AUTOMOC` 的输入与产物；补齐菜单/工具栏骨架。

### 2026-08-11 — P1.3: MainWindow、Q_OBJECT 与 AUTOMOC

- 目标：抽出带 `Q_OBJECT` 的 `MainWindow`，启用 `AUTOMOC`，用菜单/工具栏动作更新状态栏，并巩固三套自动处理的分工。
- 新知识讲解：`Q_OBJECT` 标记类参与元对象系统；`CMAKE_AUTOMOC ON` 在构建阶段运行 `moc` 生成元对象代码。`Ui::` 组装器本身不需要 `Q_OBJECT`；需要 `moc` 的是声明了 `Q_OBJECT` 的窗口类。`connect` 的 context（第三个参数）绑定连接生命周期。
- 理解检查：能说明无 `Q_OBJECT` 则一般不必 `AUTOMOC`；有 `Q_OBJECT` 无 `AUTOMOC` 时更可能在**链接**阶段失败。能列出 `AUTOUIC`←`.ui`、`AUTORCC`←`.qrc`（及清单文件）、`AUTOMOC`←含 `Q_OBJECT` 的类。
- 可选项目对照：独立学习。
- 我做了什么：新增 `mainwindow.h`/`.cpp`，`main` 只创建 `MainWindow`；CMake 打开 `AUTOMOC` 并加入头/源；菜单与工具栏共享 `About` 动作，点击后对话框 + 状态栏提示；中央区继续显示 qrc 图标。接线阶段在多次编译错误后由教练协助完成定稿。
- 证据：`cmake --build out/qt/p1-widget-shell` => 出现 `Automatic MOC and UIC`，链接生成 `p1_widget_shell`；运行后 File/工具栏 About 可触发状态栏消息。
- 我能解释：三套 AUTO* 的输入分工；缺 `AUTOMOC` 时常见链接期缺 `moc` 符号。
- 卡点或误解：曾把失败阶段说成编译；曾在 `main` 外调 `setupUI`、lambda 未捕获 `this`/未设 context、误用 `ui->mainWindow`。
- 下一步：P2 — QObject 对象树与信号槽（sender/receiver/context 与所有权）。

### 2026-08-13 — P2.1: connect 的四个角色与 context

- 目标：用「按钮点击更新标签」标出 sender、signal、context、slot，并说明缺少 context 时的悬空风险。
- 新知识讲解：`QObject::connect(sender, &Class::signal, context, functor)` 把事件接到要做的事上；第三参数绑定连接寿命。父对象 `this` 与 connect 的 context `this` 是两张网。
- 理解检查：正确标出 P1 About 连接的四个角色。起初把「窗口销毁会连带销毁 sender」和 context 混在一起；已分开：对象树管子对象销毁，context 管连接断开。能说明无 context 且 sender 仍在时，lambda 仍会执行并对已销毁对象造成 UB。
- 可选项目对照：独立学习。
- 我做了什么：在 `p2-click-label` 中独立写出 `QObject::connect(button, &QPushButton::clicked, label, [label]() { label->setText(...); })`。context 选 `label`，因为槽操作的就是它。
- 证据：`cmake -S topics/qt/exercises/p2-click-label -B out/qt/p2-click-label -DCMAKE_PREFIX_PATH="C:/Software/Qt/6.11.0/msvc2022_64"` => 配置成功（Visual Studio 18 2026 / MSVC）；`cmake --build out/qt/p2-click-label --config Debug` => `p2_click_label.vcxproj -> out\qt\p2-click-label\Debug\p2_click_label.exe`。运行前需把 `C:\Software\Qt\6.11.0\msvc2022_64\bin` 放到 PATH 最前，否则缺少 `Qt6Cored.dll`。点击按钮后标签由 `waiting` 变为 `clicked`。
- 我能解释：四个角色；`label` 适合做 context；无第三参数时，危险出现在 label 已销毁而 button 仍在。当前代码里两者都以 `window` 为父对象，所以这个悬空情况不容易出现。
- 卡点或误解：无概念性失败。工具摩擦：相对 `-S` 路径依赖仓库根目录；`--config Debugcd` 是把下一条命令粘进了配置名；Windows Debug 运行需要 Qt 6 Kit 的 `bin`，且不能让 PATH 上的 Qt 5.15.2（`D:\TempQT`）抢先。
- 下一步：P2.2 — 对象树自动销毁，并对照 C++ 智能指针；用销毁或断开连接做一次行为验证。

### 2026-08-15 — P2.2: 对象树销毁与连接失效

- 目标：说明 QObject 父子树与 `unique_ptr` 不是同一种所有权，并用销毁 context 验证连接失效。
- 新知识讲解：父对象销毁时按对象树递归释放子对象；对象树只管 QObject 父子关系，`unique_ptr` 是通用 C++ 所有权。从槽里销毁对象应优先 `deleteLater()`，避免在当前调用栈中立刻 `delete` 同一 QObject。
- 理解检查：正确预测不写 `delete` 也不泄漏（父析构带走子对象）。能区分对象树与智能指针。能说明销毁作为 context 的 `label` 后，接收对象没了、相关连接也没了，再点 `click` 不会再改文字。
- 可选项目对照：独立学习。
- 我做了什么：在 `p2-click-label` 增加 `delete` 按钮，对 `label` 调用 `deleteLater()`；context 仍为 `label`。
- 证据：`cmake -S topics/qt/exercises/p2-click-label -B out/qt/p2-click-label -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase` 与 `cmake --build out/qt/p2-click-label` => `Built target p2_click_label`；运行后 click → 文字变为 clicked；delete 后再 click → 不再更新且不崩溃。
- 我能解释：对象树自动析构；销毁 context 会拆除以其为接收端的连接；槽内销毁用 `deleteLater`。
- 卡点或误解：起初在槽里直接 `delete label`；已改为 `deleteLater()`。
- 下一步：P3 — Widgets、布局、Action 与主窗口交互。Direct/Queued 与 `Q_PROPERTY` 延后到有跨线程或属性绑定时再专练。

### 2026-08-15 — P3.1: 布局管理器替换 setGeometry

- 目标：用 `QVBoxLayout`/`QHBoxLayout` 排布标签与按钮，使窗口缩放时控件仍按相对关系排列。
- 新知识讲解：布局描述相对关系而非绝对像素；一个 widget 只有一个顶层 layout；内层 layout 经 `addLayout` 挂到外层，构造时不要再传同一 `&window`。`addStretch` 可把多余空间吸到一侧，让控件靠左/靠右。
- 理解检查：正确预测 `setGeometry` 不随窗口缩放；明白与布局同时设几何是抢控制权而非 UB。能说明变宽时多余水平空间主要分给按钮行，靠左可用 `addStretch`。
- 可选项目对照：独立学习。
- 我做了什么：在脚手架 `p3-layout-form` 中去掉 `setGeometry`，用外层竖直 + 内层水平布局；保留 click/clear 的 connect。起初内层也写了 `(&window)`，已改为无父构造再 `addLayout`。
- 证据：`cmake -S topics/qt/exercises/p3-layout-form -B out/qt/p3-layout-form -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase`；`cmake --build out/qt/p3-layout-form` => `Built target p3_layout_form`；运行后缩放时控件随布局变化，按钮仍能改标签文字。
- 我能解释：顶层唯一 layout；嵌套用 `addLayout`；拉伸与 `addStretch` 的用途。
- 卡点或误解：双 layout 同时 `(&window)`；竖直顺序曾为按钮在上（可选调换）。
- 下一步：P3.2 — `QAction` 与可启停计时，练习 UI 状态不能只靠一次初始化。
