#include <iostream>


constexpr double nth(double x , int n)
{
    double res = 1; 
    int i = 0; 
    
    while(i<n)
    {
        res *= x; 
        ++i; 
    }
    return res; 
}



int main()
{
    double a = 2; 
    int b = 10;

    std:: cout << nth(a, b) << "\n";
   consteval double square2(double x) { return x * x; }
}