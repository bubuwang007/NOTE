## 简介

C 标准库的 **errno.h** 头文件定义了整数变量 **errno**，它是通过系统调用设置的，在错误事件中的某些库函数表明了什么发生了错误。该宏扩展为类型为 int 的可更改的左值，因此它可以被一个程序读取和修改。

在程序启动时，**errno** 设置为零，C 标准库中的特定函数修改它的值为一些非零值以表示某些类型的错误。您也可以在适当的时候修改它的值或重置为零。

**errno.h** 头文件定义了一系列表示不同错误代码的宏，这些宏应扩展为类型为 **int** 的整数常量表达式。

## 库宏

下面列出了头文件 errno.h 中定义的宏：

| 序号 |                          宏 & 描述                           |
| :--: | :----------------------------------------------------------: |
|  1   | [extern int errno](https://www.runoob.com/cprogramming/c-macro-errno.html) 这是通过系统调用设置的宏，在错误事件中的某些库函数表明了什么发生了错误。 |
|  2   | [EDOM Domain Error](https://www.runoob.com/cprogramming/c-macro-edom.html) 这个宏表示一个域错误，它在输入参数超出数学函数定义的域时发生，errno 被设置为 EDOM。 |
|  3   | [ERANGE Range Error](https://www.runoob.com/cprogramming/c-macro-erange.html) 这个宏表示一个范围错误，它在输入参数超出数学函数定义的范围时发生，errno 被设置为 ERANGE。 |



~~~c
#define EPERM        1  /* Operation not permitted */
#define ENOFILE      2  /* No such file or directory */
#define ENOENT       2
#define ESRCH        3  /* No such process */
#define EINTR        4  /* Interrupted function call */
#define EIO      	 5  /* Input/output error */
#define ENXIO        6  /* No such device or address */
#define E2BIG        7  /* Arg list too long */
#define ENOEXEC      8  /* Exec format error */
#define EBADF        9  /* Bad file descriptor */
#define ECHILD      10  /* No child processes */
#define EAGAIN      11  /* Resource temporarily unavailable */
#define ENOMEM      12  /* Not enough space */
#define EACCES      13  /* Permission denied */
#define EFAULT      14  /* Bad address */
/* 15 - Unknown Error */
#define EBUSY       16  /* strerror reports "Resource device" */
#define EEXIST      17  /* File exists */
#define EXDEV       18  /* Improper link (cross-device link?) */
#define ENODEV      19  /* No such device */
#define ENOTDIR     20  /* Not a directory */
#define EISDIR      21  /* Is a directory */
#define EINVAL      22  /* Invalid argument */
#define ENFILE      23  /* Too many open files in system */
#define EMFILE      24  /* Too many open files */
#define ENOTTY      25  /* Inappropriate I/O control operation */
/* 26 - Unknown Error */
#define EFBIG       27  /* File too large */
#define ENOSPC      28  /* No space left on device */
#define ESPIPE      29  /* Invalid seek (seek on a pipe?) */
#define EROFS       30  /* Read-only file system */
#define EMLINK      31  /* Too many links */
#define EPIPE       32  /* Broken pipe */
#define EDOM        33  /* Domain error (math functions) */
#define ERANGE      34  /* Result too large (possibly too small) */
/* 35 - Unknown Error */
#define EDEADLOCK   36  /* Resource deadlock avoided (non-Cyg) */
#define EDEADLK     36
/* 37 - Unknown Error */
#define ENAMETOOLONG    38  /* Filename too long (91 in Cyg?) */
#define ENOLCK      39  /* No locks available (46 in Cyg?) */
#define ENOSYS      40  /* Function not implemented (88 in Cyg?) */
#define ENOTEMPTY   41  /* Directory not empty (90 in Cyg?) */
#define EILSEQ      42  /* Illegal byte sequence */
~~~

