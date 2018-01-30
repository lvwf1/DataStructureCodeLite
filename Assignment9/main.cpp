//The goal of this assignment is to reinforce the tree data structure in C++. Specifically, the assignment is to do the following:
//Construct a function that will display a binary tree by levels (each level on a separate line).  
//If there is no node at a position in a level, then the function should display NULL.  
//Only levels that contain at least 1 datum should be displayed.
#include <iostream>
#include "bintree.h"

using namespace std;
using namespace main_savitch_10;

template<class Item>
void printlevel(binary_tree_node<Item>* node)
{
    if(node->data())
        cout<<node->data()<<" ";
    else
        cout<<"NULL"<<" ";
}

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
    binary_tree_node<int>* nr3=new binary_tree_node<int>(80);
    binary_tree_node<int>* nl3=new binary_tree_node<int>(20);
    binary_tree_node<int>* nr4=new binary_tree_node<int>(75);
    nl->set_right(nl2);
    nl1->set_left(nl3);
    nr->set_right(nr2);
    nr2->set_left(nr3);
    nr3->set_left(nr4);
    //Print the binary tree
    print(n,0);
    breadthfirst(printlevel<int>,n);
}