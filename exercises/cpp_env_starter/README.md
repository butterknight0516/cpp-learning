# Linux C++ 环境验证示例

适用：Ubuntu 22.04 及更新版本，以及工具版本符合要求的 Debian。WSL2 中的 Ubuntu 同样适用；CMake 需至少 3.20。用于验证多文件编译、头文件、标准线程、CMake、CTest 和 GDB。

先安装基础工具。在本目录的 Linux 终端执行下面的脚本；脚本会通过 apt 安装软件，按提示输入 sudo 密码。

```bash
bash setup_ubuntu.sh
```

如果已经安装工具，可以直接构建。始终在此项目根目录运行以下命令。

## Debug 构建、运行和环境检查

```bash
cmake -S . -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=/usr/bin/g++
cmake --build build/debug --parallel 2
./build/debug/cpp_demo
ctest --test-dir build/debug --output-on-failure
```

预期程序输出 Linux C++ environment OK: 5，CTest 报告 1 个检查通过。这里的检查只验证示例能编译和运行，不代表未来业务项目已经通过完整测试。

## GDB

```bash
gdb ./build/debug/cpp_demo
```

GDB 中依次执行：

```text
break main
run
next
next
next
print result
backtrace
continue
quit
```

线程 join 完成后，result 应为 5；此前无需假定工作线程已经执行。

## Release 构建

```bash
cmake -S . -B build/release -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=/usr/bin/g++
cmake --build build/release --parallel 2
./build/release/cpp_demo
```

性能实验使用 Release，并记录实际编译参数。Debug 用于学习与调试。

## AddressSanitizer + UndefinedBehaviorSanitizer

```bash
cmake -S . -B build/asan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON -DCMAKE_CXX_COMPILER=/usr/bin/g++
cmake --build build/asan --parallel 2
ctest --test-dir build/asan --output-on-failure
```

这两种工具检查部分内存和未定义行为问题。ThreadSanitizer 后续单独构建，不与 AddressSanitizer 混用。Sanitizer 构建不用于性能结论。

## VS Code

在 Windows 安装 VS Code 和 WSL 扩展。在 Ubuntu 中进入本目录并执行 code .，确认左下角显示 WSL。

在 WSL 侧安装 Microsoft C/C++ 与 CMake Tools 扩展。执行 CMake: Select a Kit 选择 /usr/bin/g++，然后 CMake: Configure、CMake: Build、CMake: Debug。在 src/main.cpp 的输出行设置断点。

## 格式化

```bash
clang-format -i src/main.cpp src/add.cpp include/demo/add.hpp
```

## 同步

提交源文件、CMakeLists.txt、README、配置与安装脚本；不提交 build。两台设备各自安装工具、各自编译。标准库与线程由工具链提供；未来 Protobuf、Boost 等依赖按阶段添加。
