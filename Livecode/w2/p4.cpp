#include <compare> 
#include <iostream> 


struct foo
{
    int i ; 
    friend std::strong_ordering operator<=>(foo const& , foo const&) = default; 
};

bool operator==(const foo& a , const foo& b)
{
    return a.i == b.i; 
}

bool operator<(const foo& a , const foo& b)
{
    return a.i < b.i; 
}


int main()
{
    foo a{2}; 
    foo b{2}; 

    std::cout << (a == b) << (a != b) << '\n'; 
    std::cout << (a < b) << (a <= b) << '\n';
    std::cout << ( a < b) << (a >= b) << '\n';
}

// p4.cpp:11:6: error: declaration of ‘bool operator==(const foo&, const foo&)’ has a different exception specifier
//    11 | bool operator==(const foo& a , const foo& b)
//       |      ^~~~~~~~
// p4.cpp:8:33: note: from previous declaration ‘constexpr bool operator==(const foo&, const foo&) noexcept’
//     8 |     friend std::strong_ordering operator<=>(foo const& , foo const&) = default;
//       |                                 ^~~~~~~~