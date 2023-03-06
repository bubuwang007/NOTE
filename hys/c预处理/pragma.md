# Pragma 指令与 `__pragma` 和 `_Pragma` 关键字

Pragma 指令指定计算机特定或操作系统特定的编译器功能。 以 `#pragma` 开头行指定 pragma 指令。 使用 Microsoft 特定 **`__pragma`** 关键字可以在宏定义内编写 pragma 指令。 C99 中引入并由 C++11 采用的标准 **`_Pragma`** 预处理器运算符与之类似。



## 语法

`#pragma` token-string
`__pragma` (token-string) // 两个前导下划线 - Microsoft 特定扩展
`_Pragma` (string-literal) // C99



## alloc_textz杂注

