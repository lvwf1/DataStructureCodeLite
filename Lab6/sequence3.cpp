// FILE: sequence3.h
// CLASS PROVIDED: sequence (part of the namespace main_savitch_5)
// This is the header file for the project described in Section 5.4
// of "Data Structures and Other Objects Using C++"
// This is called "sequence3" because some students already implemented
// sequence1 (with a fixed array) and sequence2 (with a dynamic array).
#include <iostream>     // Provides iostream
#include <cassert>      // Provides assert
#include <algorithm>    //
#include "sequence3.h"

using namespace std;
namespace main_savitch_5
{
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   typedef ____ size_type
//     sequence::size_type is the data type of any variable that keeps track of
//     how many items are in a sequence.
//
// CONSTRUCTOR for the sequence class:
//   sequence( )
     
    sequence::sequence()
    {
        head_ptr=NULL;
        tail_ptr=NULL;
        cursor=NULL;
        precursor=NULL;
        many_nodes=0;
    }
//     Postcondition: The sequence has been initialized as an empty sequence.
//
    sequence::sequence(const sequence& source)
    {
        if(source.size()==0||source.cursor==source.head_ptr)//The source sequence only has zero or one element
        {
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            start();//Precursor should be null anyway, Cursor will be null if there is no element
        }
        else //The source sequence has two or above elements
        {
            list_copy(source.head_ptr,head_ptr,tail_ptr);
            cursor=source.cursor;
            precursor=source.precursor;//Copy the cursor and precursor
        }
        many_nodes=source.many_nodes;//Copy the number of elements
    }
    
    void sequence::operator =(const sequence& source)
    {
        if(this==&source)//Take care of self-assignment
            return;
        if(source.size()==0||source.cursor==source.head_ptr)//The source sequence only has zero or one element
        {
            list_copy(source.head_ptr,head_ptr,tail_ptr);
            start();//Precursor should be null anyway, Cursor will be null if there is no element
        }
        else //The source sequence has two or above elements
        {
            list_copy(source.head_ptr,head_ptr,tail_ptr);
            cursor=source.cursor;
            precursor=source.precursor;//Copy the cursor and precursor
        }
        many_nodes=source.many_nodes;//Copy the number of elements
    }
    
    sequence::~sequence()
    {
        list_clear(head_ptr);//Remove the whole list
        many_nodes=0;//Set the number of elements to 0
    }
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void start( )
    void sequence::start()
    {
        if(head_ptr==NULL)//Nothing in the list
        {
            cursor=NULL;
            precursor=NULL;
        }
        else//Cursor moves to the front
        {
            cursor=head_ptr;
            precursor=NULL;
        }
    }
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//
//   void advance( )
//     Precondition: is_item returns true.
    void sequence::advance()
    {
        assert(is_item());
        precursor=cursor;
        cursor=cursor->link();
    }
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
//   void insert(const value_type& entry)
    void sequence::insert(const value_type& entry)
    {
        if(precursor==NULL&&cursor==NULL)//Nothing in the list
        {
            list_head_insert(head_ptr,entry);
            cursor=head_ptr;
            precursor=NULL;
            tail_ptr=head_ptr;//Insert to the front
        }
        else if(precursor==NULL||cursor==NULL)//Cursor is at the front or (maybe and) at the end of the list
        {
            list_head_insert(head_ptr,entry);
            precursor=NULL;
            cursor=head_ptr;//Insert to the front
        }
        else//Cursor is at the middle of the list
        {
            list_insert(precursor,entry);
            cursor=precursor->link();//Insert before the current item
        }
        ++many_nodes;//increment the number of elements
    }
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void attach(const value_type& entry)
    void sequence::attach(const value_type& entry)
    {
        if(precursor==NULL&&cursor==NULL)//Nothing in the list
        {
            list_head_insert(head_ptr,entry);
            cursor=head_ptr;
            precursor=NULL;
            tail_ptr=head_ptr;//Insert to the front(end)
        }
        else if(cursor==tail_ptr||precursor==tail_ptr)//Cursor is at the end of the list
        {
            list_insert(tail_ptr,entry);
            precursor=tail_ptr;
            tail_ptr=tail_ptr->link();
            cursor=tail_ptr;//Insert to the end
        }
        else//Cursor is at the middle of the list
        {
            list_insert(cursor,entry);
            precursor=cursor;
            cursor=cursor->link();//Insert after the current item
        }
        ++many_nodes;//increment the number of elements
    }
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void remove_current( )
//     Precondition: is_item returns true.
    void sequence::remove_current()
    {
        assert(is_item());
        if(cursor==head_ptr)//Cursor is at the front or there is only one element
        {
            list_head_remove(head_ptr);
            cursor=cursor->link();//Remove the front element
        }
        else//Cursor is at the middle of the list
        {
            cursor=cursor->link();
            list_remove(precursor);//Remove the middle element
        }
        --many_nodes;//decrement the number of elements
    }
//     Postcondition: The current item has been removed from the sequence, and
//     the item after this (if there is one) is now the new current item.
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   size_type size( ) const
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
    sequence::value_type sequence::current() const
    {
        return cursor->data();
    }
//     Postcondition: The item returned is the current item in the sequence.
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
}