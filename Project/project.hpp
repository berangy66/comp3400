#ifndef uwindsor_2023w_comp3400_project_hpp_
#define uwindsor_2023w_comp3400_project_hpp_
//=============================================================================
// nessary include header file for the project.hpp file.
//=============================================================================
#include <iostream> //for std::cout
#include <string> //for std::string
#include <algorithm> //for std::min
#include <vector> //for std::vector
#include <ranges> //for std::ranges
#include <numeric> //for std::iota
#include <random> //for std::random_device
#include <iomanip>
#include <concepts>
#include <iterator>
#include <type_traits>
#include <ranges> 




#include "utils.hpp" //for the utils.hpp file.

//=============================================================================
// nested namespaces uwindsor_2023w::comp3400::project.
//=============================================================================

namespace uwindsor_2023w {
namespace comp3400 {           
namespace project {

//=============================================================================


//=============================================================================
// min() Overloaded Definitions
// Updated min() function to take in one or more arguments
//=============================================================================
template <typename T>
constexpr T const& min(T const& a)
{
  return a;
}

template <typename T> 
constexpr T const& min(T const& a, T const& b)
{
  return a < b ? a : b;
  
}

template <typename T, typename... Rest>
requires (std::same_as<T, Rest> && ...) 
 constexpr T min(T const& a, T const& b, Rest const& ... rest)
{//5.18 chapter 5
  return min( min(a,b), rest...);

  //return std::min({a,b,rest...});

  //return std::min({a,b,rest...}, cmp);
  //std::min({a,b,rest...},[](T const&a, T const&b){ return std::min({a, b, rest...})}); //not sure how to fix this return statement
  //std::pair<T, T> min(std::min(a,b), std::min(rest...));
}
//=============================================================================

//=============================================================================
// The levenshtein() Function Definition
//=============================================================================
template <typename stringA , typename stringB>
requires(std::ranges::sized_range< stringA> &&
 std::ranges::sized_range<stringB> &&
 std::ranges::random_access_range<stringA> &&
 std::ranges::random_access_range<stringB> &&
 std::same_as<
   std::ranges::range_value_t<stringA>,
   std::ranges::range_value_t<stringB>
   >)
 std::size_t levenshtein(stringA const& a, stringB const& b) //function prototype for levenshtein function
{
//Any indices involving items in ranges/std::vector must be of type std::size_t.
//To obtain the size of a range
// std::ranges::size();
// std::ranges::size();
std::vector<std::size_t> v0 (std::ranges::size(b) + 1); // i.e., v0.resize(n + 1)
//iota function is used to fill the range with a sequence of numbers, starting from 0 and incrementing by 1.
iota(v0.begin() , v0.end(), 0);  // i.e., for i from 0 to n: v0[i] = i, 
//std::ranges::size() returns the size of the range as a std::size_t.
std::vector<std::size_t> v1 (std::ranges::size(b) + 1);// i.e., v1.resize(n + 1)

// initialize v0 (the previous row of distances)
    // this row is A[0][i]: edit distance from an empty s to t;
    // that distance is the number of characters to append to  s to make t.
for(std::size_t i = 0; i < std::ranges::size(a); ++i)
{
  v1[0] = i + 1; // i.e., v1[0] = i + 1
  // or equivalently: v1.front() = i+1;


        // use formula to fill in the rest of the row
     // for j from 0 to n - 1:
  for(std::size_t j = 0; j < std::ranges::size(b); ++j)
  {

     //calculing cost for A[i + 1][j + 1]
     size_t deletiocost = v0[j + 1] + 1; //deletion cost := v0[j + 1] + 1
     size_t insertioncost = v1[j] + 1; //insertion cost := v1[j] + 1


    auto const& a_iter = std::ranges::begin(a);
    auto const& b_iter = std::ranges::begin(b);
    size_t substitutionCost;
    if(a_iter[i] == b_iter[j])
    {
       substitutionCost =  v0[j];
    }
    else
    {
       substitutionCost = v0[j] + 1;
    }

    v1[j + 1] = min(deletiocost, insertioncost, substitutionCost);
  }//end of inner for loop
// copy v1 (current row) to v0 (previous row) for next iteration
// since data in v1 is always invalidated, a swap without copy could be more efficient
  swap(v0, v1); // swap v0 (current row) and v1 (previous row) to process next row
 
}//end of outer for loop
 // after the last swap, the results of v1 are now in v0
return v0[std::ranges::size(b)];

}//end of levenshtein function
//Note: iota() REplace each elment with a swquence of incremented value(sice C++11) pg 571


//=============================================================================
//The class char_mutator Definition
//=============================================================================

class char_mutator
{
  public:
  //The overload must return a char.
  template <typename... Args>
  char operator()(Args&&...) const
  {
    return validChar[range(re)];
  }

  char_mutator() :
  validChar { // validChar = 
    []() {
        std::string retval;
        
        for(short i= 0; i < std::numeric_limits<char>::max()+1; ++i)
        {
          if(std::isalnum(i) || std::ispunct(i) || i == ' ')
          {
            //append the mutated string to the retval string
            //retval += i;
            retval.push_back(i);
          }
        }//end of for loop

        return retval;
    } () //calling the lambda and putting retval as input for validChar construction, perfectly forwarding
    },
  range(0, validChar.size() - 1),
  re(std::random_device{}())
  {
  }



    private:
    std::string validChar; //string to be mutated
    mutable std::uniform_int_distribution<std::size_t> range; //uniform distribution of integers
    mutable std::default_random_engine re; //random number generator
  
    
}; //end of class char_mutator

//=============================================================================
// The mutate() Function Definition
//The mutate() function declaration/definition must have this prototype:
//=============================================================================
template <
  std::ranges::range Individual,
  typename MutateOp,
  typename URBG
> 
requires
  std::uniform_random_bit_generator<std::remove_cvref_t<URBG>> &&
  std::invocable<MutateOp, std::ranges::range_value_t<Individual>>
  void mutate(
    Individual& individual, 
    double const rate, 
    MutateOp m , 
    URBG&& urbg
  ){
    std::uniform_real_distribution<double> range(0.0 , 1.0);
    std::ranges::for_each(individual, [&](auto& arg)
    {
      if(range(urbg) < rate)
      {
        arg = m(arg);
      }
    });
  }




  //==================================================================================
  // The crossover() Function Definition
  //==================================================================================

//The crossover() Function Definition
template <
  typename URBG1, 
  typename URBG2, 
  typename Individual
>
requires
  //URBG1 and URBG2 must be std::uniform_random_bit_generator concepts and must be the same type.
  std::uniform_random_bit_generator<std::remove_cvref_t<URBG1>> &&
  std::uniform_random_bit_generator<std::remove_cvref_t<URBG2>> &&
  //Requires both parents to have the same underlying element type. 
  std::ranges::forward_range<Individual> &&
  std::ranges::sized_range<Individual> &&
  smart_insertable<Individual>
auto crossover(
 std::size_t const ncrossover_points,
 URBG1&& urbg_starting_parent,
 URBG2&& urbg_crossover_points,
 Individual const& parent1,
 Individual const& parent2
) -> std::remove_cvref_t<Individual> 

/*
he crossover function requires the following::

NOTE: The URBG1 and URBG2 parameters are uniform random bit generators.
The urbg_starting_parent argument is used to determine which parent to start copying from.
This URBG will be used with std::bernoulli_distrbution.
The urbg_crossover_points argument is used to determine the crossover indices to switch which parent is copied from for that "chunk".
This URBG will be used with std::uniform_int_distribution.
NOTE: The parent1 and parent2 parameters are const forward ranges with constant-time size() support.
ASIDE: Each parent range is considered to be that parent's "DNA".
ASIDE: The test_crossover.cpp program intentionally uses parent ranges that have different lengths so you can easily see how such is handled. (Normally with genetic algorithms one ensures both parents have the same length.)
You may only use these C++ Standard Library types and function calls in this functions code
You may only use these C++ Standard Library types and function calls in this functions code:
std::adjacent_difference()
std::advance()
std::back_inserter()
std::bernoulli_distribution
std::ranges::cbegin()
std::ranges::cend()
std::ranges::copy()
std::copy_n()
std::iota()
std::remove_cvref_t<Individual>
*/

{
 //Determining minimim size of the two parents. Store this in a read-only variable
  std::size_t const psize_truncated = std::min(std::ranges::size(parent1), std::ranges::size(parent2)); //size of the smaller parent

//==================================================================================
//use the std::bernoulli_distribution. Declare a std::bernoulli_distribution variable with probability 0.5
  std::bernoulli_distribution bd(0.5); 

//==================================================================================
//bool variable "which_parent" identiifies which parent range is currently being copied from and initialize it to the
// std::bernoulli_distribution variable being applied to urbg_starting_parent
   bool which_parent = bd(urbg_starting_parent);

//==================================================================================
//if statement such that if any of ncrossover_points or (parent1's range size or parent2's range size are 0) -> if( psize_truncated is 0),
//then return the parent argument as-is per the which_parent variable's value.
 if(ncrossover_points == 0 || psize_truncated == 0)
 {
    if(which_parent) 
    {
      return parent1;
    }
    else
    {
      return parent2;
    }
 }

//==================================================================================
//*******Realize the number of crossover points, k, you need is stored in the "ncrossover_points" function argument variable. *****/
//******* not sure what this means or what to do ?******//


//==================================================================================
//Declare a std::vector<size_t> variable to hold the indices of each crossover point.
//Construct this vector with psize_truncated-1 elements. (This needs to be done in order to use std::iota().)
//This variable will be referred to as "crossover_indices" below.
 std::vector<size_t> crossover_indices(psize_truncated - 1);


//==================================================================================
//Call std::iota() over all elements in crossover_indices starting at 1 --not 0
// ASIDE: Think about why you might want to do this starting at 1 and not 0.
// ASIDE: Also why have an array of indices counting upwards? This allows one to use std::ranges::sample()
// to uniformly sample (without replacement) the crossover points. Cool eh?!!! :-)
 std::iota(std::ranges::begin(crossover_indices), std::ranges::end(crossover_indices), 1);


//==================================================================================
// Declare a std::vector<size_t> to hold the crossover offset values.
// This variable will be referred to as "crossover_offsets" below.
// Until std::adjacent_difference() is called below, the elements are really indices --not offsets.
//  After std::adjacent_difference() is called on this vector all of the values will be relative offsets. 
//  Such will be needed to easily copy alternating "chunks" from each parent. 
  std::vector<size_t> crossover_offsets;


//==================================================================================
// Call reserve_or_noop() on crossover_offsets with ncrossover_points.
// ASIDE: Why? This will help improve the code efficiency as crossover_offsets grows in size.
reserve_or_noop(crossover_offsets, ncrossover_points);


//==================================================================================
// Call std::ranges::sample() on the vector crossover_indices, using std::back_inserter() to append elements to crossover_offsets, 
// sampling ncrossover_points with the urbg_crossover_points UBRG.
//C++ Standard Library container, e.g., std::vector, is a range --so it can be passed to std::ranges::sample().
std::ranges::sample(crossover_indices, std::back_inserter(crossover_offsets), ncrossover_points, urbg_crossover_points);


//==================================================================================
// Now with crossover_offsets populated with some crossover points, call std::adjacent_difference() to compute the adjacent differences of each index.
// This will make the crossover_offsets vector have relative offsets starting the the beginning. This will allow one to use iterators to track iterator 
// positions in each parent when copying data.
// ASIDE: If you did not realize it yet, this is why you want std::iota() to start at 1. If you start at 0, then the first "chunk" to copy might be of size
//  zero. Remember earlier you determined which_parent to start copying from --and you want to copy at least 1 element from a parent each time.
// ASIDE: The reason crossover_indices has psize_truncated-1 elements instead of psize_truncated elements is that you want to copy all remaining elements
//  from the parent in the last chunk. Since the parents might not be the same size, this allows you to stop looping just before the last chunk is copied
//   so you can perform the copy of the last chunk copying all remaining elements.


//  std::adjacent_difference(v.begin(), v.end(), v.begin()); ?? why?? 
//OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first) or this ??
std::adjacent_difference(crossover_offsets.begin(), crossover_offsets.end(), crossover_offsets.begin());

//==================================================================================
/**** needs to be done now is to copy alternating chunks from each parent in to a container that is returned
 from the function. Guidance on how this can be achieved: ****/
//==================================================================================

//==================================================================================
//Declare the return value variable of type Individual with any const, volatile, and reference removed from the Individual type.
//ASIDE: This variable will be called "retval" below.
// ASIDE: You will need to use this to declare a variable to hold the return value. If you wrote Individual variable_name; you might discover that might not work
//  if Individual had const or reference decorations. Removing such eliminates the issue, e.g., write std::remove_cvref_t<Individual> variable_name; 
//  to declare the variable that will be used to hold the computed result that need to be returned from the function.
std::remove_cvref_t<Individual> retval;


//==================================================================================
// Call reserve_or_noop() on retval with the result of std::max() of std::ranges::size() of parent1 and std::ranges::size() of parent2.
// ASIDE: This std::max() call is max() in the C++ Standard Library. (Earlier the definition of min() used was the one you wrote.)
// ASIDE: Why do this? Efficiency. Also one does not know in this function the type of Individual which could be a std::vector, std::string, std::list, etc.
reserve_or_noop(retval, std::max(std::ranges::size(parent1), std::ranges::size(parent2)));


//==================================================================================
// Call smart_inserter passing retval storing the return value in a variable.
// ASIDE: This variable will be referred to as "out" below.
// ASIDE: Look at utils.hpp to see what smart_inserter() does.
 auto out = smart_inserter(retval);



//==================================================================================
// Declare a variable whose initial value is std::ranges::cbegin(parent1);
// ASIDE: This variable will be referred to as "p1pos" below.
auto p1pos = std::ranges::cbegin(parent1);

//==================================================================================
// Declare a variable whose initial value is std::ranges::cbegin(parent2);
// ASIDE: This variable will be referred to as "p2pos" below.
auto p2pos = std::ranges::cbegin(parent2);


//==================================================================================
//for loop that iterates over all elements in crossover_offsets
//Within the for loop, each element will be referred to as "offset".
// If which_parent is set to the parent1 value, then call std::copy_n() passing in p1pos, offset, and out. Assign the return value of std::copy_n() to out.
// If which_parent is set to the parent2 value, then do the same as for parent1 except with parent2.
// Call std::advance() on p1pos adjusting it by offset.
// Call std::advance() on p2pos adjusting it by offset.
// Change which parent to be the value representing the other parent.
// Tip: If you used a bool for which_parent, you can "which_parent = !which_parent;" to toggle its value between the two states. Using a bool avoids
//  having to have more if statements, etc. If also makes it easy to test for "which_parent" in if statements since one can write lines 
//  of code like this: "if (which_parent) /* parent1 code */; else /* parent2 code */;"
for(auto offset : crossover_offsets)
{
  if(which_parent)
  {
    out = std::copy_n(p1pos, offset, out);

  }
 if(!which_parent) // or else like beyond_project.hpp live code?? 
  {
    out = std::copy_n(p2pos, offset, out);
  }


  which_parent = !which_parent;  // double check with Prof.
  std::advance(p1pos, offset);
  std::advance(p2pos, offset);
}


//==================================================================================
// After the for loop, if which_parent is set to the value for parent1, then call std::ranges::copy() on the range [p1pos,std::ranges::cend(parent1))
//  passing in out. Otherwise do the same but for p2pos and parent2.
// ASIDE: Notice this copies the last chunk to the end of the appropriate parent range.
// ASIDE: The reason for using std::ranges::copy() is because std::ranges::end(), etc. can return sentinel values in general, 
// i.e., it might not return an iterator which std::copy() requires. (Know that std::ranges::begin(), etc. always return iterators).
if(which_parent)
{
  std::ranges::copy(p1pos, std::ranges::cend(parent1), out);
}
else
{
  std::ranges::copy(p2pos, std::ranges::cend(parent2), out);
}



//==================================================================================
//Return retval.
return retval;

}//end of crossover function definition
 


//=============================================================================

} // namespace project
} // namespace comp3400
} // namespace uwindsor_2023w

//=============================================================================

 #endif // #ifndef namespaces uwindsor_2023w::comp3400::project_hpp