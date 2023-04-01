#include <algorithm> 
#include <iterator> 
#include <iostream> 
#include <vector> 

using namespace std; 

int main()
{
    vector<int> v; 
    
    int i ; 
    while (cin >> i)
    {
        v.push_back(i); 
    }

    transform(
        v.begin(), // start of input
        v.end(), // end of input 
        v.begin(),
        [](auto const& i) { return i * 2; }
    );

    for( auto e : v)
    {
        cout << e << '\n'; 
    }
}