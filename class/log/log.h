#if !defined(__LOG_)
#define __LOG_

#include <iostream>
#include <mutex>
#include <string>
#include <fstream>
#include <time.h>
#include <sys/time.h>

using namespace std;

class Time
{
private:
    /* data */
public:
    Time(/* args */);
    string now();
    ~Time();
    time_t _now;
    struct tm *times;
    struct timeval val;
};

string Time::now()
{
    char m_buf[48] = {};
    struct tm my_tm = *times;
    snprintf(m_buf, 48, "%d-%02d-%02d %02d:%02d:%02d.%02ld",
             my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday,
             my_tm.tm_hour, my_tm.tm_min, my_tm.tm_sec, val.tv_sec);
    return m_buf;
}

Time::Time(/* args */)
{
    time(&_now);
    times = localtime(&_now);
    struct timeval now = {0, 0};
    gettimeofday(&now, NULL);
}

Time::~Time()
{
}

class logs
{
private:
    /* data */
    logs(/* args */);
    ~logs();
    mutex mux;
    ofstream file;

public:
    static logs *get_instance()
    {
        static logs instance;
        return &instance;
    }
    void write_log(string content)
    {
        for (size_t i = 0; i < 10; i++)
        {
            file << Time().now() + " "
                 << "INFO: "
                 << content << endl;
        }
    }
    void flush() { file.flush(); }
    enum LEVEL
    {
        INFO,
        DEBUG,
        WARN,
    };
};

logs::logs(/* args */)
{
    cout << "instance is called" << endl;
    file = ofstream("./test.log", ios::app);
}

logs::~logs()
{
    cout << "del instance logs" << endl;
}

#define LOG_DEBUG(format)                        \
    {                                            \
        logs::get_instance()->write_log(format); \
        logs::get_instance()->flush();           \
    }
// #define LOG_INFO(format, ...) if(0 == m_close_log) {Log::get_instance()->write_log(1, format, ##__VA_ARGS__); Log::get_instance()->flush();}
// #define LOG_WARN(format, ...) if(0 == m_close_log) {Log::get_instance()->write_log(2, format, ##__VA_ARGS__); Log::get_instance()->flush();}
// #define LOG_ERROR(format, ...) if(0 == m_close_log) {Log::get_instance()->write_log(3, format, ##__VA_ARGS__); Log::get_instance()->flush();}

#endif // __LOG_
