~~~
Welcome to the "PC" subdirectory of the Python distribution
***********************************************************
~~~



~~~
This "PC" subdirectory contains complete project files to make several older PC ports of Python, as well as all the PC-specific Python source files. 
这个“PC”子目录包含完整的项目文件，用于制作Python的几个旧PC端口，以及所有特定于PC的Python源文件。

It should be located in the root of the Python distribution, and there should be directories "Modules", "Objects", "Python", etc. in the parent directory of this "PC" subdirectory. 
它应该位于Python发行版的根目录中，并且在这个“PC”子目录的父目录中应该有“Modules”、“Objects”、“Python”等目录。

Be sure to read the documentation in the Python distribution.
~~~



~~~
Python requires library files such as string.py to be available in one or more library directories. The search path of libraries is set up when Python starts. To see the current Python library search path, start Python and enter "import sys" and "print sys.path".
Python要求诸如string.py这样的库文件在一个或多个库目录中可用。库的搜索路径是在Python启动时设置的。要查看当前Python库搜索路径，请启动Python并输入“import sys”和“print sys.path”。
~~~



~~~
All PC ports use this scheme to try to set up a module search path:

  1) The script location; the current directory without script.
  2) The PYTHONPATH variable, if set.
  3) Paths specified in the Registry.
  4) Default directories lib, lib/win, lib/test, lib/tkinter;
     these are searched relative to the environment variable
     PYTHONHOME, if set, or relative to the executable and its
     ancestors, if a landmark file (Lib/string.py) is found ,
     or the current directory (not useful).
  5) The directory containing the executable.
~~~



~~~
The best installation strategy is to put the Python executable and DLL in some convenient directory such as C:/python, and copy all library files and subdirectories (using XCOPY) to C:/python/lib.
最好的安装策略是将Python可执行文件和DLL放在一些方便的目录中，例如C:/ Python，并复制所有库文件和子目录(使用XCOPY)

Then you don't need to set PYTHONPATH.  Otherwise, set the environment variable PYTHONPATH to your Python search path.
For example, set PYTHONPATH=.;d:\python\lib;d:\python\lib\win;d:\python\lib\dos-8x3
~~~



~~~
There are several add-in modules to build Python programs which use the native Windows operating environment.  The ports here just make "QuickWin" and DOS Python versions which support a character-mode (console) environment.  Look in www.python.org for Tkinter, PythonWin, WPY and wxPython.
有几个外接程序模块用于构建使用本机Windows操作环境的Python程序。这里的端口只是支持字符模式(控制台)环境的“QuickWin”和DOS Python版本。在www.python.org中查找Tkinter, PythonWin, WPY和wxPython。
~~~



~~~
To make a Python port, start the Integrated Development Environment (IDE) of your compiler, and read in the native "project file" (or makefile) provided.  This will enable you to change any source files or build settings so you can make custom builds.
要进行Python移植，请启动编译器的集成开发环境(IDE)，并读取提供的本地“项目文件”(或makefile)。这将使您能够更改任何源文件或构建设置，以便您可以进行自定义构建。
~~~



~~~
pyconfig.h    An important configuration file specific to PC's.

config.c    The list of C modules to include in the Python PC version. Manually edit this file to add or remove Python modules.
			Python PC版中要包含的C模块列表。手动编辑此文件以添加或删除Python模块。
~~~



~~~
Additional files and subdirectories for 32-bit Windows
======================================================

python_nt.rc   Resource compiler input for python15.dll.

dl_nt.c		   Additional sources used for 32-bit Windows features.

getpathp.c     Default sys.path calculations (for all PC platforms).

dllbase_nt.txt A (manually maintained) list of base addresses for various DLLs, to avoid run-time relocation.
~~~



~~~
Note for Windows 3.x and DOS users
==================================

Neither Windows 3.x nor DOS is supported any more.  The last Python version that supported these was Python 1.5.2; the support files were present in Python 2.0 but weren't updated, and it is not our intention to support these platforms for Python 2.x.
~~~

