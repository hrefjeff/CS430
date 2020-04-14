/*
This file is just a scratch pad really. Copy and paste into
https://www.onlinegdb.com/online_c++_compiler 
and just get to coding. (ctrl+l jump to line number)
*/

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

void insert_item_into(vector<item>& container, int weight, int value);
void readFile( string filename,  
               vector<item> & container
             );

int main ()
{
  vector <item> inventory;
  
  readFile("input.txt", inventory);

  for (int i = 0; i < inventory.size (); i++)
    cout << inventory[i].value << " ";

  return 0;
}

void insert_item_into(vector<item>& container, int weight, int value)
{
    item tmp = item();
    tmp.weight = weight;
    tmp.value = value;

    container.push_back(tmp);
}

void readFile(string filename, vector<item>& container) 
{  

    ifstream inFile; 
    inFile.open(filename.c_str()); 

    int weight; 
    int value; 

    if (!inFile.fail()) 
    { 
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
