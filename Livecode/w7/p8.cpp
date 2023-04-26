#include <string>
#include <cstring>
#include <iostream>

using namespace std; 

template <typename T>
T mymin(T a, T b)
{
    return a < b ? a : b; 
}

const char* mymin(const char* a, const char* b)
{
    return strcmp(a,b) < 0 ? a : b; 
}


int main()
{
    cout << mymin(7,2) << '\n'; 
    cout << mymin(7.8, 2.3) << '\n'; 

    string a = "dsadsa"; 
    string b = "zHGDSDGSDFSGD"; 
    cout << mymin(a, b) << '\n'; 


    const char c[] = "ZZZdsadsa"; 
    const char d[] = "zHGDSGSDFSGD";
    cout << mymin(c, d) << '\n'; 
    cout << mymin(d, c) << '\n'; 

}