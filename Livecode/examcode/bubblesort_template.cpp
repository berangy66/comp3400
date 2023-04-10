#include<iostream> 
#include<utility> // for std::swap 


template<typename ForwardIterator> 
void bubbleSort(ForwardIterator begin , ForwardIterator end)
{
    for(auto i = begin ; i !=end ; ++i)
    {
        for(auto j = begin; j !=end - 1 ; ++j )
        {
            if(*j >  *(j + 1))
            {
                std::swap(*j , *(j + 1)); 
            }
        }
    }
}

int main()
{
    int array [] = {100, 20 , 40 , 50 , 60}; 
    int n = sizeof(array) / sizeof(array[0]);
    bubbleSort(std::begin(array), std::end(array)); 
    std::cout << "sorted array: "; 
    for(int i = 0 ; i < n ; i++)
    {
        std::cout << array[i] << " "; 
    }
    std::cout << '\n';
    return 0;

}