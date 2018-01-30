//The goal of this assignment is to reinforce the tree data structure in C++. Specifically, the assignment is to do the following:
//Binary search trees have their best performance when they are balanced, which means that at each node, n, the height of the left 
//subtree of n is within one of the height of the right subtree of n.  Write a function (and a test program) which takes a sorted 
//list of entries and produces a balanced binary search tree.
#include <iostream>
#include "bintree.h"
#include <list>
#include <vector>

using namespace std;
using namespace main_savitch_10;

template<class Item>
binary_tree_node<Item>* balancetree(vector<Item>& v, int begin, int end)
{
    if (begin>end)
      return NULL;//Base case: Nothing is returned when begin is greater than end
 
    int mid = (begin + end)/2;//Consider all middle elements to be roots
    
    binary_tree_node<Item>* r = new binary_tree_node<Item>(v[mid]);//Create the middle roots
 
    r->set_left(balancetree(v, begin, mid-1));//Recursively create the left root, use mid-1 to avoid the left sub-tree repeat the same element
 
    r->set_right(balancetree(v, mid+1, end));//Recursively create the right root, use mid+1 to avoid the right sub-tree repeat the same element
 
    return r;   //Return the root
}
template<class Item>
vector<Item> ListToVector(list<Item>& l)
{
    vector<Item> v;
    for(typename list<Item>::const_iterator i = l.begin(); i != l.end(); ++i)
        v.push_back(*i);
    return v;
}
template<class Item>
void printlist(list<Item>& l)
{
    cout<<"The sorted list: ";
	for(typename list<Item>::const_iterator i = l.begin(); i != l.end(); ++i)
		cout << *i << " ";
	cout << endl;
}
int main()
{
    list<int> mylist;
    int n=10;          //Enter how many items in your desired binary tree
    for(int i=0;i<n;i++)
        mylist.push_back(i);
    printlist(mylist);                 //Print your items in a sorted list
    vector<int> myvector=ListToVector(mylist);        //Convert a list to a vector
    binary_tree_node<int>* mybalancetree=balancetree(myvector,0,myvector.size()-1);  //Convert a vector to a balanced binary tree
    cout<<"This is the balanced binary search tree"<<endl;
    print(mybalancetree,0);            //Print the balanced tree
    return 0;
}