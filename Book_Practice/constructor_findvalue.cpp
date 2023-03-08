#include <iostream> 

struct Z                    {int z; Z() : z(1){ }   virtual int f() {return -z;}};
// Define a struct Z with a single member variable 'z', initialized to 1. The struct also contains a virtual function 'f' which returns the negation of 'z'.

struct Y                    {int y; Y() : y(10){ }   virtual int f() {return -y;}};
// Define a struct Y with a single member variable 'y', initialized to 10. The struct also contains a virtual function 'f' which returns the negation of 'y'.

struct A: Z                {int a; A() : a(100){ }   virtual int f() {return z;}};
// Define a struct A that inherits from Z, with a single member variable 'a', initialized to 100. The struct also contains a virtual function 'f' which returns 'z'.

struct B: virtual A         {int b; B() : b(1000){ }   virtual int f() {return a;}};
// Define a struct B that virtually inherits from A, with a single member variable 'b', initialized to 1000. The struct also contains a virtual function 'f' which returns 'a'.

struct C: virtual A, Y      {int c; C() : c(10000){ }   virtual int f() {return a + y;}};
// Define a struct C that virtually inherits from A and Y, with a single member variable 'c', initialized to 10000. The struct also contains a virtual function 'f' which returns the sum of 'a' and 'y'.

struct D: B, C              {int d; D() : d(100000){ }   virtual int f() {return b + c;}};
// Define a struct D that inherits from B and C, with a single member variable 'd', initialized to 100000. The struct also contains a virtual function 'f' which returns the sum of 'b' and 'c'.

int main()
{
    D d; // Create an object of type D named 'd'.
    A* a = &d; // Create a pointer to an object of type A, pointing to 'd'.
    Z& z = d; // Create a reference to an object of type Z, referencing 'd'.
    C c; // Create an object of type C named 'c'.
    Z& z2 = c; // Create a reference to an object of type Z, referencing 'c'.

    std::cout << d.f() << ", " << a->f() << ", " << z.f() << ", " << z2.f() << '\n'; 
    // Call the 'f' function on 'd', 'a', 'z', and 'z2', printing the return values separated by commas and followed by a newline character.
}
