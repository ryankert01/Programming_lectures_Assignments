// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <fstream>
using std::istream;
using std::ifstream;
using std::ios;

struct Term
{
   int coef = 0;  // the coefficient of a term
   int expon = 0; // the exponent of a term
};

// term1 = term2
void assign( Term &term1, Term &term2 );

// Polynomial class definition
class Polynomial
{
public:
   // polynomial = 0
   void reset();

   // inputs a polynomial from the file Polynomials.dat
   void input( istream &inFile );

   // outputs the specified polynomial
   void output();

   // returns true if and only if the specified polynomial has at least a zero term
   bool hasZeroTerm();

   // returns true if and only if polynomial1 == polynomial2
   bool equal( Polynomial &polynomial2 );

   // polynomial1 = -polynomial2
   void minus( Polynomial &polynomial2 );

   // addend += adder
   void addition( Polynomial adder );

   // minuend -= subtrahend
   void subtraction( Polynomial &subtrahend );

   // product = multiplicand * multiplier
   void multiplication( Polynomial &multiplier, Polynomial &product );

   // quotient = dividend / divisor; remainder = dividend % divisor
   // provided that the degree of dividend >= the degree of divisor
   void division( Polynomial &divisor, Polynomial &quotient, Polynomial &remainder );

   int size = 0;          // the number of terms of the polynomial
   Term *terms = nullptr; // all terms of the polynomial
};


int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
   ifstream inFile( "Polynomials.dat", ios::in | ios::binary );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   Polynomial dividend;
   Polynomial divisor;
   Polynomial quotient;
   Polynomial remainder;
   Polynomial buffer;

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      // input dividend and divisor from the file Polynomials.dat
      dividend.input( inFile );
      divisor.input( inFile );
/**/
      cout << "dividend:  ";
      dividend.output();

      cout << " divisor:  ";
      divisor.output();

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      dividend.division( divisor, quotient, remainder );

/**/
      cout << "quotient:  ";
      quotient.output();
      cout << endl;


      if( quotient.hasZeroTerm() )
         cout << "quotient has at least a zero term!\n";
      else
      {
         // buffer = divisor * quotient
         divisor.multiplication( quotient, buffer );

         if( buffer.hasZeroTerm() )
            cout << "buffer has at least a zero term!\n";
         else
         {
            // buffer = buffer + remainder = divisor * quotient + remainder
            buffer.addition( remainder );

            if( buffer.hasZeroTerm() )
               cout << "buffer has at least a zero term!\n";
            else
               // if buffer != dividend, an error occurred!
               if( buffer.equal( dividend ) )
                  numErrors--;
         }
      }

      dividend.reset();
      divisor.reset();
      quotient.reset();
      remainder.reset();
      buffer.reset();
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

// term1 = term2
void assign( Term &term1, Term &term2 )
{
   term1.coef = term2.coef;
   term1.expon = term2.expon;
}

// polynomial = 0
void Polynomial::reset()
{
   size = 0;
   if( terms != nullptr )
   {
      delete[] terms;
      terms = nullptr;
   }
}

// inputs a polynomial from the file Polynomials.dat
void Polynomial::input( istream &inFile )
{
   int numericString[ arraySize ] = {};

   inFile.read( reinterpret_cast< char * >( numericString ), 80 );

   size = arraySize;
   while( size > 0 && numericString[ size - 1 ] == 0 )
      size--;

   terms = new Term[ size ];
   for( int i = 0; i < size; ++i )
      terms[ i ].coef = numericString[ i ];

   inFile.read( reinterpret_cast< char * >( numericString ), 80 );

   for( int i = 0; i < size; ++i )
      terms[ i ].expon = numericString[ i ];
}

// outputs the specified polynomial
void Polynomial::output()
{
   // the specified polynomial is zero polynomial
   if( size == 0 )
      cout << 0;
   else
   {
      if( terms[ 0 ].coef < 0 )
         cout << "-" << -terms[ 0 ].coef;
      else if( terms[ 0 ].coef > 0 )
         cout << terms[ 0 ].coef;

      if( terms[ 0 ].expon > 0 )
      {
         if( terms[ 0 ].expon == 1 )
            cout << "x";
         else
            cout << "x^" << terms[ 0 ].expon;
      }

      for( int i = 1; i < size; i++ )
      {
         if( terms[ i ].coef < 0 )
            cout << " - " << -terms[ i ].coef;
         else if( terms[ i ].coef > 0 )
            cout << " + " << terms[ i ].coef;

         if( terms[ i ].expon > 0 )
         {
            if( terms[ i ].expon == 1 )
               cout << "x";
            else
               cout << "x^" << terms[ i ].expon;
         }
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool Polynomial::hasZeroTerm()
{
   if( size != 0 )
      for( int i = 0; i < size; i++ )
         if( terms[ i ].coef == 0 )
            return true;

   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool Polynomial::equal( Polynomial &polynomial2 )
{
   if( size != polynomial2.size )
       return false;

   for( int i = 0; i < size; i++ )
      if( terms[ i ].coef != polynomial2.terms[ i ].coef ||
          terms[ i ].expon != polynomial2.terms[ i ].expon )
          return false;

   return true;
}

// polynomial1 = -polynomial2
void Polynomial::minus( Polynomial &polynomial2 )
{
   if( size != 0 )
      delete[] terms;
   terms = new Term[ polynomial2.size ];

   size = polynomial2.size;
   for( int i = 0; i < size; i++ )
   {
      terms[ i ].coef = -polynomial2.terms[ i ].coef;
      terms[ i ].expon = polynomial2.terms[ i ].expon;
   }
}

// addend += adder
void Polynomial::addition( Polynomial adder )
{
   Polynomial sum;
   sum.terms = new Term[ arraySize ];
   int i = 0;
   int j = 0;
   int k = 0;

   if (size == 0)
   {
      k = adder.size;
      for(int a = 0; a < adder.size; a++)
      {
         assign(sum.terms[a], adder.terms[a]);
      }
   }
   else if (adder.size == 0)
   {
      k = size;
      for (int a = 0; a < size; a++)
      {
         assign(sum.terms[a], terms[a]);
      }
   }
   else
   {
       while (i < size && j < adder.size)
      {

         if(terms[i].expon > adder.terms[j].expon)
         {
            assign(sum.terms[k], terms[i]);
            i++; k++;
         }
         else if(terms[i].expon < adder.terms[j].expon)
         {
            assign(sum.terms[k], adder.terms[j]);
            j++; k++;
         }
         else if(terms[i].expon == adder.terms[j].expon)
         {
            sum.terms[k].coef = terms[i].coef + adder.terms[j].coef;
            if(sum.terms[k].coef != 0)
            {
               sum.terms[k].expon = terms[i].expon;
               k++;
            }
            i++; j++;
         }

      }
        if(i == size)
      {
         while(j < adder.size)
         {
            assign(sum.terms[k], adder.terms[j]);
            j++; k++;
         }
      }
      else if(j == adder.size)
      {
           while (i < size)
           {
               assign(sum.terms[k], terms[i]);
               i++; k++;
           }
      }
   }


   if( size != k )
   {
      if( size != 0 )
         delete[] terms;
      terms = new Term[ k ];
      size = k;
   }

   for( int i = 0; i < size; i++ ) // addend = sum
      assign( terms[ i ], sum.terms[ i ] );

   delete[] sum.terms;
}

// minuend -= subtrahend
void Polynomial::subtraction( Polynomial &subtrahend )
{
   Polynomial buffer;
   buffer.size = subtrahend.size;
   buffer.terms = new Term[ buffer.size ]();

   // buffer = -subtrahend
   buffer.minus( subtrahend );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( buffer );

   delete[] buffer.terms;

   if( size > 0 && terms[ 0 ].coef == 0 )
      cout << "Leading zeroes in minuend not allowed!\n";
}

// product = multiplicand * multiplier
void Polynomial::multiplication( Polynomial &multiplier, Polynomial &product )
{
   // product = 0;
   if( product.size != 0 )
   {
      product.size = 0;
      delete[] product.terms;
   }

   Polynomial buffer;
   buffer.size = size;
   buffer.terms = new Term[buffer.size]();

   // if( multiplicand != 0 && multiplier != 0 )
   if( size != 0 && multiplier.size != 0 )
   {
      for(int i = 0; i < multiplier.size; i++)
      {
         
         for(int j = 0; j < size; j++)
         {
            buffer.terms[j].expon = multiplier.terms[i].expon + terms[j].expon;
            buffer.terms[j].coef = multiplier.terms[i].coef * terms[j].coef;
         }
         product.addition(buffer);
         
      }


   }
   delete[] buffer.terms;

   if( product.size > 0 && product.terms[ 0 ].coef == 0 )
      cout << "Leading zeroes in product not allowed!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the degree of dividend >= the degree of divisor
void Polynomial::division( Polynomial &divisor, Polynomial &quotient, Polynomial &remainder )
{
   // remainder = dividend
   remainder.size = size;
   remainder.terms = new Term[ remainder.size ]();
   for( int i = 0; i < remainder.size; i++ )
      assign( remainder.terms[ i ], terms[ i ] );

   Polynomial monomial;
   monomial.size = 1;
   monomial.terms = new Term[ 1 ]();

   Polynomial buffer;

   Polynomial temp;
   temp.size = arraySize;
   temp.terms = new Term[ arraySize ]();

   if( quotient.size != 0 )
      delete[] quotient.terms;
   quotient.size = 0;

   while(remainder.size != 0 && remainder.terms[0].expon >= divisor.terms[0].expon)
      {
         temp.terms[quotient.size].coef = remainder.terms[0].coef / divisor.terms[0].coef;
         temp.terms[quotient.size].expon = remainder.terms[0].expon - divisor.terms[0].expon;
         monomial.terms[0].coef = temp.terms[quotient.size].coef;
         monomial.terms[0].expon = temp.terms[quotient.size].expon;
         divisor.multiplication(monomial, buffer);
         remainder.subtraction(buffer);
         quotient.size++;
      }


   quotient.terms = new Term[ quotient.size ];
   for( int i = 0; i < quotient.size; ++i )
      assign( quotient.terms[ i ], temp.terms[ i ] );

   delete[] monomial.terms;
   delete[] buffer.terms;
   delete[] temp.terms;

   if( quotient.size > 0 && quotient.terms[ 0 ].coef == 0 )
      cout << "Leading zeroes in quotient not allowed!\n";

   if( remainder.size > 0 && remainder.terms[ 0 ].coef == 0 )
      cout << "Leading zeroes in remainder not allowed!\n";
}