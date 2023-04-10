#include <algorithm> 
#include <functional> 
#include <iterator> 
#include <set> 
#include <vector> 
#include <iostream> 


int main()
{
    using namespace std;

    vector<int> v{ -432, 1, -4, 3 , -1000, 5 , -2, 34, 254, 9, -53 };
    set<int> s{begin(v), end(v)};

    copy(begin(s), end(s), ostream_iterator<int>(cout," "));
}