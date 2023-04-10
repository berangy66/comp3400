#include <algorithm> 
#include <vector> 
#include <iostream> 

int main()
{
    using namespace std; 

    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8 , 9 ,10};

    auto pos1 = find(v.begin() , v.end(), 4);
    auto pos2 = find(pos1, v.end(), 8); 
    transform(pos1, pos2, pos1, [](int i) { return 2*i; }); 

    for(int e : v)
    {
        cout << e << ' '; 
    
    }
    cout << '\n'; 
}