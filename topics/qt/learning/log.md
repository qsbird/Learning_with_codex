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
