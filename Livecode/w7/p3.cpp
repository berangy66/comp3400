#include <tuple>
#include <string> 
#include <iostream> 

using namespace std; 

int main()
{
    tuple<int, double, string> t{5, 21.2, "dsadasdsa" }; 
    cout << get<1>(t) << '\n'; 
    get<1>(t) = -43e-2; 
    cout << get <1>(t) << '\n'; 

    //structured bindings 
    auto const [a, b, c] = t; 
    cout << a << ' ' << b << ' ' << c << '\n'; 
}