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

void reset( int *&coefficient, int *&exponent, int &size );

// enable user to input a polynomial
void input( istream &inFile, int *&coefficient, int *&exponent, int &size );

// outputs the specified polynomial
void output( int *coefficient, int *exponent, int size );

// returns true if and only if the specified polynomial has at least a zero term
bool hasZeroTerm( int *coefficient, int size );

// returns true if and only if polynomial1 == polynomial2
bool equal( int *coefficient1, int *exponent1, int size1,
            int *coefficient2, int *exponent2, int size2 );

// polynomial1 = -polynomial2
void minus( int *&coefficient1, int *&exponent1, int &size1,
            int *coefficient2, int *exponent2, int size2 );

// addend += adder
void addition( int *&addendCoef, int *&addendExpon, int &addendSize,
               int *adderCoef, int *adderExpon, int adderSize );

// minuend -= subtrahend
void subtraction( int *&minuendCoef, int *&minuendExpon, int &minuendSize,
                  int *subtrahendCoef, int *subtrahendExpon, int subtrahendSize );

// product = multiplicand * multiplier
void multiplication( int *multiplicandCoef, int *multiplicandExpon, int multiplicandSize,
                     int *multiplierCoef, int *multiplierExpon, int multiplierSize,
                     int *&productCoef, int *&productExpon, int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( int *dividendCoef, int *dividendExpon, int dividendSize,
               int *divisorCoef, int *divisorExpon, int divisorSize,
               int *&quotientCoef, int *&quotientExpon, int &quotientSize,
               int *&remainderCoef, int *&remainderExpon, int &remainderSize );

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

   int *dividendCoef = nullptr;
   int *dividendExpon = nullptr;
   int *divisorCoef = nullptr;
   int *divisorExpon = nullptr;
   int dividendSize = 0;
   int divisorSize = 0;

   int *quotientCoef = nullptr;
   int *quotientExpon = nullptr;
   int *remainderCoef = nullptr;
   int *remainderExpon = nullptr;
   int quotientSize = 0;
   int remainderSize = 0;

   int *bufferCoef = nullptr;
   int *bufferExpon = nullptr;
   int bufferSize = 0;

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      // input dividend and divisor from the file Polynomials.dat
      input( inFile, dividendCoef, dividendExpon, dividendSize );
      input( inFile, divisorCoef, divisorExpon, divisorSize );
/**/
      cout << "dividend:  ";
      output( dividendCoef, dividendExpon, dividendSize );

      cout << " divisor:  ";
      output( divisorCoef, divisorExpon, divisorSize );

      // quotient = dividend / divisor; remainder = dividend % divisor
      // thus, dividend == divisor * quotient + remainder
      division( dividendCoef, dividendExpon, dividendSize,
                divisorCoef, divisorExpon, divisorSize,
                quotientCoef, quotientExpon, quotientSize,
                remainderCoef, remainderExpon, remainderSize );

/**/
      cout << "quotient:  ";
      output( quotientCoef, quotientExpon, quotientSize );
      cout << endl;

      if( quotientSize > 0 )
      {
         if( hasZeroTerm( quotientCoef, quotientSize ) )
            cout << "quotient has at least a zero term!\n";
         else
         {
            // buffer = divisor * quotient
            multiplication( divisorCoef, divisorExpon, divisorSize,
                            quotientCoef, quotientExpon, quotientSize,
                            bufferCoef, bufferExpon, bufferSize );

            if( hasZeroTerm( bufferCoef, bufferSize ) )
               cout << "buffer has at least a zero term!\n";
            else
            {
               // buffer = buffer + remainder = divisor * quotient + remainder
               addition( bufferCoef, bufferExpon, bufferSize,
                         remainderCoef, remainderExpon, remainderSize );

               if( hasZeroTerm( bufferCoef, bufferSize ) )
                  cout << "buffer has at least a zero term!\n";
               else
                  // if buffer != dividend, an error occurred!
                  if( equal( bufferCoef, bufferExpon, bufferSize,
                      dividendCoef, dividendExpon, dividendSize ) )
                      numErrors--;
            }
         }
      }

      reset( dividendCoef, dividendExpon, dividendSize );
      reset( divisorCoef, divisorExpon, divisorSize );

      reset( quotientCoef, quotientExpon, quotientSize );
      reset( remainderCoef, remainderExpon, remainderSize );

      reset( bufferCoef, bufferExpon, bufferSize );
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

void reset( int *&coefficient, int *&exponent, int &size )
{
   size = 0;
   if( coefficient != nullptr )
   {
      delete[] coefficient;
      coefficient = nullptr;
   }
   if( exponent != nullptr )
   {
      delete[] exponent;
      exponent = nullptr;
   }
}

// enable user to input a polynomial
void input( istream &inFile, int *&coefficient, int *&exponent, int &size )
{
   int numericString[ arraySize ] = {};

   inFile.read( reinterpret_cast< char * >( numericString ), 80 );

   size = arraySize;
   while( size > 0 && numericString[ size - 1 ] == 0 )
      size--;

   coefficient = new int[ size ];
   for( int i = 0; i < size; ++i )
      coefficient[ i ] = numericString[ i ];

   inFile.read( reinterpret_cast< char * >( numericString ), 80 );

   exponent = new int[ size ];
   for( int i = 0; i < size; ++i )
      exponent[ i ] = numericString[ i ];
}

// outputs the specified polynomial
void output( int *coefficient, int *exponent, int size )
{
   // the specified polynomial is zero polynomial
   if( size == 0 )
      cout << 0;
   else
   {
      if( coefficient[ 0 ] < 0 )
         cout << "-" << -coefficient[ 0 ];
      else if( coefficient[ 0 ] > 0 )
         cout << coefficient[ 0 ];

      if( exponent[ 0 ] > 0 )
      {
         if( exponent[ 0 ] == 1 )
            cout << "x";
         else
            cout << "x^" << exponent[ 0 ];
      }

      for( int i = 1; i < size; i++ )
      {
         if( coefficient[ i ] < 0 )
            cout << " - " << -coefficient[ i ];
         else if( coefficient[ i ] > 0 )
            cout << " + " << coefficient[ i ];

         if( exponent[ i ] > 0 )
         {
            if( exponent[ i ] == 1 )
               cout << "x";
            else
               cout << "x^" << exponent[ i ];
         }
      }
   }

   cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool hasZeroTerm( int *coefficient, int size )
{
   if( size != 0 )
      for( int i = 0; i < size; i++ )
         if( coefficient[ i ] == 0 )
            return true;

   return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( int *coefficient1, int *exponent1, int size1,
            int *coefficient2, int *exponent2, int size2 )
{
   if( size1 != size2 )
      return false;

   for( int i = 0; i < size1; i++ )
      if( coefficient1[ i ] != coefficient2[ i ] || exponent1[ i ] != exponent2[ i ] )
         return false;

   return true;
}

// polynomial1 = -polynomial2
void minus( int *&coefficient1, int *&exponent1, int &size1,
            int *coefficient2, int *exponent2, int size2 )
{
   size1 = size2;
   for( int i = 0; i < size1; i++ )
   {
      coefficient1[ i ] = -coefficient2[ i ];
      exponent1[ i ] = exponent2[ i ];
   }
}

// addend += adder
void addition(int*& addendCoef, int*& addendExpon, int& addendSize,
	int* adderCoef, int* adderExpon, int adderSize)
{
	int* sumCoef = new int[arraySize]();
	int* sumExpon = new int[arraySize]();
	int i = 0;
	int j = 0;
	int k = 0;

	//if is zero
   if (addendSize == 0)
   {
      k = adderSize;
      for (int a = 0; a < adderSize; a++)
      {
         sumCoef[a] = adderCoef[a];
         sumExpon[a] = adderExpon[a];
      }
   }
   else if (adderSize == 0)
   {
      k = addendSize;
      for (int a = 0; a < addendSize; a++)
      {
         sumCoef[a] = addendCoef[a];
         sumExpon[a] = addendExpon[a];
      }
   }
	else
	{
		while (true)
		{
			if (adderExpon[i] > addendExpon[j])
			{
				sumExpon[k] = adderExpon[i];
				sumCoef[k] = adderCoef[i];
				i++; k++;
			}
			else if (adderExpon[i] < addendExpon[j])
			{
				sumExpon[k] = addendExpon[j];
				sumCoef[k] = addendCoef[j];
				j++; k++;
			}
			else
			{
				sumExpon[k] = addendExpon[j];
				sumCoef[k] = addendCoef[j] + adderCoef[i];
				i++; j++; k++;
			}
			if (i == adderSize && j == addendSize)
				break;
		}
	}
   if(hasZeroTerm(sumCoef, k))
   {
      int bufferSize = 0;
      int *bufferCoef = new int[k]();
      int *bufferExpon = new int[k]();
      for (int i = 0; i < k; i++)
      {
         if (sumCoef[i])
         {
            bufferCoef[bufferSize] = sumCoef[i];
            bufferExpon[bufferSize] = sumExpon[i];
            bufferSize++;
         }
         
      }
      //copy buffer to sum
      k = bufferSize;
      for (int j = 0; j < bufferSize; j++)
      {
         sumCoef[j] = bufferCoef[j];
         sumExpon[j] = bufferExpon[j];
      }
      delete[] bufferCoef;
      delete[] bufferExpon;
      
   }
	if (addendSize != k)
	{
		addendCoef = new int[k];
		addendExpon = new int[k];
	}
	addendSize = k;
	for (int i = 0; i < addendSize; i++) // addend = sum
	{
		addendCoef[i] = sumCoef[i];
		addendExpon[i] = sumExpon[i];
	}

    
	delete[] sumCoef;
	delete[] sumExpon;
}

// minuend -= subtrahend
void subtraction( int *&minuendCoef, int *&minuendExpon, int &minuendSize,
                  int *subtrahendCoef, int *subtrahendExpon, int subtrahendSize )
{
   // buffer = 0
   int bufferSize = subtrahendSize;
   int *bufferCoef = new int[ bufferSize ]();
   int *bufferExpon = new int[ bufferSize ]();

   // buffer = -subtrahend
   minus( bufferCoef, bufferExpon, bufferSize, subtrahendCoef, subtrahendExpon, subtrahendSize );

   // minuend = minuend + buffer = minuend - subtrahend
   addition( minuendCoef, minuendExpon, minuendSize, bufferCoef, bufferExpon, bufferSize );

   delete[] bufferCoef;
   delete[] bufferExpon;

   if( minuendSize > 0 && minuendCoef[ 0 ] == 0 )
      cout << "Leading zeroes in minuend not allowed!\n";
}

// product = multiplicand * multiplier
void multiplication( int *multiplicandCoef, int *multiplicandExpon, int multiplicandSize,
                     int *multiplierCoef, int *multiplierExpon, int multiplierSize,
                     int *&productCoef, int *&productExpon, int &productSize )
{
   // product = 0;
   productSize = 0;

   int bufferSize = multiplicandSize;
   int *bufferCoef = new int[ bufferSize ]();
   int *bufferExpon = new int[ bufferSize ]();

   // if( multiplicand != 0 && multiplier != 0 )
   if( multiplicandSize != 0 && multiplierSize != 0 )
   {
       for (int i = 0; i < multiplierSize; i++)
       {
           //buffer = multiplier[i] * multiplicand
           for (int j = 0; j < multiplicandSize; j++)
           {
               bufferExpon[j] = multiplierExpon[i] + multiplicandExpon[j];
               bufferCoef[j] = multiplierCoef[i] * multiplicandCoef[j];
           }
           addition(productCoef, productExpon, productSize, bufferCoef, bufferExpon, bufferSize);
       }
   }

   delete[] bufferCoef;
   delete[] bufferExpon;

   if( productSize > 0 && productCoef[ 0 ] == 0 )
      cout << "Leading zeroes in product not allowed!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division( int *dividendCoef, int *dividendExpon, int dividendSize,
               int *divisorCoef, int *divisorExpon, int divisorSize,
               int *&quotientCoef, int *&quotientExpon, int &quotientSize,
               int *&remainderCoef, int *&remainderExpon, int &remainderSize )
{
   // remainder = dividend
   remainderSize = dividendSize;
   remainderCoef = new int[ remainderSize ]();
   remainderExpon = new int[ remainderSize ]();
   for( int i = 0; i < remainderSize; i++ )
   {
      remainderCoef[ i ] = dividendCoef[ i ];
      remainderExpon[ i ] = dividendExpon[ i ];
   }

   int monomialSize = 1;
   int *monomialCoef = new int[ 1 ]();
   int *monomialExpon = new int[ 1 ]();

   int bufferSize = 0;
   int *bufferCoef = nullptr;
   int *bufferExpon = nullptr;

   int tempCoef[ arraySize ] = {};
   int tempExpon[ arraySize ] = {};
   quotientSize = 0;

   while (remainderSize != 0 && (remainderExpon[0] >= divisorExpon[0]))
   {
       tempCoef[quotientSize] = remainderCoef[0] / divisorCoef[0];
       tempExpon[quotientSize] = remainderExpon[0] - divisorExpon[0];
       
       monomialExpon[0] = tempExpon[quotientSize];
       monomialCoef[0] = tempCoef[quotientSize];
       
       multiplication(divisorCoef, divisorExpon, divisorSize, monomialCoef, monomialExpon, 1, bufferCoef, bufferExpon, bufferSize);
       subtraction(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);
       quotientSize++;
   }

   quotientCoef = new int[ quotientSize ];
   quotientExpon = new int[ quotientSize ];
   for( int i = 0; i < quotientSize; ++i )
   {
      quotientCoef[ i ] = tempCoef[ i ];
      quotientExpon[ i ] = tempExpon[ i ];
   }

   delete[] monomialCoef;
   delete[] monomialExpon;

   delete[] bufferCoef;
   delete[] bufferExpon;

   if( quotientSize > 0 && quotientCoef[ 0 ] == 0 )
      cout << "Leading zeroes in quotient not allowed!\n";

   if( remainderSize > 0 && remainderCoef[ 0 ] == 0 )
      cout << "Leading zeroes in remainder not allowed!\n";
}
