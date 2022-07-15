// equality_comparable

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <sys/time.h>
#include <string>

using namespace std;

void PrintFError(const char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 256, format, args);
    // perror(buffer);
    cout << buffer << endl;
    va_end(args);
}

string toString(int64_t microSecondsSinceEpoch_)
{
    char buf[32] = {0};
    int64_t kMicroSecondsPerSecond = 1000 * 1000;
    int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
    int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
    snprintf(buf, sizeof(buf) - 1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
    return string(buf);
}

void times()
{
    time_t t;
    time(&t);
    // struct tm *s;
    // s = localtime(&t);
    cout << ctime(&t);
}

string test1()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    string res = toString(seconds * 1000 * 1000 + tv.tv_usec);
    return res;
    // return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}

int main(int argc, char const *argv[])
{
    time_t t;
    time(&t);
    struct tm *s;
    s = localtime(&t);
    char buf[40];
    snprintf(buf, 40, "time is %5d", 100);
    cout << buf << endl;
    PrintFError("thisis%d", 10);
    times();
    cout << test1() << endl;
    return 0;
}
