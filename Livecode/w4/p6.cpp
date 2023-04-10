#include <memory>  //std::unique_ptr
#include <iostream> //std::cout
#include <string> //std::string
#include <vector> //std::vector

class object
{
public: 
    object(std::string const& name) : name_{name} {}

    void write(std::ostream& os) 
    {
        os << " name: " << name_ << '\n';
    }

private: 
    std::string name_ ; 
};

int main() 
{
    using namespace std; 

    vector<unique_ptr<object>> v; 

    v.push_back(make_unique<object>("Bella"));
    v.push_back(make_unique<object>("Leyla"));
    v.push_back(make_unique<object>("Adessa"));

    v.insert(v.begin(), make_unique<object>("Ben"));
    v.insert(v.begin() + 1, make_unique<object>("Sylvia"));
    v.insert(v.begin(),make_unique<object>(object("Mom")));
    v.insert(v.begin(), make_unique<object>(object("Dad")));
   

    for (auto const& e: v)
    {
        e->write(std::cout);
    }
}
