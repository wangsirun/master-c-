#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

std::mutex mux;
std::condition_variable cn;

int num = 10;

void test(int i)
{
    std::unique_lock<std::mutex> lock(mux);
    std::cout << "wait here: " << i << std::endl;
    cn.wait(lock);
    std::cout << "execute: " << i << std::endl;
    std::cout << i << std::endl;
}

void go()
{
    std::cout << "go here: " << std::endl;
    std::unique_lock<std::mutex> lock(mux);
    cn.notify_all();
}

int main(int argc, char const *argv[])
{
    std::thread pool[10];
    for (size_t i = 0; i < 10; i++)
    {
        pool[i] = std::thread(test, i);
    }
    go();
    for (auto &p : pool)
    {
        p.join();
    }

    return 0;
}
