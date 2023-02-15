#include <iostream> 
#include <vector> 


struct Vector 
{
    double* elem;   // pointer to elements
    int sz;         // number of elements
    public: 
       
};

Vector v; 

void vector_init(Vector& v, int s)   //initialize a Vector 
{
    v.elem = new double[s];     // intitializ a Vector 
    v.sz = s; 
}

double read_and_sum(int s)
{//read s integers from cin and return their sum; s is assumed to be 
   // Vector v; 
    vector_init(v,s);        //allocate s elements for v

    for(int i = 0; i != s ; ++i)
    {
        std::cout << "enter integer\n";
        std::cin >> v.elem[i]; // read inot elements 
    }
    double sum = 0 ;
    for (int i = 0 ; i != s ; ++i)
     {
           sum+= v.elem[i]; // compute the sum of the elments
     } 
        return sum; 
}

int main()
{
 
   
   double results =  read_and_sum(3);
   std::cout << results << " result of the sum is\n"; 
}