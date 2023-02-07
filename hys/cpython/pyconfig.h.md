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
		#define COMPILER _Py_PASTE_VERSION("64 bit (ARM64)")
        #define PY_SUPPORT_TIER 3
        #define PYD_PLATFORM_TAG "win_arm64"
	#else
		#define COMPILER _Py_PASTE_VERSION("64 bit (Unknown)")
		#define PY_SUPPORT_TIER 0
	#endif
#endif

/* set the version macros for the windows headers */
/* Python 3.9+ requires Windows 8 or greater */
#define Py_WINVER 0x0602 /* _WIN32_WINNT_WIN8 */
#define Py_NTDDI NTDDI_WIN8
~~~

设置windows相关宏定义



~~~c
/* 
	We only set these values when building Python - we don't want to force
	these values on extensions, as that will affect the prototypes and
	structures exposed in the Windows headers. Even when building Python, we
	allow a single source file to override this - they may need access to
	structures etc so it can optionally use new Windows features if it
	determines at runtime they are available.
*/
#if defined(Py_BUILD_CORE) || defined(Py_BUILD_CORE_BUILTIN) || defined(Py_BUILD_CORE_MODULE)
	#ifndef NTDDI_VERSION
    	#define NTDDI_VERSION Py_NTDDI
    #endif
	#ifndef WINVER
		#define WINVER Py_WINVER
	#endif
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT Py_WINVER
	#endif
#endif

/* _W64 is not defined for VC6 or eVC4 */
#ifndef _W64
	#define _W64
#endif
~~~



~~~c
/* Define like size_t, omitting the "unsigned" */
#ifdef MS_WIN64
	typedef __int64 Py_ssize_t;
	#define PY_SSIZE_T_MAX LLONG_MAX
#else
	typedef _W64 int Py_ssize_t;
	#define PY_SSIZE_T_MAX INT_MAX
#endif
#define HAVE_PY_SSIZE_T 1

#if defined(MS_WIN32) && !defined(MS_WIN64)
	#if defined(_M_IX86)
		#if defined(__INTEL_COMPILER)
			#define COMPILER ("[ICC v." _Py_STRINGIZE(__INTEL_COMPILER) " 32 bit (Intel) with MSC v." _Py_STRINGIZE(_MSC_VER) " 			CRT]")
			#define PY_SUPPORT_TIER 0
		#else
			#define COMPILER _Py_PASTE_VERSION("32 bit (Intel)")
			#define PY_SUPPORT_TIER 1
		#endif /* __INTEL_COMPILER */
		#define PYD_PLATFORM_TAG "win32"
    #elif defined(_M_ARM)
        #define COMPILER _Py_PASTE_VERSION("32 bit (ARM)")
        #define PYD_PLATFORM_TAG "win_arm32"
        #define PY_SUPPORT_TIER 0
	#else
		#define COMPILER _Py_PASTE_VERSION("32 bit (Unknown)")
		#define PY_SUPPORT_TIER 0
	#endif
#endif /* MS_WIN32 && !MS_WIN64 */
			
~~~



~~~c
typedef int pid_t;

/* define some ANSI types that are not defined in earlier Win headers */
#if _MSC_VER >= 1200
/* This file only exists in VC 6.0 or higher */
	#include <basetsd.h>
#endif

#endif /* _MSC_VER */ //结束_MSC_VER
~~~

basetsd.h	Type definitions for the basic sized types.  基本数据类型定义



~~~c
/* ------------------------------------------------------------------------*/
/* mingw and mingw-w64 define __MINGW32__ */
#ifdef __MINGW32__
	#ifdef _WIN64
		#define MS_WIN64
	#endif
#endif /* __MINGW32__*/
~~~



~~~c
/* ------------------------------------------------------------------------*/
/* egcs/gnu-win32 defines __GNUC__ and _WIN32 */
#if defined(__GNUC__) && defined(_WIN32)
/* XXX These defines are likely incomplete, but should be easy to fix.
   They should be complete enough to build extension modules. */
/* Suggested by Rene Liebscher <R.Liebscher@gmx.de> to avoid a GCC 2.91.*
   bug that requires structure imports.  More recent versions of the
   compiler don't exhibit this bug.
*/
    #if (__GNUC__==2) && (__GNUC_MINOR__<=91)
    	#warning "Please use an up-to-date version of gcc! (>2.91 recommended)"
    #endif

    #define COMPILER "[gcc]"
    #define PY_LONG_LONG long long
    #define PY_LLONG_MIN LLONG_MIN
    #define PY_LLONG_MAX LLONG_MAX
    #define PY_ULLONG_MAX ULLONG_MAX
#endif /* GNUC */
~~~



~~~c
/* ------------------------------------------------------------------------*/
/* lcc-win32 defines __LCC__ */
#if defined(__LCC__)
/* XXX These defines are likely incomplete, but should be easy to fix.
   They should be complete enough to build extension modules. */

#define COMPILER "[lcc-win32]"
typedef int pid_t;
/* __declspec() is supported here too - do nothing to get the defaults */

#endif /* LCC */

/* ------------------------------------------------------------------------*/
/* End of compilers - finish up */
~~~

编译器宏定义结束



