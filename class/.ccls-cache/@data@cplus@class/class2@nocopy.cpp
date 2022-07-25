#include <iostream>

class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;
    void operator=(const noncopyable &) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

// 默认是私有继承
class Mytest : noncopyable
{
private:
    /* data */
public:
    Mytest(/* args */);
    ~Mytest();
};

Mytest::Mytest(/* args */)
{
}

Mytest::~Mytest()
{
}

int main(int argc, char const *argv[])
{
    Mytest t = {};
    // Mytest s;
    // s = t;
    return 0;
}
