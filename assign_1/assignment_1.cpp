#include <iostream>
using namespace std;

const int SIZE = 10;

void bubbleSort(int[]);
void insertionSort(int[]);
void printArray(int[]);

int main()
{
    int arr[SIZE] = {5,2,6,9,7,4,1,8,10,3};

    cout << "OG array: " << endl;
    printArray(arr);

    cout << "====Bubble Sort====" << endl;

    bubbleSort(arr);
    printArray(arr);

    cout << "====Insertion Sort====" << endl;

    int second_arr[SIZE] = {5,2,6,9,7,4,1,8,10,3};

    insertionSort(second_arr);
    printArray(second_arr);

    return 0;
}

void bubbleSort(int arr[])
{
    int i,j,tmp = 0;

    for (i = 0; i < SIZE; i++)
    {
    	for (j = SIZE-1; j >= i+1; j--)
    	{
    	    if (arr[j] < arr[j-1])
    	    {
                tmp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = tmp;
    	    }
    	}
    }
}

void insertionSort(int arr[])
{
    int i,j,key = 0;

    for (j=1; j<SIZE; j++)
    {
        key = arr[j];
        i = j - 1;
        
        // roll through sorted list
        while (i >= 0 && arr[i] > key)
        {
            arr[i+1] = arr[i];
            i--;
        }

        // Insert key into sorted list
        arr[i+1] = key;
    }
}

void printArray(int arr[])
{
    for (int i = 0; i<SIZE; i++)
        cout << arr[i] << " | ";
    cout << endl;
}
