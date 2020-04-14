#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct item
{
    int weight;
    int value;
};

const int max_weight = 5;
void insert_item_into(vector<item>& container, int weight, int value);
int optimal_knapsack(vector<item>& container, int max_weight, int num_of_items);
void print_contents_of(vector<item> container);
void print_item(item);

int main()
{
    vector<int> v = {12, 10, 20, 15};
    vector<int> w = {2, 1, 3, 2};

    vector<item> inventory;
    int num_of_items = v.size();

    for (int i = 0; i < v.size(); i++)
    {
        insert_item_into(inventory,w[i],v[i]);
    }

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
    item tmp = item();
    tmp.weight = weight;
    tmp.value = value;
    container.push_back(tmp);
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
    int solution_table[num_of_items+1][max_weight+1];

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
                solution_table[item][weight] = 0;
            }

            // if item fits in bag
            else if (container[item-1].weight <= weight)
            {
                // add v_sub_i, subtract w_sub_i
                value_with_item = container[item-1].value + optimal_table[item-1][weight - container[item-1].weight];
                value_without_item = optimal_table[item-1][weight];

                if (value_with_item > value_without_item)
                {
                    //cout << "Assigning [" << item << "," << weight << "] : " << value_with_item << " (value including item #" << item-1 << ")" << endl;
                    optimal_table[item][weight] = value_with_item;
                    solution_table[item][weight] = container[item-1].weight;
                }
                else
                {
                    //cout << "Assigning [" << item << "," << weight << "] : " << value_without_item << " (value excluding item #" << item-1 << ")" << endl;
                    optimal_table[item][weight] = value_without_item;
                    solution_table[item][weight] = 0;
                }

            }

            // if item doesnt fit in bag, just use previous value
            else
            {
                //cout << "Assigning [" << item << "," << weight << "] : " << optimal_table[item-1][weight] << " (because item #" << item-1 << " won't fit)" << endl;
                optimal_table[item][weight] = optimal_table[item-1][weight];
                solution_table[item][weight] = 0;
            }
        }
    }


    // print solution
    int sol_weight = max_weight;
    int sol_item = num_of_items;
    while (sol_weight > 0 && sol_item > 0)
    {
        if (solution_table[sol_item][sol_weight] > 0)
            cout << "Took item " << sol_item - 1 << endl;

        sol_weight = sol_weight - solution_table[sol_item][sol_weight];
        sol_item--;
    }
    
    // Print optimal value table
    for (int row=num_of_items; row >= 0; row--){
        for (int col=0; col <= max_weight; col++)
        {
            cout << optimal_table[row][col] << '\t';
        }
        cout << endl;
    }
    //    cout << " === " << endl;
    // /* Print item weight table */
    // for (int row=num_of_items; row >= 0; row--){
    //     for (int col=0; col <= max_weight; col++)
    //     {
    //         cout << solution_table[row][col] << '\t';
    //     }
    //     cout << endl;
    // }

    cout << endl;

    return optimal_table[num_of_items][max_weight];

}
