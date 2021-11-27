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

void reset( Term *&polynomial, int &size );

// enable user to input a polynomial
void input( istream &inFile, Term *&polynomial, int &size );

// outputs the specified polynomial
void output( Term *polynomial, int size );

// returns true if and only if the specified polynomial has at least a zero term
bool hasZeroTerm( Term *polynomial, int size );

// returns true if and only if polynomial1 == polynomial2
bool equal( Term *polynomial1, int size1, Term *polynomial2, int size2 );

// polynomial1 = -polynomial2
void minus( Term *&polynomial1, int &size1, Term *&polynomial2, int size2 );

// addend += adder
void addition( Term *&addend, int &addendSize, Term *adder, int adderSize );

// minuend -= subtrahend
void subtraction( Term *&minuend, int &minuendSize, Term *subtrahend, int subtrahendSize );

// product = multiplicand * multiplier
void multiplication( Term *multiplicand, int multiplicandSize,
   Term *multiplier, int multiplierSize, Term *&product, int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( Term *dividend, int dividendSize, Term *divisor, int divisorSize,
               Term *&quotient, int &quotientSize, Term *&remainder, int &remainderSize );

const int numTestCases = 200; // the number of test cases
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

   Term *dividend = nullptr;
   Term *divisor = nullptr;
   int dividendSize = 0;
   int divisorSize = 0;

   Term *quotient = nullptr;
   Term *remainder = nullptr;
   int quotientSize = 0;
   int remainderSize = 0;

   Term *buffer = nullptr;
   int bufferSize = 0;

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      // input dividend and divisor from the file Polynomials.dat
      input( inFile, dividend, dividendSize );
      input( inFile, divisor, divisorSize );
/**/
      cout << "dividend:  ";
      output( dividend, dividendSize );

      cout << " divisor:  ";
      output( divisor, divisorSize );

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      division( dividend, dividendSize, divisor, divisorSize,
                quotient, quotientSize, remainder, remainderSize );

/**/
      cout << "quotient:  ";
      output( quotient, quotientSize );
      cout << endl;

      if( quotientSize > 0 )
      {
         if( hasZeroTerm( quotient, quotientSize ) )
            cout << "quotient has at least a zero term!\n";
         else
         {
            // buffer = divisor * quotient
            multiplication( divisor, divisorSize,
                            quotient, quotientSize, buffer, bufferSize );

            if( hasZeroTerm( buffer, bufferSize ) )
               cout << "buffer has at least a zero term!\n";
            else
            {
               // buffer = buffer + remainder = divisor * quotient + remainder
               addition( buffer, bufferSize, remainder, remainderSize );

               if( hasZeroTerm( buffer, bufferSize ) )
                  cout << "buffer has at least a zero term!\n";
               else
                  // if buffer != dividend, an error occurred!
                  if( equal( buffer, bufferSize, dividend, dividendSize ) )
                      numErrors--;
            }
         }
      }

      reset( dividend, dividendSize );
      reset( divisor, divisorSize );

      reset( quotient, quotientSize );
      reset( remainder, remainderSize );

      reset( buffer, bufferSize );
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

void reset( Term *&polynomial, int &size )
{
   size = 0;
   if( polynomial != nullptr )
   {
      delete[] polynomial;
      polynomial = nullptr;
   }
}

// enable user to input a polynomial
void input( istream &inFile, Term *&polynomial, int &size )
{
   int numericString[ arraySize ] = {};

   inFile.read( reinterpret_cast< char * >( numericString ), 80 );

   size = arraySize;
   while( size > 0 && numericString[ size - 1 ] == 0 )
      size--;

   polynomial = new Term[ size ];
   for( int i = 0; i < size; ++i )
      polynomial[ i ].coef = numericString[ i ];
/*
   for( int i = 0; i < size; ++i )
      cout << setw( 4 ) << numericString[ i ];
   cout << endl;
*/
   inFile.read( reinterpret_cast< char * >( numericString ), 80 );

   for( int i = 0; i < size; ++i )
      polynomial[ i ].expon = numericString[ i ];
/*
   for( int i = 0; i < size; ++i )
      cout << setw( 4 ) << exponent[ i ];
   cout << endl;
*/
}

// outputs the specified polynomial
void output( Term *polynomial, int size )
{
   // the specified polynomial is zero polynomial
   if( size == 0 )
      cout << 0;
   else
   {
      if( polynomial[ 0 ].coef < 0 )
         cout << "-" << -polynomial[ 0 ].coef;
      else if( polynomial[ 0 ].coef > 0 )
         cout << polynomial[ 0 ].coef;

      if( polynomial[ 0 ].expon > 0 )
      {
         if( polynomial[ 0 ].expon == 1 )
            cout << "x";
         else
            cout << "x^" << polynomial[ 0 ].expon;
      }

      for( int i = 1; i < size; i++ )
      {
         if( polynomial[ i ].coef < 0 )
            cout << " - " << -polynomial[ i ].coef;
         else if( polynomial[ i ].coef > 0 )
            cout << " + " << polynomial[ i ].coef;

         if( polynomial[ i ].expon > 0 )
         {
            if( polynomial[ i ].expon == 1 )
               cout << "x";
            else
               cout << "x^" << polynomial[ i ].expon;
         }
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool hasZeroTerm( Term *polynomial, int size )
{
   if( size != 0 )
      for( int i = 0; i < size; i++ )
         if( polynomial[ i ].coef == 0 )
            return true;

   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( Term *polynomial1, int size1, Term *polynomial2, int size2 )
{
   if( size1 != size2 )
      return false;

   for( int i = 0; i < size1; i++ )
      if( polynomial1[ i ].coef != polynomial2[ i ].coef ||
          polynomial1[ i ].expon != polynomial2[ i ].expon )
         return false;

   return true;
}

// polynomial1 = -polynomial2
void minus( Term *&polynomial1, int &size1, Term *&polynomial2, int size2 )
{
   size1 = size2;
   for( int i = 0; i < size1; i++ )
   {
      polynomial1[ i ].coef = -polynomial2[ i ].coef;
      polynomial1[ i ].expon = polynomial2[ i ].expon;
   }
}

// addend += adder
void addition( Term *&addend, int &addendSize, Term *adder, int adderSize )
{
   Term *sum = new Term[ arraySize ]();
   int i = 0;
   int j = 0;
   int k = 0;

/*  for (int n = 0; n < addendSize; n++)
       cout << addend[n].expon << "  ";
   cout << endl;
   for (int n = 0; n < addendSize; n++)
       cout << addend[n].coef << "  ";
   cout << endl;
   for (int n = 0; n < adderSize; n++)
       cout << adder[n].expon << "  ";
   cout << endl;
   for (int n = 0; n < adderSize; n++)
       cout << adder[n].coef << "  ";
   cout << endl;*/ 

   if (addendSize == 0)
   {
      k = adderSize;
      for(int a = 0; a < adderSize; a++)
      {
         sum[a].coef = adder[a].coef;
         sum[a].expon = adder[a].expon;
      }
   }
   else if (adderSize == 0)
   {
      k = addendSize;
      for (int a = 0; a < addendSize; a++)
      {
         sum[a].coef = addend[a].coef;
         sum[a].expon = addend[a].expon;
      }
   }
   else
   {
       while (1)
      {

         if(addend[i].expon > adder[j].expon)
         {
            sum[k].expon = addend[i].expon;
            sum[k].coef = addend[i].coef;
            i++; k++;
         }
         else if(addend[i].expon < adder[j].expon)
         {
            sum[k].expon = adder[j].expon;
            sum[k].coef = adder[j].coef;
            j++; k++;
         }
         else if(addend[i].expon == adder[j].expon)
         {
            sum[k].coef = addend[i].coef + adder[j].coef;
            if(sum[k].coef != 0)
            {
               sum[k].expon = addend[i].expon;
               k++;
            }
            i++; j++;
         }
         if (i == addendSize)
         {
             while (j < adderSize)
             {
                 sum[k].expon = adder[j].expon;
                 sum[k].coef = adder[j].coef;
                 j++; k++;
             }
             break;
         }
         if (j == adderSize)
         {
             while (i < addendSize)
             {
                 sum[k].expon = addend[i].expon;
                 sum[k].coef = addend[i].coef;
                 i++; k++;
             }
             break;
         }
      }

   }
   /*
   for (int i = 0; i < k; i++)
   {
       cout << sum[i].expon << " ";
   }
   cout << endl;
   for (int i = 0; i < k; i++)
   {
       cout << sum[i].coef << " ";
   }
   cout << endl;*/

   if( addendSize != k )
      addend = new Term[ k ];

   addendSize = k;
   for( int i = 0; i < addendSize; i++ ) // addend = sum
      addend[ i ] = sum[ i ];

   delete[] sum;
}

// minuend -= subtrahend
void subtraction( Term *&minuend, int &minuendSize, Term *subtrahend, int subtrahendSize )
{
   // buffer = 0
   int bufferSize = subtrahendSize;
   Term *buffer = new Term[ bufferSize ]();

   // buffer = -subtrahend
   minus( buffer, bufferSize, subtrahend, subtrahendSize );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( minuend, minuendSize, buffer, bufferSize );

   delete[] buffer;

   if( minuendSize > 0 && minuend[ 0 ].coef == 0 )
      cout << "Leading zeroes in minuend not allowed!\n";
}

// product = multiplicand * multiplier
void multiplication( Term *multiplicand, int multiplicandSize,
   Term *multiplier, int multiplierSize, Term *&product, int &productSize )
{
   // product = 0;
   productSize = 0;

   int bufferSize = multiplicandSize;
   Term *buffer = new Term[ bufferSize ]();

   // if( multiplicand != 0 && multiplier != 0 )
   if( multiplicandSize != 0 && multiplierSize != 0 )
   {
      for(int i = 0; i < multiplierSize; i++)
      {
         for(int j = 0; j < multiplicandSize; j++)
         {
            buffer[j].expon = multiplier[i].expon + multiplicand[j].expon;
            buffer[j].coef = multiplier[i].coef * multiplicand[j].coef;
         }
         addition(product, productSize, buffer, bufferSize);
      }
   }

   delete[] buffer;

   if( productSize > 0 && product[ 0 ].coef == 0 )
      cout << "Leading zeroes in product not allowed!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( Term *dividend, int dividendSize, Term *divisor, int divisorSize,
               Term *&quotient, int &quotientSize, Term *&remainder, int &remainderSize )
{
   // remainder = dividend
   remainderSize = dividendSize;
   remainder = new Term[ remainderSize ]();
   for( int i = 0; i < remainderSize; i++ )
      remainder[ i ] = dividend[ i ];

   int monomialSize = 1;
   Term *monomial = new Term[ 1 ]();

   int bufferSize = 0;
   Term *buffer = nullptr;

   Term temp[ arraySize ] = {};
   quotientSize = 0;

   while(remainderSize != 0 && remainder[0].expon >= divisor[0].expon)
   {
      temp[quotientSize].coef = remainder[0].coef / divisor[0].coef;
      temp[quotientSize].expon = remainder[0].expon - divisor[0].expon;
      monomial[0].coef = temp[quotientSize].coef;
      monomial[0].expon = temp[quotientSize].expon;
      multiplication( divisor, divisorSize, monomial, 1, buffer, bufferSize);
      subtraction( remainder, remainderSize, buffer, bufferSize);
      quotientSize++;
   }

   quotient = new Term[ quotientSize ];
   for( int i = 0; i < quotientSize; ++i )
      quotient[ i ] = temp[ i ];

   delete[] monomial;

   delete[] buffer;

   if( quotientSize > 0 && quotient[ 0 ].coef == 0 )
      cout << "Leading zeroes in quotient not allowed!\n";

   if( remainderSize > 0 && remainder[ 0 ].coef == 0 )
      cout << "Leading zeroes in remainder not allowed!\n";
}
