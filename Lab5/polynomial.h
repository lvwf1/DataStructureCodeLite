#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

#include <cstdlib>
#include <iostream>

class polynomial
{
public:
    typedef std::size_t size_type;

//     postcondition: This polynomial has been create with all zero
//     coefficients, except for coefficient c for the specified exponent.
//     When used as a default constructor (using default values for
//     both arguments), the result is a polynomial with all zero
//     coefficients.
    polynomial(double c = 0.0, size_type exponent = 0);

    // postcondition: all memory allocated to the polynomial has been deallocated
    ~polynomial();
  
    // postcondition: copy of p has been created
    polynomial (const polynomial& p);
    
    // postcondition: p has been assigned to the current polynomial
    polynomial& operator = (const polynomial& p);
    
     //  postcondition: Adds the given amount to the coefficient of the  specified exponent.
    void add_to_coef(double amount, size_type exponent);

    //  postcondition: Sets the coefficient for the specified exponent.
	void assign_coef(double coefficient, size_type exponent);
    
    //  postcondition: Returns coefficient at specified exponent of this polynomial.
    double coefficient(size_type exponent) const;
    
    //postcondition:  The function returns the value of the largest exponent
    //  with a non-zero coefficient.  If all coefficients are zero, then the function returns zero.
    size_type degree( ) const;
    
    // postcondition: returns first derivative of the function
	polynomial derivative( ) const;
    
    //postcondition: returns value of the polynomial evaluated at x
	double eval(double x) const;
    
    //postcondition:  The return value is the next exponent n which is LARGER
    //   than e such that coefficient(n) != 0.  If there is no such term, then the return value is zero.
	size_type next_term(size_type e) const;
    
    //postcondition: The return value is the next exponent n which is SMALLER
    //  than e such that coefficient(n) != 0.  If there is no such term, then the return value is
    // UINT_MAX from <climits>.
	size_type previous_term(size_type e) const;
    
   //postcondition: returns value of the polynomial evaluated at x
    double operator( ) (double x) const;

private:
    void resize (size_type new_capacity);
    void find_current_degree();
    double* coefficients;
    size_type current_degree;
    size_type capacity;
};

    // postcondition: returns the sum of p1 and p2
    polynomial operator +(const polynomial& p1, const polynomial& p2);
    
    // postcondition: returns the difference of p1 and p2
    polynomial operator -(const polynomial& p1, const polynomial& p2);
    
    // postcondition: returns the product of p1 and p2
    polynomial operator *(const polynomial& p1, const polynomial& p2);
    
    // postcondition: The polynomial has been printed to ostream out, which,
    //  in turn, has been returned to the calling function.
    std::ostream& operator << (std::ostream& out, const polynomial& p);

#endif // _POLYNOMIAL_H_