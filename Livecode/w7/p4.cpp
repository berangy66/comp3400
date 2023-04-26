#include <tuple>
#include <string>
#include <variant> 
#include <iostream> 

using namespace std; 

int main()
{
    tuple<int , double, string> t{5, 21.2, "dsadasdsa" };

    variant<int, double, string> v; 
    v = 5; 
    v = 3.14; 
    v = "dfasfasfdsafdas"; 

    variant<monostate, int, double, string> v2; 
}