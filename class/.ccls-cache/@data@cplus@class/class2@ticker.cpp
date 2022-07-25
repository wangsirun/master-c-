#include <cstdint>
#include <functional>
#include <chrono>
#include <thread>
#include <future>
#include <condition_variable>
#include <iostream>
#include <mutex>

class Ticker
{
public:
    typedef std::chrono::duration<int64_t, std::nano> tick_interval_t;
    typedef std::function<void()> on_tick_t;

    Ticker(std::function<void()> onTick, std::chrono::duration<int64_t, std::nano> tickInterval)
        : _onTick(onTick), _tickInterval(tickInterval), _running(false) {}
    ~Ticker() {}

    void start()
    {
        if (_running)
            return;
        _running = true;
        std::thread run(&Ticker::timer_loop, this);
        run.detach();
    }

    void stop() { _running = false; }

    void setDuration(std::chrono::duration<int64_t, std::nano> tickInterval)
    {
        _tickIntervalMutex.lock();
        _tickInterval = tickInterval;
        _tickIntervalMutex.unlock();
    }

private:
    void timer_loop()
    {
        while (_running)
        {
            std::thread run(_onTick);
            run.detach();

            _tickIntervalMutex.lock();
            std::chrono::duration<int64_t, std::nano> tickInterval = _tickInterval;
            _tickIntervalMutex.unlock();
            std::this_thread::sleep_for(tickInterval);
        }
    }

    on_tick_t _onTick;
    tick_interval_t _tickInterval;
    volatile bool _running;
    std::mutex _tickIntervalMutex;
};

void tick()
{
    std::cout << "tick\n";
}

int main(int argc, char const *argv[])
{
    std::chrono::duration<int, std::milli> timer_duration1(1000);
    std::chrono::duration<int, std::milli> timer_duration2(500);
    std::chrono::duration<int> main_wait(5);

    Ticker ticker(std::function<void()>(tick), timer_duration1);
    ticker.start();

    std::this_thread::sleep_for(main_wait);
    ticker.setDuration(timer_duration2);
    std::this_thread::sleep_for(main_wait);
    ticker.stop();
}