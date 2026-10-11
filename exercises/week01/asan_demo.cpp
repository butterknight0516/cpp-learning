#include <iostream>
using namespace std;

//g++ -g -O0 -fsanitize=address -fno-omit-frame-pointer asan_demo.cpp -o asan_demo
//./asan_demo

int main() {
    int* arr = new int[3]{1, 2, 3};

    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;

    arr[3] = 100;  // 数组越界！

    delete[] arr;
    return 0;
}