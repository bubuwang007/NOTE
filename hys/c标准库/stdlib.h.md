## 简介

**stdlib .h** 头文件定义了四个变量类型、一些宏和各种通用工具函数。



## 库变量

| 序号 |                         变量 & 描述                          |
| :--: | :----------------------------------------------------------: |
|  1   | **size_t** 这是无符号整数类型，它是 **sizeof** 关键字的结果。 |
|  2   |        **wchar_t** 这是一个宽字符常量大小的整数类型。        |
|  3   |           **div_t** 这是 **div** 函数返回的结构。            |
|  4   |          **ldiv_t** 这是 **ldiv** 函数返回的结构。           |

~~~c
typedef unsigned __int64 size_t;
typedef unsigned short wchar_t;

typedef struct _div_t
{
    int quot;
    int rem;
} div_t;

typedef struct _ldiv_t
{
    long quot;
    long rem;
} ldiv_t;
~~~



## 库宏

下面是头文件 stdlib.h 中定义的宏：

| 序号 | 宏 & 描述                                                    |
| :--- | :----------------------------------------------------------- |
| 1    | **NULL** 这个宏是一个空指针常量的值。                        |
| 2    | **EXIT_FAILURE** 这是 exit 函数失败时要返回的值。            |
| 3    | **EXIT_SUCCESS** 这是 exit 函数成功时要返回的值。            |
| 4    | **RAND_MAX** 这个宏是 rand 函数返回的最大值。                |
| 5    | **MB_CUR_MAX** 这个宏表示在多字节字符集中的最大字符数，不能大于 MB_LEN_MAX。 |



~~~c
#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

// Argument values for exit()
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Maximum value that can be returned by the rand function:
#define RAND_MAX 0x7fff

// Maximum number of bytes in multi-byte character in the current locale
// (also defined in ctype.h).
#ifndef MB_CUR_MAX
    #if defined _CRT_DISABLE_PERFCRIT_LOCKS && !defined _DLL
        #define MB_CUR_MAX __mb_cur_max
    #else
        #define MB_CUR_MAX ___mb_cur_max_func()
    #endif

    #ifdef _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY
        extern int __mb_cur_max;
    #else
        #define __mb_cur_max (___mb_cur_max_func())
    #endif

    _Post_satisfies_(return > 0 && return < MB_LEN_MAX)
    _ACRTIMP int __cdecl ___mb_cur_max_func(void);

    _Post_satisfies_(return > 0 && return < MB_LEN_MAX)
    _ACRTIMP int __cdecl ___mb_cur_max_l_func(_locale_t _Locale);
#endif
~~~



## 库函数

下面是头文件 stdlib.h 中定义的函数：

| 序号 | 函数 & 描述                                                  |
| :--- | :----------------------------------------------------------- |
| 1    | [double atof(const char *str)](https://www.runoob.com/cprogramming/c-function-atof.html) 把参数 *str* 所指向的字符串转换为一个浮点数（类型为 double 型）。 |
| 2    | [int atoi(const char *str)](https://www.runoob.com/cprogramming/c-function-atoi.html) 把参数 *str* 所指向的字符串转换为一个整数（类型为 int 型）。 |
| 3    | [long int atol(const char *str)](https://www.runoob.com/cprogramming/c-function-atol.html) 把参数 *str* 所指向的字符串转换为一个长整数（类型为 long int 型）。 |
| 4    | [double strtod(const char *str, char **endptr)](https://www.runoob.com/cprogramming/c-function-strtod.html) 把参数 *str* 所指向的字符串转换为一个浮点数（类型为 double 型）。 |
| 5    | [long int strtol(const char *str, char **endptr, int base)](https://www.runoob.com/cprogramming/c-function-strtol.html) 把参数 *str* 所指向的字符串转换为一个长整数（类型为 long int 型）。 |
| 6    | [unsigned long int strtoul(const char *str, char **endptr, int base)](https://www.runoob.com/cprogramming/c-function-strtoul.html) 把参数 *str* 所指向的字符串转换为一个无符号长整数（类型为 unsigned long int 型）。 |
| 7    | [void *calloc(size_t nitems, size_t size)](https://www.runoob.com/cprogramming/c-function-calloc.html) 分配所需的内存空间，并返回一个指向它的指针。 |
| 8    | [void free(void *ptr)](https://www.runoob.com/cprogramming/c-function-free.html) 释放之前调用 *calloc、malloc* 或 *realloc* 所分配的内存空间。 |
| 9    | [void *malloc(size_t size)](https://www.runoob.com/cprogramming/c-function-malloc.html) 分配所需的内存空间，并返回一个指向它的指针。 |
| 10   | [void *realloc(void *ptr, size_t size)](https://www.runoob.com/cprogramming/c-function-realloc.html) 尝试重新调整之前调用 *malloc* 或 *calloc* 所分配的 ptr 所指向的内存块的大小。 |
| 11   | [void abort(void)](https://www.runoob.com/cprogramming/c-function-abort.html) 使一个异常程序终止。 |
| 12   | [int atexit(void (*func)(void))](https://www.runoob.com/cprogramming/c-function-atexit.html) 当程序正常终止时，调用指定的函数 **func**。 |
| 13   | [void exit(int status)](https://www.runoob.com/cprogramming/c-function-exit.html) 使程序正常终止。 |
| 14   | [char *getenv(const char *name)](https://www.runoob.com/cprogramming/c-function-getenv.html) 搜索 name 所指向的环境字符串，并返回相关的值给字符串。 |
| 15   | [int system(const char *string)](https://www.runoob.com/cprogramming/c-function-system.html) 由 string 指定的命令传给要被命令处理器执行的主机环境。 |
| 16   | [void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))](https://www.runoob.com/cprogramming/c-function-bsearch.html) 执行二分查找。 |
| 17   | [void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))](https://www.runoob.com/cprogramming/c-function-qsort.html) 数组排序。 |
| 18   | [int abs(int x)](https://www.runoob.com/cprogramming/c-function-abs.html) 返回 x 的绝对值。 |
| 19   | [div_t div(int numer, int denom)](https://www.runoob.com/cprogramming/c-function-div.html) 分子除以分母。 |
| 20   | [long int labs(long int x)](https://www.runoob.com/cprogramming/c-function-labs.html) 返回 x 的绝对值。 |
| 21   | [ldiv_t ldiv(long int numer, long int denom)](https://www.runoob.com/cprogramming/c-function-ldiv.html) 分子除以分母。 |
| 22   | [int rand(void)](https://www.runoob.com/cprogramming/c-function-rand.html) 返回一个范围在 0 到 *RAND_MAX* 之间的伪随机数。 |
| 23   | [void srand(unsigned int seed)](https://www.runoob.com/cprogramming/c-function-srand.html) 该函数播种由函数 **rand** 使用的随机数发生器。 |
| 24   | [int mblen(const char *str, size_t n)](https://www.runoob.com/cprogramming/c-function-mblen.html) 返回参数 *str* 所指向的多字节字符的长度。 |
| 25   | [size_t mbstowcs(schar_t *pwcs, const char *str, size_t n)](https://www.runoob.com/cprogramming/c-function-mbstowcs.html) 把参数 *str* 所指向的多字节字符的字符串转换为参数 *pwcs* 所指向的数组。 |
| 26   | [int mbtowc(whcar_t *pwc, const char *str, size_t n)](https://www.runoob.com/cprogramming/c-function-mbtowc.html) 检查参数 *str* 所指向的多字节字符。 |
| 27   | [size_t wcstombs(char *str, const wchar_t *pwcs, size_t n)](https://www.runoob.com/cprogramming/c-function-wcstombs.html) 把数组 *pwcs* 中存储的编码转换为多字节字符，并把它们存储在字符串 *str* 中。 |
| 28   | [int wctomb(char *str, wchar_t wchar)](https://www.runoob.com/cprogramming/c-function-wctomb.html) 检查对应于参数 *wchar* 所给出的多字节字符的编码。 |
