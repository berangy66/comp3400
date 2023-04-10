#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

template <typename RndIter>
RndIter find_pivot_iter(RndIter first , RndIter last)
{
    //Determine the pivot, return an iterator to the pivot
    auto const d = std::distance(first , last); 

    switch(d)
    {
        //
        case 0 : {return last;} //empty range

        case 1 : {return first;} //one element

        case 2 : {return std::max(first, first + 1); } //two elements

        default: { return std::min(std::min(first + d/2, last - 1), first, 
            [](auto const& a, auto const& b){ return *a < *b; }); }
    }
}

template <typename RndIter>
void quick_sort(RndIter const& first , RndIter const& last)
{
    using std::iter_swap; 
    using std::partition; 
    using std::prev;
    using std::next;

    if(first == last) return; // empty range list

    //Determine the pivot, return an iterator to the pivot
    auto const pivot = find_pivot_iter(first, last); 

    //swap the pivot with the first position... , 
    iter_swap(first, pivot); 

    //partition excluding the pivot value now in *first
    auto pos_after_pivot = partition(next(first),last, 
        [&first](auto const& v){return v < *first; }
    ); 

    //if the first half is not empty, move the pivot value back to 
    //the correct position; otherwise, the pivot value is in the correct position
    if(first != prev(pos_after_pivot))
    {
        auto prev_to_pos_after_pivot = prev(pos_after_pivot);
        iter_swap(first, prev_to_pos_after_pivot);

        //sort the first half before pivot
        quick_sort(first, prev_to_pos_after_pivot);


    }
    //sort the second half after pivot
    quick_sort(pos_after_pivot, last); 
}

int main()
{
    std::vector<int> v = {4 , 0 , 45 , 78 , 90, 45, 67, 1000, 100, 300, 300 , 200}; 
    quick_sort(v.begin(), v.end()); 
    for(auto const& e : v)
    {
        std::cout << e << " "; 
    }
    std::cout << std::endl; 
    return 0; 
}
