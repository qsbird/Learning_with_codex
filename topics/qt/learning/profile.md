# Qt 学习档案

首次正式学习前填写；答案变化时更新。路线见 [roadmap.md](roadmap.md)，每次练习证据见 [log.md](log.md)。

## 目标与节奏

- 主要目标：
- 当前 C++ 水平：
- 当前 Qt 水平：
- 当前 CMake/qmake 水平：
- 每周可投入时间：
- 计划完成日期：
- 偏好的练习方式：
- 当前阻塞：

## 学习模式

- 选择：`独立学习`
- 独立学习：默认使用 `topics/qt/exercises/`；不填写任何外部路径也可以开始。
- 项目对照（仅在选择后填写）：
  - 项目名称：
  - 本地根目录：
  - 分支或修订：
  - Qt 版本与构建方式：
  - 本次只读对照的文件或符号：

项目路径在另一台机器缺失、不可访问或不便共享时，将模式改回 `独立学习`，并在日志中写明原因；不要把路径作为练习的前提。

## 基线诊断

开始 P0 前记录以下结果。“不知道”是有效答案，用来安排先讲解再练习，不用于评分。

1. 运行 `cmake --version`，并在 Qt Creator 或终端中记录可用 Qt Kit 的 Qt、编译器和 CMake 版本。
2. 是否能从空构建目录配置、构建并运行一个最小 Qt Widgets 程序？
3. 用自己的话描述 `QApplication`、事件循环和主窗口之间的关系。
4. 是否见过 `QObject` 父子关系？它与 C++ 智能指针分别解决什么问题？
5. 是否听过 Direct connection 与 Queued connection？只记录是否见过；不了解时会先用最小例子讲解。
6. 是否见过 `.ui`、`.qrc` 或 `.ts`？只记录文件用途，不要求预先知道生成工具。
7. 是否接触过模型/视图？只记录是否见过，不要求预先列出 `QAbstractItemModel` 接口。

## 环境记录

- 记录日期：2026-08-13（Windows 机；此前 P0/P1 证据来自 macOS Homebrew Qt 6.11.1）
- 操作系统：Windows 10/11（win32 10.0.26200）
- Qt 6 Kit 目录：`C:/Software/Qt/6.11.0/msvc2022_64`
- 编译器与版本：MSVC 19.51.36252.0（Visual Studio 18 2026）
- CMake 与生成器：CMake 4.3.0；`Visual Studio 18 2026`（多配置，构建时 `--config Debug`）
- Qt Creator（如使用）：`C:\Software\Qt\Tools\QtCreator`（本课用终端）
- 在普通终端中可发现的 Qt 命令：PATH 上先找到的是 Qt 5.15.2（`D:\TempQT\msvc2019_64`）；配置/运行 Qt 6 练习必须显式使用 6.11.0 Kit，并把其 `bin` 放到 PATH 最前
- 练习构建根目录：`out/qt/`

不要假设 `PATH`、盘符、Qt 安装位置或外部项目在另一台机器上存在。每台机器重新记录自己的 Kit 即可。

## P0 前需要补齐的信息

- 实际使用的 Qt 6 Kit：`C:/Software/Qt/6.11.0/msvc2022_64`（本机）；macOS 课次曾用 Homebrew `qtbase/6.11.1`
- 用于构建的终端（Developer PowerShell / Qt Creator / 其他）：PowerShell（仓库根目录）
- 每周可投入时间：
- 最小练习是否已有可重复的测试数据或可见结果：有。`p2-click-label` 点击后标签由 waiting 变为 clicked；运行需 Qt 6 `bin` 在 PATH 最前
- 若选择项目对照：项目名称、修订和本次只读范围；否则填“不适用”。不适用
