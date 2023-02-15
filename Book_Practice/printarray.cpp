#include <iostream> 



void print()
{
    int v1[10] = {0 ,1 ,2 ,3 ,4 ,5 , 6, 7, 8 ,9};
    for( auto i = 0; i != 10 ; ++i)
    {
        std::cout << v1[i] << '\n';
    }
}


void print2()
{
    int v[] = {0,1,2,3,4,5,6,7,8,9};
    for(auto x:v) //for each x in v
    std::cout << x << '\n'; 

    for(auto x : { 10, 21 ,32 ,43 , 54 , 65}) //for each integer in the list
    std::cout << x << '\n'; 
}

void increment()
{
    int x; 
    int v[] = { 0, 1, 2, 3, 4 ,4 ,5 ,6, 7, 8 , 9}; 
    for(auto& x : v) //add 1 to each x in v
    ++x; 
    std::cout << x << '\n'; 
}


int main()
{
    print(); 
    print2(); 
    increment(); 
}