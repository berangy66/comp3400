#include <memory>  //std::unique_ptr
#include <string> //std::string 
#include <iostream> //std::cout
#include <vector> //std::vector


class xml_object
{
public:
    xml_object(std::string const& name) : 
    name_{name}
    {

    }

    virtual ~xml_object(){}

    virtual void write(std::ostream& os) const = 0; 


   
private:
    std::string name_; 
};

class node: public xml_object
{
    public: 
    node(std::string const& name) :
    xml_object{name}
    {

    }


    void write(std::ostream& os) const override
    {
        os << "<node></node> "; 
    }
};



int main()
{
    using namespace std; 
    //a vector holding unipue_ptr to xml_object to the base via polymorphism , up is a unique_ptr to xml_object
    vector<unique_ptr<xml_object>> v; 

    //a unique_ptr<node> is easily created by clalling make_unique<node>
    //passing in the desired node object
    v.push_back(make_unique<node> (node("abcdedf")));
    v.push_back(make_unique<node> (node("1234567fd")));
    v.push_back(make_unique<node>(node("%%%%%%:wabcdedf")));


     


    for(auto const& e: v)
    {
        e->write(std::cout  );
    }
}