#include <iostream>

class Z {
public:
    int z;
    virtual void printZ() { std::cout << "Z: " << z << std::endl; }
};

class Y {
public:
    int y;
    virtual void printY() { std::cout << "Y: " << y << std::endl; }
};

class A : virtual public Z {
public:
    int a;
    void printA() { std::cout << "A: " << a << std::endl; }
};

class B : virtual public A {
public:
    int b;
    void printB() { std::cout << "B: " << b << std::endl; }
};

class C : virtual public A, public Y {
public:
    int c;
    void printC() { std::cout << "C: " << c << std::endl; }
};

class D : public B, public C {
public:
    int d;
    void printD() { std::cout << "D: " << d << std::endl; }
};


int main() {
    D dObject;
    dObject.z = 1;
    dObject.y = 2;
    dObject.a = 3;
    dObject.b = 4;
    dObject.c = 5;
    dObject.d = 6;

    B* bPtr = &dObject;
    bPtr->printZ();  // Calls Z::printZ()
    bPtr->printA();  // Calls A::printA()
    bPtr->printB();  // Calls B::printB()

    std::cout << std::endl;

    C* cPtr = &dObject;
    cPtr->printZ();  // Calls Z::printZ()
    cPtr->printA();  // Calls A::printA()
    cPtr->printC();  // Calls C::printC()
    cPtr->printY();  // Calls Y::printY()

    std::cout << std::endl;

    D* dPtr = &dObject;
    dPtr->printZ();  // Calls Z::printZ()
    dPtr->printA();  // Calls A::printA()
    dPtr->printC();  // Calls C::printC()
    dPtr->printY();  // Calls Y::printY()
    dPtr->printB();  // Calls B::printB()
    dPtr->printD();  // Calls D::printD()

    return 0;
}
