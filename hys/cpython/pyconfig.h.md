~~~c
#ifndef Py_CONFIG_H
#define Py_CONFIG_H
~~~



~~~c
/* pyconfig.h.  NOT Generated automatically by configure.

This is a manually maintained version used for the Watcom,
Borland and Microsoft Visual C++ compilers.  It is a
standard part of the Python distribution.

WINDOWS DEFINES:
The code specific to Windows should be wrapped around one of
the following #defines

MS_WIN64 - Code specific to the MS Win64 API
MS_WIN32 - Code specific to the MS Win32 (and Win64) API (obsolete, this covers all supported APIs)
MS_WINDOWS - Code specific to Windows, but all versions.
Py_ENABLE_SHARED - Code if the Python core is built as a DLL.

Also note that neither "_M_IX86" or "_MSC_VER" should be used for
any purpose other than "Windows Intel x86 specific" and "Microsoft
compiler specific".  Therefore, these should be very rare.


NOTE: The following symbols are deprecated:
NT, USE_DL_EXPORT, USE_DL_IMPORT, DL_EXPORT, DL_IMPORT
MS_CORE_DLL.

WIN32 is still required for the locale module.

*/
~~~

windows的定义：

1. MS_WIN64

2. MS_WIN32

3. MS_WINDOWS
4. Py_ENABLE_SHARED Code if the Python core is built as a DLL.



NT, USE_DL_EXPORT, USE_DL_IMPORT, DL_EXPORT, DL_IMPORT, MS_CORE_DLL. 弃用

~~~c
/* Deprecated USE_DL_EXPORT macro - please use Py_BUILD_CORE */
#ifdef USE_DL_EXPORT
#       define Py_BUILD_CORE
#endif /* USE_DL_EXPORT */
~~~

弃用USE_DL_EXPORT

改用Py_BUILD_CORE



~~~c
/* Visual Studio 2005 introduces deprecation warnings for
   "insecure" and POSIX functions. The insecure functions should
   be replaced by *_s versions (according to Microsoft); the
   POSIX functions by _* versions (which, according to Microsoft,
   would be ISO C conforming). Neither renaming is feasible, so
   we just silence the warnings. */

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE 1
#endif
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE 1
#endif
~~~

Visual Studio 2005引入弃用警告insecure和POSIX函数。 不安全的函数应该被*_s版本所取代(根据微软的说法); POSIX函数的\_\*版本(根据微软的说法，符合ISO C标准)。 两种重命名都不可行，所以我们只是让他不警告。



~~~c
#define HAVE_IO_H
#define HAVE_SYS_UTIME_H
#define HAVE_TEMPNAM
#define HAVE_TMPFILE
#define HAVE_TMPNAM
#define HAVE_CLOCK
#define HAVE_STRERROR

#include <io.h>

#define HAVE_STRFTIME
#define DONT_HAVE_SIG_ALARM
#define DONT_HAVE_SIG_PAUSE
#define LONG_BIT        32
#define WORD_BIT 32

#define MS_WIN32 /* only support win32 and greater. */
#define MS_WINDOWS
#define NT_THREADS
#define WITH_THREAD
#ifndef NETSCAPE_PI
	#define USE_SOCKET
#endif
~~~

定义了一些预定义头

其中io.h:

~~~c
//
// io.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// This file declares the low-level I/O and file handling functionality.
//
#pragma once
#ifndef _INC_IO // include guard for 3rd party interop
    #define _INC_IO
    #include <corecrt_io.h>
#endif // _INC_IO
~~~



~~~c
/* Compiler specific defines */

/* ------------------------------------------------------------------------*/
/* Microsoft C defines _MSC_VER */
/*
MS VC++ 16.0 _MSC_VER = 1928 (Visual Studio 2019)
MS VC++ 15.0 _MSC_VER = 1910 (Visual Studio 2017)
MS VC++ 14.0 _MSC_VER = 1900 (Visual Studio 2015)
MS VC++ 12.0 _MSC_VER = 1800 (VisualStudio 2013)
MS VC++ 11.0 _MSC_VER = 1700 (VisualStudio 2012)
MS VC++ 10.0 _MSC_VER = 1600(VisualStudio 2010)
MS VC++ 9.0 _MSC_VER = 1500(VisualStudio 2008)
MS VC++ 8.0 _MSC_VER = 1400(VisualStudio 2005)
MS VC++ 7.1 _MSC_VER = 1310(VisualStudio 2003)
MS VC++ 7.0 _MSC_VER = 1300(VisualStudio .NET)
MS VC++ 6.0 _MSC_VER = 1200(VisualStudio 98)
MS VC++ 5.0 _MSC_VER = 1100(VisualStudio 97)
*/
#ifdef _MSC_VER
    /* We want COMPILER to expand to a string containing _MSC_VER's *value*.
     * This is horridly tricky, because the stringization operator only works
     * on macro arguments, and doesn't evaluate macros passed *as* arguments.
     * Attempts simpler than the following appear doomed to produce "_MSC_VER"
     * literally in the string.
     扩展一个包含_MSC_VER的字符串宏
     */ 
    #define _Py_PASTE_VERSION(SUFFIX) \
            ("[MSC v." _Py_STRINGIZE(_MSC_VER) " " SUFFIX "]")
    /* e.g., this produces, after compile-time string catenation,
     *      ("[MSC v.1200 32 bit (Intel)]")
     *
     * _Py_STRINGIZE(_MSC_VER) expands to
     * _Py_STRINGIZE1((_MSC_VER)) expands to
     * _Py_STRINGIZE2(_MSC_VER) but as this call is the result of token-pasting
     *      it's scanned again for macros and so further expands to (under MSVC 6)
     * _Py_STRINGIZE2(1200) which then expands to
     * "1200"
     */
    #define _Py_STRINGIZE(X) _Py_STRINGIZE1((X))
    #define _Py_STRINGIZE1(X) _Py_STRINGIZE2 ## X
    #define _Py_STRINGIZE2(X) #X
    // _Py_STRINGIZE2(X) #X ==》 _Py_STRINGIZE2(helloworld) = _Py_STRINGIZE2("helloworld")
    // _Py_STRINGIZE1(X) _Py_STRINGIZE2 ## X ==》 _Py_STRINGIZE2X 拼接


    #ifdef _WIN64
        #define MS_WIN64
    // 定义MS_WIN64

#endif
~~~



~~~c
/* set the COMPILER and support tier
 * 设置编译器和支持层
 * win_amd64 MSVC (x86_64-pc-windows-msvc): 1
 * win32 MSVC (i686-pc-windows-msvc): 1
 * win_arm64 MSVC (aarch64-pc-windows-msvc): 3
 * other archs and ICC: 0
 */
#ifdef MS_WIN64
    #if defined(_M_X64) || defined(_M_AMD64)
        #if defined(__INTEL_COMPILER)
            #define COMPILER ("[ICC v." _Py_STRINGIZE(__INTEL_COMPILER) " 64 bit (amd64) with MSC v." _Py_STRINGIZE(_MSC_VER) " 			CRT]")
            #define PY_SUPPORT_TIER 0
        #else
            #define COMPILER _Py_PASTE_VERSION("64 bit (AMD64)")
            #define PY_SUPPORT_TIER 1
        #endif /* __INTEL_COMPILER */
		#define PYD_PLATFORM_TAG "win_amd64"
	#elif defined(_M_ARM64)


~~~







