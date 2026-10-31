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

### 2026-08-15 — P3.2: QTimer 启停与 UI 状态同步

- 目标：用 Start/Stop 控制 `QTimer`，保持 Action 启用状态与运行状态一致，并在 timeout 时更新 ticks。
- 新知识讲解：`QTimer` 到期发 `timeout`；关联控件的 enabled 必须在每次状态切换后刷新（如 `syncUi(bool)`）。`Q_UNUSED(x)` 仅用于消除“未使用变量”编译警告，不是运行时逻辑。
- 理解检查：正确预测只初始化一次 enabled 时会一直只能 Start、不能 Stop。能说明控件状态相互约束，无法靠一次初始化覆盖全部交互。
- 可选项目对照：独立学习。
- 我做了什么：在 `p3-timer-tool` 实现 `syncUi`、Start/Stop 与 `timeout` 接线；一度漏接 `timeout` 导致 ticks 不变，已补上。
- 证据：`cmake -S topics/qt/exercises/p3-timer-tool -B out/qt/p3-timer-tool -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase`；`cmake --build out/qt/p3-timer-tool` => `Built target p3_timer_tool`；Start 后 ticks 增加且 Start/Stop 启用状态互换，Stop 后停止计数。
- 我能解释：状态关联导致不能只初始化一次；漏接 `timeout` 时计时器可跑但 UI 数字不变。
- 卡点或误解：漏写 `timeout` 连接；本机同时存在 `out/qt/p3-timer-tool` 与 CMake Tools 的 `out/qt/vscode/exercises/p3-timer-tool` 两份产物，需确认运行的是刚重建的那份。
- 下一步：P4 — 模型/视图入门（先从 `QStringListModel` 开始）。

### 2026-08-24 — P4.1: QStringListModel、view 与经 model 追加

- 目标：把现成字符串模型接到 `QListView`，并通过 model 接口追加一行，使视图刷新。
- 新知识讲解：数据在 model，显示在 view；`QModelIndex` 是格子地址，取值用 `model->data(index)`。改数据必须走 model（`setModel`、`insertRow`/`setData` 或 `setStringList`），model 会通知 view；只改 `stringList()` 的拷贝不会刷新。
- 理解检查：正确预测未 `setModel` 时看不见 model 里已有的 alpha/beta。能说明必须改 model 才能增删改查列表。起初把 index 说成“返回数据行的接口”，已收紧为地址。
- 可选项目对照：独立学习。
- 我做了什么：在 `p4-string-list` 调用 `view->setModel(model)`；`add` 时 `insertRow` 再 `setData`。
- 证据：`cmake -S topics/qt/exercises/p4-string-list -B out/qt/p4-string-list -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase`；`cmake --build out/qt/p4-string-list` => `Built target p4_string_list`；运行后列表显示 alpha/beta，点 add 追加 gamma。
- 我能解释：view 显示的数据来自 model；脱离 model 的 `QStringList` 拷贝不会驱动刷新。
- 卡点或误解：index 与 data 的分工；IDE 构建目录仍可能是 `out/qt/vscode/exercises/p4-string-list`。
- 下一步：P4.2 — 只读二维自定义模型，落实 `rowCount`/`data`/`index`/`parent` 与模型通知。

### 2026-09-17 — P4.2: 只读二维 ResultModel

- 目标：实现只读二维自定义模型，让 `QTableView` 显示 3 行姓名/分数，并解释 `rowCount`/`data`/`index`/`parent`。
- 新知识讲解：view 通过模型契约询问尺寸与单元格，不直接读 `results_`；表模型在 `parent` 有效时 `rowCount`/`columnCount` 返回 0；`QAbstractTableModel` 已实现平坦表的 `index()` 与 `parent()`；`data` 用 `DisplayRole` 和列号从已有数据作答。
- 理解检查：正确预测当前 stub 会显示空表，但起初把原因说成缺少 `insertRow`/`setData`；已纠正为初始数据靠契约函数报告。随后能判断 `rowCount(根)=3`、`rowCount(单元格)=0`。独立说明二维表不必自己实现 `index()`/`parent()`，因为基类已提供。
- 可选项目对照：独立学习。
- 我做了什么：在 `resultmodel.cpp` 实现 `rowCount`、`columnCount`、`data`。首次实现忽略 `parent` 且 `data` 只返回 score；经提示后补上 parent 规则和按列返回 name/score。`QString` 与 `int` 不能直接用于同一三元表达式，改为两侧都包成 `QVariant`。
- 证据：`cmake -S topics/qt/exercises/p4-readonly-table -B out/qt/p4-readonly-table -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase`；`cmake --build out/qt/p4-readonly-table` => `Built target p4_readonly_table`。非 GUI 询问模型：`rows=3 cols=2 childRows=0 cellParentValid=0 a00=alpha a01=91 a10=beta a11=84 a20=gamma a21=96 emptyRole=0`。
- 我能解释：`setModel` 只建立连接；view 看到的行数和文字分别来自 `rowCount` 与 `data`。二维表是平的，格子没有父节点，`index(row, column)` 只编址行列，因此沿用 `QAbstractTableModel` 的 `index()`/`parent()`，不必在子类重复实现。
- 卡点或误解：把 P4.1 的 `insertRow`/`setData` 误当成初始显示的前提；第一次 `data` 两列都返回分数；三元运算符要求两端类型一致。
- 下一步：P4 仍进行中——模型通知（如 `dataChanged` / `beginInsertRows`）或一次事件分发；按年度计划约 09-24 收口。

### 2026-10-05 — P4.2: 只读模型契约复习

- Entry ID: qt.P4.2.model-contract-review.2026-10-05
- Lesson ID: qt.P4.3 开始前的前置回忆；不改变 P4.2 的历史完成记录。
- 目标：在不看提示的情况下说明已有数据为何能显示，以及单元格作 parent 时 rowCount 的结果。
- 学习者原话：insertRow 是向 model 中添加数据，而 ResultModel 在构造时就有数据初始化了，因此无需 insertRow，只要重写 rowCount 等必要的函数就可以。用其中一个单元格的 QModelIndex 再调用 rowCount 会返回 0，因为当前数据只有一个层级，alpha、beta、gamma 三行都没有各自的子项。
- 结果：两问都正确（explanation assistance: none）。学习者阅读了自己的 `resultmodel.cpp`，教练未提示答案。
- 反馈：视图不读取 `results_`，而是调用 `rowCount`、`columnCount` 和 `data`。单元格 index 是有效 parent，平坦表在这时返回 0。这次回忆把当前能力记为 explained；2026-09-17 的实现仍包含当时的提示，不改写那次记录。
- 复习：下一次 2026-10-12，换一个问法：视图显示分数时调用哪个函数，对根 index 调用 rowCount 应返回几。
- 下一步：讲解现有单元格变化与新增行分别要发的通知，先做一次预测，再安排最小代码改动。

### 2026-10-05 — P4.3: 静默修改分数后的通知预测

- Entry ID: qt.P4.3.score-prediction.2026-10-05
- Lesson ID: qt.P4.3
- 目标：确认学习者能说出静默修改已有分数时视图仍显示旧值，以及应发出的通知。
- 学习者原话：“会显示91，需要发 datachanged”。
- 结果：旧值 91 和 `dataChanged` 都正确。前一轮讲解已经说明这两点，因此这是理解检查，不是独立实现。
- 下一步：由学习者实现 `ResultModel::setScore`，只通知被修改的那一个分数格。检查目标在定义该函数前会链接失败。

### 2026-10-05 — P4.3: setScore 通知检查通过

- Entry ID: qt.P4.3.notify-check.2026-10-05
- Lesson ID: qt.P4.3
- 目标：修改已有行的分数，并只通知该行的分数格。
- 学习者实现：在 `resultmodel.cpp` 的 `setScore` 中先拒绝越界行，再写入 `results_[row].score`，然后 `emit dataChanged(index(row, 1), index(row, 1))`。检查程序未改。
- Assistance: none
- 验证命令与结果：在已配置的 `out/qt/p4-readonly-table-notify` 中执行 `cmake --build ... --target p4_readonly_table_notify_check`，返回 0。运行该程序打印 `emissions=1 top=0,1 bottom=0,1 name=alpha score=100 other=84`，退出码 0。本机为 Apple Clang 21.0.0，Qt 前缀 `/opt/homebrew/opt/qtbase`。
- 尚未收口：命令通过还不能代替对通知范围的说明。
- 下一步：学习者说明为什么 `dataChanged` 的两端都是第 1 列。

### 2026-10-17 — 恢复时纠正历史工程入口文件名

- Entry ID: qt.log.filename-correction.2026-10-17
- 发现：state 的日志哈希与当前 log 不一致。逐项核对相对 Git HEAD 的 diff，除 2026-10-05 的三条已被 state 引用的学习记录外，2026-08-09 — P1.1: Designer 表单与 AUTOUIC 的“我做了什么”将工程入口 CMakeLists.txt 替换为 HelloConfig.cmake。
- 纠正：该历史条目中的工程入口应按 CMakeLists.txt 理解；真实 Qt 聚合入口与练习入口也都是 CMakeLists.txt。保留旧条目，以本条纠正引用；同时修正 README 中相同的错误名称。
- 证据边界：10-05 的 setScore 实现、命令结果与待答问题保持有效；该处名称替换不改变历史完成或能力等级。复核后刷新日志哈希。

### 2026-10-17 — 恢复 P4.3，等待通知范围解释

- Entry ID: qt.resume.2026-10-17
- 依据：学习者停止 CMake 与 LLM 后继续今天学习；按年度检查点和未完成会话恢复 Qt P4.3，不跳到 P5 或系统新课。
- 进度核对：P0～P3、P4.1/P4.2 历史完成；P4.3 已有 10-05 独立实现 setScore 与通过检查的证据，仍缺对通知范围的学习者解释。P4 阶段保持进行中。
- 今日环境/教练验证：macOS，AppleClang 21.0.0.21000101，Unix Makefiles，Qt 前缀 /opt/homebrew/opt/qtbase。仓库根目录执行 `cmake -S topics/qt/exercises/p4-readonly-table -B out/qt/p4-notify-20261017 -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase`、`cmake --build out/qt/p4-notify-20261017 --target p4_readonly_table_notify_check`、`out/qt/p4-notify-20261017/p4_readonly_table_notify_check`，均返回 0；输出 `emissions=1 top=0,1 bottom=0,1 name=alpha score=100 other=84`。未改目标源码，未进行 GUI 刷新观察。
- 帮助与证据：今天仅恢复与复验，不新增学习者答案或能力等级；hint_level=0、solution_shown=false 沿用原会话。
- 继续原问题：dataChanged 的两个 index 为什么都是第 1 列，而不是从第 0 列到第 1 列？保留 10-05 的问题 ID 和首次提问日期，等待实际回答。
- 复习安排：10-12 到期的只读模型契约复习仍待做，不因今日计划核对而改成已复习；先处理原会话问题。
- 仓库恢复：已检查 main/upstream 为本地引用 0/0、无冲突标记；存在跨主题未提交记录与源码，已保留并核对相关内容，不作混合提交。课程尚未收口，不创建完成提交。

### 2026-10-17 — P4.3: 通知范围与有效列的误解澄清

- Entry ID: qt.P4.3.notify-range.correction.2026-10-17
- Lesson ID: qt.P4.3
- 学习者原话：“因为通常模型树中只有一列数据有实际意义”。
- 评估：原通知范围解释未通过。当前练习是平坦二维表，第 0 列姓名、第 1 列分数均有意义；不能以树模型只有一列有意义作为通知第 1 列的依据。
- 本轮讲解：dataChanged 的两个 index 表示受影响矩形的左上角与右下角，包含端点。setScore 只修改某一行的分数，所以两端为同一个分数格；把同一行第 0 列也包括进去会扩大通知范围，通常造成不必要的更新，不代表姓名列无意义。
- 来源核对：Qt 官方 QAbstractItemModel::dataChanged 文档（https://doc.qt.io/qt-6/qabstractitemmodel.html#dataChanged），确认同 parent 的两个端点覆盖包含边界的范围。未改代码或重复构建。
- 帮助程度：教练已直接解释原问题的答案，记录为 correction assistance: solution；不新增学习者掌握或完成证据。历史独立 setScore 实现证据保留。
- 下一理解检查：若连续修改第 0、1、2 行的分数，姓名不变，并合并成一次 dataChanged 通知，两个端点分别应该写成哪个 index？等待学习者实际回答后再评估。

### 2026-10-17 — P4.3: index 行列顺序纠正

- Entry ID: qt.P4.3.row-column.correction.2026-10-17
- Lesson ID: qt.P4.3
- 待评估条件：第 0、1、2 行分数变化、姓名不变，用一次 dataChanged 通知。
- 学习者原话：“（1，0）（1，2）”。
- 评估：答案未通过。按 index(row, column) 解读，给出的末端包含不存在的第 2 列；坐标呈现行列顺序颠倒，不能据此推断已经掌握范围。
- 本轮讲解：index 的第一个参数是行、第二个参数是列；示范 index(2, 1) 对应第 2 行分数格。三行分数的正确范围是 index(0, 1) 到 index(2, 1)。教练已展示本题答案（correction assistance: solution）。
- 下一步：缩小为一个单元格的检查——若只修改第 2 行的姓名，dataChanged 的两个端点分别怎么写？等待实际答案；不提前标记 P4.3 完成。
- 验证范围：未改源码或重复构建，保留此前运行证据。

### 2026-10-18 — P4.3: 单格坐标回答正确，转入姓名通知实践

- Entry ID: qt.P4.3.setName.practice-start.2026-10-18
- Lesson ID: qt.P4.3
- 学习者原话：“（2，0）”，回答只修改第 2 行姓名的通知端点问题。
- 评估：正确定位第 2 行第 0 列；学习者只写一个坐标，教练补充单格变化时两端都取该坐标。这是此前行列顺序讲解后的理解检查（explanation assistance: hint），尚不构成独立范围实现或本课完成。
- 教学调整：连续文字题曾出现范围依据和行列顺序误解，本轮结束坐标题循环，转入一个已知操作的代码变体，不引入新 API。
- 教练准备：在现有 resultmodel.h 声明 setName(int row, const QString &name)，resultmodel.cpp 添加空实现和行为 TODO；新增 check_name_notification.cpp 与独有 target p4_readonly_table_name_check。保留学习者 setScore 与原检查。未代写 setName 目标逻辑。
- 新任务：学习者只实现 setName 函数体；拒绝越界行，修改该行姓名，保持分数不变，只发一次该姓名格的 dataChanged。名称参数已在签名提供。
- 准备验证：仓库根目录执行 cmake -S topics/qt -B out/qt/aggregate-20261018 -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase，返回 0；cmake --build out/qt/aggregate-20261018 --target p4_readonly_table_name_check p4_readonly_table_notify_check，返回 0。本机 AppleClang 21.0.0.21000101，Unix Makefiles；只确认该前缀可用，不推断 Qt 精确版本。
- 基线行为：out/qt/aggregate-20261018/exercises/p4-readonly-table/p4_readonly_table_name_check 返回 1，oneCell=0 changedName=0 unchangedValues=1 ignoredInvalid=0，符合未实现状态；同目录 p4_readonly_table_notify_check 返回 0，emissions=1 top=0,1 bottom=0,1 name=alpha score=100 other=84。脚手架构建不是学习者实践证据。
- 每日恢复：核对 10-18 日期、年度 10-17～10-23 窗口与会话；继续 Qt P4.3，CMake/LLM 维持停止。main 与已有 upstream 引用 0/0（未 fetch）；已有跨主题未提交记录和改动保留，不混合提交。
- 下一步：等待真实 setName 修改后运行姓名检查与已有分数检查，再收集关键通知范围解释。P4.3/P4 保持未完成，模型契约到期复习仍待做。


### 2026-10-20 — P4.3: 按新学习教练重开阅读阶段

- Entry ID: qt.P4.3.restart-reading.2026-10-20
- Lesson ID: qt.P4.3
- 学习者请求：检查进度，使用新的 learning-coach 技能，重新开始本章；定位文件为 exercises/p4-readonly-table/resultmodel.cpp。
- 进度核对：P0～P3、P4.1/P4.2 历史完成；P4.3 保留 10-05 独立 setScore 与通知检查证据、10-17 范围及行列顺序纠正、10-18 提示后单格定位。当前 setName 仍为空实现；P4.3/P4 未完成。
- 教学调整：按学习者明确选择，从阅读 → 概念讨论 → 编码实践重新开始 P4.3。保留原练习和已记录提示/答案暴露，不将重新开始当作独立完成或能力清零。材料已准备并在本轮交付：learning/materials/qt.P4.3.md（来源 qt-item-model、qt-table-model、qt-model-index）。本轮未提出概念检查题或下发编码任务。
- 阅读断点：等待学习者确认读完或提出疑问；阅读位置、阅读耗时、重复澄清次数与本次理解均未知。后续先讨论一个目标相关的变化场景，再按理解情况进入原 setName 实践；既有完整分数解法可见，独立迁移证据需另行辨别。
- 每日核对：2026-10-20 位于年度计划 10-17～10-23 Qt 收口窗口。维持 CMake/LLM 停止；未来一至两周先推进本课实际出口，再依年度条件安排 Systems M0。10-12 到期模型契约复习仍未作答；材料回顾不计复习通过。
- 仓库恢复：已核对现存 Qt 未提交源码和记录，无未解决合并冲突；本地 HEAD 与已有 origin/main 引用为 0 ahead / 0 behind，未 fetch。跨主题未提交工作保留，当前重开不作完成提交。
- 今日环境：macOS；CMake 4.3.0；AppleClang 21.0.0.21000101；Unix Makefiles；/opt/homebrew/opt/qtbase/bin/qtpaths --qt-version 返回 6.11.1。该日期的机器观察独立于 profile 中的 Windows 历史记录。
- 教练基线验证：仓库根目录运行 cmake -S topics/qt -B out/qt/aggregate-20261020 -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase，返回 0；cmake --build out/qt/aggregate-20261020 --target p4_readonly_table_notify_check p4_readonly_table_name_check，返回 0。分数检查返回 0：emissions=1 top=0,1 bottom=0,1 name=alpha score=100 other=84；姓名检查返回 1：oneCell=0 changedName=0 unchangedValues=1 ignoredInvalid=0，符合空实现基线。未修改目标源码，未观察 GUI；这些是教练准备，不新增学习者掌握证据。
- 来源：当天重查 Qt 官方在线 6.12.0 模型/表模型/索引文档，仅核对材料使用的接口契约，未运行官方示例。
- 下一步：等待阅读完成确认；保存实际阅读位置后继续讨论。P4.3 保持 in_progress，概念等级与复习日期不升级。


### 2026-10-31 — P4.3: 通知范围与先写后通知解释通过

- Entry ID: qt.P4.3.range-timing-discussion.2026-10-31
- Lesson ID: qt.P4.3
- 阅读确认：学习者回复“可以讨论了”，已从 learning/materials/qt.P4.3.md 阅读阶段进入讨论；阅读耗时未知。
- 本次问题：只修改第 1 行的姓名与分数，其他两行不变，一次 dataChanged 的两个端点是什么，为什么先修改数据再通知？
- 学习者代码回答：`emit dataChanged(index(1, 0), index(1, 1));`
- 学习者解释原话：“因为发出通知后，视图就会根据指定位置获取数据并更新，此时如果内部数据还没更新，就会产生时序上的错误”。
- 评估：范围和时序均正确；本次作答未追加提示（explanation assistance: none），属于阅读后的理解检查。保留历史提示与解法暴露，不把这一回答当作独立代码实践。教练补充：通知接收者可能立即读取模型。
- 转入实践：仅由学习者实现 exercises/p4-readonly-table/resultmodel.cpp 的 setName 函数体。有效行只更新姓名、保持分数和其他行不变，并发一次该姓名格的通知；越界行不改数据、不发通知。教练未修改目标代码，setName 仍为空实现。
- 本日教练环境验证：macOS，Qt 6.11.1（/opt/homebrew/opt/qtbase/bin/qtpaths --qt-version），CMake 4.3.0，AppleClang 21.0.0.21000101，聚合入口配置成功。仓库根目录执行 `cmake -S topics/qt -B out/qt/aggregate-20261031 -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qtbase`，以及 `cmake --build out/qt/aggregate-20261031 --target p4_readonly_table_name_check p4_readonly_table_notify_check` 均返回 0。
- 行为基线：`out/qt/aggregate-20261031/exercises/p4-readonly-table/p4_readonly_table_name_check` 返回 1，输出 `oneCell=0 changedName=0 unchangedValues=1 ignoredInvalid=0`，符合空实现；同目录 `p4_readonly_table_notify_check` 返回 0，输出 `emissions=1 top=0,1 bottom=0,1 name=alpha score=100 other=84`。未观察 GUI。这些仅为教练准备，不是本次学习者实现证据。
- 计划核对：年度原窗口已过，10-31～11-06 只推进本课阅读、讨论与姓名实践及验证，11-07～11-13 按实际证据安排模型契约复习与 C0 复核，达标后才准备 Systems M0。CMake/LLM 维持停止，未补记完成或复习。
- 下一步：等待学习者真实 setName 修改，再运行姓名与分数检查，收集关键决定说明。P4.3/P4 未完成；模型契约到期复习仍待做，不创建完成提交。


### 2026-10-31 — P4.3: 姓名更新实现与两项行为检查通过

- Entry ID: qt.P4.3.setName-check.2026-10-31
- Lesson ID: qt.P4.3
- 学习者报告“完成”，核对源码发现 setName 已由空实现改为：拒绝负数或超出 results_.size() 的行，写入 results_[row].name，再发出 dataChanged(index(row, 0), index(row, 0))。目标修改由学习者完成，教练未代写或修正；保留源码中的 TODO 注释，不以注释未删判错。
- 帮助边界：本次编码未追加提示；历史已讲过单格姓名坐标且 setScore 完整实现可见，因此新姓名实践保守标记 practice assistance: hint，不宣称从零独立掌握。10-05 独立 setScore 实践证据与本日无追加提示的范围/时序解释保留。
- 验证：仓库根目录执行 `cmake --build out/qt/aggregate-20261031 --target p4_readonly_table_name_check p4_readonly_table_notify_check` 返回 0。
- 姓名检查：`out/qt/aggregate-20261031/exercises/p4-readonly-table/p4_readonly_table_name_check` 返回 0，输出 `oneCell=1 changedName=1 unchangedValues=1 ignoredInvalid=1`。
- 分数回归：`out/qt/aggregate-20261031/exercises/p4-readonly-table/p4_readonly_table_notify_check` 返回 0，输出 `emissions=1 top=0,1 bottom=0,1 name=alpha score=100 other=84`。检查程序未修改，未观察 GUI；静态核对也确认先写数据后发通知。
- 阶段：进入 practice/reflect。收集最后一个简短解释：setName 为什么不需要调用 insertRow，而只需 dataChanged？等待实际答案，尚未记录章节完成，不创建完成提交。


### 2026-10-31 — P4.3: 模型通知课次完成

- Entry ID: qt.P4.3.completed.2026-10-31
- Lesson ID: qt.P4.3
- 结果：本课已完成。P4.2 已有模型契约实现与解释；结合本课分数、姓名的更新通知、范围和时序解释，P4 阶段退出条件已满足。完成课次标识为 qt.P4.3，阶段为 P4，两者分开记录。
- 所教知识：已有单元格值变化用 dataChanged；端点是同 parent 下含边界的矩形区域，index 参数先行后列；先写数据再通知，以便接收者立即查询新值；改变已有值与添加行的结构变化不同。
- 学习者实践：10-05 独立实现 setScore（见 qt.P4.3.notify-check.2026-10-05）；本日本人实现 setName 的行号检查、姓名写入和单格通知。姓名实践沿用历史帮助与可见分数模板，保守记为 hint，不升级为从零独立实现。教练未代写目标逻辑。
- 学习者解释：本日范围/时序回答见 qt.P4.3.range-timing-discussion.2026-10-31；最后反思原话为“insertrow是向模型中 添加新行，setName要做的是更新已有数据”。这次未追加提示（explanation assistance: none），正确区分结构变化和已有数据更新。
- 验证命令及结果：仓库根目录 `cmake --build out/qt/aggregate-20261031 --target p4_readonly_table_name_check p4_readonly_table_notify_check` 返回 0；`out/qt/aggregate-20261031/exercises/p4-readonly-table/p4_readonly_table_name_check` 返回 0，`oneCell=1 changedName=1 unchangedValues=1 ignoredInvalid=1`；同目录 `p4_readonly_table_notify_check` 返回 0，`emissions=1 top=0,1 bottom=0,1 name=alpha score=100 other=84`。环境为本日已核对的 macOS / Qt 6.11.1 / AppleClang 21.0.0.21000101 / CMake 4.3.0。未观察 GUI，结论限于模型行为与通知契约。
- 误解收口：10-17 曾将“只有一列有意义”作为通知依据，并混淆行列顺序；本日能正确给出第 1 行两列的范围并实现姓名单格通知，原错误不再作为当前解释。历史纠正和帮助仍保留，尚未证明延迟保持。
- 复习安排：2026-11-01 做一次简短通知范围/时序回忆，若通过再按约 7 天、21 天安排后续复习；原 2026-10-12 到期的模型契约复习尚未完整作答，保留原日期，不因本课完成改成复习通过。
- 下一步：先做模型契约短复习并复核年度 C0 的记录与仓库同步，再准备 C++ Linux Systems M0 的独立 RAII 基线；不自动开启 Qt P5，CMake/LLM 维持停止。
- 记录与范围：先持久化本次证据、状态和复习，再清除已结束会话。Git 仅纳入本课 Qt 源码、检查、材料与记录；共享教学流程和其他主题的已有未提交改动保留。历史日志中已有的工程入口名称替换不随本次提交，暂存状态摘要按暂存日志计算，工作区摘要仍匹配其实际日志。
