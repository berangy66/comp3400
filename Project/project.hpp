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


//********************why is this not working? *******************************************************************************************//
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

  //***************************************************************************************************************************************//

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
template <typename URBG1, typename URBG2, typename Individual>
requires
  std::uniform_random_bit_generator<std::remove_cvref_t<URBG1>> &&
  std::uniform_random_bit_generator<std::remove_cvref_t<URBG2>> &&
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
 

  // reserve_or_noop();
  // std::size_t;
 


  
std::size_t k = min( std::ranges::size(parent1), std::ranges::size(parent2));
  // auto p1it = std::ranges::size(parent1); 
  // auto p2lit = std::ranges::size(parent2);


   std::bernoulli_distribution  probability {0.5};

  bool which_parent {probability( urbg_starting_parent)};
  std::ranges::sample(urbg_crossover_points, k , ncrossover_points + 1);
  std::remove_cvref_t<Individual> retvale{};
  

  if(which_parent == false)//false is parent1
  {

  }
  if(which_parent == true) // true is parent2
  {
  
  }

 std::vector<size_t> crossover_point;
  for(;;)
  {

  }

  for(;;)
  {

  }
return 0 ; 
 }







//=============================================================================

} // namespace project
} // namespace comp3400
} // namespace uwindsor_2023w

//=============================================================================

 #endif // #ifndef namespaces uwindsor_2023w::comp3400::project_hpp