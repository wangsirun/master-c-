#include <stdio.h>
#include <sys/uio.h>
#include<string>
#include<iostream>

int main(int argc, const char * argv[]) {
    struct iovec vec[2];
    char buf1[] = "ABCDEFG";
    char buf2[] = "1234567";
    int str_len;
    vec[0].iov_base = buf1;
    vec[0].iov_len = 3;
    vec[1].iov_base = buf2;
    vec[1].iov_len = 4;

    str_len = writev(1, vec, 2); //1是系统标准输出文件描述符
    puts("");
    printf("Write bytes: %d \n", str_len);
    std::cout << "this is a test" << std::endl;
    return 0;
}
