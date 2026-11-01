# 拷贝构造与拷贝赋值：看目标对象是否已经存在

课次上下文：`cpp-linux-systems.M0` 的复制约束前置讲解。准备/核对日期：2026-11-01。**环境：macOS 本机，C++20。** 本次只讲两种操作及禁止方式，暂不展开移动语义。

两条声明共同规定 FileOwner 不允许复制，但保护的入口不同。判断时先问：目标对象是在这条语句中刚创建，还是早已存在？

## 创建一个新对象：拷贝构造

```cpp
FileOwner(const FileOwner&) = delete;
```

名字和类名相同、没有返回类型，所以它是构造函数。参数是同类型对象的引用，表示以已有对象作为构造来源；const 表示不能通过这个引用修改来源，& 表示引用，不会为传这个参数又复制一份对象。

如果允许这项操作，下面两种写法都会用已有 a 初始化新对象 b：

```cpp
m0::FileOwner a(nullptr);
m0::FileOwner b(a);     // b 在这里创建：拷贝构造
```

或者：

```cpp
m0::FileOwner a(nullptr);
m0::FileOwner b = a;    // b 在这里创建：仍然是拷贝构造
```

第二种写法虽然带等号，但它是一条声明和初始化语句，不是对已有 b 赋值。对于这里已有名字的同类型对象 a，两种写法都受拷贝构造声明约束。

## 修改一个已经存在的对象：拷贝赋值

```cpp
FileOwner& operator=(const FileOwner&) = delete;
```

operator= 是赋值运算符函数。其参数表示赋值来源；最前面的 FileOwner& 是返回类型，常规赋值接口返回目标对象的引用。这里函数已被删除，不会真的执行返回。

```cpp
m0::FileOwner a(nullptr);
m0::FileOwner b(nullptr); // b 此时已经存在
b = a;                   // 对已有 b 赋值：拷贝赋值
```

赋值并不重新开始 b 的生命周期，也不是销毁 b 再重新构造。对于资源拥有者，还必须考虑 b 原先负责的资源如何处理；直接覆盖一个原有句柄还可能遗失它的释放责任。我们当前选择禁止复制，之后另学资源转移。

## = delete 表示禁止调用这项操作

它不是运行时释放内存的 delete 表达式，也不是把函数写成空函数体。编译器选中被删除的函数时，会拒绝这段代码。

因此上面故意演示的拷贝写法，在现有 FileOwner 中都不能通过编译。第一条声明保护“复制出新对象”的入口，第二条保护“向已有对象赋值”的入口。只禁止其中一种，不能完整表达禁止复制这两种操作的要求。

| 写法（a 是已有同类型对象） | b 的状态 | 操作 |
|---|---|---|
| `FileOwner b(a);` | 正在创建 | 拷贝构造 |
| `FileOwner b = a;` | 正在创建 | 拷贝构造 |
| `b = a;` | 已经存在 | 拷贝赋值 |

普通数据值经常可以合理复制；独占文件拥有者若仅复制指针，会让两个对象都承担同一文件的关闭责任。当前两条声明把这类误用尽早变成编译错误；本节不要求你删除现有防护或运行重复关闭程序。

教练已在本机用 `-fsyntax-only` 分别编译两个空句柄示例：创建 b 的示例报告 deleted constructor；已有 b 的赋值示例报告 deleted operator '='。编译拒绝正是预期，不是运行时崩溃；示例未执行，也没有修改你的 FileOwner。

来源 ID：`cpp-copy-constructor`、`cpp-copy-assignment`、`cpp-deleted-functions`。依据 [拷贝构造](https://eel.is/c++draft/class.copy.ctor)、[拷贝赋值](https://eel.is/c++draft/class.copy.assign) 与 [删除的函数](https://eel.is/c++draft/dcl.fct.def.delete)。这些是滚动 C++ 工作草案，本次只使用 C++20 已有基础规则。

## 追问补充：两种初始化形式为何又有区别

`FileOwner b(a)` 是直接初始化，`FileOwner b = a` 是拷贝初始化。当前a是已有同类型对象，两种形式都选择拷贝构造；但一般规则不等价。

```cpp
class Number {
public:
    explicit Number(int value) : value_(value) {}
private:
    int value_;
};
Number x(3);  // 直接初始化允许使用 explicit 构造
Number y = 3; // 此转换不能使用 explicit 构造，编译拒绝
```

`explicit` 要求明确构造，限制隐式转换。“拷贝初始化”是语法名称，不保证所有情况都执行一次对象复制。[构造转换规则](https://eel.is/c++draft/class.conv.ctor)，来源ID：`cpp-constructor-conversion`。本小课不再扩展移动或拷贝消除。

先理解两个场景，有疑问继续问。此时还没有下发新的编码任务；讲解、示例和编译结果不替代你的理解或实践证据。
