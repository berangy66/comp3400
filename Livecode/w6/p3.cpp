#include <algorithm>
#include <iterator>
#include <vector> 
#include <iostream> 


int main()
{
    using namespace std; 

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto pos1 = find(v.begin(), v.end(), 4);
    auto pos2 = find(pos1, v.end(), 8);

    vector<int> v2; 
    transform(
        pos1, pos2, //input range: [pos1, pos2)
        back_inserter(v2),
        [](int i) { return 2*i; }
    );

    cout << "we found: "; 
    copy(begin(v2) , end(v2), ostream_iterator<int>(cout, " "));
    cout << '\n'; 

    cout << "original: "; 
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << '\n'; 


}