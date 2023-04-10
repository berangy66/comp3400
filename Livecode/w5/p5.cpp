#include <algorithm> 
#include <numeric> 
#include <iostream> 
#include <map>

int main()
{
    std::map<std::string, int> hist; 

    std::string s; 
    while(std::cin >> s)
    {
        ++hist[s]; 
        //whih is equiv. to : ++*hist.insert({s, 1}).first; 
    }

    for(auto const& e :hist ) 
    {
        std::cout << e.first << ' ' << e.second << '\n'; 
    }
}