#include <memory>  //std::unique_ptr
#include <iostream> //std::cout
#include <string> //std::string


class xml_object
{

public:
    xml_object(std::string const& name) :
    name_{name}
    {

    }

    virtual ~xml_object(){}

    virtual void print(std::ostream& os) const = 0;
private: 
    std::string name_; 
}; 


class node: public xml_object // node is a xml_object
{
public: 
    node(std::string const& name) :
    xml_object{name}
    {

    }

    void print(std::ostream& os) const override 
    {
        os << "<node></node>" << std::endl;
    }
};

int main()
{
    std::unique_ptr<xml_object> up {new node{"abcdedf"}}; // up is a unique_ptr to xml_object
    up->print(std::cout);
}