#include <string>
#include <filesystem>
#include <iomanip>
#include <iostream> 
#include <regex> 

using namespace std; 
namespace fs = std::filesystem; 


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "USAGE: " << argv[0] << " <path> \n"; 
        return 1; 
    }

    fs::path const base = argv[1];


    for(auto const& entry: fs::recursive_directory_iterator(base, fs::directory_options::skip_permission_denied))
    {
       std::string mypath = entry.path().native();  //item 7 
      auto const p = quoted(mypath); 

         std::cout << "Current path is " << entry << '\n'; // prints out the path 

       if(fs::is_symlink(entry) == true)
       {
            std::cout << "LINK: "  << p << '\n'; 
       }
       else if(fs::is_regular_file(entry) == true)
       {
            std::cout << "FILE: " << fs::file_size(entry) << ' ' << p << '\n';

       }
       else if(fs:: is_directory(entry) == true)
       {
            std::cout << "DIR: " << p << '\n'; 
       }

    }


}//end of function main 

//-std=c++20 -Wall -Wextra -Wold-style-cast -Werror -pedantic