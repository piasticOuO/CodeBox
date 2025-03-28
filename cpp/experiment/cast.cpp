#include <bits/stdc++.h>

class Base{
public:
    int hp;
    Base():hp(100){}
    virtual void Hello() {
        std::cout << "缺少语言模块" << std::endl;
    }
};

class Person : public Base {
public:
    Person(){}
    void Hello() {
        hp --;
        std::cout << "你看到的我" << std::endl;
    }    
};

class Machine {
    public:
    Machine(){}
    virtual void Hello() {
        std::cout << "你被骗啦！" << std::endl;
    }    
};
    

void f(int *x) {
    *x = 3;
}

const Person* create() {
    static Person ret;
    return &ret;
}

void constCast() {
    int x = 5;
    const int* ptrx = &x;
    int* y = const_cast<int*>(ptrx);
    // f(ptrx);  报错
    f(y);
    std::cout << *ptrx << std::endl;
    std::cout << *y << std::endl;

    Base* per = (Base*)(create());      // 编译器有点懵逼，但是不报错
    // Base* per2 = const_cast<Base*>(create());       // 编译器这下不乐意了
}

void staticCast() {
    double p = 3.14;
    int scx = static_cast<int>(p);
    std::cout << scx << std::endl;
}

void reinterpretCast() {
    double p = 3.14;
    int scx = 10;
    char* ptrc = reinterpret_cast<char*>(new int('a' + scx));
    int* ptrp = reinterpret_cast<int*>(&p);
    std::cout << *ptrc << " " << *ptrp << std::endl;        // 得到了非常莫名其妙的东西！
}

void dynamicCast(){
    Base* base = new Person();
    Person* person = dynamic_cast<Person*>(base);

    Machine* machine = new Machine();
    Person* person2 = dynamic_cast<Person*>(machine);

    person->Hello();
    if (person2 == nullptr) {
        std::cout << "并非人类" << std::endl;
    }
}

int main() {

    std::cout << "--- const_cast ---" << std::endl;
    constCast();
    std::cout << "--- static_cast ---" << std::endl;
    staticCast();
    std::cout << "--- reinterpret_cast ---" << std::endl;
    reinterpretCast();
    std::cout << "--- dynamic_cast ---" << std::endl;
    dynamicCast();

    return 0;
}