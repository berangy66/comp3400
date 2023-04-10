#include <iostream>


struct A                {virtual int  f() { return 1; } };
struct B : A            {virtual int f() { return 2; } };
struct C : A            {};
struct D : B, C         { virtual int f() { return B::f() | C::f(); } };
struct E: virtual A     { virtual int f() { return 4; } };
struct F: virtual A     {};
struct G: E, F          { virtual int f() { return E::f() | F::f(); } };






int main()
{
    A a;
    B b;
    C c;
    D d;
    E e;
    F f;
    G g;

    std::cout << a.f() << std::endl;
    std::cout << b.f() << std::endl;
    std::cout << e.f() << std::endl;

    std::cout << c.f() << std::endl;
    std::cout << f.f() << std::endl;

    std::cout << d.f() << std::endl;
    std::cout << g.f() << std::endl;

    return 0;
}