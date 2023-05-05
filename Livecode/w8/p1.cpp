#include <concepts> 
#include <vector> 
#include <list> 
#include <iostream> 

template <typename Container, typename Int>
concept reservable = 
requires (Container c , Int n)
{
    { c.reserve(n) }; 
}
;

int main()
{
    using namespace std; 

    vector<double> d; 
    d.reserve(56);

    cout << reservable<vector<double>, int> <<'\n';
    cout << reservable<list<double>, int> <<'\n';
}