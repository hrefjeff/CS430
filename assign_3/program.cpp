#include <iostream>
#include <vector>
using namespace std;

struct item
{
    int weight;
    int value;
};

vector<item> inventory;
vector<item> bag;


void print_item(item);
void print_contents_of(vector<item> container);
void insert_item_into(vector<item>& container, int weight, int value);
void transfer_from_to(vector<item>& from_cont, vector<item>& to_cont);
//vector<item> optimize(vector<item>& container, int max_weight, int current_value);

int main()
{

    const int num_of_items = 3;
    const int max_weight = 50;

    // vector<int> columns(num_of_items, 0);
    // vector<vector<int> > rows(3,num_of_items);

    // for(int i=0;i<rows.size(); i++)
    // {
    //     for (int j=0;j<rows[i].size(); j++)
    //     {
    //         cout << rows[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // transfer_from_to(inventory,bag);

    // print_contents_of(inventory);
    // print_contents_of(bag);

    insert_item_into(inventory,1,60);
    insert_item_into(inventory,2,100);
    insert_item_into(inventory,3,120);

//    bag = optimize(inventory,50);
    
    print_contents_of(inventory);
    print_contents_of(bag);

    return 0;
}

void print_item(item x)
{
    cout << "(W: " << x.weight << ", V: " << x.value << ")" << endl;
}

void print_contents_of(vector<item> container)
{
    for (int i = 0; i < container.size(); i++)
    {
        print_item(container[i]);
    }
}

void insert_item_into(vector<item>& container, int weight, int value)
{
    container.push_back(item());
    container[container.size() - 1].weight = weight;
    container[container.size() - 1].value = value;
}

void transfer_from_to(vector<item>& from_cont, vector<item>& to_cont)
{
    item temp = from_cont[0];
    from_cont.erase(from_cont.begin());
    to_cont.push_back(temp);
}

// pg 369 for algorithm,
// show it has 2 properties: pg 424 & 425

// vector<item> optimize(vector<item>& container, int max_weight, int current_value)
// {
//     // choose item i from container

//     // subtract i weight from max

//     // add value i to current value

//     // remove i from container

//     // vector<item> bag = optimize(container, max_weight, current_value)


//     // compare bag to solution w/o item i
// }

// vector<item> find_max_value_for_weight(vector<item>& inventory, int max_weight, int num_of_items)
// {
    
// }