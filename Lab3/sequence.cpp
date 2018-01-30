// FILE: sequence1.h
// CLASS PROVIDED: sequence (part of the namespace main_savitch_3)
// There is no implementation file provided for this class since it is
// an exercise from Section 3.2 of "Data Structures and Other Objects Using C++"
#include <iostream>     // Provides cout.
#include <cassert>      // Provides assert
#include "sequence1.h"  // Provides the sequence class with double items.
using namespace std;
namespace main_savitch_3
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
//
    const sequence::size_type sequence::CAPACITY;
// CONSTRUCTOR for the sequence class:
    sequence::sequence()
    {
        current_index = 0;
        used = 0; 
    }
//     Postcondition: The sequence has been initialized as an empty sequence.
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void start( )

    void sequence::start()
    {
        current_index= 0;
    }
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//     void advance( )
//     Precondition: is_item returns true.
    void sequence::advance()
    {
        if (is_item()== true)
            {
                current_index++;
            }
    }
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//     void insert(const value_type& entry)
//     Precondition: size( ) < CAPACITY.
    void sequence::insert(const value_type& entry)
    {
        assert (size()< CAPACITY);
        if (!is_item())
            {
                current_index=0;
                }
        for(int i=used;i>current_index;i--)
            {
                data[i]=data[i-1];
            }
        data[current_index]= entry;
        used++;
    }
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//     void attach(const value_type& entry)
//     Precondition: size( ) < CAPACITY.
    void sequence::attach(const value_type& entry){
        assert (size()< CAPACITY);
        if(is_item()&&current_index!=used)
        {
        current_index++;
        for(int i=used;i>current_index;i--)
            {
            data[i]=data[i-1];
            }
        }
        data[current_index]=entry;
        used++;
    }
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//   void remove_current( )
//     Precondition: is_item returns true.
    void sequence::remove_current()
    {
        assert(is_item()==true);
        for(int i=current_index;i<used;i++)
            {
            data[i]=data[i+1];
            }
        used--;
    }
//     Postcondition: The current item has been removed from the sequence, and the
//     item after this (if there is one) is now the new current item.
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   size_type size( ) const
    sequence::size_type sequence::size() const{
        return used;
    }
//     Postcondition: The return value is the number of items in the sequence.
//   bool is_item( ) const
    bool sequence::is_item() const{
        return current_index<used;
    }
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
    sequence::value_type sequence::current() const{
        if(is_item()){
            return data[current_index];
            }
    }
}
//     Postcondition: The item returned is the current item in the sequence.
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.