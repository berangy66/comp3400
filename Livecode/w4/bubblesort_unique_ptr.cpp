#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <memory>  //std::unique_ptr

using namespace std; 

template <typename Iter>
void bubble_sort(Iter begin, Iter end)
{
    for(auto i = begin ; i != end ; ++i)
    {
        
        for(auto j = begin ; j != end - 1 ; ++j )
        {

            if(*j > *(next(j, 1))) //next(j, 1) is the same as *(j + 1)
            {
                iter_swap(j, next(j, 1)); //iter_swap is the same as swap(*j , *(j + 1));
                
            }
        }
       
    }
}



class object
{
    public: 
        object(string const& name) :
            name_{name} 
        {

        }

        string const& name() const 
        {
            return name_ ; 
        }

        friend std::ostream& operator<<(std::ostream& os, const object& obj); //friend function to print object, not just name becuasae we want to print the whole object

    private:
        string name_ ; 
};

std::ostream& operator<<(std::ostream& os, const object& obj) 
{
    os << obj.name() ;
    return os;
}


int main()
{
    vector<unique_ptr<object>> v; //Note: unique_ptr can't be copy. there can be only one copy of it when it gets automatically ~destructed 

    string myname = " " ; 
    cout << "Enter your name (or type 'exit' to quite): " ;

    cin >> myname; 
    while(myname != "exit")
    {
        v.push_back(make_unique<object>(myname));
        cout << "Enter your name (or type 'exit' to quite): " ;
        cin >> myname;
    }

    for(auto const& e: v)
    {
        cout << e->name() << endl;
    }
    cout << endl;

    cout << "Sorted: " << endl;
    cout << "-------" << endl;

    bubble_sort(v.begin(), v.end()); //call bubble sort
    //move(v.begin(), v.end(), ostream_iterator<unique_ptr<object>>(cout, " ")); //print out the vector
   

 
    for(auto const& e: v)
    {
        cout << e->name() << endl;
    }
    cout << endl;

    return 0;
}
