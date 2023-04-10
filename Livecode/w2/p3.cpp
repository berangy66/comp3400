#include <iostream> 


struct foo
{
    int i ; 
};

//overload operator== to compare foo a & foo b
bool operator==(const foo& a , const foo& b)
{
    return a.i == b.i; 
}


int main()
{
    foo a{2};
    foo b{2};

    std::cout << (a == b) << (a != b) << '\n'; 
}
