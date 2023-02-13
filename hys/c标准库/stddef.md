## 简介

**stddef .h** 头文件定义了各种变量类型和宏。这些定义中的大部分也出现在其它头文件中。

## 库变量

下面是头文件 stddef.h 中定义的变量类型：

| 序号 |                         变量 & 描述                          |
| :--: | :----------------------------------------------------------: |
|  1   |  **ptrdiff_t** 这是有符号整数类型，它是两个指针相减的结果。  |
|  2   | **size_t** 这是无符号整数类型，它是 **sizeof** 关键字的结果。 |
|  3   |        **wchar_t** 这是一个宽字符常量大小的整数类型。        |

## 库宏

下面是头文件 stddef.h 中定义的宏：

| 序号 |                          宏 & 描述                           |
| :--: | :----------------------------------------------------------: |
|  1   | [NULL](https://www.runoob.com/cprogramming/c-macro-null.html) 这个宏是一个空指针常量的值。 |
|  2   | [offsetof(type, member-designator)](https://www.runoob.com/cprogramming/c-macro-offsetof.html) 这会生成一个类型为 size_t 的整型常量，它是一个结构成员相对于结构开头的字节偏移量。成员是由 *member-designator* 给定的，结构的名称是在 *type* 中给定的。 |