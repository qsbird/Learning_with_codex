# G1.1 — add 之后再编辑，提交会使用什么

状态：待学习。本文是开课阅读材料，不是已完成证据。教练先讲解、等待当次理解检查，再开始[实验](../../exercises/g1-add-snapshot/README.md)。

## 这次要能解释什么

一个文件暂存后还可以继续编辑。我们要通过实际内容和 Git 源码解释：为什么普通的 `git commit -m` 使用索引中已选定的内容，以及后续编辑为什么仍留在工作区。

本次只涉及一个已跟踪的普通小文本文件。实验局部关闭换行转换和内容过滤；不使用 `commit -a`、不传提交路径、不研究交互暂存。

## 最小模型

| 名称 | 本课中的含义 | 怎样观察 |
| --- | --- | --- |
| 工作区 | 当前磁盘上的 `note.txt` | `Get-Content note.txt` |
| blob | 对象库中按对象 ID 定位的一份内容；不包含文件名 | 知道 ID 后用 `git cat-file -p <ID>` |
| 索引 / 暂存区 | 记录路径、mode、对象 ID 等信息；本次关注路径指向哪份 blob | `git ls-files --stage`、`git show :note.txt` |
| HEAD 中的文件 | 当前提交的树记录的该路径内容 | `git show HEAD:note.txt` |

索引不是另一个可直接打开的文本目录。`git add` 选定当时的文件内容，把对象 ID 放入对应条目；后续写文件操作不会主动改这个条目。普通索引提交使用这些条目形成快照。[add 文档](https://github.com/git/git/blob/v2.45.1/Documentation/git-add.txt)、[commit 文档](https://github.com/git/git/blob/v2.45.1/Documentation/git-commit.txt)

先用一句话复述工作区与索引的区别。未能说明时先修正模型，暂不开始练习。

## 本次命令和记号

以下命令在实验仓库内执行，逐条讲解后再用；它们是可用工具，不是要求一次粘贴的完整操作顺序。

| 写法 | 每个新部分的用途 |
| --- | --- |
| `Get-Content note.txt` | PowerShell 读取该路径的文件内容 |
| `Set-Content -LiteralPath note.txt -Value 'C' -Encoding ascii` | PowerShell 把文件写成 C 并追加行末换行；`-LiteralPath` 按原样使用路径，`-Value` 是写入值，`ascii` 统一本实验编码 |
| `git add note.txt` | `add` 子命令暂存指定路径当前的内容 |
| `git ls-files --stage` | 输出索引条目；每行包含 mode、对象 ID、stage 与路径，普通无冲突条目的 stage 为 0 |
| `git show ":note.txt"` | 引号传入一个完整参数；开头的冒号表示从索引定位路径，不是 Windows 盘符 |
| `git show "HEAD:note.txt"` | `HEAD` 指当前提交；冒号后是该提交树内的路径 |
| `git cat-file -p <ID>` | `cat-file` 检查对象，`-p` 按对象类型显示可读内容；把 `<ID>` 换成实际值，不输入尖括号 |
| `git hash-object note.txt` | 计算当前文件对应的对象 ID；本次不带 `-w`，不要求把这份内容写入对象库 |
| `git commit -m "save staged note"` | `commit` 创建提交，`-m` 提供消息；本次没有 `-a` 或路径参数 |

索引条目格式参考[索引文档](https://git-scm.com/docs/gitformat-index)；对象检查与命令细节通过[官方命令目录](https://git-scm.com/docs/git)定位。本课不要求记住某个固定哈希值。

## 一个最小例子

假设工作区文件的内容是 `draft`。执行 `git add note.txt` 后，索引条目选择了该内容的对象 ID。随后编辑器将文件改为 `final`，改变的是工作区文件。

此时先回答：再次查看索引需要用表中哪条命令？它与直接读取文件是否在检查同一个位置？教练等待回答后再交付 B/C 变体。

## 阅读实际源码

基线：上游 Git `v2.45.1`。下面按本实验“已跟踪文件有修改”的条件导航，部分步骤被省略，不是完整调用栈。

| 位置 | 本次关注的问题 |
| --- | --- |
| [`git.c`](https://github.com/git/git/blob/v2.45.1/git.c) 的 `commands[]` 与 `run_builtin` | 字符串 `add` 如何对应 `cmd_add`；函数指针是怎样被调用的 |
| [`builtin/add.c`](https://github.com/git/git/blob/v2.45.1/builtin/add.c) 的 `cmd_add` | 解析参数、准备索引，处理已跟踪路径，最后调用 `write_locked_index` |
| [`read-cache.c`](https://github.com/git/git/blob/v2.45.1/read-cache.c) 的 `add_files_to_cache`、`update_callback` | 把差异结果交给回调；修改路径进入 `add_file_to_index`。此处经过回调，不能省略成相邻直接调用 |
| 同文件的 `add_file_to_index`、`add_to_index` | 检查文件、准备条目、调用 `index_path` 得到 `ce->oid`，再更新内存索引；存在未变化时提前返回等其他分支 |
| [`object-file.c`](https://github.com/git/git/blob/v2.45.1/object-file.c) 的 `index_path`、`index_fd` | 普通文件被打开并读取；当前实验的小文件进入内容处理路径，对象 ID 返回给索引条目 |

本实验已经跟踪 `note.txt`；新文件收集还有 `add_files` 路径，不要把两条路径混为一条。源码中的“cache”在这些函数名里与索引有关。

遇到以下写法时先讲解：`struct` 表示结构体，`ce->oid` 通过指针访问成员，`&ce->oid` 传成员地址供函数写入，函数指针用于保存可调用函数，回调是在后续处理阶段被调用的函数。首次只解释当前几行需要的语法，不展开所有宏与结构字段。

源码阅读的出口是指出“读取内容”“更新内存条目”“写入磁盘索引”的职责和先后关系，不要求背函数名。对象写入可能复用已有内容；不要推断每次 add 都必定新建一个对象文件。

## 接下来的本人练习

转到[首课实验说明](../../exercises/g1-add-snapshot/README.md)。先写预测，再操作，保留三个位置的内容和对象 ID 证据。最后在教练提出的“再执行一次 add”小变体中解释原因，不需要现在阅读后续单元。
