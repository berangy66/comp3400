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


// =================================================================================================
// Write the default constructor for myvector where:
// • ptr_ and size_ are properly initialized before the opening brace bracket, “{”, of the constructor,
// • ptr_ must be initialized to nullptr,
// • size_ must be explicitly default constructed, and,
// • there must be no code statements inside the constructor body’s brace brackets.
//=================================================================================================
//your default constructor appears here        myvector();
myvector() : ptr_{nullptr}, size_{0} //default constructor
{}

// =================================================================================================
// Write the copy constructor for myvector where:
// • the object being copied-from is called obj,
// • ptr_ and size_ are properly initialized before the opening brace bracket, “{”, of the constructor,
// • ptr_ must be initialized using constructor syntax utilizing a ternary operator as follows:
// – if the obj.ptr_ is not nullptr, then the result is from the code that dynamically
// allocates using new a C-style array of type value_type having obj.size_ elements,
// – otherwise, the result is nullptr.
// • size_ must be initialized to be obj.size_, and
// • the only code inside the constructor body’s brace brackets must be:
// – a call to std::copy to copy obj.size_ array elements from the array stored in the obj
// object into ptr_.
//=================================================================================================
//your copy constructor appears here        myvector(myvector const&);
myvector(myvector const& obj) : 
ptr_{new value_type[obj.size_]}, //allocate new memory for ptr_
size_{obj.size_} //copy the size of obj to size_
{
std::copy(obj.ptr_, obj.ptr_ + obj.size_, ptr_);
}

// =================================================================================================
// Write the move constructor for myvector so that:
// • the object being moved-from is called obj, and,
// • properly move the ptr_ and size_ variables from obj to this object.
// • ptr_ and size_ are properly initialized before the opening brace bracket, “{”, of the constructor,
//=================================================================================================  
//your move constructor appears here        myvectory(myvector &&); 
myvector(myvector && obj) :
ptr_{obj.ptr_}, //steal the pointer from obj
size_{obj.size_} //steal the size from obj
{
    obj.ptr_ = nullptr; //set obj's pointer to nullptr
    obj.size_ = 0; //set obj's size to 0
}

// =================================================================================================
//your copy assignment operator appears here    myvector& operator=(myvector const&); 
myvector& operator=(myvector const& obj) 
{
    if (this != &obj) //check for self-assignment
    {
        myvector temp{obj}; //create a temporary copy of obj
        swap(temp); //swap the contents of temp and *this
    }
    return *this; //return *this, by convention to allow chaining of assignment, e.g. a = b = c; 
}

// =================================================================================================
// Write the move assignment operator using the move-and-swap idiom as follows:
// • Declare a local myvector variable which moves the assignment’s right-hand side value into
// that variable during its construction.
// • Call the member swap() function to swap the local myvector variable with *this
// • Return *this.
//=================================================================================================
//your move assignment operator appears here    myvector& operator=(myvector &&); 
myvector& operator=(myvector && obj)
{
if (this != &obj) //check for self-assignment
    {
        delete[] ptr_; //deallocate the memory pointed to by ptr_
        ptr_ = obj.ptr_; //steal the pointer from obj
        size_ = obj.size_; //steal the size from obj
        obj.ptr_ = nullptr; //set obj's pointer to nullptr
        obj.size_ = 0; //set obj's size to 0
    }
    return *this; //return *this, by convention to allow chaining of assignment, e.g. a = b = c;
}

//================================================================================================
//Write the destructor ensuring that any and all acquired resources are properly released
//=================================================================================================  
//your destructor appears here          ~myvector(); 
~myvector()
{
delete[] ptr_;
}

// =================================================================================================
// Write the array operator overload to index the array as follows:
// • if ptr_ is not null, then return that index suitable so that the returned result can be meaningfully
// used on the left-hand side of an assignment operator,
// • otherwise, throw the value std::domain_error("ptr_ is nullptr");.
//=================================================================================================
//your array operator overload appears here
reference operator[](size_type index)
{
if (ptr_)
{
    return ptr_[index];
}
else
{
    throw std::domain_error("ptr_ is nullptr");
}
}


// =================================================================================================
// Write a member function accepting a single parameter, obj, to swap the values contained
// within *this and obj. Ensure std::swap is used to swap corresponding ptr_ and size_
// values.  *this and obj must be valid objects, and, if *this and obj are the same object,
//=================================================================================================
//your single-argument swap() memberr functionappears here 
void swap(myvector& obj) 
{
std::swap(ptr_, obj.ptr_);
std::swap(size_, obj.size_);
}

// =================================================================================================
// Write the constructor with a single size_type parameter where:
// • the size_type parameter is the number of elements, i.e., size_, the dynamically allocated
// array, i.e., ptr_, will hold,
// • ensure that ptr_ is properly initialized using constructor syntax, i.e., if the array size is
// zero, ensure it is null, otherwise it is properly dynamically allocated,
// • ensure that size_ is properly initialized using constructor syntax, and,
// • the only code that can appear within the constructor body’s brace brackets is a single call
// to std::fill() to fill the array with 0.0 values.
//=================================================================================================
//your constructor with a single size_type parameter appears here
explicit myvector(size_type size) : 
ptr_(size == 0 ? nullptr : new value_type[size]),
size_(size) 
{
std::fill(ptr_, ptr_ + size_, 0.0);
}

//your resize() member function appears here
void resize(size_type newsize, value_type value={});   //default value = 0.0

// =================================================================================================
//your inline std::ostream myvector output function appears here
ostream & operator<<( myvector const& v); //output operator overload

};//end myvector class

// =================================================================================================
inline void swap(myvector& a, myvector&b) { a.swap(b);} //provided 

//================================================================================================
// Write the inline std::ostream bitshift operator overload to output the contents of
// myvector to a std::ostream object, e.g., std::cout, as follows:
// • output each element to the std::ostream object, and,
// • ensure each element, except the last element in the array, is followed by a single space
//=================================================================================================
//your inline std::ostream myvector output function appears here 
inline ostream & operator<<(ostream & os, myvector const& v)
{
for(auto i = v.begin(); i != v.end(); ++i)
{
    os << *i << " ";
}
return os;
}

//================================================================================================
// Write the resize(size_type,value_type) member function where the size_type parameter
// is the new size that this object’s array must be resized to as follows:
// • If the new size is larger, then all elements in the current array must be copied into the
// new array with any remaining elements filled with the value of the second parameter.
// • If the new size is smaller, then all elements up to the new array size must be copied in to
// the new array.
// • If the new size is the same, then immediately return as there is nothing to do.
// This must be done as follows:
// • Declare a local myvector variable, tmp, using the constructor with the single size_type parameter
// passing the size of the new array to it.
// • Call std::copy() to copy this object’s array into tmp.
// • Call std::fill() to fill any remaining elements in tmp (should there be any) with the value
// passed as this function’s second argument.
// • Call the swap() member function to swap this object with tmp.
//=================================================================================================
//your resize() member function appears here
void myvector::resize(size_type newsize, value_type value) 
{
if (newsize == size_) { return; } // if newsize is the same as size_, return

if (newsize == 0) //
{
    delete[] ptr_; // deallocate the memory pointed to by ptr_
    ptr_ = nullptr; // set ptr_ to nullptr
    size_ = 0; // set size_ to 0
    return; 
}

value_type *temp = new value_type[newsize]; // allocate new memory for temp on the heap using new, and assign it to temp
// copy elements from ptr_ to temp using std::copy
std::copy(
        ptr_, // start of range
        ptr_ + std::min(size_, newsize), // end of range (the smaller of size_ and newsize), so that we don't copy more elements than we have in ptr_
        temp // destination
    );

// fill the remaining elements in temp with value using std::fill
std::fill(
        temp + std::min(size_, newsize), // start of range (the smaller of size_ and newsize), so that we don't fill more elements than we have in
        temp + newsize, // end of range, so that we don't fill more elements than we have in temp
        value // value to fill with, which is the second parameter of resize(), which is defaulted to 0.0
    );

// swap the contents of ptr_ and temp using std::swap
std::swap(ptr_, temp);

// deallocate the memory pointed to by temp , on the heap using delete[] to avoid memory leaks by manually deallocating memory since we used new to allocate it and we are responsible for deallocating it
delete[] temp;

size_ = newsize; // set size_ to newsize
}


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