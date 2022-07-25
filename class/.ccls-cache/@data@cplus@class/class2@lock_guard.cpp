#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
#include <stdexcept>
 
void write_to_file(const std::string & message)
{
    // 创建关于文件的互斥锁
    static std::mutex mutex;
 
    // 在访问文件前进行加锁
    std::lock_guard<std::mutex> lock(mutex);
 
    // 尝试打开文件
    std::ofstream file("example.txt");
    if (!file.is_open())
        throw std::runtime_error("unable to open file");
 
    // 输出文件内容
    file << message << std::endl;
 
    // 当离开作用域时，文件句柄会被首先析构 (不管是否抛出了异常)
    // 互斥锁也会被析构 (同样地，不管是否抛出了异常)
}