#include <algorithm>
#include <cassert>
#include "set.h"
using namespace std;

//Precondition: initial_capacity should be greater than 0
set::set(size_type initial_capacity)
{
    assert(initial_capacity>0);
    data = new value_type[initial_capacity];
    capacity=initial_capacity;
    used=0;
}
//Postcondition: The set is intialized as an empty set with initial capacity
//Efficiency: O(1)
set::set(const set& source)
{
    if(this!=&source)
    {
        capacity=source.capacity;
        used=source.used;
        data=new value_type[capacity];
        copy(source.data, source.data+used, data);
    }
}
//Postcondition: the copy constructor for the set is created, if you are copying the same sequence, nothing happens
//Efficiency:O(n)
//Since the copy() function needs to complete n steps, so the efficiency is O(n).
set::~set()
{
    delete [ ] data;
}
//Postcondition: A destructor for the set is executed whenever an object of it's class goes out of scope or whenever the delete
//               expression is applied to a pointer to the object of that class.
//               The insert/attach functions will work efficiently (without allocating
//               new memory) until this capacity is reached.
//Efficiency:O(1)
//Precondition: new_capacity should be greater than 0
void set::resize(size_type new_capacity)
{
    assert(new_capacity>0);
    value_type* larger_set;
    if(capacity==new_capacity)
        return;
    if(new_capacity<used)
        new_capacity=used;
    larger_set=new value_type[new_capacity];
    copy(data,data+used,larger_set);
    delete[] data;
    data=larger_set;
    capacity=new_capacity;
}
//Postcondition: The sequence's current capacity is changed to the 
//               new_capacity (but not less that the number of items already on the
//               list). The insert/attach functions will work efficiently (without
//               allocating new memory) until this new capacity is reached.
//Efficiency:O(n)
//Since the copy() function needs to complete n steps, so the efficiency is O(n).
void set::insert(const value_type& entry)
{
    if(capacity<used)
        resize(used+1);
    if(check(entry))
        return;
    data[used]=entry;
    used++;
}
//Postcondition: A new copy of entry has been inserted into the set when the set does 
//               not contain this element. Now the newly element is the current element
//               of the set
//Efficiency: O(n) 
//Since there are a check() function and a resize() function in insert() function, so there is "n=2*used" steps to 
//be completed. The efficiency is O(n). 
void set::remove(const value_type& target)
{
    if(!check(target))
        return;
    size_type index=used;
    while(data[index]!=target)
        --index;
    for(size_type i=index;i<used;i++)
        data[i]=data[i+1];
    --used;
}
//Postcondition: The target is removed from the set if the set contains this element. If 
//               there is no same element as the target, nothing happens. Now this target
//               no longer exist in the set
//Efficiency: O(n)
//Since the function has to find the target in "n=used" steps in worst case and the function
//has to deallocate those data "n=used" steps in worst case, so there are 2n steps to be 
//completed. The efficiency is O(n)
bool set::check(const value_type& target)
{
    size_type index=0;
    while(index<used)
    {
        if(data[index]==target)
            return true;
        else
            index++;
    }
    return false;
}
//Postcondition: If the set contains this element, return true. If not, return false.
//Efficiency: O(n)
//Since the function need to complete "n=used" step in worst case, so the efficiency is O(n)
set::size_type set::count() const
{
    return used;
}
//Postcondition: The number of elements is returned
//Efficiency: O(1)
void set::operator +=(const set& addend)
{
    if(used+addend.used>capacity)
        resize(used+addend.used);
    for(size_type i=0;i<addend.used;i++)
        insert(addend.data[i]);
}
//Postcondition: The current set will add the elements in the addend set. If the
//               capacity for the current set is less than total elements for these
//               two sets, the set will resize to larger capacity
//Efficiency:O(n^2)
//Since the function has resize() function including copy() function, which is O(n).
//And there is "n=addend.used" steps to be completed, and in each step the function 
//includes insert() function, which is O(n) due to checking if those elements exist,
//so there are n+n*n steps. Therefore, the efficiency is O(n^2) 
void set::operator -=(const set& addend)
{
    for(size_type i=0;i<addend.used;i++)
        remove(addend.data[i]);
}
//Postcondition: The set will remove elements in the addend set if they exist currently
//Efficiency:O(n^2)
//Since the function has "n=addend.used" steps to complete, in each step the function needs 
//to complete remove() function, which is "n=2*used" steps in worst case. So there are n*2n
//steps to complete in worst case. Therefore, the efficiency is O(n^2)
set set::operator ^(const set& addend)//This is an intersection function
{
    set answer;
    for(size_type i=0;i<addend.used;i++)
            if(check(addend.data[i]))
                answer.insert(addend.data[i]);
    return answer;
}
//Postcondition: The set with insertion elements of both sets is returned
//Efficiency:O(n^2)
//Since the function has to complete "n=addend.used" steps, in each steps the function needs
//to complete insert() function, which is "n=used" steps in worst case as well due to checking
//if those elements exist, so there are n*n steps. Therefore, the efficiency is O(n^2)
void set::operator =(const set& source)
{
    // Check for possible self-assignment:
    if (this == &source)
        return;
    value_type *new_data=new value_type[source.capacity];
    // Copy the data from the source array:
    copy(source.data, source.data+source.used, new_data);
	// If needed, allocate an array with a different size:
    delete [ ] data;
    data = new_data;
    used = source.used;
    capacity = source.capacity;
}
//Postcondition: The source set is assigned to current set, private properties such as data,
//               number of item, set capacity and set current index are assigned to the current 
//               set. If the source set is the same as the current set, nothing happens.
//Efficiency:O(n)
//As we can see, the copy() function needs to complete n steps, so the efficiency is O(n).
void set::display()
{
    for(size_type i=0;i<used;i++)
        cout<<data[i]<<" ";
    cout<<endl;
}
//Postcondition: The current set elements are displayed
//Efficiency:O(n)
//Since the function has "n=used" steps to be completed, so the efficiency is O(n).
set operator +(const set& s1, const set& s2)//This is an union function
{
    set answer;
    answer+=s1;
    answer+=s2;
    return answer;
}
//Postcondition: The set with uniting elements of two sets is returned
//Efficiency: O(n^2)
//This function includes two += functions, each one includes insert() function.
//Since there are two O(n^2) functions to be completed, so the efficiency is O(n^2).
set operator -(const set& s1, const set& s2)//This is a relative compliment function
{
    set answer;
    answer=s1;
    answer-=s2;
    return answer;
}
//Postcondition: The set with insertion elements of two sets is returned
//Efficiency: O(n^2)
//This function includes one = function, which has copy() function, and one -= function.
//Since there are one O(n) function and one O(n^2) function, so the efficiency is O(n^2)


//Reference from http://www.cplusplus.com/reference/algorithm/copy/
//template<class InputIterator, class OutputIterator> 
//  OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result)
//{
//  while (first!=last) {
//    *result = *first;
//    ++result; ++first;
//  }
//  return result;
//}