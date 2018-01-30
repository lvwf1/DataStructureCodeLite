//Shell Sort
//The basis of the technique is to get the items to move in big steps (rather than 
//shifting elements to the next higher index). These big-step shifts are done early
//in the algorithm, and they tend to put the array in nearly sorted order. Later in
//the algorithm, we use smaller steps (all the way down to steps of size one, just 
//like an ordinary insertion sort). But by the time that the small steps are being 
//taken, the array is nearly sorted, and that's a situation where insertionsort is
//efficient. The choice of the various step sizes affects the performance of the 
//algorithm, but one sequence that is empirically good starts at n/2, and each 
//subsequent step size is about the previous size divided by 2.2.
//The overall pseudocode is given here
// ss=n/2
// while(ss>0)
// {
//   do an insertionsort on the elements data[0],data[ss],data[2*ss]
//   also do an insertionsort on data[1],data[ss+1],data[2*ss+1]..
//   and on data[2], data[ss+2], data[2*ss+2]..
//   The last little insertionsort that you do starts at data[ss-1].
//   ss=round ss/2.2 to nearest integet
// }
#include<iostream>
#include<array>
#include<algorithm>
#include<cmath>

using namespace std;

void printarr(int array[],int size)
{
    for(int i=0;i<size;i++)
        cout<<array[i]<<" ";
    cout<<endl;
}
//Postcondition: print the array

int round2p2(int n)
{
    if((n*10+11)/22>n/2.2)
        return n/2.2+1;
    else
        return n/2.2;
}
//Postcondition: return the nearest integer of n/2.2

void shellsort(int array[],int size)
{
    int ss=size/2;//Set the jump step
    while(ss>0)//shell sort is finished when jump step is 0
    {
        for(int i=ss;i<size;i++){                        //compare the values from the first jump step index till the end
            while (i >= ss  && array[i] < array[i-ss]){      //compare the current value with the value after the jump step
                //cout<<i<<" "<<i-ss<<endl;
                //cout<<array[i]<<" "<<array[i-ss]<<endl;
                swap(array[i],array[i-ss]);  //Swap the value if necessary
                i-=ss;  //Insertion sort: compare the value with all possible previous values until the jumping-front interval is sorted
                //printarr(array,10);
            }
        }
        //cout<<ss<<endl;
        ss=round2p2(ss); //diminish the jump step by dividing by 2.2
    }
}
int main()
{
    int array[10];//Initialize an array
    for(int i=0;i<10;i++)
    {
        array[i]=rand()%100;//Put random numbers into the array
    }
    cout<<"Unsorted array: ";
    printarr(array,10);//Display unsorted array
    shellsort(array,10);//Shell sort
    cout<<"Sorted array: ";
    printarr(array,10);//Display sorted array
    return 0;
}