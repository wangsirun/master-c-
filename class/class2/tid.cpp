#include <thread>
#include <iostream>
#include <vector>

using namespace std;

void test()
{
    cout << "hello"<< endl;
    cout << this_thread::get_id() << endl;    
    cout << endl;
}


int main (int argc, char *argv[])
{
    vector<thread> container; 
    cout << this_thread::get_id() << endl;    
    for (size_t i = 0; i < 10; i++) {
        container.emplace_back(thread(test));
    }

    for(auto &&t: container)
    {
        t.join();
    }
    return 0;
}
