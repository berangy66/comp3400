#include <algorithm> 
#include <iterator> 
#include <iostream>
#include <vector>

template <typename Iter> 
void quick_sort(Iter first , Iter last)
{
    if(first != last)
    {
        auto const pivot = *std::next(first, std::distance(first,last) / 2);
        Iter middle1 = std::partition(first, last, [pivot](auto const& elem) { return elem < pivot; });
        Iter middle2 = std::partition(middle1, last, [pivot](auto const& elem) { return !(pivot < elem); });
        quick_sort(first, middle1);
        quick_sort(middle2, last);
    }
}


int main()
{
    std::vector<std::string> v{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    quick_sort(v.begin(), v.end());
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    return 0;
}