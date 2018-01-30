#ifndef set_h
#define set_h
#include <cstdlib>  // Provides size_t
#include <iostream>  //Provides iostream

class set
    { 
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef int value_type;
        typedef std::size_t size_type;
        static const size_type DEFAULT_CAPACITY = 3;
        // CONSTRUCTOR
        set(size_type initial_capacity=DEFAULT_CAPACITY);
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
        value_type* data;  // The array to store items
        size_type used;    // How much of array is used
        size_type capacity; // The maximum elements to store
    };
    // NONMEMBER FUNCTIONS for the set class
    set operator +(const set& s1, const set& s2);
    set operator -(const set& s1, const set& s2);
    std::ostream& operator <<(std::ostream & outs, const set& source);
#endif // set_h