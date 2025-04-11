#include <bits/stdc++.h>

class Task{
public:
    void work(std::function<void(int)> f) {
        sleep(1);
        x ++;
        return f(x);
    }
private:
    int x{};
};


int main() {

    Task task;

    task.work([&task](int x){
        task.work([&task, &x](int y){
            task.work([&task, &x, &y](int z){
                std::cout << x + y + z << std::endl;
            }); 
        });
    });

    return 0;
}