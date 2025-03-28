/*

要实现一个unique_ptr，我们需要：
基础函数：包括普通构造函数、拷贝构造函数、移动构造函数、析构函数、拷贝赋值运算符、移动赋值运算符
    其中，要ban的：拷贝构造函数、拷贝赋值运算符
    剩下的要实现
像指针一样：包括解引用、箭头、是否为空
其他成员函数：包括release、reset、获取原始指针

make_unique 即new一个指针来存储传入值并用智能指针包起来，返回智能指针。
值得注意的是需要std::forward<>实现完美转发。

AI说可以扩展的点：
1. 可以传一个自定义删除器：加一个typename Deleter = std::default_delete<T>
2. 增加数组支持：直接写一个特化版本

*/

#include <iostream>
#include <memory>

template<class T>
class MyUniquePtr{
private:
    T* ptr;
public:
    explicit MyUniquePtr(T* ptr = nullptr):ptr(ptr){}
    MyUniquePtr(const MyUniquePtr<T>& muptr) = delete;
    MyUniquePtr operator=(const MyUniquePtr<T>& muptr) = delete;

    MyUniquePtr(MyUniquePtr<T>&& muptr) noexcept {
        ptr = muptr.ptr;
        muptr.ptr = nullptr;
    }
    MyUniquePtr& operator=(MyUniquePtr<T>&& muptr) noexcept {
        if (this != &muptr) {
            delete ptr;
            ptr = muptr.ptr;
            muptr.ptr = nullptr;
        }
        return this;
    }
    ~MyUniquePtr() {
        delete ptr;
    }
    
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    void reset(T* ptr_ = nullptr) noexcept {
        delete ptr;
        ptr = ptr_;
    }

    T* release() noexcept {
        T* ptr_ = ptr;
        ptr = nullptr;
        return ptr_;
    }

    T* get() {
        return ptr;
    }

    const T* get() const noexcept {
        return ptr;
    }
};

template<typename T, typename... Args>
MyUniquePtr<T> make_unique(Args&&... args) {
    return MyUniquePtr<T>(new T(std::forward<Args>(args)...));
}


// 测试用

int main() {

    MyUniquePtr<int> x(new int(5));
    // MyUniquePtr<int> y = x;    这是不可以的。
    std::cout << *x << std::endl;

    MyUniquePtr<int> y = std::move(x); 
    std::cout << *y << std::endl;

    auto ptr = make_unique<std::pair<int,int>>(5, 6);
    std::cout << ptr -> first << " " << ptr -> second << std::endl;

    return 0;
}