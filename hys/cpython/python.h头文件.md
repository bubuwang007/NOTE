~~~
#ifndef Py_PYTHON_H
#define Py_PYTHON_H
~~~

定义 Py_PYTHON_H



~~~
// Include Python header files
#include "patchlevel.h"
#include "pyconfig.h"
#include "pymacconfig.h"
~~~

引入python头文件，主要为版本和配置信息，后续学习。



~~~
#if defined(__sgi) && !defined(_SGI_MP_SOURCE)
#  define _SGI_MP_SOURCE
#endif
~~~

不知道啥用



~~~~
// stdlib.h, stdio.h, errno.h and string.h headers are not used by Python
// headers, but kept for backward compatibility. They are excluded from the
// limited C API of Python 3.11.
#if !defined(Py_LIMITED_API) || Py_LIMITED_API+0 < 0x030b0000
#  include <stdlib.h>
#  include <stdio.h>              // FILE*
#  include <errno.h>              // errno
#  include <string.h>             // memcpy()
#endif
#ifndef MS_WINDOWS
#  include <unistd.h>
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>             // size_t
#endif
~~~~

如果没定义Py_LIMITED_API或Py_LIMITED_API+0 < 0x030b0000，引入stdlib.h, stdio.h, errno.h and string.h，目的暂不明确。

如果定义MS_WINDOWS，引入<unistd.h>

如果定义HAVE_STDDEF_H，引入<stddef.h>





