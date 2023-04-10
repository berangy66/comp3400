#include <iostream> 
#include <vector> 

template < typename ForwardIterator> 
void bubble_Sort(ForwardIterator begin , ForwardIterator end)
{
    for( auto i = begin ; i != end ; ++i)
    {
        bool swapped = false; 
        for(auto j = begin ; j != end - std::distance(begin, i) - 1 ; ++j )
        {
            if(*j > *(j + 1))
            {
                std::swap(*j , *(j + 1));
                swapped = true;
            }
        }
        if(!swapped) break; 
    }
}


int main()
{
    std::vector<int> v = {64, 19 , 40 , 23 , 75, 01, 300, 100}; 
    bubble_Sort(v.begin(), v.end()); 

    for(auto i : v)
    {
         std::cout << i << " " ; 
    }
    std::cout << std::endl;

    return 0 ;  
}


