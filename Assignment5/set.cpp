#include <algorithm>
#include <cassert>
#include "set.h"
#include "node1.h"
using namespace std;

//Precondition: initial_capacity should be greater than 0
namespace main_savitch_5
{
    set::set()
    {
        head_ptr=NULL;
        tail_ptr=NULL;
        cursor=NULL;
        many_nodes=0;
    }
//Postcondition: The set is intialized as an empty set with initial capacity
//Efficiency: O(1)
    set::set(const set& source)
    {
        if(this!=&source)
        {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            many_nodes=source.many_nodes;
        }
    }
//Postcondition: the copy constructor for the set is created, if you are copying the same sequence, nothing happens
//Efficiency:O(n)
//Since the copy() function needs to complete n steps, so the efficiency is O(n).
    set::~set()
    {
        list_clear(head_ptr);//Remove the whole list
        many_nodes=0;//Set the number of elements to 0
    }
//Postcondition: A destructor for the set is executed whenever an object of it's class goes out of scope or whenever the delete
//               expression is applied to a pointer to the object of that class.
//               The insert/attach functions will work efficiently (without allocating
//               new memory) until this capacity is reached.
//Efficiency:O(n)
//Since node_clear takes n steps depending on how many head_ptrs they were removing, the whole list will be cleared
//after every elements become the head_ptrs, so it needs to complete n steps, the efficiency is O(n)
    void set::insert(const value_type& entry)
    {
        if(many_nodes==0)
        {
            list_head_insert(head_ptr,entry);
            tail_ptr=head_ptr;
            ++many_nodes;
        }
        if(!check(entry))
        {
            list_insert(tail_ptr,entry);
            tail_ptr=tail_ptr->link();
            ++many_nodes;
        }
    }
//Postcondition: A new copy of entry has been inserted into the set when the set does 
//               not contain this element. Now the newly element is the current element
//               of the set
//Efficiency: Worst: O(n) / Best: O(1)
//For the best case, since list_head_insert and list_insert efficiency is O(1), it will be O(1) if there is no node.
//If there are nodes, the function should call check function to verify if the element is already in the set, that
//will call list_search, which will loop through the whole list. The efficiency is O(n). So the efficiency for insert
//is O(n) for the worst case, O(1) for the best case.
    void set::remove(const value_type& target)
    {
        if(many_nodes==0)
            return;
        if(head_ptr->data()==target)
            list_head_remove(head_ptr);
        else if(check(target))
        {
            cursor=head_ptr;
            while(cursor->link()->data()!=target&&cursor->link()!=NULL)
                cursor=cursor->link();
            list_remove(cursor);
        }
        --many_nodes;
    }
//Postcondition: The target is removed from the set if the set contains this element. If 
//               there is no same element as the target, nothing happens. Now this target
//               no longer exist in the set
//Efficiency: O(n^2) Worst/O(1) Best
//First, we need to verify if the first element is target, if yes, remove it. This efficiency is O(1).
//Then, we need to call the check function to verify the element is already in the set, the
//check function will call list_search, whose efficiency is O(n). Next, we need to loop through the 
//set to locate the pointer pointing to precursor of target, then removing the target, its efficiency is O(n). 
//Therefore, the efficiency is O(n^2) for the worst case and O(1) for the best case.
    bool set::check(const value_type& target)
    {
        if(list_search(head_ptr,target)!=NULL)
            return true;
        else
            return false;
    }
//Postcondition: If the set contains this element, return true. If not, return false.
//Efficiency: O(n)
//Since the function will call list_search once, the efficiency for list_search is O(n).
//So the check function is O(n)
    set::size_type set::count() const
    {
        return many_nodes;
    }
//Postcondition: The number of elements is returned
//Efficiency: O(1)
    void set::operator +=(const set& addend)
    {
        if(many_nodes==0)
        {
            list_copy(addend.head_ptr, head_ptr, tail_ptr);
            many_nodes=addend.many_nodes;
        }
        else
        {
            for(cursor=addend.head_ptr;cursor!=NULL;cursor=cursor->link())
                insert(cursor->data());
        }
    }
//Postcondition: The current set will add the elements in the addend set. If the
//               capacity for the current set is less than total elements for these
//               two sets, the set will resize to larger capacity
//Efficiency:O(n^2) worst/ O(n) best
//For the best case, no node in the set, it needs to copy the addend set, whose efficiency
//is O(n). Then if there are some elements in the set already, the function will loop through
//the addend set and insert. This function will take n steps to insert n elements to the original
//set, the insert function's efficiency is O(n) for the worst case. So this function efficiency
//is O(n) for the best case and O(n^2) for the worst case. 
    void set::operator -=(const set& addend)
    {
        if(many_nodes==0&&addend.many_nodes==0)
            return;
        else
        {
            for(cursor=addend.head_ptr;cursor!=NULL;cursor=cursor->link())
                remove(cursor->data());
        }
    }
//Postcondition: The set will remove elements in the addend set if they exist currently
//Efficiency:O(n^3) Worst/O(1) Best
//For the best case, no element in the set, its efficiency is O(1). Then if there are some 
//elements in the set already, the function will loop through the addend set and remove
//all elements existed in the addend set, whose efficiency is O(n). Next, the remove 
//function efficiency is O(n^2) or O(1). Therefore, this function's efficiency is O(1)
//for the best case and O(n^3) for the worst case.
    set set::operator ^(const set& addend)//This is an intersection function
    {
        set answer;
        if(many_nodes!=0&&addend.many_nodes!=0){
            for(cursor=addend.head_ptr;cursor!=NULL;cursor=cursor->link())
                if(check(cursor->data()))
                    answer.insert(cursor->data());
        }
        return answer;
    }
//Postcondition: The set with insertion elements of both sets is returned
//Efficiency: O(n^3) Worst/O(1) Best/ O(n^2) Achievable
//Since the function needs to loop through the addend set, its efficiency is O(n).
//Then the function checks if the current set contains the addend set's elements, 
//its efficiency is O(n). Next, the function inserts those common elements into the 
//answer set, this step causes double check. Those elements should be sole so there is 
//no need to double check. Currently, our function needs to take O(n), but O(1) can be
//achieved. Therefore, the function's efficiency is O(1) for the best case, and O(n^3) 
//for the worst case, but O(n^2) is achievable
    void set::operator =(const set& source)
    {
        if(this==&source)
            return;
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        cursor=tail_ptr;
        many_nodes=source.many_nodes;
    }
//Postcondition: The source set is assigned to current set, private properties such as data,
//               number of item, set capacity and set current index are assigned to the current 
//               set. If the source set is the same as the current set, nothing happens.
//Efficiency:O(n)
//As we can see, the copy() function needs to complete n steps, so the efficiency is O(n).
    void set::display()
    {
        for(node *p=head_ptr;p!=NULL;p=p->link())
            cout<<p->data()<<" ";
        cout<<endl;
    }
//Postcondition: The current set elements are displayed
//Efficiency:O(n)
//Since the function has many_nodes steps to be completed, so the efficiency is O(n).
    set operator +(const set& s1, const set& s2)//This is an union function
    {
        set answer;
        answer+=s1;
        answer+=s2;
        return answer;
    }
//Postcondition: The set with uniting elements of two sets is returned
//Efficiency: O(n^2) Worst/O(n) Best
//This function includes two += functions, each one includes insert() function.
//Since there are two O(n^2) functions to be completed, so the efficiency is O(n^2) for
//the worst case and O(n) for the best case.
    set operator -(const set& s1, const set& s2)//This is a relative compliment function
    {
        set answer;
        answer=s1;
        answer-=s2;
        return answer;
    }
}
//Postcondition: The set with insertion elements of two sets is returned
//Efficiency: O(n^3) Worst/O(n) Best
//This function includes one = function, which has copy() function, and one -= function.
//Since there are one O(n) function and one O(n^3) function, so the efficiency is O(n^3)
//for the worst case and O(n) for the best case


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