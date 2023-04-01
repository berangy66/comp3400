#include <algorithm> 
#include <iterator> 
#include <iostream> 
#include <vector> 

using namespace std;

int main()
{
    vector<int> v; 
#if 1
    int i ; 
    while( cin >> i)
    {
        v.push_back(i);
    }
#else
    copy(
        istream_iterator<int>(cin), // start of input
        istream_iterator<int> () , // end of input
        v.push_back(i);
    );
#endif


#if 1
    for(auto e : v)
    {
        cout << e << '\n'; 
    }


#elif 0 

auto it = v.begin(); 
auto it_end = v.end(); 
for(; it != it_end; ++i)
{
    cout << *it << '\n';
}

#else
    copy(
        v.begin(), // start of input
        v.end() , // end of input
        ostream_iterator<int>(cout, "\n") // start of output
    ); 

#endif
}