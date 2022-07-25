#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>

using namespace std;

void test(int i)
{
    cout << "start" << endl;
    sleep(i);
    cout << "yes" << endl;
}

int main(int argc, char const *argv[])
{
    thread t = thread(test, 1);
    thread t1 = thread(test, 2);
    thread t2 = thread(test, 3);
    t.detach();
    t1.detach();
    t2.detach();
    cout << "here" << endl;
    sleep(2);
    return 0;
}
