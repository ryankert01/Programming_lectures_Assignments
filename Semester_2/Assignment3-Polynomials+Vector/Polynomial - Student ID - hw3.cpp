#include <iostream>
using std::cout;
using std::endl;

#include "Polynomial.h" // include definition of class Polynomial

Polynomial::Polynomial( size_t n )
   : polynomial( n )
{
}

Polynomial::Polynomial( size_t n, int coefficient[], int exponent[] )
   : polynomial( n )
{
   for( size_t i = 0; i < n; i++ )
   {
      polynomial.at( i ).coef = coefficient[ i ];
      polynomial.at( i ).expon = exponent[ i ];
   }
}

Polynomial::Polynomial( const Polynomial &right )
   : polynomial( right.polynomial )
{
}

Polynomial::~Polynomial()
{
}

const Polynomial Polynomial::assign( const Polynomial &right )
{
   if( &right != this ) // avoid self-assignment
      polynomial.assign( right.polynomial );

   return *this; // enables x = y = z, for example
}

bool Polynomial::equal( const Polynomial &right )
{
   if( polynomial.size() != right.polynomial.size() )
      return false;

   for( size_t i = 0; i < polynomial.size(); i++ )
      if( polynomial.at( i ).coef != right.polynomial.at( i ).coef ||
          polynomial.at( i ).expon != right.polynomial.at( i ).expon )
         return false;

   return true;
}

void Polynomial::addition( const Polynomial &adder )
{
   Polynomial sum( polynomial.size() + adder.polynomial.size() );
   size_t i = 0;
   size_t j = 0;
   size_t k = 0;




   if( sum.polynomial.size() != k )
      sum.polynomial.resize( k );

   polynomial.assign( sum.polynomial );

   if( !zero() && leadingCoef() == 0 )
      cout << "addend has leading zeroes!\n";
}

void Polynomial::subtraction( const Polynomial &subtrahend )
{
   Polynomial buffer( subtrahend.minus() );

   addition( buffer ); // minuend = minuend + buffer = minuend - subtrahend

   if( !zero() && leadingCoef() == 0 )
      cout << "minuend has leading zeroes!\n";
}

Polynomial Polynomial::multiplication( const Polynomial &multiplier ) const
{
   Polynomial product;
   Polynomial buffer( polynomial.size() );




   if( !product.zero() && product.leadingCoef() == 0 )
      cout << "product has leading zeroes!\n";

   return product;
}

Polynomial Polynomial::division( const Polynomial &divisor )
{
   Polynomial quotient;
   Polynomial remainder( *this );
   Polynomial monomial( 1 );




   if( !quotient.zero() && quotient.leadingCoef() == 0 )
      cout << "quotient has leading zeroes!\n";

   return quotient;
}

Polynomial Polynomial::modulus( const Polynomial &divisor )
{
   Polynomial quotient;
   Polynomial remainder( *this );
   Polynomial monomial( 1 );




   if( !remainder.zero() && remainder.leadingCoef() == 0 )
      cout << "remainder has leading zeroes!\n";

   return remainder;
}

void Polynomial::output()
{
   // the current polynomial is zero polynomial
   if( zero() )
      cout << 0;
   else
   {
      if( leadingCoef() < 0 )
         cout << "-" << -leadingCoef();
      else if( leadingCoef() > 0 )
         cout << leadingCoef();

      if( degree() > 0 )
      {
         if( degree() == 1 )
            cout << "x";
         else
            cout << "x^" << degree();
      }

      for( size_t i = 1; i < polynomial.size(); i++ )
      {
         if( polynomial.at( i ).coef < 0 )
            cout << " - " << -polynomial.at( i ).coef;
         else if( polynomial.at( i ).coef > 0 )
            cout << " + " << polynomial.at( i ).coef;

         if( polynomial.at( i ).expon > 0 )
         {
            if( polynomial.at( i ).expon == 1 )
               cout << "x";
            else
               cout << "x^" << polynomial.at( i ).expon;
         }
      }
   }

   cout << endl;
}

bool Polynomial::hasZeroTerm()
{
   if( !zero() )
      for( size_t i = 0; i < polynomial.size(); i++ )
         if( polynomial.at( i ).coef == 0 )
            return true;

   return false;
}

Polynomial Polynomial::minus() const
{
   Polynomial minus( polynomial.size() );
   for( size_t i = 0; i < minus.polynomial.size(); i++ )
   {
      minus.polynomial.at( i ).coef = -polynomial.at( i ).coef;
      minus.polynomial.at( i ).expon = polynomial.at( i ).expon;
   }

   return minus;
}

bool Polynomial::zero() const
{
   return polynomial.empty();
}

int Polynomial::degree() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().expon;
}

int Polynomial::leadingCoef() const
{
   if( polynomial.empty() )
      return 0;
   else
      return polynomial.front().coef;
}