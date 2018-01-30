#include <iostream>
#include <list>
#include "bintree.h"

using namespace std;
using namespace main_savitch_10;

template<class Item>
void printbf(binary_tree_node<Item>* node_ptr)
{
    cout<<node_ptr->data()<<" ";
}
int sum=0;//Global accumulator
template<class Item>
void sumoftree(binary_tree_node<Item>* node_ptr)
{
    sum+=node_ptr->data();
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
    nl->set_right(nl2);
    nr->set_right(nr2);
    queue<int> q;
    //Print the binary tree
    print(n,0);
    //Traverse the binary tree breadthfirstly
    cout<<"Breadthfirst Traversal: ";
    breadthfirst(printbf<int>,n);
    cout<<endl;
    //Calculate the sum of binary tree
    breadthfirst(sumoftree<int>,n);
    cout<<"Sum of the binary tree: "<<sum<<endl;
    return 0;
}