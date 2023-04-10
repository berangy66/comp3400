#include <iostream> 

class object 
{
    public: 
        ~object() {std::cout << "~object @" << this << "\n"; } // not virtual, so only 'object' destructor is called
};

class node : public object
{
    public: 
        ~node() {std:: cout <<"~node @" << this << '\n'; } // not virtual, so only 'node' destructor is called
};


int main()
{
    object* o = new node; // not all destructors called! , only 'object' destructor is called
    delete o; // not all destructedors called!
}