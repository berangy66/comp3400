#include <algorithm> // for std:: transform()
#include <iterator> // 
#include <iostream> //

using namespace std; 

int main()
{
    transform(
        istream_iterator<int>(cin) , // start of input 
        istream_iterator<int>(), // end of input
        ostream_iterator<int>(cout, "\n"), // start of output

        [](int i)  {  return i * 2; } // lambda function
    );
}


  //
  // std::transform() is called "map" in mathematics and in many other
  // languages. This is because it maps every element from a half-open input 
  // range [first,last) to an output sequence (via the output iterator passed
  // to the third argument). The mapping is done by calling the function passed
  // to the fourth argument.
  //
  // Notice the first three arguments are identical to std::copy().
  //

   //
    // The function passed to the third argument is a "lambda function". A
    // lambda function is a function without a name, e.g., std::copy,
    // std::transform, std::sqrt, etc. are all functions with names. While one
    // can use auto to give a lambda function a name, normally this isn't done.
    // So for a lambda function to be useful (as it doesn't have a name) it
    // needs to be immediately passed to a function argument that will make use
    // of it.
    //
    // In C++, all lambda functions are compiled in to function objects (i.e.,
    // classes with operator() overloaded) as this results in more efficient
    // generated code than using function pointers.
    //
    // Also C++ lambdas need not specify the return type in most instances
    // --the C++ compiler can deduce it from the function.
    //
    // Clearly if you need to use a specific function more than once, it is
    // often better to define the function normally (giving it name). If the
    // function will only be used once and it is short, using a lambda function
    // is typically best.
    //
    // Lambda functions in C++ always start with square brackets. (Things can
    // be put in to the brackets.)
    //