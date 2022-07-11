#include <arpa/inet.h>
#include <stdlib.h>
#include <iostream>

int main()
{
    char IP[] = "159.12.8.109";
    in_addr address;
    int number = inet_aton(IP, &address); //将点分十进制的IP地址转化为二进制的网络字节序
    if (number == 0)
    {
        std::cerr << "error IP!";
        exit(1);
    }
    // std::cout << number << std::endl;
    std::cout << address.s_addr << std::endl;
    std::cout << inet_ntoa(address) << std::endl; //将网络字节序地址转化为点分十进制表示形式
    return 0;
}