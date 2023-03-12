如果你会用 C，添加新的 Python 内置模块会很简单。以下两件不能用 Python 直接做的事，可以通过 *extension modules* 来实现：实现新的内置对象类型；调用 C 的库函数和系统调用。

为了支持扩展，Python API（应用程序编程接口）定义了一系列函数、宏和变量，可以访问 Python 运行时系统的大部分内容。Python 的 API 可以通过在一个 C 源文件中引用 `"Python.h"` 头文件来使用。

扩展模块的编写方式取决与你的目的以及系统设置；下面章节会详细介绍。

注解：

C扩展接口特指CPython，扩展模块无法在其他Python实现上工作。在大多数情况下，应该避免写C扩展，来保持可移植性。举个例子，如果你的用例调用了C库或系统调用，你应该考虑使用 [`ctypes`](https://www.bookstack.cn/read/python-3.10.0-zh/422388da98311a88.md#module-ctypes) 模块或 [cffi](https://cffi.readthedocs.io/) 库，而不是自己写C代码。这些模块允许你写Python代码来接口C代码，而且可移植性更好。



# 一个简单的例子

让我们创建一个扩展模块 `spam` (Monty Python 粉丝最喜欢的食物…) 并且想要创建对应 C 库函数 `system()` [1](https://www.bookstack.cn/read/python-3.10.0-zh/adb9747775c5cc4c.md#id5) 的 Python 接口。 这个函数接受一个以 null 结尾的字符串参数并返回一个整数。 我们希望可以在 Python 中以如下方式调用此函数:

~~~python
>>> import spam
>>> status = spam.system("ls -l")
~~~

首先创建一个 `spammodule.c` 文件。（传统上，如果一个模块叫 `spam`，则对应实现它的 C 文件叫 `spammodule.c`；如果这个模块名字非常长，比如 `spammify`，则这个模块的文件可以直接叫 `spammify.c`。）

文件中开始的两行是：

~~~c
#define PY_SSIZE_T_CLEAN
#include <Python.h>
~~~

这会导入 Python API（如果你喜欢，你可以在这里添加描述模块目标和版权信息的注释)。

注解:

由于 Python 可能会定义一些能在某些系统上影响标准头文件的预处理器定义，因此在包含任何标准头文件之前，你 *必须* 先包含 `Python.h`。

推荐总是在 `Python.h` 前定义 `PY_SSIZE_T_CLEAN` 。查看 [提取扩展函数的参数](https://www.bookstack.cn/read/python-3.10.0-zh/adb9747775c5cc4c.md#parsetuple) 来了解这个宏的更多内容。

所有在 `Python.h` 中定义的用户可见的符号都具有 `Py` 或 `PY` 前缀，已在标准头文件中定义的那些除外。 考虑到便利性，也由于其在 Python 解释器中被广泛使用，`"Python.h"` 还包含了一些标准头文件: `<stdio.h>`，`<string.h>`，`<errno.h>` 和 `<stdlib.h>`。 如果后面的头文件在你的系统上不存在，它还会直接声明函数 `malloc()`，`free()` 和 `realloc()`。

下面添加C函数到扩展模块，当调用 `spam.system(string)` 时会做出响应，(我们稍后会看到调用)：

~~~c
static PyObject *
spam_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;
    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}
~~~

有个直接翻译参数列表的方法(举个例子，单独的 `"ls -l"` )到要传递给C函数的参数。C函数总是有两个参数，通常名字是 *self* 和 *args* 。