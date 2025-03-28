#include <iostream>

void f(const int &x) {
    std::cout << "左值: " << x << std::endl;
}

void f(int &&x) {
    std::cout << "右值: " << x << std::endl;
}

void g(const int &x) {
    std::cout << "g判定为左值。";
    f(std::forward<const int&>(x));
}

void g(int &&x) {
    std::cout << "g判定为右值。";
    f(std::forward<int&&>(x));
}


int main() {

    int x = 5;
    f(5);       // 识别为右值，调用右值引用
    f(x);       // 识别为左值，调用左值引用

    g(5);       // g判定为右值，f判定为右值
    g(x);       // g判定为左值，f判定为左值

    return 0;
}