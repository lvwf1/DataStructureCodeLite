/*Write a multithreaded sorting program that works as follows: A list of integers
is divided into two smaller lists of equal size. Two separate threads (which we
will term sorting threads) sort each sublist using a sorting algorithm of your
choice. The two sublists are then merged by a third thread—a merging thread
—which merges the two sublists into a single sorted list.
Because global data are shared cross all threads, perhaps the easiest way
to set up the data is to create a global array. Each sorting thread will work on
one half of this array. A second global array of the same size as the unsorted
integer array will also be established. The merging thread will then merge
the two sublists into this second array. Graphically, this program is structured
according to Figure 4.20.
This programming project will require passing parameters to each of the
sorting threads. In particular, it will be necessary to identify the starting index
from which each thread is to begin sorting. Refer to the instructions in Project
1 for details on passing parameters to a thread.
The parent thread will output the sorted array once all sorting threads have
exited.
*/

#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void merge(vector<int>& vec, unsigned int start, unsigned int mid, unsigned int end)
{
    vector<int> one (vec.begin() + start, vec.begin() + mid + 1);
    vector<int> two (vec.begin() + mid + 1, vec.begin() + end + 1);

    unsigned int a = 0;
    unsigned int b = 0;
    unsigned int index = start;
    while (a < one.size() && b < two.size())
    {
        if (one[a] < two[b])
            vec[index ++] = one[a ++];
        else 
            vec[index ++] = two[b ++];
    }

    // merge the left-over elements
    while (a < one.size())
        vec[index ++] = one[a ++];
    while (b < two.size())
        vec[index ++] = two[b ++];
}

void merge_sort(vector<int>& vec, unsigned int start, unsigned int end)
{
if (start >= end)
    return;

unsigned int mid = start + (end - start) / 2;

// multi-thread version
thread first(merge_sort, std::ref(vec), start, mid);
thread second(merge_sort, std::ref(vec), mid + 1, end);
first.join();
second.join();

/*
// single-thread version, testified.
//merge_sort(vec, start, mid);
//merge_sort(vec, mid + 1, end); 
*/

merge(vec, start, mid, end);
}


int main()
{
    int a[] = {4, 2, 5, 9, 7, 1, 3, 6, 10, 19, 20, 15, 18, 13, 12, 11, 17, 16, 8, 14};
    vector<int> vec(a, a + 20);
    merge_sort(vec, 0, 19);
    for (int i = 0; i < 20; i ++)
        cout << vec[i] << " ";
    cout<<endl;
    return 0;
}