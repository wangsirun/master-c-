#include <iostream>
#include <string>

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

int main(int argc, char const *argv[])
{
    /* code */
    test t = {"sirun.wang"};
    cout << t.res() << endl;
    return 0;
}
