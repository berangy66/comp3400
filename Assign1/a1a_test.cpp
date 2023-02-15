#include <string>  //for std:string 
#include <filesystem> //for std:filesystem 
#include <iomanip> //for std:::quoted
#include <iostream> // std::cout , std::cerr
#include <regex>

//create two namespaces(std & std;;filesystem)
//C++ "namespace aliases" used to assign shorten anme to another namespacee
//deafault namespace will search for unknown sysmbols of "std"
//Use the namespace alias call "fs" to access symbols in the std::filesystem
namespace fs = std::filesystem;
using namespace std; 
char const* re = ".*"; 
//using std::filesystem::recursive_directory_iterator; //we are telling the compiler to look in this filesystem for recursive_directory_iterator
using std::basic_regex;


/******** MAIN FUNCTION STARTS *******/
int  //NOTE: main() ALWAYS return an int value. ALWAYS. Standard defines the value of teh int return to be 0(zero). If a return statement is not provided by user in main 
main(int argc, char *argv[]){ //main is the only function returning a value that is permitted to not have a return statment. "echo $?" return exit states of main function 
    

   if(argc != 2 && argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <path> [<regex>]\n"; 
        return 1; 
    }
    if(argc == 3)
    {
        re = argv[2]; 
    }
      cout << argv[1] << '\n';
         cout << argv[2] << '\n';
            cout << argv[3] << '\n';

    cout << "DEBUG: " << re << '\n';
  
    regex compiled_re(re); 
    smatch m; 
    fs::path const base = argv[1]; 
   

    

    for(auto const& entry : fs::recursive_directory_iterator(base,fs::directory_options::skip_permission_denied))
    {
       std::cout << "Current path is " << entry << '\n'; // prints out the path 
        //std::coutn << "Parent direcoty" <<fs::parent_path() <<'\n';
     
    
       // ITEM 7) Inside the for loop, you will need to obtain the name the entry variable refers to . 
       //This can be done by invoking entry's .path() member function, followed by the .native() member function (of a fs::path object).
       // Assign the result to a std::string variable.
       string const s = entry.path().native();
        //auto const p = quoted(s); 
        if(regex_match(entry.path().filename().native(), m , compiled_re))
        {
            std::cout << "good: " << entry << '\n';
            if( fs::is_symlink(entry) == true)
        {
        
            std::cout <<"LINK:" ;
        
        }
        //your previous range for body should be inside this if statement
        }

        
    }

}//end of function main 










