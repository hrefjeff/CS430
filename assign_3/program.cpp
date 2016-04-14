#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct item
{
    int weight;
    int value;
};

void insert_item_into(vector<item>& container, int weight, int value);
int optimal_knapsack(vector<item>& container, int max_weight, int num_of_items);
void print_contents_of(vector<item> container);
void print_item(item);
void readFile( string filename, 
               vector<item> & container,
               int & container_capacity,
               int & num_of_items
             );
int main()
{

    vector<item> inventory;
    int max_weight;
    int num_of_items;

    //=============Begin File Read Stuff=====================
    fstream file;
    string filename;
    bool badFile = true;

    do {

        cout << "Input file name: ";
        cin >> filename;
        
        file.open(filename);
        badFile = file.fail();
        file.close();

    } while (badFile);

    readFile(filename,inventory,max_weight,num_of_items);
    //=============End File Read Stuff=======================

    print_contents_of(inventory);

    int optimal_value = optimal_knapsack(inventory,max_weight,num_of_items);

    cout <<  "Optimal Knapsack Value: " << optimal_value << endl;

    return 0;
}

void print_item(item x)
{
    cout << "(W: " << x.weight << ", V: " << x.value << ")" << endl;
}

void print_contents_of(vector<item> container)
{

    cout << endl << "=====Contents of container=====" << endl;

    for (int i = 0; i < container.size(); i++)
    {
        cout << "Item " << i << ": ";
        print_item(container[i]);
    }

    cout << "==============================="<< endl;
}

void insert_item_into(vector<item>& container, int weight, int value)
{
    container.push_back(item());
    container[container.size() - 1].weight = weight;
    container[container.size() - 1].value = value;
}

/*

    3 items, max weight 5

    a: (W: 1, V: 60)
    b: (W: 2, V: 100)
    c: (W: 3, V: 120)

    5 | 0 | 60 | 180  | [220]
    4 | 0 | 60 | 180  | 180
    3 | 0 | 60 | 180  | 180
    2 | 0 | 60 | [120]| 120
    1 | 0 | 60 | 60   | 60
    0 | 0 | 0  | 0    | 0 
    ------------------------
        0 | a  |  b   | c

*/
int optimal_knapsack(vector<item>& container, int max_weight, int num_of_items)
{

    int item, weight, value_with_item, value_without_item;
    int optimal_table[num_of_items+1][max_weight+1];

    // iterate through items
    for (int item = 0; item <= num_of_items; item++)
    {
        // assign optimal value for wieght of item i
        for (int weight = 0; weight <= max_weight; weight++)
        {
            // base case where no money can be made, 
            // where no item is chosen
            // carrying capacity of bag is 0
            if (item == 0 || weight == 0)
            {
                //cout << "Assigning [" << item << "," << weight << "] : 0" << endl;
                optimal_table[item][weight] = 0;
            }

            // if item fits in bag
            else if (container[item-1].weight <= weight)
            {
                // add v_sub_i, subtract w_sub_i
                value_with_item = container[item-1].value + optimal_table[item-1][weight - container[item-1].weight];
                value_without_item = optimal_table[item-1][weight];

                //assign bigger of the two values
                if (value_with_item > value_without_item)
                {
                    //cout << "Assigning [" << item << "," << weight << "] : " << value_with_item << " (value including item #" << item-1 << ")" << endl;
                    optimal_table[item][weight] = value_with_item; 
                }
                else
                {
                    //cout << "Assigning [" << item << "," << weight << "] : " << value_without_item << " (value excluding item #" << item-1 << ")" << endl;
                    optimal_table[item][weight] = value_without_item;
                }

            }

            // just use previous value
            else
            {
                //cout << "Assigning [" << item << "," << weight << "] : " << optimal_table[item-1][weight] << " (because item #" << item-1 << " won't fit)" << endl;
                optimal_table[item][weight] = optimal_table[item-1][weight];
            }
        }
    }

    return optimal_table[num_of_items][max_weight];

}

void readFile(string filename, vector<item>& container, int & container_capacity, int & num_of_items)
{ 
    ifstream inFile;
    inFile.open(filename.c_str());

    int weight;
    int value;

    if (!inFile.fail())
    {

        inFile >> container_capacity;
        inFile >> num_of_items;

        item tmp = item();

        while (!inFile.eof())
        {
            inFile >> value;
            inFile >> weight;

            insert_item_into(container,weight,value);
        }
    }

    inFile.close();
}

//======================Resources=======================

// show problem has 2 properties: pg 424 & 425
// pg 369 for algorithm

// BOTTOM_UP_CUT_ROD(p,n), where p is price table and n is max size pg 366
// let r[0...n] be a new array        result array for saving subprobs
// r[0] = 0
// for j = 1 to n
//     q = -inf
//     for i = 1 to j
//         q = max(q, p[i] + r[j-i])
//     r[j] = q
// return r[n]
