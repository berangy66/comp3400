#include <tuple> 
#include <string> 
#include <iostream> 

using namespace std; 

int main()
{
    tuple<int, double, string> t{5, 21.2, "asdasdsa" }; 
    cout << get<0>(t) << '\n'; 
    cout << get<1>(t) << '\n';
    cout << get<2>(t) << '\n'; 
}