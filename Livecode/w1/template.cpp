#include <iostream>
#include<temp


template <typename T>

T min(T a, T b) {
   
    return a < b ? a : b;
}


int main()
{
   std:: cout << min(2,2) << std::endl;
    std::cout << min( 2.3 , 13.2) << std::endl;
   // min(3.3, 1); // error

}

// template.cpp:3:3: note: candidate: ‘template<class T> T min(T, T)’
//     3 | T min(T a, T b) {
//       |   ^~~
// template.cpp:3:3: note:   template argument deduction/substitution failed:
// template.cpp:12:15: note:   deduced conflicting types for parameter ‘T’ (‘double’ and ‘int’)
//    12 |     min(3.3, 1); // error
//       |               ^
// cc1plus: all warnings being treated as errors