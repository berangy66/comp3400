#include <algorithm>
#include <numeric> 
#include <iostream> 
#include <vector>

int main()
{
    std::vector<double> v{0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};

    for(double const& elem : v)
    {
        std::cout << elem << " " ; 

    }
    std::cout << std::endl;
}