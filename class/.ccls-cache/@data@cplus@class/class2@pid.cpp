#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

void getid()
{
    cout << getpid() << endl;
}

void getids()
{
    thread::id res = this_thread::get_id();
    cout << res << endl;
}

int main(int argc, char const *argv[])
{
    getid();
    getid();
    getids();
    getids();
    return 0;
}
