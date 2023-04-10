#include <algorithm> 
#include <functional> 
#include <iterator> 
#include <set>
#include <vector> 
#include <iostream> 


int main()
{
    using namespace std;

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto pos1 = find(v.begin(), v.end(), 4);
    auto pos2 = find(pos1, v.end(), 8); 

    set<int> s; 
    transform(
        pos1, pos2, //input rang [pos1, pos2)
        inserter(s, s.end()),
        [](int i) { return 2*i; }
    );
    sort(pos1, pos2, greater<>{} );

    cout << "We found and transform: "; 
    copy(begin(s), end(s), ostream_iterator<int>(cout, " "));
    cout << '\n'; 

    cout << "Original: "; 
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << '\n'; 
}