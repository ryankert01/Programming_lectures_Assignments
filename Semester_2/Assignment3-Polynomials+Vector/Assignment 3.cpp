// Polynomial division provided that the quotient and remainder have integer coefficients

#include <fstream>
using std::ifstream;
using std::ios;

#include "Polynomial.h" // include definition of class Polynomial

void load( ifstream &inFile, int &numTerms, int coefficient[], int exponent[] );

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

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      int coefficient[ arraySize ] = {};
      int exponent[ arraySize ] = {};
      int numTerms;

      load( inFile, numTerms, coefficient, exponent );
      Polynomial dividend( numTerms, coefficient, exponent );

      load( inFile, numTerms, coefficient, exponent );
      Polynomial divisor( numTerms, coefficient, exponent );

      cout << "dividend:  ";
      dividend.output();

      cout << " divisor:  ";
      divisor.output();

      // quotient = dividend / divisor
      Polynomial quotient( dividend.division( divisor ) );

      // remainder = dividend % divisor
      Polynomial remainder( dividend.modulus( divisor ) );

      // thus, dividend == divisor * quotient + remainder

      cout << "quotient:  ";
      quotient.output();
      cout << "remainder:  ";
      remainder.output();
      cout << endl;

      if( quotient.hasZeroTerm() || remainder.hasZeroTerm() )
         cout << "quotient or remainder has a zero term!\n";
      else
      {
         // buffer = divisor * quotient
         Polynomial buffer( divisor.multiplication( quotient ) );

         if( buffer.hasZeroTerm() )
            cout << "buffer has a zero term!\n";
         else
         {
            // buffer = buffer + remainder = divisor * quotient + remainder
            buffer.addition( remainder );

            if( buffer.hasZeroTerm() )
               cout << "buffer has a zero term!\n";
            else
               // if buffer != dividend, an error occurred!
               if( buffer.equal( dividend ) )
                  numErrors--;
         }
      }
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

void load( ifstream &inFile, int &numTerms, int coefficient[], int exponent[] )
{
   inFile.read( reinterpret_cast< char * >( coefficient ), arraySize * sizeof( int ) );
   inFile.read( reinterpret_cast< char * >( exponent ), arraySize * sizeof( int ) );

   numTerms = arraySize;
   while( numTerms > 0 && coefficient[ numTerms - 1 ] == 0 )
      numTerms--;
}