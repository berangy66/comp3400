#include <string> 
#include <cstring>
#include <iostream> 

using namespace std; 

template <typename T, typename U>
concept has_my_interface = 
    requires (T t, U u)
    {
        { t + u }; 
        { foo(t, u)}; 
    }
    ; 

void foo(int , double)
{

}

template <typename T, typename U> 
requires has_my_interface<T,U> 
void cool( T t, U u)
{
    cout << t+u; 
    foo(t, u); 
}

int main()
{
    cool(1, 2.2);
    cool("fddasd", 1);
}