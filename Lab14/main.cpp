#include<iostream>
#include<list>
#include<math.h>

using namespace std;

void printlist(list<unsigned> l)
{
    for(list<unsigned>::const_iterator it=l.begin();it!=l.end();it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
}

void radixsort(list<unsigned> &original)
{
    list<unsigned int> list0;//Provide two lists to store values
    list<unsigned int> list1;
    const int MAX_ITERATIONS=sizeof(unsigned int)*8;
    for(unsigned int i=0,divisor=1;i<MAX_ITERATIONS;i++,divisor=divisor*2)//Loop until list1 is empty or exceed the maximum iteration
    {
        for(list<unsigned int>::const_iterator it=original.begin();it!=original.end();it++)//Loop the original list
            {
                if((*it/divisor)%2==0)//Put appropriate values into list0 or list1
                    list0.push_back(*it);
                else
                    list1.push_back(*it);
            }
        original.clear();
        if(list1.empty())//When we find all values are less than the divisor, end the loop
            i=MAX_ITERATIONS;
        original.splice(original.begin(),list1);//Reconstruct the original list, list0 followed by list1
        original.splice(original.begin(),list0);
    }
}

//Postcondition: the integer list is sorted

int main()
{
    list<unsigned int> original;
    unsigned int myints[]={77,51,17,22,98,39,45,80,69,6};
    original.assign(myints,myints+10);
    
    cout<<"Original unsorted list: ";
    printlist(original);
    
    radixsort(original);
    
    cout<<"Sorted list: ";
    printlist(original);
    return 0; 
}