#include <cstddef>
#include <utility> 
#include <ostream>
#include <iostream> 
#include <algorithm> 
#include <stdexcept>

using namespace std; 

class myvector
{
public:
using value_type = double;  
using size_type = size_t; 
using reference = value_type&; 
using const_reference = value_type const&;
using difference_type = std::ptrdiff_t; 
using iterator = double*; 
using const_iterator = double const*; 

private: 
value_type *ptr_;   //ptr_ is an array of length size_ , or , nullptr if size_ == 0
std::size_t size_;  //length of array stored at ptr_ , or , 0 if ptr_ == nullptr 

public:
iterator begin() {return ptr_ ; } //provided 
const_iterator begin() const { return ptr_ ; } //provided
const_iterator cbegin() const { return ptr_ ; } //provided 
iterator end() { return ptr_ ? ptr_ + size_ : ptr_ ; } //provided
const_iterator end() const { return ptr_ ? ptr_ + size_ : ptr_ ; };//provided 
const_iterator cend() const { return ptr_ ? ptr_ + size_ : ptr_; } //provided

// default constructor
//myvector() : ptr_(nullptr) , size_() {}
myvector() : ptr_ {nullptr} , size_{0}
{

}



// cpy constructor
myvector(myvector& *obj) : ptr_{ obj.ptr_ != nullptr ?  new value_type(obj.size_)  : nullptr } , size_ {obj.size_}
{
    std::copy(obj.begin() , obj.end(), _size );
} 




// move constructor 
myvector(myvector&& obj) : ptr_ (obj.ptr_), size_(obj.size_) 
{
    obj.ptr_ = nullptr;
    obj.size_ = size_; 
}



// cpy assignment operator 



// move assignment operator 



//destructor 



myvector(size_type size); 

//array operator overload





// single-argument swap() member function 
void swap(myvector& obj)
{
  
}



void resize(size_type newsize , value_type value = {});


}; // end of class 'myvector' 

inline void swap(myvector& a , myvector & b) { a.swap(b); }


//inline std::ostream myvector output function 
std::ostream<<(ostream& os , myvector& value)
{
    os << value ; 
    return os; 
}


















//================================================================================================
// function main()
//================================================================================================
int main()
{
using namespace std;
myvector a(5); 
a[0] = 1.0; 
cout << "a0: " << a << '\n'; 

myvector b(a);
b.resize(10, 2.0);
cout << "b0: " << b << '\n'; 

myvector c(move(b)); 
c.resize(7); 
c[1] = 3.0; 
sort(begin(c), end(c));
cout << "b1: " << b <<"\nc0: " << c << '\n';
a= move(c); 
cout << "c1: " << c << "\na1: " << a << '\n';
}



//================================================================================================
//**************************OUTPUT**************************************************************//
// moradib@bravo:~/comp3400/Livecode/examcode$ ./a.out
// a0: 1 0 0 0 0 
// b0: 1 0 0 0 0 2 2 2 2 2 
// b1: 
// c0: 0 0 0 1 2 2 3 
// c1: 
// a1: 0 0 0 1 2 2 3 
//================================================================================================

// =================================================================================================
// std::copy(InIter first, InIter last, OutIter out) copies the elements in the range defined
// by [first,last) to another range starting at out; and returns the next position of the last value
// written to with out, or, if no data was written, then out is returned.
// • std::fill(FwdIter first, FwdIter last, value) assigns value to the elements in the range defined
// by [first,last).
// • std::begin(c) returns c.begin().
// • std::end(c) returns c.end().
// std::min(a, b) returns the smaller value of a and b.
// • std::swap(a,b) swap() swaps the values of a and b using move or, if moves are not possible,
// copy semantics.
//=================================================================================================
