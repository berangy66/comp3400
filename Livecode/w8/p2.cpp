#include <concepts>
#include <vector> 
#include <list> 
#include <iostream> 

template <typename Container, typename Int> 
concept reservable = 
    requires (Container c, Int n)
    {
        {c.reserve(n) }; 
    }
;

template <typename Container, typename Int>
requires reservable<Container, Int> 
void reserve(Container&& c , Int const& n)
{
    c.reserve(n);
}

int main()
{
    using namespace std; 

    vector<double> d; 
    reserve(d, 56); 
}