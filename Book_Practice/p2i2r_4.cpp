#include <iostream>

int ar[] = {1,2,3,4,5};

using myiterator = int*; 
myiterator mybegin()
{
    return &ar[0];
}
myiterator myend()
{
    return mybegin() + 5;
}



int main()
{
    using namespace std; 

    for(myiterator i = mybegin(); i != myend(); ++i)
    {
        cout << *i << ' '; 
        cout << '\n';
    }
}