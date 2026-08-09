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
