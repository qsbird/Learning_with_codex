# 资料来源与版本

核对日期：2026-11-03。优先使用 Git 官方文档、项目源码和官方测试；中文讲解由教练提供，英文术语与源码标识保留。

## 基线与核对范围

- 本机程序：`2.45.1.windows.1`，通过 `git --version` 观察。
- 通用实现阅读：固定上游 [`v2.45.1`](https://github.com/git/git/tree/v2.45.1)。这是本课阅读基线，不表示当前最新版。
- 已实际打开并核对：该 tag 的 `git.c`、`builtin/add.c`、`read-cache.c`、`object-file.c`、`builtin/pull.c`、`Documentation/git-add.txt` 与 `Documentation/git-commit.txt`。
- 已核对官方在线命令目录、内部原理介绍、索引格式、Trace2 与测试说明。在线文档可能更新；当参数或细节与基线有关时，以固定 tag 的文档为准。
- 尚未下载完整 Git 源码、编译 Git、运行官方测试或核对 Windows 补丁；不能把阅读资料视为这些工作的证据。

## 主资料

| 资料 | 用途与阅读范围 |
| --- | --- |
| [Pro Git：内部原理入口](https://git-scm.com/book/en/v2/Git-Internals-Plumbing-and-Porcelain) | 理解 objects、refs、HEAD、index 与底层命令的关系；按实验选读 |
| [Git 官方命令目录](https://git-scm.com/docs/git) | 查当前命令、参数、概念指南与底层命令 |
| [固定版本 add 文档](https://github.com/git/git/blob/v2.45.1/Documentation/git-add.txt) | 首课核对暂存内容的时间点及再次暂存的含义 |
| [固定版本 commit 文档](https://github.com/git/git/blob/v2.45.1/Documentation/git-commit.txt) | 区分普通索引提交、`-a` 与显式路径参数的行为 |
| [索引格式说明](https://git-scm.com/docs/gitformat-index) | 按需查路径、对象 ID、mode、stat 与 stage，不要求首课解析二进制格式 |
| [用户手册](https://git-scm.com/docs/user-manual) | 补充低层操作与 Hacking Git 章节 |
| [首次贡献指南](https://git-scm.com/docs/MyFirstContribution) | 需要构建、增加插桩或运行测试时参考；本课不要求提交上游补丁 |
| [官方测试说明](https://github.com/git/git/blob/master/t/README) | 了解测试组织、用例与筛选运行方式；实际用例须在固定 tag 下重新选取 |
| [Trace2 文档](https://git-scm.com/docs/api-trace2) | 需要时辅助观察埋点事件与执行阶段 |

## 源码导航

以下入口统一基于 `v2.45.1`。G1.1 的路径已核对；其他单元的深入函数与对应测试在开课时核对，不预先声称已运行。

| 问题 | 入口 |
| --- | --- |
| 子命令如何分派 | [`git.c`](https://github.com/git/git/blob/v2.45.1/git.c)：`commands[]`、`run_builtin` |
| `add` 的参数、已跟踪路径处理与落盘 | [`builtin/add.c`](https://github.com/git/git/blob/v2.45.1/builtin/add.c)：`cmd_add`、`write_locked_index` 调用处 |
| 索引条目与更新回调 | [`read-cache.c`](https://github.com/git/git/blob/v2.45.1/read-cache.c)：`add_files_to_cache`、`update_callback`、`add_file_to_index`、`add_to_index` |
| 从文件读入 blob | [`object-file.c`](https://github.com/git/git/blob/v2.45.1/object-file.c)：`index_path`、`index_fd` |
| 提交 | [`builtin/commit.c`](https://github.com/git/git/blob/v2.45.1/builtin/commit.c) |
| 状态与差异 | [`wt-status.c`](https://github.com/git/git/blob/v2.45.1/wt-status.c)、[`builtin/diff.c`](https://github.com/git/git/blob/v2.45.1/builtin/diff.c) |
| 分支与切换/恢复 | [`builtin/branch.c`](https://github.com/git/git/blob/v2.45.1/builtin/branch.c)、[`builtin/checkout.c`](https://github.com/git/git/blob/v2.45.1/builtin/checkout.c) |
| 重置 | [`builtin/reset.c`](https://github.com/git/git/blob/v2.45.1/builtin/reset.c) |
| 获取与拉取 | [`builtin/fetch.c`](https://github.com/git/git/blob/v2.45.1/builtin/fetch.c)、[`builtin/pull.c`](https://github.com/git/git/blob/v2.45.1/builtin/pull.c) |
| 合并与推送 | [`builtin/merge.c`](https://github.com/git/git/blob/v2.45.1/builtin/merge.c)、[`builtin/push.c`](https://github.com/git/git/blob/v2.45.1/builtin/push.c) |

## 使用边界

- 不按文件顺序通读整个 Git；沿当前问题确定的执行路径查找。
- 源码行为涉及文件类型、过滤器、换行转换、稀疏索引或平台差异时，明确当前实验条件。
- 首课只研究普通小文本文件、普通 `add` 和不带 `-a`、不带路径的 `commit -m`；其他模式留到相关单元。
- 资料链接与源码核对是教练准备；学习者是否理解依据本课日志中的本人证据。
