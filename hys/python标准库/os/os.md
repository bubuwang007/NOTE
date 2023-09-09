`os`模块提供了一种使用与操作系统相关的功能的便捷式途径。

# 内置的异常

## `os.error`

~~~python
os.error # 内建的OSError的别名
~~~



# 运行平台相关

## `os.name`

运行代码的操作系统的名称。以下名称目前已注册: `'posix'`, `'nt'`, `'java'`.

需要更详细的操作系统信息可参阅 `sys.platform`

```txt
posix  Linux 和 Mac OS
nt  Windows
java  Java 虚拟机环境
```



## `os.uname()`

返回当前操作系统的识别信息。返回值是一个有5个属性的对象：

- `sysname` - 操作系统名
- `nodename` - 机器在网络上的名称（需要先设定）
- `release` - 操作系统发行信息
- `version` - 操作系统版本信息
- `machine` - 硬件标识符

为了向后兼容，该对象也是可迭代的，像是一个按照 `sysname`，`nodename`，`release`，`version`，和 `machine` 顺序组成的元组。

*在 3.3 版更改:* 返回结果的类型由元组变成一个类似元组的对象，同时具有命名的属性。

可用: ==仅Unix可用==



# 环境变量

## `os.environ`

一个 [mapping](https://docs.python.org/zh-cn/3/glossary.html#term-mapping) 对象，其中键值是代表进程环境的字符串。 例如，`environ['HOME']` 是你的主目录（在某些平台上）的路径名，相当于 C 中的 `getenv("HOME")`。

这个映射是在第一次导入`os`模块时捕获的，通常作为 Python 启动时处理 `site.py` 的一部分。除了通过直接修改`os.environ`之外，在此之后对环境所做的更改不会反映在`os.environ`中。

该映射除了可以用于查询环境外，还能用于修改环境。当该映射被修改时，将自动调用 `putenv()`。

可以删除映射中的元素来删除对应的环境变量。当从 `os.environ`删除元素时，以及调用 `pop()` 或 `clear()` 之一时，将自动调用 `unsetenv()`。

> 注: 直接调用 `putenv()`和  `unsetenv()`并不会影响 `os.environ` ，所以推荐直接修改 `os.environ`。



## `os.putenv(key, value, /)`

将名为 *key* 的环境变量值设置为 *value*。该变量名修改会影响由`os.system()`, `popen()`, `fork()` 和 `execv()` 发起的子进程。



## `os.unsetenv(key, /)`

删除名为 *key* 的环境变量。变量名的改变会影响由 `os.system()`，`popen()`，`fork()` 和 `execv()` 触发的子进程。



## `os.environb`

`environ` 的字节版本：一个 mapping 对象，其中键值都是 bytes 对象，代表进程环境。 `environ` 和 `environb` 是同步的（修改 `environb` 会更新 environ，反之亦然）。只有在 `supports_bytes_environ`为 `True` 的时候 `environb`才是可用的。

*3.2 新版功能.*

 ==Windows不可用==



## `os.supports_bytes_environ`

如果操作系统上原生环境类型是字节型则为 `True` (例如在 Windows 上为 `False`)。

*3.2 新版功能.*

 ==Windows为False==

# 进程参数

这些函数和数据项提供了操作当前进程和用户的信息。

## Windows可用







## 非Windows可用

## `os.ctermid()`

返回与进程控制终端对应的文件名。

可用: ==Unix, not Emscripten, not WASI==



## `os.setegid(egid, /)`

设置当前进程的有效组ID。

可用: ==Unix, not Emscripten, not WASI==



## `os.seteuid(euid, /)`

设置当前进程的有效用户ID。

可用: ==Unix, not Emscripten, not WASI==



## `os.setgid(gid, /)`

设置当前进程的有效用户ID。

可用: ==Unix, not Emscripten, not WASI==







# 文件和目录

## `os.access(path, mode, *, dir_fd=None, effective_ids=False, follow_symlinks=True)`

测试调用用户是否具有对 *path* 的指定访问权限。

*mode* 为 `F_OK`时用于测试 *path* 是否存在，也可以对 `R_OK`、`W_OK` 和 `X_OK`中的一个或多个进行“或”运算来测试指定权限。允许访问则返回 [`True`](https://docs.python.org/zh-cn/3/library/constants.html#True)，否则返回 [`False`](https://docs.python.org/zh-cn/3/library/constants.html#False)。

~~~txt
os.F_OK: 测试path是否存在。
os.R_OK: 测试path是否可读。
os.W_OK: 测试path是否可写。
os.X_OK: 测试path是否可执行。
~~~

如果 *effective_ids* 为 `True`，`access()`将使用 有效用户ID/用户组ID 而非 实际用户ID/用户组ID 进行访问检查。您的平台可能不支持 *effective_ids*，您可以使用 `os.supports_effective_ids`检查它是否可用。如果不可用，使用它时会抛出 `NotImplementedError`异常。

*在 3.3 版更改:* 添加 `dir_fd`、`effective_ids` 和 `follow_symlinks` 参数。

*在 3.6 版更改:* 接受一个 `path-like object`。



## `os.supports_dir_fd`

一个 `set`对象，指示 `os`模块中的哪些函数接受一个打开的文件描述符作为 `dir_fd` 参数。不同平台提供的功能不同，且 Python 用于实现 `dir_fd` 参数的底层函数并非在 Python 支持的所有平台上都可用。考虑到一致性，支持 `dir_fd` 的函数始终允许指定描述符，但如果在底层不支持时调用了该函数，则会抛出异常。（在所有平台上始终支持将 `dir_fd` 指定为 `None`。）

要检查某个函数是否接受打开的文件描述符作为 `dir_fd` 参数，请在 `supports_dir_fd` 前使用 `in` 运算符。例如，如果 [`os.stat()`](https://docs.python.org/zh-cn/3/library/os.html#os.stat) 在当前平台上接受打开的文件描述符作为 `dir_fd` 参数，则此表达式的计算结果为 `True`:

```
os.stat in os.supports_dir_fd
```

==目前`dir_fd`  参数仅在 Unix 平台上有效，在 Windows 上无效。==

*3.3 新版功能.*

可用: ==目前仅 Unix 平台支持，Windows 不支持。==



## `os.supports_effective_ids`

一个 `set`对象，指示 `os.access()`是否允许在当前平台上将其 *effective_ids* 参数指定为 `True`。（所有平台都支持将 *effective_ids* 指定为 `False`。）如果当前平台支持，则集合将包含 `os.access()`，否则集合为空。

如果当前平台上的 [`os.access()`](https://docs.python.org/zh-cn/3/library/os.html#os.access) 支持 `effective_ids=True`，则此表达式的计算结果为 `True`:

```
os.access in os.supports_effective_ids
```

*3.3 新版功能*。

可用: ==目前仅 Unix 平台支持，Windows 不支持。==



## `os.chdir(path)`

将当前工作目录更改为 *path*。

本函数支持 指定文件描述符为参数。其中，描述符必须指向打开的目录，不能是打开的文件。

本函数可以抛出 `OSError`及其子类的异常，如 `FileNotFoundError`、[`PermissionError`](https://docs.python.org/zh-cn/3/library/exceptions.html#PermissionError) 和 [`NotADirectoryError`](https://docs.python.org/zh-cn/3/library/exceptions.html#NotADirectoryError) 异常。

引发一个 [审计事件](https://docs.python.org/zh-cn/3/library/sys.html#auditing) `os.chdir`，附带参数 `path`。

*3.3 新版功能:* 在某些平台上新增支持将 *path* 参数指定为文件描述符。

*在 3.6 版更改:* 接受一个 [path-like object](https://docs.python.org/zh-cn/3/glossary.html#term-path-like-object)。



## `os.fchdir(fd)`

## `os.getcwd()`
