#include <iostream> 


class object
{
    public:
        virtual ~object () { std::cout << "~object @" << this << '\n'; }
};


class node : public object 
{
    public : 
     ~node() { std::cout << "~node @" << this << '\n'; }
}; 


int main()
{
    object* o = new node; 
    delete o; 
}