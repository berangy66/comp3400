#include <algorithm>
#include <numeric>
#include <iostream>
#include <list>


int main()
{
    std::list<double> v; 

    double d;
    while(std::cin >> d) 
    {
        v.push_back(d); 
    }

    while(!v.empty())
    {
        double val= v.back(); 
        v.pop_back(); 
        std::cout << val << '\n'; 
    }
}