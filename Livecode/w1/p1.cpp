#include <algorithm> // for std:: copy()
#include <iterator> // for std:: {i ,s }tream_iterator, std:: back_insert_iterator
#include <iostream> // for std:: cin, std:: cout


using namespace std; 

int main()
{
    copy(
        istream_iterator<int>(cin), // start of input
        istream_iterator<int> () , // end of input
        ostream_iterator<int>(cout, "\n") // start of output
    );
}

//
    // First two arguments of std::copy() are an input range composed of two
    // iterators of the half-open interval: [start position,end position).
    //
    // std::istream_iterator<T>(s) is a special type that allows one to
    // treat the input stream "s" as a range of items of type "T".
    //
    // std::istream_iterator<T>() is a special type whose default constructor
    // (i.e., the constructor that accepts no arguments) represents the
    // "end" of the input stream (which occurs when end-of-file is reached
    // or when an input error occurs reading in a value of type T --whichever
    // occurs first).
    //
    //
    // The third argument of std::copy() is where output is to be placed.
    // 
    // std::ostream_iterator<T>(s,str) is a special type that allows one to 
    // treat an output stream "s" as an output iterator that outputs type T 
    // values. After each element of type T is output, the output iterator
    // also writes str.
    //