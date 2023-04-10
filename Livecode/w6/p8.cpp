#include <algorithm> 
#include <functional> 
#include <set>
#include <map> 
#include <string> 
#include <vector> 
#include <iostream> 

//
//The live code tries to use std::map with std::ostream_iterator --and that 
//won't work. Why wont it work? Because the C++ standard 
//states taht when when looking up names for functions to call it looks up 
//name in namespace of the type used. with:
//
//  std:;map<std::string, int> 
//
// all of the types involved , i.e., 
//
//  std::map<std::string, int>
//  std::pari<std::string const, int> 
//  std::string
//
// etc. are in the std namspace. this means any operator<<() overload we write
// in a different namespace will not be found --and there is no overload of
// operator<< in the std namespace for std::pair. Thus, the compiler reprots an
// error that there is no operator<< overload available.
//
// there are ways around this, including:
//  *use std::for_each with a lambda function instead of 
//     std::ostream_iterator
//  *create a type in your own namespace in it to produce the output.
//
// of these, using a lambda is simplest so that is what is done in this file. 
//
// ASIDE: Normally this doesn't pose a problem since one is not typically
//        outputing std::pair object with dat only from std namesapce, 
//        bur, admittedly it is an edge case that is annoying. 
//
// Using std::for_each is okay if only outputting the elements since
// std::for_each is required to be non-modifying of the input range.
//
// The reason std::copy cannot be used with a lambda is becuase std::copy()
// assigns the outp iterator to each value. A lambda is a fucntion and must
// be called and not assigned

std::ostream& operator<<(std::ostream& os, std::pair<std::string const, int> const& p)
{
    os << p.first << ' ' << p.second; 
    return os; 
}

int main()
{
    using namespace std; 

    map<string, int> dict; 

    string s; 
    while(cin>> s)
        ++dict[s]; 

    //next line will not compile (see above )...
    //copy(begin(dict), end(dict), ostream_iterator<std::pair<std::string, int> >{cout, " "});
    for_each(begin(dict), end(dict), [](auto const& p) { cout << p; } );
}
