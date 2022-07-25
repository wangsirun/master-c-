#include <iostream>
#include <thread>
#include <functional>
#include <algorithm> // std::all_of
#include <array>     // std::array
#include <vector>    // std::array
#include <map>       // std::array
#include <string>    // std::array

using namespace std;

class MYthread
{
private:
    /* data */
    bool stop = false;
    int execNum = 0;

public:
    typedef function<void(int)> called;
    MYthread(called f) : func(f) {}
    void Start(int);
    void Waper(function<void(int)>, int);
    ~MYthread();

    called func;
};

void MYthread::Waper(function<void(int)> s, int i)
{
    s(i);
    stop = true;
}

void MYthread::Start(int i)
{
    thread t(&MYthread::Waper, this, func, i);
    t.detach();
    while (!stop)
    {
        std::this_thread::yield();
    }
}

MYthread::~MYthread()
{
}

typedef typename MYthread::called Call;

void test(int i)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "called: " << i << endl;
}

void test1()
{
    std::array<int, 7> foo = {0, 1, -1, 3, -3, 5, -5};

    if (std::any_of(foo.begin(), foo.end(), [](int i)
                    { return i < 0; }))
        std::cout << "There are negative elements in the range.\n";
    for (auto &&i : foo)
    {
        cout << i << endl;
    }

    return;
}

void test2()
{
    int myints[] = {10, 20, 30, 40};
    int *p;

    p = std::find(myints, myints + 4, 30);
    if (p != myints + 4)
        std::cout << "Element found in myints: " << *p << '\n';
    else
        std::cout << "Element not found in myints\n";

    // using std::find with vector and iterator:
    std::vector<int> myvector(myints, myints + 4);
    std::vector<int>::iterator it;

    it = find(myvector.begin(), myvector.end(), 30);
    if (it != myvector.end())
        std::cout << "Element found in myvector: " << *it << '\n';
    else
        std::cout << "Element not found in myvector\n";
}

bool IsOdd(int i)
{
    return ((i % 2) == 1);
}

void test3()
{
    std::vector<int> myvector;

    myvector.push_back(10);
    myvector.push_back(25);
    myvector.push_back(40);
    myvector.push_back(55);

    std::vector<int>::iterator it = std::find_if(myvector.begin(), myvector.end(), IsOdd);
    std::cout << "The first odd value is " << *it << '\n';
}

int main(int argc, char const *argv[])
{
    /* code */
    Call f = test;
    MYthread th(f);
    th.Start(100);

    std::array<int, 8> foo = {3, 5, 7, 11, 13, 17, 19, 23};

    if (all_of(foo.begin(), foo.end(), [&](int &i)
               { return i < 0; }))
        cout << "All the elements are odd numbers.\n";

    for (auto &&i : foo)
    {
        cout << i << endl;
    }
    test1();

    vector<int> list = {1, 2, 4, 4, 4, 4};
    int res = count(list.begin(), list.end(), 4);
    cout << res << endl;

    int myints[] = {10, 20, 30, 5, 15};
    std::vector<int> v(myints, myints + 5);

    std::make_heap(v.begin(), v.end());
    std::cout << "initial max heap   : " << v.front() << '\n';

    std::pop_heap(v.begin(), v.end());
    v.pop_back();
    std::cout << "max heap after pop : " << v.front() << '\n';
    cout << v.size() << endl;

    map<string, int> maps;
    maps["site"] = 100;
    int site = maps.at("site");
    int sites = maps["sit"];
    cout << site << endl;
    cout << sites << endl;
    return 0;
}