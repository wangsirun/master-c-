#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace std;

char mybuffer[80];
int main()
{
    fstream pFile;
    pFile.open("./example.txt");
    cout << pFile.is_open() << endl;
    if (pFile.is_open() != 1)
    {
        perror("Error opening file");
    }
    // SEEK_SET 文件开始位置 SEEK_CUR 文件当前位置 SEEK_END 文件结束位置
    // pFile.seekp(pFile.tellg());
    pFile.seekp(SEEK_END);
    pFile << "this is a test";
    pFile.flush();
    pFile.seekg(0);
    // pFile.getline(mybuffer, 80);
    pFile.getline(mybuffer, 80, '\n');
    // pFile >> mybuffer;
    cout << string(mybuffer) << endl;
    pFile.close();
    //     cout << "flush" << endl;
    //     // sleep(3);
    //     cout << "here" << endl;
    //     fgets(mybuffer, 80, pFile);
    //     cout << string(mybuffer) << endl;
    //     fclose(pFile);
    //     return 0;
    // }
}