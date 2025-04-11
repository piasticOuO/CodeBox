#include <bits/stdc++.h>
#include <coroutine>
class Reader{
public:
    bool await_ready() {
        return false;
    }
    void await_suspend(std::coroutine_handle<> handle) {

        std::thread thread([this, handle]() {
            x ++;
            handle.resume();                
        });

        thread.detach();
    }
    int await_resume() {
        return x;
    }
private:
    int x{};
};

class Task{
public:
    class promise_type{
    public:
        Task get_return_object() {
            return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }
        void return_value(int value_) {
            value = value_;
        }
        std::suspend_always yield_value(int value_) {
            value = value_;
            return {};
        }

        int get_value() {
            return value;
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
    private:
        int value{};
    };

    Task(std::coroutine_handle<promise_type> handle) : handle(handle) {}
    ~Task() { handle.destroy(); }
    int GetValue() const {
        return handle.promise().get_value();
    }
    void Next() {
        handle.resume();
    }
private:
    std::coroutine_handle<promise_type> handle;
};

Task getInt() {
    Reader reader;
    int x = 0;
    while (x < 10) {
        x = co_await reader;
        co_yield x;    
    }
    co_return x;
}
int main() {
    auto task = getInt();
    std::string s;
    while (std::cin >> s) {
        std::cout << task.GetValue() << std::endl;
        // 协程结束后被挂起，只要不恢复就可以一直调用！但是如果结束了那么协程句柄就会变成野指针！
        if (task.GetValue() < 10) task.Next();      
    }
    return 0;
}