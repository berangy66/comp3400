#include <string> //std::string
#include <filesystem> //for std::filesystem , recursive_directory_iterator
#include <iomanip> //for std::quoted
#include <iostream> //std::cout, std::cerr
#include <regex> //

//create two namespaces(std & std::filesystem)
//C++ "namespace aliases" used to assign shorten name to another namespacee
//deafault namespace will search for unknown sysmbols of "std"
//Using the namespace alias call "fs" to access symbols in the std::filesystem
using namespace std; 
namespace fs = std::filesystem; 

/******** MAIN FUNCTION STARTS *******/
int main(int argc, char *argv[])
{
    if(argc != 2 && argc !=3) // if argc < 2 & 3 print cerr
    {
        cerr << "USAGE: " << argv[0] << " <path> [<regex>]\n"; 
        return 1; 
    }

    fs::path const base = argv[1]; //passing path to recursively search assigned to var base from argv[1]
    char const *re = ".*"; //hard coding the argv[3] in event user doesnt enter 3rd argv

    if(argc == 3) //argc == 3  then change var re value to argv[2] entered by user
    {
        re = argv[2] ; 
      
    }
    regex compiled_re(re); //compile regex with var *re value

    //iterate recursively through all directory entries under the passed path by var base
    for(auto const& entry: fs::recursive_directory_iterator(base, fs::directory_options::skip_permission_denied))
    {
       std::string s = entry.path().lexically_relative(base).native(); //to obtain relative directory name, 
       auto const p = quoted(s); //wrap a string inquotes and store in variable p 

   
        smatch m; //var m to hold result of a match/non-match values called by regex_math
        if(regex_match(entry.path().filename().native(), m , compiled_re))
        {
            if(fs::is_symlink(entry) == true) //if is syslink print Link 
            {
                    std::cout << "LINK: "  << p << '\n'; 
            }
            else if(fs::is_regular_file(entry) == true) // if is regular file
            {
                    std::cout << "FILE: " << fs::file_size(entry) << ' ' << p << '\n';

            }
            else if(fs:: is_directory(entry) == true) //if is directory print Dir 
            {
                    std::cout << "DIR: " << p << '\n'; 
            }
            else // not a file , dir or syslink
            {
                    std::cout << "OTHER: " << p << '\n'; 
            }
            
        }//end of regex_match() if 

    }//end of for loop


}//end of function main 

//g++ -std=c++20 -Wall -Wextra -Wold-style-cast -Werror -pedantic a1c.cpp