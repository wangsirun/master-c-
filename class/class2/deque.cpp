#include <iostream>
#include <deque>
#include <string>
#include <utility>

using namespace std;

int main(int argc, char *argv[])
{
    std::deque<int> s;
    for (size_t i = 0; i <= 10; i++)
    {
        s.push_back(i);
    }
    cout << s.size() << endl;
    s.push_front(100);
    pair<int, int> k(1, 10);
    cout << k.first << endl;
    cout << k.second << endl;
    pair<string, string> ks = make_pair("s", "sirun");
    cout << ks.first << endl;
    return 0;
}
