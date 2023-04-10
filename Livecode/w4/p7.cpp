#include <memory>  //std::unique_ptr
#include <iostream> //std::cout
#include <string> //std::string
#include <vector> //std::vector


class object
{
public: 
    object(std::string const& name) : name_{name} {}

   std::string const& name() const { return name_; }

private: 
    std::string name_ ; 
};



int main() 
{
    using namespace std; 

    vector<unique_ptr<object>> v; 

    std::string myname = "";
    std::cout << "Enter your name (or type 'exit' to quit): ";
    std::cin >> myname;
    while(myname != "exit")
    {
        v.push_back(make_unique<object>(myname));
        std::cout << "Enter your name (or type 'exit' to quit): ";
        std::cin >> myname;
    }

    for (auto const& e: v)
    {
        std::cout << e->name() << std::endl;
    }

        
    sort(v.begin(), v.end(), [](auto const& a, auto const& b) { return a->name() < b->name(); });
    cout << "Sorted: " << endl;
    cout << "-------" << endl;
    for (auto const& e: v)
    {
        std::cout << e->name() << std::endl;
    }
}
