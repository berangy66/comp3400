#include <iostream>
#include <cmath>

using namespace std; 

void divison(double a , double b)
{
    double my_num{a / b}; 
    cout << "your division number is " << my_num << '\n';
}




int main()
{
    double a , b; 
    cout << "please enter two numbers\n"; 
    cin >> a; 
    cin >> b; 

    divison(a , b);

    
}