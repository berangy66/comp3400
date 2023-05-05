#include <concepts>
#include <vector> 
#include <list> 
#include <iostream> 

template <typename Container, typename Int> 
concept reservable = 
    requirement (Container c , Int n)
    {
        {c.reserve(n) };

    }
 ;

 
    