cmake_minimum_required(VERSION 3.16)

project(fileProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行程序及其源文件
add_executable(fileProject
    main.cpp
    src/file_utils.cpp
)

# 指定头文件搜索目录
target_include_directories(fileProject PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)