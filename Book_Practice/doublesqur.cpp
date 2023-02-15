#include <iostream> //include ("import") the declarations fro the I/O stream library
#include <cmath> 
#include <complex>
#include <vector>


using namespace std; // make names from std visible without std:: ($3.4)

double square(double x)
{
    return x * x;
}

void print_square(double x)
{
    cout << "The square of " << x << " is " << square(x) << "\n";
}

int main()
{
    print_square(1.234); // print: the square of 1.234 is 1.5.2276

    double s2 = sqrt(2); // sqrt() buildin f'n return square root of value 
    cout << s2 << "\n"; 

    double s3 = square(4); // square() buildin f'n return the square of a value 
    cout << s3 << "\n";

    double d4 {5};
    cout << d4 << "\n"; 

    complex<double> z1 {s3,d4}; 
    cout << z1 << "\n";

    std::vector<int> v{1,2,3,4,5,6};
    for(int i = 0; i < v.size(); i++){
    std::cout << v.at(i) << "\n"; 
    }

    auto b {true}; // we avoid redundancy and writing long type names. 
    cout << b << "\n"; //this is speicially important in generic programming where the exact type of an object can be hard for the programmer to know and the type names can be quite long 
    

}


/*
The type of a function consists of its return type and the sequence of its argument types. For example:
double get(const vector<double>& vec, int index); // type: double(const vector<double>&,int)

A function can be a member of a class (§2.3, §4.2.1). For such a member function, the name of its
class is also part of the function type. For example:
char& String::operator[](int index); // type: char& String::(int)

*/