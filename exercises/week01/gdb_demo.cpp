#include <iostream>
using namespace std;

int getValue(int* ptr) {
    return *ptr;
}

void process() {
    int* p = nullptr;
    int value = getValue(p);
    cout << value << endl;
}

int main() {
    process();
    return 0;
}