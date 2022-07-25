#include <memory>
#include <vector>
#include <iostream>
#include <type_traits>

struct C
{
    // constructors needed (until C++20)
    C(int i) : i(i) {}
    C(int i, float f) : i(i), f(f) {}
    int i;
    float f{};
};

int main()
{
    // using `auto` for the type of `sp1`
    auto sp1 = std::make_shared<C>(1); // overload (1)
    // static_assert(std::is_same_v<decltype(sp1), std::shared_ptr<C>>);
    std::cout << "sp1->{ i:" << sp1->i << ", f:" << sp1->f << " }\n";

    // being explicit with the type of `sp2`
    std::shared_ptr<C> sp2 = std::make_shared<C>(2, 3.0f); // overload (1)
    // static_assert(std::is_same_v<decltype(sp2), std::shared_ptr<C>>);
    // static_assert(std::is_same_v<decltype(sp1), decltype(sp2)>);
    std::cout << "sp2->{ i:" << sp2->i << ", f:" << sp2->f << " }\n";
}