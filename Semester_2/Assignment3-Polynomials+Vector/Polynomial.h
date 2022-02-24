#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "vector.h" // include definition of class vector

// Polynomial class definition
class Polynomial
{
public:

   // Constructs an empty polynomial, with no terms.
   Polynomial( size_t n = 0 );

   // Constructs a polynomial with n terms.
   // The coefficient and exponent of i-th term are
   // coefficient[ i ] and exponent[ i ], respectively.
   Polynomial( size_t n, int coefficient[], int exponent[] );

   // Constructs a polynomial with a copy of each of the terms in "right".
   Polynomial( const Polynomial &right );

   // Destructor with empty body.
   ~Polynomial();

   // Assigns new contents to the current polynomial, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the terms from "right" into the current polynomial.
   // (with "right" preserving its contents).
   const Polynomial assign( const Polynomial &right );

   // Returns true if and only if the current polynomial is equal to "right".
   bool equal( const Polynomial &right );

   // the current polynomial += adder
   void addition( const Polynomial &adder );

   // the current polynomial -= subtrahend
   void subtraction( const Polynomial &subtrahend );

   // Returns the product of the current polynomial and multiplier.
   Polynomial multiplication( const Polynomial &multiplier ) const;

   // Returns the quotient of the current polynomial divided by divisor
   // provided that the divisor is not zero polynomial and
   // the degree of the current polynomial >= the degree of divisor.
   Polynomial division( const Polynomial &divisor );

   // Returns the remainder of the current polynomial divided by divisor
   // provided that the divisor is not zero polynomial and
   // the degree of the current polynomial >= the degree of divisor.
   Polynomial modulus( const Polynomial &divisor );

   // Outputs the current polynomial.
   void output();

   // Returns true if and only if the current polynomial has at least a term with zero coefficient.
   bool hasZeroTerm();

private:
   vector polynomial; // a polynomial

   // Returns the minus of the current polynomial.
   Polynomial minus() const;

   // Returns true if and only if the current polynomial is zero polynomial.
   bool zero() const;

   // Returns the degree of the current polynomial.
   int degree() const;

   // Returns the leading coefficient of the current polynomial.
   int leadingCoef() const;

}; // end class Polynomial

#endif