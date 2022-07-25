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

inline string Time::now()
{
    char m_buf[48] = {};
    struct tm my_tm = *times;
    snprintf(m_buf, 48, "%d-%02d-%02d %02d:%02d:%02d.%02ld",
             my_tm.tm_year + 1900, my_tm.tm_mon + 1, my_tm.tm_mday,
             my_tm.tm_hour, my_tm.tm_min, my_tm.tm_sec, val.tv_sec);
    return m_buf;
}

inline Time::Time(/* args */)
{
    time(&_now);
    times = localtime(&_now);
    struct timeval now = {0, 0};
    gettimeofday(&now, NULL);
}

inline Time::~Time()
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
    enum LEVEL
    {
        DEBUG,
        INFO,
        WARN,
        ERROR,
    };
    void write_log(LEVEL level, string content)
    {
        switch (level)
        {
        case DEBUG:
            file << Time().now() + " [debug] " << content << endl;
            break;
        case INFO:
            file << Time().now() + " [info] " << content << endl;
            break;
        case WARN:
            file << Time().now() + " [warn] " << content << endl;
            break;
        case ERROR:
            file << Time().now() + " [error] " << content << endl;
            break;

        default:
            break;
        }
    }
    void flush() { file.flush(); }
};

inline logs::logs(/* args */)
{
    cout << "instance is called" << endl;
    file = ofstream("./test.log", ios::app);
}

inline logs::~logs()
{
    cout << "del instance logs" << endl;
}

#define LOG_DEBUG(format)                                            \
    {                                                                \
        logs::get_instance()->write_log(logs::LEVEL::DEBUG, format); \
        logs::get_instance()->flush();                               \
    }
#define LOG_INFO(format)                                            \
    {                                                               \
        logs::get_instance()->write_log(logs::LEVEL::INFO, format); \
        logs::get_instance()->flush();                              \
    }
#define LOG_WARN(format)                                            \
    {                                                               \
        logs::get_instance()->write_log(logs::LEVEL::WARN, format); \
        logs::get_instance()->flush();                              \
    }
#define LOG_ERROR(format)                                            \
    {                                                                \
        logs::get_instance()->write_log(logs::LEVEL::ERROR, format); \
        logs::get_instance()->flush();                               \
    }

#endif // __LOG_
