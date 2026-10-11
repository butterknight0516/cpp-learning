#include "demo/add.hpp"

#include <iostream>
#include <thread>

int main() {
    int result = 0;
    std::thread worker([&result] { result = demo::add(2, 3); });
    worker.join();

    if (result != 5) {
        std::cerr << "Environment check failed\n";
        return 1;
    }
    std::cout << "Linux C++ environment OK: " << result << '\n';
    return 0;
}
