#include <iostream>
using namespace std;

const int SIZE = 10;

void bubbleSort(int[]);
void selectionSort(int[]);
void printArray(int[]);

int main()
{
    int arr[SIZE] = {5,2,6,9,19,4,1,29,10,3};
    //int arr[SIZE] = {5,2,3};


    cout << "OG array: " << endl;
    printArray(arr);

    cout << "====Bubble Sort====" << endl;

    bubbleSort(arr);
    printArray(arr);

    cout << "====Selection Sort====" << endl;

    int second_arr[SIZE] = {5,2,6,9,19,4,1,29,10,3};
    selectionSort(second_arr);
    printArray(second_arr);

    return 0;
}

void bubbleSort(int arr[])
{
    int tmp = 0;
    bool swap = true;

    for (int i=0; (i<SIZE) && swap; i++)
    {
	swap = false;

	for (int j=0; j<SIZE-1; j++)
	{
	    if (arr[j] > arr[j+1])
	    {
		tmp = arr[j];
		arr[j] = arr[j+1];
		arr[j+1] = tmp;
		swap = true;
	    }
	}
    }
}

void selectionSort(int arr[])
{
    int tmp = 0;
    int min_index = 0;

    for (int i=0; i<SIZE-1; i++)
    {
        min_index = i;

        for (int j=i+1; j<SIZE; j++)
	{
	    if (arr[j] < arr[min_index])
		min_index = j;
	}

	tmp = arr[i];
	arr[i] = arr[min_index];
    	arr[min_index] = tmp;
    }
}



void printArray(int arr[])
{
    for (int i = 0; i<SIZE; i++)
        cout << arr[i] << " | ";
    cout << endl;
}
