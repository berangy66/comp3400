#include <string> 
#include <iostream>

using namespace std; 

template <typename T>
T mymin(T a, T b)
{
    return a < b ? a : b; 
}


int main()
{
    cout << mymin(7,2) << '\n';
    cout << mymin(7.7, 2.2) << '\n'; 

    string a = "adfadf"; 
    string b = "zHGDSDGSDFSGD"; 
    cout << mymin(a,b) << '\n'; 


}