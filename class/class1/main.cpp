#include <iostream>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <functional>
#include <unistd.h>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>
#include <memory>
#include <thread>

using namespace std;

// C++ WaitGroup like golang sync.WaitGroup
class WaitGroup
{
public:
    void Add(int incr = 1) { counter += incr; }
    void Done() { --counter; }
    void Wait()
    {
        std::unique_lock<std::mutex> lock(mutex);
        cond.wait(lock, [&]()
                  { return counter <= 0; });
        // cond.notify_all();
        return;
    }
    int num() { return counter; }

private:
    std::mutex mutex;
    std::atomic<int> counter;
    std::condition_variable cond;
};

auto wg = new (WaitGroup);

class Mythread
{
public:
    typedef function<void *(void *)> callback;
    Mythread(const callback &s);
    void start();
    void join();
    static void *waper(void *arg);
    void ps();
    ~Mythread();

private:
    /* data */
    pthread_t t;
    callback func_;
};

void *Mythread::waper(void *arg)
{
    Mythread *thread = static_cast<Mythread *>(arg);
    sleep(1);
    thread->func_(thread);
    wg->Done();
    // thread->func_();
}

void Mythread::ps()
{
    cout << "inner ps function called" << endl;
}

void Mythread::start()
{
    pthread_create(&t, nullptr, waper, this);
}

void Mythread::join()
{
    pthread_join(t, nullptr);
}

Mythread::Mythread(const callback &s)
{
    func_ = s;
}

Mythread::~Mythread()
{
}

void *test(void *k)
{
    Mythread *thread = static_cast<Mythread *>(k);
    thread->ps();
    cout << "test function" << endl;
}

void t(Mythread *i)
{
    i->ps();
}

int main(int argc, char const *argv[])
{
    wg->Add(10);
    for (size_t i = 0; i < 10; i++)
    {
        Mythread *threads = new Mythread(test);
        threads->start();
    }
    wg->Wait();
    return 0;
}
