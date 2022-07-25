#include <iostream>
#include <fcntl.h>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    int fd = open("./example.txt", O_RDONLY);
    int s = fcntl(fd, F_GETFL);
    cout << s << endl;
    return 0;
}
