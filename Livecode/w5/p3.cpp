#include <algorithm>
#include <numeric> 
#include <iostream> 
#include <list>

int main()
{
    std::list<double> v {0.0, 1.1, 2.2, 3.3, 4.4,}; 

#if 0 
    for(double const& elem : v)
    {
        std::cout << elem << '\n'; 
    }
#else   
    std::list<double>::const_iterator i = v.begin(); 
    std::list<double>::const_iterator i_end = v.end(); 
    for(; i != i_end; ++i)
    {
        std::cout << *i << '\n'; 
    }
#endif
}