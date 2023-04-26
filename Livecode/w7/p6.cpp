#include <string>
#include <iostream> 

using namespace std;

template <typename T>
struct one 
{
    T t; 
};


template <typename DatumType>
struct list_node
{
    DatumType datum; 
    list_node<DatumType> *prev; 
    list_node<DatumType> *next; 
};



int main()
{
    one<int> o1, o2, o3; 
    one<string> o4; 

    list_node<int> ln1; 
    list_node<list_node<one<string>>> ln2; 

    
}