# 使用cmake_minimum_required()设置CMake版本
cmake_minimum_required(VERSION 3.10)

# 使用project() 设置项目名称命令
project(Tutorial)

# 添加可执行文件
add_executable(Tutorial main.cpp)