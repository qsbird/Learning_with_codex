# G1.1 — 暂存后继续编辑

本说明供开课时使用；目前只准备材料和起始状态。先阅读[本课材料](../../learning/materials/git-source.G1.1.md)，教练讲解所需命令并等待理解检查。

## Goal / 目标

解释一次普通索引提交为何使用暂存的内容，并能从源码指出索引条目的更新位置。

## Starting point / 起点

教练在学习仓库根目录执行：

```powershell
& ./topics/git-source/exercises/g1-add-snapshot/prepare.ps1
```

脚本输出新实验仓库的绝对路径。进入该路径后操作；默认路径为根目录下的 `out/git-source/g1-add-snapshot/`。

初始状态：`note.txt` 的初始提交内容是 A，索引也为 A；工作区已改为 B。只有一个跟踪文件，无远端。脚本准备的提交不计本人实践。

脚本不删除或覆盖已有实验；需要新副本时传入 `-Name g1-add-snapshot-2`。脚本内部的初始化、局部配置和路径处理由教练负责，本次不要求掌握。

## Prerequisite evidence / 前置证据

当前无本人证据。开课时先解释工作区、索引、blob、HEAD，以及阅读材料列出的命令；正确完成一个当次复述或预测后再开始。

## New syntax / 新写法

`git add`、不带 `-a` 或路径的 `git commit -m`、`git ls-files --stage`、`git show` 的 `:路径` 与 `HEAD:路径`、`git cat-file -p`、`git hash-object`，以及 PowerShell 的文件读取与写入。逐个参数、输入和效果见阅读材料。

## Mini example / 最小例子

```powershell
git show ":note.txt"
```

这条命令查看索引选择的文件内容；双引号将 `:note.txt` 作为完整参数。它不会修改工作区，也不执行提交。

## Predict / 预测

先写下：如果暂存 B，随后把工作区写成 C，然后做一次普通索引提交，提交、索引、工作区各会是什么？哪一步读取了磁盘文件？

教练等待回答，不先代做整个序列。

## Task / 本人任务

1. 检查三个位置的起始内容。
2. 暂存 B，记下该路径的索引对象 ID，并用对象检查命令读取它。
3. 只把工作区内容改成 C，比较索引与工作区的对象 ID；保持暂存操作次数为一次。
4. 创建普通索引提交，保留三处内容的输出。
5. 在固定版本源码中指出内容读入、条目更新、索引落盘的职责；回调步骤要注明。

不要在学习仓库根目录执行实验步骤。不要用 `commit -a`、`commit note.txt` 或额外的 add 改变本轮条件；这些变体之后另选。

## Verify / 验证

在实验仓库执行以下只读检查，并与事先预测逐项比较：

```powershell
git show "HEAD:note.txt"
git show ":note.txt"
Get-Content note.txt
git ls-files --stage
git hash-object note.txt
```

对象 ID 从实际输出取得；不要照抄其他机器或其他文件字节得到的哈希。预测有差异时，先核对操作顺序与命令参数，不额外 add 来“修成”某个结果。

## Explain / 解释

用自己的话说明这次的三处内容与对象 ID 为什么一致或不同；对应到源码中的读取与条目更新职责。随后预测“提交前再执行一次 add”会改变什么，等教练确认需要的变体仓库准备好后再实验。

完成需要本人操作、准确命令输出、正确源码解释和当次小变体；不生成后续复习任务。
