#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

struct item
{
    int weight;
    int value;
    bool operator<(const item& rhs) const
    {
        return weight > rhs.weight;
    }
};

unordered_map<int,int> solution_map;


void readFile(string filename, priority_queue<item>& container, int & num_of_items, int & container_capacity);

void print_item(item);
void print_contents_of(priority_queue<item>);
void insert_item_into(priority_queue<item>&, int, int);
void transfer_from_to(priority_queue<item>&, priority_queue<item>&);
int optimize(int, priority_queue<item>&);
//void optimize(int, int, priority_queue<item>&,priority_queue<item>&);

int main()
{

    priority_queue<item> inventory;
    priority_queue<item> bag;
    int num_of_items;
    int max_weight;

    //=============Begin File Read Stuff=====================
    fstream file;
    string filename;
    bool badFile = true;

    do {

        cout << "Input file name: ";
        //cin >> filename;
        filename = "input.txt";
        
        file.open(filename);
        badFile = file.fail();
        file.close();

    } while (badFile);

    readFile(filename,inventory,num_of_items,max_weight);
    //=============End File Read Stuff=======================

    cout << endl;

    print_contents_of(inventory);


    int result = optimize(max_weight,inventory);


    cout << "Number of Items : " << num_of_items << endl;
    cout << "Bag Capacity    : " << max_weight << endl;
    cout << "Max value      : " << result << endl;



    // for (int i = 0; i < result.size(); i++)
    //     cout << "Max revenue at weight: " << i << " is " << result[i] << " " << endl;


    //optimize(max_weight, current_val, inventory, bag);

    
    //print_contents_of(bag);

    return 0;
}


void print_item(item x)
{
    cout << "(W: " << x.weight << ", V: " << x.value << ")" << endl;
}

void print_contents_of(priority_queue<item> container)
{
    while (!container.empty())
    {
        cout 
            << "(W: " 
                << container.top().weight
            << ", V: " 
                << container.top().value
            << ")" << endl;
        container.pop();
    }
}

void insert_item_into(priority_queue<item>& container, int weight, int value)
{
    item tmp = item();
    tmp.weight = weight;
    tmp.value = value;
    container.push(tmp);
}

void transfer_from_to(priority_queue<item>& from_cont, priority_queue<item>& to_cont)
{
    to_cont.push(from_cont.top());
    from_cont.pop();
}

// BOTTOM_UP_CUT_ROD(p,n), where p is price table and n is max size pg 366
// let r[0...n] be a new array        result array for saving subprobs
// r[0] = 0
// for j = 1 to n
//     q = -inf
//     for i = 1 to j
//         q = max(q, p[i] + r[j-i])
//     r[j] = q
// return r[n]


// pg 369 for algorithm
// records value AND choices that led to it
// let r[0...n] and s[0...n] be new arrays
// EXTENDED_BOTTOM_UP_CUT_ROD(p,n), where p is price table, and a rod size n
// r[0] = 0
// for j = 1 to n                       for each rod size
//     q = -inf                         compute revenue and size of first cut
//     for i = 1 to j
//         if q < p[i] + r[j - i]
//             q = p[i] + r[j-1]
//             s[j] = i
//      r[j] = q
// return r and s


// show it has 2 properties: pg 424 & 425
// shoud take in inventory table, and capacity
int optimize(int max_weight, priority_queue<item>& container)
{
    vector<int> result_array;
    result_array.resize(max_weight);
    int bag_weight = 0;
    int bag_val = 0;
    
    result_array[0] = 0;    // 0 weight gets 0 dollars

    // in order of increasing weight
    // for each weight compute max revenue
    // then save to resultant array
    for (int curr_weight = 1; curr_weight < max_weight; curr_weight++)
    {               
        bag_val = 0;

        for (int i = 1; i < curr_weight; i++)
        {
            if ((bag_weight + container.top().weight) < i)
            {
                // take max
                // if current bag val is less,
                // add container[i] + result_array[curr_weight-i]
                if (bag_val < (container.top().value + result_array[curr_weight - i]))
                {
                    
                    cout << endl;
                    cout << "(W: " << container.top().weight << ", V: " << container.top().value << ")" << endl;
                    cout << endl;

                    bag_val = container.top().value + result_array[curr_weight - i];
                    bag_weight += container.top().weight;
                    container.pop();
                } 
                else 
                {
                    bag_val = result_array[curr_weight - i];
                }
            }
           
        }

        result_array[curr_weight] = bag_val;

        cout << "Weight " << curr_weight << " value:" << result_array[curr_weight] << endl;
    }

        

    return result_array[max_weight-1];

    // // if solved for this weight, use best solution
    // if ()
    // {


    // // 
    // } else {

    //     // Keep going if the container isn't empty
    //     // and
    //     // Keep going if the item at top of container can fit into bag
    //     while ((!container.empty()) && (container.top().weight < max_weight))
    //     {
    //         // choose item i from container
    //         transfer_from_to(container,loot_bag);
            
    //         // subtract i weight from max
    //         max_weight = max_weight - loot_bag.top().weight;
            
    //         // add value i to current value
    //         current_value = current_value + loot_bag.top().value;

    //         // subprob(n-1)
    //         optimize(max_weight, current_value, container, loot_bag);

    //     }
    // }

    // // compare bag to solution w/o item i
    // if (current_value > )

    // return value;
}

void readFile (string filename, priority_queue<item>& container, int & num_of_items, int & container_capacity) { 

    ifstream inFile;
    inFile.open(filename.c_str());

    int name;
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

            tmp.value = value;
            tmp.weight = weight;

            container.push(tmp);
        }
    }

    inFile.close();
}
