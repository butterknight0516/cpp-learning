cmake_minimum_required(VERSION 3.20)
project(cpp_env_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(cpp_demo src/main.cpp src/add.cpp)
target_include_directories(cpp_demo PRIVATE include)
target_link_libraries(cpp_demo PRIVATE Threads::Threads)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(cpp_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
if(ENABLE_SANITIZERS)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        message(FATAL_ERROR "This sanitizer configuration requires GCC or Clang")
    endif()
    target_compile_options(cpp_demo PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(cpp_demo PRIVATE -fsanitize=address,undefined)
endif()

enable_testing()
add_test(NAME environment_smoke COMMAND cpp_demo)
