# 使用cmake_minimum_required()设置CMake版本
cmake_minimum_required(VERSION 3.10)

# 使用project() 设置项目名称命令
project(Tutorial)

# 添加可执行文件
add_executable(Tutorial main.cpp)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# 下面代码开启/Zc:__cplusplus选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus /std:c++20")