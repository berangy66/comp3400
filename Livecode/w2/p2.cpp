#include <iostream> 


struct foo
{
  int i;
};

bool operator==(const foo& a, const foo& b)
{
    return a.i == b.i; //return true if the two objects are equal
}

int main()
{
  foo a{2};
  foo b{2};
  std::cout << (a == b) << '\n';
}