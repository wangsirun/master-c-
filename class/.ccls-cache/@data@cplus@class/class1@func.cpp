#include <iostream>
#include <functional>

int main(int argc, char const *argv[])
{
    typedef std::function<void(std::string)> call;
    call();
    return 0;
}
