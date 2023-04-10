#include <iostream>

struct foo
{
  int i;
};

int main()
{
  foo a{2};
  foo b{2};
  std::cout << (a == b) << '\n';
}
//this will not compile because the compiler does not know how to compare two foo objects
//to fix this we need to overload the == operator
//This code will not compile because it is attempting to compare two instances of the foo struct using the == operator, which is not defined for user-defined types in C++