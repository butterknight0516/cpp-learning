#include <iostream>
using namespace std;

class A{
public:
    int val;

    A(int val){
        this->val = val;
        cout << "creating A with value " << val << endl;
    }

    ~A(){
        cout << "destroy A with value " << this->val << endl;
    }
};

A b(20);
A *c = new A(30);

int main(void){
    A a(10);
    A *d = new A(40);

    /*
    output:
    creating A with value 20
    creating A with value 30
    creating A with value 10
    creating A with value 40
    destroy A with value 10
    destroy A with value 20

    注意：new的对象要delete掉，否则会发生内存泄漏，因为程序结束指针被释放，但是申请的内存空间没有被释放！
    creating A with value 20
    creating A with value 30
    creating A with value 10
    creating A with value 40
    destroy A with value 30
    destroy A with value 40
    destroy A with value 10
    destroy A with value 20
    */

    delete c;
    delete d;

    return 0;
}