#include <iostream>
#include <memory>

struct B;

struct A {
    std::shared_ptr<B> b;
    ~A() { std::cout << "~A\n"; }
};

struct B {
    std::weak_ptr<A> a;
    ~B() { std::cout << "~B\n"; }
};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();

    a->b = b;
    b->a = a;

    std::cout << a.use_count() << ' '
              << b.use_count() << '\n';
    //B是shared_ptr:输出2 2, a和b都没有被释放。
    /*B是weak_ptr:输出2 1
        ~A
        ~B
    */
    return 0;
}