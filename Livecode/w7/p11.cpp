#include <string>
#include <cstring> 
#include <iostream> 


using namespace std; 


template<typename... Ts> 
auto hmmm(Ts const&... args)
{
    //FOLD EXpresion(msut be in parentheses)...
    return (args + ... + 0);
}


int main()
{
    cout << hmmm() << '\n';
    cout << hmmm(1) << '\n'; 
    cout << hmmm(1, 1.0) << '\n'; 
}