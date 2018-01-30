//The goal of this assignment is to reinforce the B-tree data structure in C++. 
//Specifically, the assignment is to do problem 3 on page 582 of the text.  
//You will need a test program.  This assignment will be worth 50 points 
//but it will be graded on the basis of 200 points.  
//Thus, there are 150 "bonus points" possible.
//use a B tree to implement the set class from figure 11.5 on page 551. follow the programming tips from page 569-570.

#include <iostream>
#include "BTree.h"


using namespace std;

int main()
{
    BTree b(2);
    b.insert(30);
    b.insert(50);
    b.insert(10);
    b.insert(70);
    b.insert(90);
    b.insert(110);
    b.insert(130);
    b.insert(150);
    b.insert(170);
    b.traverse();
    return 0;
}