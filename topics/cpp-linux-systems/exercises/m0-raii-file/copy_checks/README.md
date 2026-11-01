# M0.2：区分两类被禁止的复制操作

课次：`cpp-linux-systems.M0.2`。本节环境：**macOS 本机 / Apple Clang / C++20**。只做语法检查，不运行文件复制或修改现有 FileOwner。

你已理解创建新对象与对已有对象赋值的区别。现在只填写两个文件各一个 TODO：

- `construct.cpp`：用已有 a 初始化一个新 FileOwner，触发被删除的拷贝构造。
- `assign.cpp`：把已有 a 赋给已存在的 c，触发被删除的拷贝赋值。

每个文件独立编译，保持其他代码不动；不改 `file_owner.h`、`control.cpp` 或检查脚本。脚本会先确认两个普通空拥有者可以分别构造，再要求你的两份探针各出现一种特定的编译错误，其他无关错误不算通过。

从仓库根目录运行：

```sh
python3 topics/cpp-linux-systems/exercises/m0-raii-file/copy_checks/check_copy.py
```

成功标准：control.cpp 编译成功；construct.cpp 报 deleted constructor；assign.cpp 报 deleted operator '='；脚本最终返回 0、三行 PASS。这里“两次编译被拒绝”正是我们要验证的行为。初始两个 TODO 为空，因此后两项会 FAIL。

辅助脚本只对当前 Clang 英文诊断作匹配，`--probe-dir` 供教练验证脚手架。它不链接、不执行被拒绝的程序，也不生成源目录中的二进制。

说明材料：[拷贝构造与拷贝赋值](../../../learning/materials/copy-construction-vs-assignment.md)。这次实践前完整语句示例已经讲解过，按有帮助的编译验证记录；不以两个语句的复写宣称从零独立资源类型设计。实际改好后解释两种错误为何不同，再作一个没有给出答案的小迁移。
