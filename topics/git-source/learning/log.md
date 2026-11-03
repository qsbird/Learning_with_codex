# Git 源码学习日志

本文件追加记录本课的实际活动。准备材料与学习者实践分开记录；没有本人操作与解释时，不记章节完成。

## 课程初始化

### 2026-11-03 — 课程约定与材料准备

- 目标：创建独立的 Git 命令源码兴趣支线。
- 学习者选择：同意“命令语义 → 数据变化 → C 实现 → 实验验证”；要求创建相关材料并推送远端。
- 约束：不安排复习、不接入现有计划、不设课时配额与完成日期。
- 已准备：G0～G8 选学目录、官方资料清单、学习方式、G1.1 阅读材料及离线实验脚手架。
- 环境观察：Windows PowerShell；本机 `git version 2.45.1.windows.1`；通用源码阅读基线为上游 `v2.45.1`。
- 学习者证据：仅有课程选择与授权；尚无本课命令预测、本人实验或源码解释。
- 章节状态：全部未开始；准备工作不计为完成章节。
- 教练验证：见后续追加的材料验证记录；不据此推断学习者已经掌握。
- 下一步：等待学习者主动开课；建议选择 `git-source.G1.1`，所需 G0 概念在当次讲解。

## 完成课次的追加格式

正式学习后，按根目录约定追加日期、目标与结果、所教知识、本人操作与帮助程度、准确验证命令和结果、误解、学习者解释及可选下一步。只在出口证据齐全后标记章节完成；不生成复习日期。

### 2026-11-03 — 教练材料验证（不计学习者证据）

- 准备命令：`& ./topics/git-source/exercises/g1-add-snapshot/prepare.ps1 -Name g1-material-check-20261103`。
- 起始检查：实验仓库的 `git show HEAD:note.txt` 与 `git show :note.txt` 都为 A，工作区文件为 B。
- 教练冒烟操作：在该实验仓库执行 `git add -- note.txt`，用 `Set-Content -LiteralPath note.txt -Value 'C' -Encoding ascii` 写入 C，再执行 `git commit -m 'check: commit staged B'`。
- 内容验证：`git show HEAD:note.txt` => B；`git show :note.txt` => B；`Get-Content note.txt` => C。`git cat-file -p` 读取暂存对象 => B；`git hash-object note.txt` 的 ID 与索引对象 ID 不同。
- 隔离检查：实验仓库无远端；重复准备同名目录按预期拒绝，C 内容保留；`git check-ignore out/git-source/g1-material-check-20261103/note.txt` 确认输出被忽略。
- 材料检查：PowerShell AST 解析无错误；本次课程及根目录、主题目录的 11 份 Markdown 的本地链接均存在；`git diff --check` 通过。
- 结果与局限：教练准备与目标行为验证通过；未运行官方 Git 测试套件，未进行源码单步调试。学习者尚未开课，所有章节仍未开始。
