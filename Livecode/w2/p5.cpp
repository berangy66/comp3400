#include<compare> 
#include<iostream> 

struct foo
{
    int i; 
    friend std::strong_ordering operator<=>(foo const&, foo const&) = default; 
};

int main()
{
    foo a{2}; 
    foo b{2}; 

    std::cout << (a == b) << (a != b) << '\n';
    std::cout << (a < b) << (a <= b)  << '\n';
    std::cout << (a > b) << ( a>= b) << '\n';
}