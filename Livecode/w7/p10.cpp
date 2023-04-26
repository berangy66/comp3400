#include <string> 
#include <cstring> 
#include <iostream> 

using namespace std; 

template <typename... Ts> 
int hmmm(Ts... args)
{
    return sizeof...(args);
}


int main()
{
    cout << hmmm() <<'\n'; 
    cout << hmmm(1) << '\n'; 
    cout << hmmm(1, 1.0) << '\n'; 

}