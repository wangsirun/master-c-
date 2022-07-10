/* assert example */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <iostream> /* assert */

using namespace std;

void test(int i)
{
    assert(i == 10);
    cout << i << endl;
}

int main(int argc, char const *argv[])
{
    /* code */
    test(10);
    return 0;
}
