#include <algorithm> 
#include <numeric> 
#include <iterator>
#include <iostream> 
#include <list>



int main()
{
    using namespace std; 

    std::list<double> v; 

    double d; 
    while(std::cin >> d)
        v.push_back(d); 

v.sort(); //since std::sort cannot be used with std::list
    //sort(begin(v) , end(v)); 

auto pos = find(begin(v), end(v) , 1.);
auto pos2 = find(pos, end(v) , 7.); 

copy(pos, pos2, ostream_iterator<double>(cout,"\n"));
}