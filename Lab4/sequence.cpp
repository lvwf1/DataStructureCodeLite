// FILE: sequence2.h
// CLASS PROVIDED: sequence (part of the namespace main_savitch_4)
// There is no implementation file provided for this class since it is
// an exercise from Chapter 4 of "Data Structures and Other Objects Using C++"
#include <iostream>     // Provides cout.
#include <algorithm>    // Provides copy function
#include <cassert>      // Provides assert
#include "sequence2.h"  // Provides the sequence class with double items.
using namespace std;
namespace main_savitch_4
{
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   typedef ____ size_type
//     sequence::size_type is the data type of any variable that keeps track of
//     how many items are in a sequence.
//   static const size_type DEFAULT_CAPACITY = _____
//     sequence::DEFAULT_CAPACITY is the initial capacity of a sequence that is
//     created by the default constructor.
        const sequence::size_type sequence::DEFAULT_CAPACITY;
// CONSTRUCTOR for the sequence class:
//   sequence(size_t initial_capacity = DEFAULT_CAPACITY)
    sequence::sequence(size_type initial_capacity)
    {
        data=new value_type[initial_capacity];
        capacity=initial_capacity;
        used=0;
    }
//     Postcondition: The sequence has been initialized as an empty sequence.
    sequence::sequence(const sequence& source)
    {
        if(this!=&source)
            {
                capacity=source.capacity;
                used=source.used;
                data=new value_type[capacity];
                copy(source.data, source.data+used, data);
                current_index=source.current_index;
            }
    }
//     Postcondition: the copy constructor for the sequence is created, if you are copying the same sequence, nothing happens
    sequence::~sequence()
    {
        delete [ ] data;
    }
//     Postcondition: A destructor is executed whenever an object of it's class goes out of scope or whenever the delete
//                    expression is applied to a pointer to the object of that class.
//     The insert/attach functions will work efficiently (without allocating
//     new memory) until this capacity is reached.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void resize(size_type new_capacity)
    void sequence::resize(size_type new_capacity)
    {
        if(new_capacity > used) 
        {
			value_type *new_data = new value_type [new_capacity];
			copy(data, data+used, new_data);
			delete [] data;
			data = new_data;
			capacity = new_capacity;
		}
    }
//     Postcondition: The sequence's current capacity is changed to the 
//     new_capacity (but not less that the number of items already on the
//     list). The insert/attach functions will work efficiently (without
//     allocating new memory) until this new capacity is reached.
//
//   void start( )
    void sequence::start()
    {
        current_index= 0;
    }
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//
//   void advance( )
//     Precondition: is_item returns true.
    void sequence::advance()
    {
        assert(is_item());
        current_index++;
    }
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
//   void insert(const value_type& entry)
    void sequence::insert(const value_type& entry)
    {
        if( size() == capacity ) 
			resize(capacity+DEFAULT_CAPACITY);
        if (!is_item())
            current_index=0;
        for(size_type i=used;i>current_index;i--)
                data[i]=data[i-1];
        data[current_index]=entry;
        used++;
    }
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void attach(const value_type& entry)
    void sequence::attach(const value_type& entry)
    {
        if( size() == capacity )
			resize(capacity+DEFAULT_CAPACITY);
        if(!is_item()) 
            current_index = used-1;
        current_index++;
        for(size_type i=used;i>current_index;i--)
                data[i]=data[i-1];
        data[current_index]=entry;
        used++;
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
        for(size_type i=current_index;i<used;i++)
            data[i]=data[i+1];
        used--;
    }
//     Postcondition: The current item has been removed from the sequence, and the
//     item after this (if there is one) is now the new current item.

    void sequence::operator =(const sequence& source)
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
        if(source.is_item())
			current_index = source.current_index;
		else
			current_index = used;
    }
//      Postcondition: The source sequence is assigned to current sequence, private properties such as data,
//      number of item, sequence capacity and sequence current index are assigned to the current sequence. 
//      If the source sequence is the same as the current sequence, nothing happens.
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   size_type size( ) const
    sequence::size_type sequence::size() const
    {
        return used;
    }
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool is_item( ) const
    bool sequence::is_item() const
    {
        return current_index<used;
    }
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
    sequence::value_type sequence::current() const
    {
        assert(is_item());
        return data[current_index];
    }
}
//     Postcondition: The item returned is the current item in the sequence.
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//
// DYNAMIC MEMORY USAGE by the List
//   If there is insufficient dynamic memory, then the following functions
//   throw a BAD_ALLOC exception: The constructors, insert, attach. 