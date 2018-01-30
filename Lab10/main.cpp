//Write a function that takes a binary search tree as input and produces a linked list
//of the entries, with the entries sorted (smallest entries at the front of the list and
//largest entries at the back). Hint: use in-order traversal

#include <iostream>
#include <list>
#include "bintree.h"

using namespace std;
using namespace main_savitch_10;

template<class Item>
list<Item> l;

template<class Item>
void pushback(binary_tree_node<Item>* n)
{
    l<Item>.push_back(n->data());
}
//Postcondition: Inorder travesal the binary search tree and push each elements to the back of the linked list

int main()
{
    //Build the binary tree
    binary_tree_node<int>* nr1=new binary_tree_node<int>(45); 
    binary_tree_node<int>* nl1=new binary_tree_node<int>(25);
    binary_tree_node<int>* nl=new binary_tree_node<int>(30,nl1);
    binary_tree_node<int>* nr=new binary_tree_node<int>(50,nr1);
    binary_tree_node<int>* n=new binary_tree_node<int>(40,nl,nr);
    binary_tree_node<int>* nl2=new binary_tree_node<int>(35);
    binary_tree_node<int>* nr2=new binary_tree_node<int>(60);
    nl->set_right(nl2);
    nr->set_right(nr2);
    //Print the binary tree
    print(n,0);
    //Sort the binary tree
    inorder(pushback<int>,n);
    //Print the sorted binary tree
    cout<<"Sorted Entries: ";
	for(list<int>::const_iterator i = l<int>.begin(); i != l<int>.end(); ++i)
		cout << *i << " ";
	cout << endl;
    return 0;
}