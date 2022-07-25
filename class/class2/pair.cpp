#include <iostream>
#include <utility>
#include <functional>

int main(int argc, char const *argv[])
{
    /* code */
    auto p = std::make_pair(1, 1);
    p.second = 199;
    std::cout << p.first << std::endl;
    int c;
    std::tie(std::ignore, c) = p;
    std::cout << c << std::endl;
    return 0;
}
