#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    char *a = "aBcDeF";
    char *b = "AbCdEf";
    // 相同返回0
    if (!strcasecmp(a, b))
    {
        cout << a << "=" << b << endl;
    }
}