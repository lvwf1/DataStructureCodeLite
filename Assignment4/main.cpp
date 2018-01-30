// FILE: set_demo.cxx
// This is a small demonstration program showing how the set class is used.
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <iomanip>     // Provides setw function for setting output width
#include "set.h"      // With value_type defined as an int
using namespace std;

int main( )
{
    set s,s1,s2,s3;
    for(int i=0;i<10;i++)
        s1.insert(i);//Test insertion and resize
    for(int i=5;i<15;i++)
        s2.insert(i);
    for(int i=10;i<20;i++)
        s3.insert(i);
    cout<<"The elements of s1: ";
    s1.display();//Test display
    cout<<"The elements of s2: ";
    s2.display();
    cout<<"The elements of s3: ";
    s3.display();
    s3.insert(15);//Test insert existed values and check
    cout<<"The elements of s3: ";
    s3.display();
    s=s1+s2;//Test union and assignment operator
    cout<<"The union elements of s1 and s2: ";
    s.display();
    s=s1-s2;//Test relative compliment
    cout<<"The relative compliment elements of s1 and s2: ";
    s.display();
    cout<<"The insertion compliment elements of s1 and s2: ";
    s=s1^s2;//Test intersection
    s.display();
    s3.remove(1);//Test remove inexistent values
    s3.display();
    s3.remove(11);//Test remove existed values
    s3.display();
    set s4=s3;//Test the copy constructor
    cout<<"The number of element of s4: "<<s4.count()<<endl;//Test the count function
    s4.display();
	return 0;
}