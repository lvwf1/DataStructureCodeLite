#ifndef set_h
#define set_h
#include <cstdlib>  // Provides size_t
#include <iostream>  // Provides iostream
#include "node1.h"  // Provides node1

namespace main_savitch_5
{
class set
    { 
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef int value_type;
        typedef std::size_t size_type;
        // CONSTRUCTOR
        set();
        // COPY CONSTRUCTOR
        set(const set& source);
        // DESTRUCTOR
        ~set();
        // MODIFICATION MEMBER FUNCTIONS
        void resize(size_type new_capacity);
        void insert(const value_type& entry);
        void remove(const value_type& target);
        bool check(const value_type& target);
        size_type count() const;
        void operator +=(const set& addend);
        void operator -=(const set& addend);
        set operator ^ (const set& addend);
        void operator =(const set& source);
        void display();
        // CONSTANT MEMBER FUNCTIONS
    private:
        node *head_ptr;
        node *tail_ptr;
        node *cursor;
        size_type many_nodes;
    };
    // NONMEMBER FUNCTIONS for the set class
    set operator +(const set& s1, const set& s2);
    set operator -(const set& s1, const set& s2);
    std::ostream& operator <<(std::ostream & outs, const set& source);
}
#endif // set_h