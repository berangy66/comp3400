#include <memory>  //std::unique_ptr
#include <iostream> 


class object 
{
    public: 
        virtual ~object(){ std::cout << "~object @ " << this << '\n'; }
};

class node : public object
{
    public: 
        ~node () { std::cout << "~node @" << this << '\n'; }
};

int main()
{
    std::unique_ptr<object> up{new node};
}