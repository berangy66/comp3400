#include <random> 
#include <iostream> 

int main()
{
    using namespace std;
    
    random_device rd; 

    default_random_engine re(rd()); //seed is rd()'s return value

    uniform_int_distribution<int> ud(0,99); 
    for(int i=0; i !=5; ++i)
    {
        cout << ud(re) << '\n'; 
    }

}