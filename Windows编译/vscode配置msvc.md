1. vscode安装C/C++扩展包

![image-20221228174916391](C:\Users\Administrator\Desktop\vscode配置msvc.assets\image-20221228174916391.png)

2. 安装msvc

3. 打开**Developer Command Prompt for Visual Studio**

![image-20221228180836342](C:\Users\Administrator\Desktop\vscode配置msvc.assets\image-20221228180836342.png)

4. 创建工程

~~~
cd C:\Users\Administrator\Desktop\CODE\c
mkdir projects
cd projects
mkdir helloworld
cd helloworld
code .
~~~

5. run vscode outside the Developer command prompt
   配置task.json

   ~~~
   {
     "version": "2.0.0",
     "windows": {
       "options": {
         "shell": {
           "executable": "cmd.exe",
           "args": [
             "/C",
             // The path to VsDevCmd.bat depends on the version of Visual Studio you have installed.
             "\"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat\"",
             "&&"
           ]
         }
       }
     },
     "tasks": [
       {
         "type": "shell",
         "label": "cl.exe build active file",
         "command": "cl.exe",
         "args": [
           "/Zi",
           "/EHsc",
           "/Fe:",
           "${fileDirname}\\${fileBasenameNoExtension}.exe",
           "${file}"
         ],
         "problemMatcher": ["$msCompile"],
         "group": {
           "kind": "build",
           "isDefault": true
         }
       }
     ]
   }
   ~~~

   