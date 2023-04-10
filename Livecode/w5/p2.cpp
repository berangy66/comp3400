#include <algorithm>
#include <numeric> 
#include <iostream>

int main()
{
    std::vector<double> v{0.0, 1.1, 2.2, 3.3, 4.4}; 

#if 0 
    for(double const& elem: v)
    {
        std::cout << elem << '\n'; 
    }

#else
    std::vector<double>::const_iterator i = v.begin(); 
    std::vector<double>::const_iterator i_end = v.end(); 

    for(; i != i_end; ++i)
    {
        std::cout << *i << '\n'; 
    }

#endif
}