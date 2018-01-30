#include "polynomial.h"
#include <algorithm>
#include <cmath>
#include <climits>

void polynomial::resize (size_type new_capacity)
{
    if (new_capacity > current_degree)
    {
        double* temp = new double[new_capacity];
        std::copy (coefficients, coefficients + current_degree + 1, temp);
        for (size_type i = current_degree +2; i < new_capacity; ++i)
            temp[i] = 0.0;
        delete [] coefficients;
        capacity = new_capacity;
        coefficients = temp;
    }
}

void polynomial::find_current_degree()
{
    size_type result = previous_term(capacity);
    if (result == UINT_MAX)
        result = 0;
    current_degree = result;
}

//     postcondition: This polynomial has been create with all zero
//     coefficients, except for coefficient c for the specified exponent.
//     When used as a default constructor (using default values for
//     both arguments), the result is a polynomial with all zero
//     coefficients.
polynomial::polynomial(double c, size_type exponent)
{
    coefficients = new double[exponent + 1];
    for (size_type i = 0; i <= exponent; ++i)
        coefficients[i] = 0.0;
    coefficients[exponent] = c;
    capacity = exponent + 1;
    if (c == 0.0)
        current_degree = 0;
    else
        current_degree = exponent;
}

// postcondition: all memory allocated to the polynomial has been deallocated
polynomial::~polynomial()
{
    delete[] coefficients;
}

// postcondition: copy of p has been created
polynomial::polynomial(const polynomial& p)
{
    coefficients = new double[p.capacity];
    std::copy (p.coefficients, p.coefficients + p.capacity, coefficients);
    capacity = p.capacity;
    current_degree = p.current_degree;
}

// postcondition: p has been assigned to the current polynomial
polynomial& polynomial::operator=(const polynomial& p)
{
    if (this != &p)
    {
        if (current_degree != p.current_degree)
        {
            delete [] coefficients;
            coefficients = new double[p.capacity];
        }
        std::copy (p.coefficients, p.coefficients + p.capacity, coefficients);
        capacity = p.capacity;
        current_degree = p.current_degree;
    }
    return *this;
}

//  postcondition: Adds the given amount to the coefficient of the  specified exponent.
void polynomial::add_to_coef(double amount, size_type exponent)
{
    assign_coef(coefficients[exponent] + amount, exponent);
}

//  postcondition: Sets the coefficient for the specified exponent.
void polynomial::assign_coef(double coefficient, size_type exponent)
{
    if (exponent + 1 > capacity)
       resize (exponent + 1);
   coefficients[exponent] = coefficient;
   if (exponent > current_degree || (exponent == current_degree && coefficients[exponent] == 0.0))
        find_current_degree();
}

//  postcondition: Returns coefficient at specified exponent of this polynomial.
double polynomial::coefficient(size_type exponent) const
{
    double result;
    if (exponent < capacity)
        result = coefficients[exponent];
    else
        result = 0.0;
    return result;
}

// postcondition:  The function returns the value of the largest exponent
//  with a non-zero coefficient.  If all coefficients are zero, then the function returns zero.
polynomial::size_type polynomial::degree() const
{
    return current_degree;
}

// postcondition: returns first derivative of the function
polynomial polynomial::derivative() const
{
    polynomial d(0, current_degree);
    for (size_type i = 0; i < current_degree; ++i)
        d.coefficients[i] = (i +1) * coefficients[i+1];
    return d;
}

// postcondition: The return value is the value of this polynomial with the
//  given value for the variable x.
double polynomial::eval(double x) const
{
    double sum = 0.0;
    for (size_type i = 0; i <= current_degree; ++i)
        sum += coefficients[i] * pow (x, i);
    return sum;
}

// postcondition:  The return value is the next exponent n which is LARGER
//   than e such that coefficient(n) != 0.  If there is no such term, then the return value is zero.
polynomial::size_type polynomial::next_term(size_type e) const
{
    size_type result = e + 1;
    while (result <= current_degree && coefficients[result] == 0.0)
        result++;
    if (result > current_degree)
        result = 0;
    return result;
}

// postcondition: The return value is the next exponent n which is SMALLER
//  than e such that coefficient(n) != 0.  If there is no such term, then the return value is
// UINT_MAX from <climits>.
polynomial::size_type polynomial::previous_term(size_type e) const
{
    size_type result = UINT_MAX;
    if (e > 0)
    {
        result = e - 1;
        while (result > 0 && coefficients[result] == 0.0)
            result--;
        if (result == 0 && coefficients[0] == 0.0)
            result = UINT_MAX;
    }
    return result;
}

// postcondition: returns value of the polynomial evaluated at x
double polynomial::operator()(double x) const
{
    return eval(x);
}

// postcondition: returns the sum of p1 and p2
polynomial operator+(const polynomial& p1, const polynomial& p2)
{
    polynomial::size_type degree = std::max (p1.degree(), p2.degree());
    polynomial p (0, degree);
    for (polynomial::size_type i = 0; i <= degree; ++i)
        p.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
    return p;
}

// postcondition: returns the difference of p1 and p2
polynomial operator-(const polynomial& p1, const polynomial& p2)
{
    polynomial::size_type degree = std::max (p1.degree(), p2.degree());
    polynomial p (0, degree);
    for (polynomial::size_type i = 0; i <= degree; ++i)
        p.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
    return p;
}

polynomial term_by_poly (double coef, polynomial::size_type exp, const polynomial& p)
{
    polynomial product (0.0, p.degree() + exp);
    polynomial::size_type index = p.degree();
    while (index != UINT_MAX)
    {
        product.assign_coef(coef * p.coefficient(index), index + exp);
        index = p.previous_term(index);
    }
    return product;
}

// postcondition: returns the product of p1 and p2
polynomial operator*(const polynomial& p1, const polynomial& p2)
{
    polynomial::size_type degree = p1.degree() + p2.degree();
    polynomial product (0, degree);
    polynomial::size_type index = p1.degree();
    while (index != UINT_MAX)
    {
        polynomial temp = term_by_poly (p1.coefficient(index), index, p2);
        product = product + temp;
        index = p1.previous_term(index);        
    }
    return product;
}

// postcondition: The polynomial has been printed to ostream out, which,
//  in turn, has been returned to the calling function.
std::ostream& operator<<(std::ostream& out, const polynomial& p)
{
    polynomial::size_type index = p.degree();
    while (index != UINT_MAX)
    {
        out << " + " << p.coefficient(index) << "x^" << index;
        index = p.previous_term(index);
    }
    return out;
}
