#include <algorithm> 
#include <functional>
#include <iterator>
#include <set> 
#include <vector> 
#include <iostream> 


int main()
{
    using namespace std; 

    vector<int> v{ -432, 1, -4, 3 , -1000, 5, -2, 34, 254, 9, -53 }; 

    auto pos1 = find(v.begin(), v.end(), 3);
    auto pos2 = find(pos1, v.end() , 34); 

    set<int> s; 
    transform(
        pos1 , pos2, // input range: [pos1, pos2)
        inserter(s, s.end()),
        [](int i) { return 2*i; }
    );
    sort(pos1, pos2, greater<>{});

    cout << "We found and transform: ";
    copy(begin(s), end(s), ostream_iterator<int>(cout, " " ));
    cout << '\n'; 

    cout << "Orginal: "; 
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << '\n'; 

}