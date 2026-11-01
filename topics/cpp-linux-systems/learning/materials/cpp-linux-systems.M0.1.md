# M0.1：把资源释放交给对象生命周期

课次：`cpp-linux-systems.M0.1`。材料准备与来源核对：2026-10-31。

**本节环境：macOS 本机，C++20。** 这一节讲 C++ 的作用域、析构和异常退栈，使用的规则不依赖 Linux 系统调用。暂时不需要启动 Colima。建议结合代码阅读约 8～12 分钟，实际时间按你的节奏。

读完后，你应能沿着一段代码说明：对象什么时候构造、什么时候析构，以及如何利用这个时机释放资源。我们先阅读，再讨论，最后做一个范围较小的文件封装。原先 90 分钟的独立基线暂不开始；先把陌生概念学会。

## 资源为什么需要有人负责释放

程序使用的资源包括文件、动态分配的内存和锁。它们常有成对的操作：打开文件以后要关闭，申请内存以后要释放，取得锁以后要解锁。只做前半步，资源可能持续占用。

如果把释放操作写在函数最后，就必须检查所有离开函数的路径。函数可能运行到末尾，也可能在某个条件成立时提前 return，还可能抛出异常。业务分支越多，手动保证每条路径都释放资源就越容易漏掉。

我们想建立这样的约定：一旦某个对象接管了资源，这个对象就负责资源的释放。业务代码只需保持对象的生命周期正确。这个对象也常被称为资源的“拥有者”；这里的所有权指释放责任，不是变量能否访问这个资源。

RAII 的英文全称是 Resource Acquisition Is Initialization，通常译为“资源获取即初始化”。先记住它的操作含义：让资源获取/接管与对象初始化关联，把资源释放放进对象析构过程。这样 C++ 对对象生命周期的规则就能帮助我们管理资源。[Core Guidelines R.1](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-raii)

## 先观察 C++ 已经提供的自动析构

对于下面这种普通局部对象：

```cpp
{
    SomeClass object;
    // 使用 object
}
```

执行到声明处会构造对象。离开它所在的代码块时，会调用它的析构函数。这个规则也适用于中途 return 离开代码块。这里讨论的是像 object 这样的局部自动对象，尚不讨论全局对象、static 或直接 new 出来的对象。[局部对象离开代码块的规则](https://eel.is/c++draft/stmt.dcl)

构造函数使用类名，例如 `SomeClass(...)`，负责对象的初始化。析构函数在类名前加 `~`，例如 `~SomeClass()`，没有参数、没有返回类型；对象被销毁时，C++ 按规则调用它。普通局部对象不需要你手动写 `object.~SomeClass()`。[析构函数规则](https://eel.is/c++draft/class.dtor)

先用一个只打印日志的类观察时机。它还没有管理文件，只是帮助我们看清“创建与销毁”发生在哪里：

```cpp
#include <iostream>

class ScopeTrace {
public:
    ScopeTrace(const char* label) : label_(label)
    {
        std::cout << "enter " << label_ << '\n';
    }

    ~ScopeTrace()
    {
        std::cout << "leave " << label_ << '\n';
    }

private:
    const char* label_;
};
```

`label_` 保存传入的名称，便于区分日志。冒号后的 `label_(label)` 是成员初始化列表：在构造函数体执行前，用参数 label 初始化成员 label_。示例传入的都是字符串字面量，例如 `"outer"`；这些文字在整个程序运行期间都存在，因此本例保存其指针来打印。这里没有动态分配字符串，也没有引入字符串所有权问题。

创建 `ScopeTrace outer("outer");` 时打印 `enter outer`，销毁它时打印 `leave outer`。这两条日志来自我们写的函数体；决定何时调用这些函数的是 C++ 的对象生命周期规则。

## 三条路径，共用同一个销毁机制

现在使用刚才的类：

```cpp
#include <stdexcept>

void work(bool early, bool fail)
{
    ScopeTrace outer("outer");
    {
        ScopeTrace inner("inner");
        if (early) {
            return;
        }
        if (fail) {
            throw std::runtime_error("demo");
        }
        std::cout << "body\n";
    }
    std::cout << "after inner\n";
}
```

`outer` 属于函数体，`inner` 属于内部那对花括号。两个对象先后构造；要一起离开它们的作用域时，后构造的先析构。

调用 `work(false, false)`，代码按普通路径执行：

```text
enter outer
enter inner
body
leave inner
after inner
leave outer
```

`inner` 在内部代码块结束时已经销毁，所以 `after inner` 出现时，outer 仍然存在，inner 已不再存在。

调用 `work(true, false)`，执行到 return 就离开整个函数：

```text
enter outer
enter inner
leave inner
leave outer
```

虽然 return 后的业务语句不再执行，C++ 仍然要销毁离开的作用域中的局部对象。析构不是放在函数末尾、可能被 return 跳过的普通业务语句；它由语言的退出规则安排执行。

第三条路径是抛出异常，并让调用者捕获：

```cpp
try {
    work(false, true);
} catch (const std::exception& error) {
    std::cout << "caught: " << error.what() << '\n';
}
```

`throw` 报告异常，普通执行路径转向匹配的 catch。`std::runtime_error` 是标准库异常类型，`what()` 提供说明文字。这里的 `const std::exception&` 用引用接收异常对象，避免为了接收而复制它；本节先掌握控制流即可。

输出为：

```text
enter outer
enter inner
leave inner
leave outer
caught: demo
```

从抛出位置向外寻找并进入异常处理代码时，会销毁沿途已经成功构造的局部对象。这一过程叫“栈展开”或“异常退栈”。因此，调用者的 catch 开始执行前，work 里面的 inner、outer 已经按相反顺序析构。[异常退栈规则](https://eel.is/c++draft/except.ctor)

可以把三条路径连成同一条机制：

```text
成功构造局部拥有者 → 使用资源
                        ↓
          运行到块末尾 / 提前 return / 异常退栈
                        ↓
                  调用拥有者的析构
                        ↓
                    执行资源释放
```

本例日志程序已经由教练在 Mac 上编译运行核对；源码位于 `exercises/m0-raii-file/scope_trace.cpp`。现在不要求你运行它或修改练习，先把输出与作用域连起来。

## 从“打印日志”连接到“关闭文件”

ScopeTrace 演示了析构时机。真正的 RAII 类型利用同样的时机做清理。标准库 `std::ofstream` 就是一个可以直接使用的文件对象：

```cpp
#include <fstream>

void save_report(bool stop)
{
    std::ofstream output("raii-reading-demo.txt");
    if (!output) {
        return; // 文件未成功打开
    }
    output << "header\n";
    if (stop) {
        return;
    }
    output << "body\n";
}
```

output 对象负责管理关联的文件流。成功打开后，无论这次走到函数末尾还是 stop 分支离开，output 的析构都会处理关闭。你无需在每个 return 前重复调用 close。标准库文件流已经实现了相应资源管理；这段代码只是使用现成类型，没有给出我们待写的 FileOwner 实现。[标准文件流与缓冲区析构](https://eel.is/c++draft/filebuf.cons)

文件被关闭和业务数据是否成功写入是两个问题。实际应用仍需检查 I/O 错误；本课先学习释放责任和时机。

以后手写资源封装时，需要让对象保存它管理的资源，并在析构中安排正确释放。编译器不会凭空知道你的成员代表什么资源：例如，普通 `std::FILE*` 局部变量离开作用域，指针变量本身结束生命，并不会自动调用 fclose。RAII 的关键是使用或编写一个真正承担释放责任的对象。

## 先掌握几条边界

“已经成功构造”很重要。如果某个对象自己的构造函数抛异常、尚未构造完成，这个完整对象的析构函数不会正常补跑；已经构造完成的成员有自己的销毁规则。后面的封装实践会据此安排资源获取失败的处理。

同一资源应有清楚的释放责任。把同一个文件句柄交给两个独立拥有者，会造成重复关闭的风险。本节先不复制或移动拥有者；后续小课再讲如何限制复制、如何转移责任，不把这些一次塞进当前练习。

析构承担清理，清理过程中应避免让异常向外逃逸；尤其在异常退栈期间再次抛出异常会导致程序终止。[异常终止规则](https://eel.is/c++draft/except.terminate)说明了这种情况。此处的异常例子都有外层 catch；不把 RAII 扩大理解为进程被强制终止时也必定执行所有清理。

对象生命周期与资源释放是有联系的两件事：语言安排对象何时析构，而资源类型的实现决定析构时清理什么。你在实践中需要建立并验证这种联系。

## 阅读结束后的下一步

先读到能把“局部对象 → 离开作用域 → 析构 → 资源释放”连成一条路径即可，有疑问随时提出。阅读后我们会讨论一个小场景，再进入仅包含作用域与释放的文件实践。此时不要求实现移动构造、移动赋值，也没有开始 90 分钟独立计时。

来源 ID：`cpp-core-guidelines`、`cpp-object-scope`、`cpp-unwinding`、`cpp-destructors`、`cpp-filebuf`、`cpp-termination`。工作草案是滚动文档，本材料只使用 C++20 已有的基础生命周期规则。普通局部对象的这些语言规则在本课不要求切换 Linux；当前代码运行证据只来自 Mac。阅读位置、耗时和理解情况等待学习者确认，材料交付本身不算掌握。
