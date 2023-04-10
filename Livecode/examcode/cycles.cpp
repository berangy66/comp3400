// function to detect whether or not there are
// cycles in his graphs (whose nodes are identified by numbers in a std::map, see below). Whether
// or not there is a cycle needs to be determined by a function called has_cycles whose prototype
// is as follows:
#include<map> 
#include<vector> 
#include<stack> 
#include<iostream> 

using namespace std; 

template
<
    typename Func,
    typename Predicate, 
    typename Value
>
bool has_cycles(
    Func const& next,
    Predicate const& has_next, 
    Value const& v
)
{
    Value slow = v;
    Value fast = next(v);
    while (fast != slow) {
        slow = next(slow);
        if (!has_next(fast))
        {
            return false;
        }
        fast = next(next(fast));
    }
    return true;
}

//=============================================================================================

int main()
{
    using graph = map<int, int>; 
    graph no_cycles{ {1,2}, {2,3}, {3,4} }; 
    graph  circular{ {1,2}, {2,3}, {3,4}, {4,1} }; 
    graph  p_shaped{ {1,2}, {2,3}, {3,4}, {4,2} };

    cout
     << has_cycles
                 ([&](auto v) {return no_cycles.find(v)->second; },
                  [&](auto v) {return no_cycles.find(v) !=end(no_cycles); } , 1)
    << has_cycles
                 ([&](auto v) {return circular.find(v)->second; },
                  [&](auto v) {return circular.find(v) !=end(circular); } ,   1)
     << has_cycles
                 ([&](auto v) {return p_shaped.find(v)->second; }, 
                  [&](auto v) {return p_shaped.find(v) !=end(p_shaped); },    1)
    << '\n'   
; 
}
    
 //outputs: 001       