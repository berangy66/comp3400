#include <iostream> 


using namespace std;




void bubbleSort(int arra[], int n)
{
    for(int i = 0 ; i < n-1 ; i++)
    {
        for(int j = 0 ; j < n-i-1; j++)
        {
            if(arra[j] > arra[j + 1])
            {
                //swap(arr[j], arr[j+1]); 
                int temp = arra[j];
                arra[j] = arra[j + 1];
                arra[j + 1] = temp; 
            }
        }
    }
}

int main()
{
    int arra[] = {64, 34, 25, 12 , 22, 11, 90};
    int n = sizeof(arra) / sizeof(arra[0]); 
    bubbleSort(arra, n ); 
    cout << "sorted array: "; 
    for(int i = 0; i < n; i++)
    {
        cout << arra[i] << " "; 
    }

    return 0 ;
}