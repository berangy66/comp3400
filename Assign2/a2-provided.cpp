//=============================================================================

#include <charconv>           // for std::from_chars
#include <compare>            // for std::strong_ordering
#include <concepts>           // for std::forward_iterator
#include <fstream>            // for std::ifstream
#include <functional>         // for std::function
#include <ios>                // for std::ios_base::failbit
#include <iostream>           // for std::cout, std::cerr
#include <map>                // for std::map
#include <optional>           // for std::optional
#include <sstream>            // for std::ostringstream
#include <stack>              // for std::stack
#include <stdexcept>          // for std::domain_error
#include <string>             // for std::string
#include <system_error>       // for std::errc
#include <memory>
#include <vector>

//=============================================================================

class mod5
{
private:
  unsigned i;

public:
  
     mod5(): //invoking parent class (:)
    i{} 
  { 
  }

  mod5(mod5 const&) = default; //copy constructor, we are using default copy constructor to avoid deep copy 
  mod5& operator=(mod5 const&) = default; //copy assignment operator, we are using default copy assignment operator to avoid deep copy

  explicit mod5(unsigned value) : //explicit keyword is used to avoid implicit conversion 
    i{value}  //invoking parent class (:) , i is the private member variable of the class mod5, value is the argument passed to the constructor, we are assigning the value to i 
  {
  }

  unsigned mod_value() const //member function 
  {
    return i % 5; //
  }

//This function computes using the right-hand side value by assignment operator and assigns it to the lhs left-hand side 
//This operator is definded as member function of the mod5 class and returns an lvalue 
  mod5& operator+=(mod5 const& rhs) //member function 
  {
      // this->i += rhs.mod_value();
      // return *this;

      i += rhs.i; //we are adding the rhs value to the lhs value, rhs.i is the private member variable of the class mod5
      return *this; //returning the lhs value
  }
  
//This function computes using the right-hand side value by assignment operator and assigns it to the lhs left-hand side 
//This operator is definded as member function of the mod5 class and returns an lvalue 
  mod5& operator-=(mod5 const& rhs)
  {
     this->i -= rhs.mod_value() ;
     return *this;
  }
  
//This function computes using the right-hand side value by assignment operator and assigns it to the lhs left-hand side 
//This operator is definded as member function of the mod5 class and returns an lvalue 
  mod5& operator*=(mod5 const& rhs)
  {
         this->i *= rhs.mod_value() ;
         return *this;
  }

//This function computes using the right-hand side value by assignment operator and assigns it to the lhs left-hand side 
//This operator is definded as member function of the mod5 class and returns an lvalue 
  mod5& operator/=(mod5 const& rhs)
  {
     // we can not have 0 (zero) as a rhs value
     //The if block will check if it is zero & will throws an exception by building a string reason using an std::ostringstream object
        if(rhs.mod_value() == 0) 
        {
            std::ostringstream buf;
            buf << "mod5 divide by zero; operands(" << i << " ," << rhs.i << ')';
            throw std::domain_error(buf.str());
        }
     
            this->i /=  rhs.mod_value() ;
            return *this;
  }
 
 //function compares the lhs mod_value with rhs mod_value and returns a bool value
friend bool operator==(mod5 const& lhs, mod5 const& rhs)
  {
     return  lhs.mod_value() == rhs.mod_value();    
  }

//The return type is auto, 
//function returns a statement by three-way-comparison of the lhs mod_value to rhs mod_value
  friend auto operator<=>(mod5 const& lhs, mod5 const& rhs) 
  {  
    return lhs.mod_value() <=> rhs.mod_value();
  }
};//End of class mod5 

//Function returns default constructed mod5 object 
//we creat local mod5 temp1 variable, then assign lhs side value and
//then we preform the operator overload of rhs on lhs & returns the local copy 
mod5 operator+(mod5 const& lhs, mod5 const& rhs)
{  
        mod5 temp1 = lhs;
        temp1 += rhs; 
        return {temp1};
}
  
//Function returns default constructed mod5 object 
//we creat local mod5 temp1 variable, then assign lhs side value and
//then we preform the operator overload of rhs on lhs & returns the local copy 
mod5 operator-(mod5 const& lhs, mod5 const& rhs)
{
  
        mod5 temp1 = lhs;
        temp1 -= rhs; 
        return {temp1};
}

//Function returns default constructed mod5 object 
//we creat local mod5 temp1 variable, then assign lhs side value and
//then we preform the operator overload of rhs on lhs & returns the local copy 
mod5 operator*(mod5 const& lhs, mod5 const& rhs)
{
    
        mod5 temp1 = lhs;
        temp1 *= rhs; 
        return {temp1};
}

//Function returns default constructed mod5 object 
//we creat local mod5 temp1 variable, then assign lhs side value and
//then we preform the operator overload of rhs on lhs & returns the local copy 
mod5 operator/(mod5 const& lhs, mod5 const& rhs)
{
    
        mod5 temp1 = lhs;
        temp1 /= rhs; 
        return {temp1};
}

//function return the std::istream variable in the function 
std::istream& operator>>(std::istream& is, mod5& m)
{
  //local variable will reads in next unsigned from is >> temp
    unsigned temp; 
     is >> temp;

    //if expression is >> temp true then assigns the rhs variable 'm' to mod5{temp}
    //else  mod5 object is not properly read in, the stream is marked as "failbit", processing on the stream will stop due to failure of reading data
    //returns the stream variable from the function
    
    //if(is >> temp)
    if(  temp == true )
    {
        mod5{temp} = m ;  
    }
    else
    {
        is.setstate(std::ios_base::failbit);
    }
      return is;

}

//Function returns by reference the std::ostream variable in the function 
//By ouputing the mode_value() of the mod5 object passed into the std::osteram object 
std::ostream& operator<<(std::ostream& os, mod5 const& m)
{
   os << m.mod_value(); 
   return os; 
   //return os << m.mode_value(); 
}

//=============================================================================

// std::optional<unsigned> either holds an unsigned value or it does not.
std::optional<unsigned> string_to_unsigned(std::string const& str)
{
  unsigned num;

  // [ptr,err] is an example of a "structured binding" --see ATOCPP textbook
  auto const [ptr, err] = 
    std::from_chars(str.data(), str.data() + str.size(), num);

  if (err == std::errc() && (ptr == str.data() + str.size()))
    // no error and all data was consumed so construct return...
    return { num };
  else
    // otherwise default construct an empty optional value...
    return {};
}

//=============================================================================

// allow the s literal suffix to be used with string literals to yield
// strings of type std::string...
using namespace std::literals::string_literals;

// convenience type alias for code below...
using mod5_stack = std::stack<mod5>;
  
//=============================================================================

//
// std::map<Key,Value> is a dictionary ordered by key-base sorting Key.
//
// std::function<FnType> holds a callable entitiy of type FnType. In this
// case FnType is void(mod5_stack&), i.e., the function has void return and
// one parameter of type mod5_stack&.
//
std::map< std::string, std::function< void(mod5_stack&) > > const op_table{
  { 
    "+"s, 
    [](mod5_stack& stk) 
    { 
      if (stk.size() < 2)
        throw std::domain_error("insufficient number of stack entries");

      auto const op1 = stk.top(); 
      stk.pop(); 

      auto const op2 = stk.top();
      stk.pop();

      stk.push(op1 + op2);
    }
  },
  { 
    "-"s, 
    [](mod5_stack& stk) 
    { 
      if (stk.size() < 2)
        throw std::domain_error("insufficient number of stack entries");

      auto const op1 = stk.top(); 
      stk.pop(); 

      auto const op2 = stk.top();
      stk.pop();

      stk.push(op1 - op2);
    }
  },
  { 
    "*"s, 
    [](mod5_stack& stk) 
    { 
      if (stk.size() < 2)
        throw std::domain_error("insufficient number of stack entries");

      auto const op1 = stk.top(); 
      stk.pop(); 

      auto const op2 = stk.top();
      stk.pop();

      stk.push(op1 * op2);
    }
  },
  { 
    "/"s, 
    [](mod5_stack& stk) 
    { 
      if (stk.size() < 2)
        throw std::domain_error("insufficient number of stack entries");

      auto const op1 = stk.top(); 
      stk.pop(); 

      auto const op2 = stk.top();
      stk.pop();

      stk.push(op1 / op2);
    }
  }
};

//=============================================================================

//
// The <algorithm> header has many algorithms in it. This is an algorithm
// defined to apply op to each pair of values in the (half-open) range 
// [first,last).
//
template <std::forward_iterator It, typename Op>
void adjacent_apply(It first, It last, Op op)
{
  if (first == last)
    return;

  It prev = first;
  ++first;

  for (; first != last; ++prev, ++first)
    op(*prev,*first);
}

//-----

int simple_rel_demo(std::istream& in)
{
  std::vector<mod5> v;

  // process the input adding all unsigned values to v...
  for (std::string token; in >> token;)
  {
    auto const num = string_to_unsigned(token);
    if (num)
      v.push_back(mod5{*num});
  }

  // process v in outputting various results...
  std::cout << "rel_demo: operator==(): ";
  adjacent_apply(v.begin(), v.end(), [](auto const& a, auto const& b)
    {
      std::cout << (a == b);
    }
  );
  std::cout << '\n';

  std::cout << "rel_demo: operator<(): ";
adjacent_apply(v.begin(), v.end(), [](auto const& a, auto const& b)
    {
      std::cout << (a < b);
    }
  );

  std::cout << '\n';
  
  std::cout << "rel_demo: operator>(): ";
  adjacent_apply( v.begin(), v.end(), [](auto const& a, auto const& b)
    {
      std::cout << (a > b);
    }
  );
  std::cout << '\n';
  return 0;
}

inline int simple_rel_demo(std::istream&& in)
{
  // in is an lvalue that refers to an rvalue
  // the next call invokes simple_rpn_demo(std::istream&)...
  return simple_rel_demo(in);
}

//=============================================================================

int simple_rpn_demo(std::istream& in)
{
  //
  // declare stack and process input...
  //
  mod5_stack stk;
  for (std::string token; in >> token;)
  {
    // if any exceptions occur, output such to cerr and continue...
    try
    {
      auto const num = string_to_unsigned(token);
      if (num)
      {
        // construct a mod5 object from *num and push it onto stk...
        stk.push(mod5{*num});
        continue;
      }
      else
      {
        // search op_table for token
        auto pos = op_table.find(token);
        if (pos != op_table.end())
          // found token, call function passing in stk...
          pos->second(stk);
        else
          // token not found, output error...
          std::cerr << "ERROR: Unknown operation: " << token << '\n';
      }
    }
    catch (std::domain_error& ex)
    {
      std::cerr << "EXCEPTION: " << ex.what() << '\n';
    }
    catch (...)
    {
      std::cerr << "FATAL: Unknown exception. Aborting.\n";
      return 1;
    }
  }

  //
  // dump stack...
  //
  std::cout << "stack(" << stk.size() << "):";
  while (!stk.empty())
  {
    std::cout << ' ' << stk.top();
    stk.pop();
  }
  std::cout << '\n';
  return 0;
}

inline int simple_rpn_demo(std::istream&& in)
{
  // in is an lvalue that refers to an rvalue
  // the next call invokes simple_rpn_demo(std::istream&)...
  return simple_rpn_demo(in); 
}

//=============================================================================

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  // call simple_rel_demo passing in a std::istream file object...
  simple_rel_demo(std::ifstream(argv[1]));

  // call simple_rpn_demo passing in a std::istream file object...
  return simple_rpn_demo(std::ifstream(argv[1]));
}

//=============================================================================
