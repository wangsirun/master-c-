#include <iostream>
#include <string>
#include <initializer_list>

using namespace std;

class test
{
private:
    /* data */
    int num = 0;
    string name;

public:
    test(string _name) : name(_name) {}
    int res() { return num; }
    ~test();
};

test::~test()
{
}

int sums(initializer_list<int> args)
{
   int res = 0; 
   for(int i : args)
   {
    res += i; 
   }
   return res;
}

int main(int argc, char const *argv[])
{
    /* code */
    test t = {"sirun.wang"};
    cout << t.res() << endl;
    cout << sums({1,2,3}) << endl;
    return 0;
}
