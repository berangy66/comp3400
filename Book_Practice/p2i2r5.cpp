#include<iostream>


using myiterator = int*; 

myiterator mybegin(int* startpos)
{
    return startpos; 
}

myiterator myend(int* stoppos)
{
    return stoppos + 5; 
}


int main()
{
    using namespace std; 

    int ar[] = {1,2,3,4,5};
    for(myiterator i = mybegin(ar); i != myend(ar); ++i)
    {
        cout << *i << ' ' << '\n'; 
    }
}