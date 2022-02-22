#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

// HugeInt struct definition
struct HugeInt
{
   int size = 1;       // the number of digits of the integer; it can never be zero
   int *ptr = new int[ 1 ](); // used to store a nonnegative integer, one digit per element
};

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt hugeInt1, HugeInt hugeInt2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt hugeInt1, HugeInt hugeInt2 );

// --hugeInt
void decrement( HugeInt &hugeInt );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( HugeInt &minuend, HugeInt subtrahend );

// multiplicand *= multiplier
void multiAssign( HugeInt &multiplicand, HugeInt multiplier );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( HugeInt dividend, HugeInt divisor, HugeInt &quotient, HugeInt &remainder );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt );

// hugeInt1 = hugeInt2
void assign( HugeInt &hugeInt1, HugeInt hugeInt2 );

void reset( HugeInt &hugeInt );

const int maxSize = 200;

int main()
{
   int t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a % b != 0 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( ( a - b ) * static_cast< int >( log10( t ) ) > 95 )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         HugeInt dividend;
         HugeInt divisor;
         HugeInt quotient;
         HugeInt remainder;

         // put all digits of t into base
         HugeInt base;
         delete[] base.ptr;
         base.ptr = new int[ 10 ]();
         base.size = 0;
         for( int i = t; i > 0; i /= 10 )
            base.ptr[ base.size++ ] = i % 10;

         // dividend = pow( t, a )
         dividend.ptr[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiAssign( dividend, base );
            if( dividend.size > maxSize - base.size )
               break;
         }

         if( dividend.size > maxSize - base.size )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor.ptr[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
            {
               multiAssign( divisor, base );
               if( divisor.size > maxSize - base.size )
                  break;
            }

            if( divisor.size > maxSize - base.size )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               decrement( dividend ); // --dividend
               decrement( divisor );   // --divisor

               division( dividend, divisor, quotient, remainder );

               if( quotient.size > 1 && quotient.ptr[ quotient.size - 1 ] == 0 )
                  cout << "quotient has a leading zero!\n";

               if( remainder.size > 1 && remainder.ptr[ remainder.size - 1 ] == 0 )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size < 100 && isZero( remainder ) )
                  for( int i = quotient.size - 1; i >= 0; i-- )
                     cout << quotient.ptr[ i ];
               else
                  cout << "is not an integer with less than 100 digits.";
               cout << endl;
            }
         }

         delete[] dividend.ptr;
         delete[] divisor.ptr;
         delete[] quotient.ptr;
         delete[] remainder.ptr;
      }
   }

   system( "pause" );
}

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt hugeInt )
{
   return ( hugeInt.size == 1 && hugeInt.ptr[ 0 ] == 0 );
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt hugeInt1, HugeInt hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   for( int i = hugeInt1.size - 1; i >= 0; i-- )
      if( hugeInt1.ptr[ i ] != hugeInt2.ptr[ i ] )
         return false;

   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt hugeInt1, HugeInt hugeInt2 )
{


}

// --hugeInt
void decrement( HugeInt &hugeInt )
{
   HugeInt buffer;
   assign( buffer, hugeInt ); // buffer = hugeInt

   --buffer.ptr[ 0 ];
   for( int i = 0; i < buffer.size - 1; i++ )
      if( buffer.ptr[ i ] < 0 )
      {
         buffer.ptr[ i ] += 10;
         buffer.ptr[ i + 1 ]--;
      }

   if( buffer.size > 1 && buffer.ptr[ buffer.size - 1 ] == 0 )
      buffer.size--;

   if( buffer.size > 1 && buffer.ptr[ buffer.size - 1 ] == 0 )
      cout << "buffer has a leading zero!\n";

   assign( hugeInt, buffer ); // hugeInt = buffer

   delete[] buffer.ptr;
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraAssign( HugeInt &minuend, HugeInt subtrahend )
{
   if( equal( minuend, subtrahend ) )
   {
      reset( minuend );
      return;
   }

   HugeInt difference;



   delete[] difference.ptr;
}

// multiplicand *= multiplier
void multiAssign( HugeInt &multiplicand, HugeInt multiplier )
{
   HugeInt product;



   delete[] product.ptr;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( HugeInt dividend, HugeInt divisor, HugeInt &quotient, HugeInt &remainder )
{
   assign( remainder, dividend ); // remainder = dividend

   if( less( dividend, divisor ) )
      reset( quotient );
   else
   {
      HugeInt buffer;



      delete[] buffer.ptr;
   }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 )
      hugeInt.ptr[ 0 ] = 0;
   else
   {
      HugeInt buffer;
      assign( buffer, hugeInt ); // buffer = hugeInt

      hugeInt.size--;
      delete[] hugeInt.ptr;
      hugeInt.ptr = new int[ hugeInt.size ]();

      for( int i = 1; i <= hugeInt.size; i++ )
         hugeInt.ptr[ i - 1 ] = buffer.ptr[ i ];
   }
}

// hugeInt1 = hugeInt2; assignment
void assign( HugeInt &hugeInt1, HugeInt hugeInt2 )
{
   hugeInt1.size = hugeInt2.size;
   delete[] hugeInt1.ptr;
   hugeInt1.ptr = new int[ hugeInt1.size ];
   for( int i = 0; i < hugeInt1.size; i++ )
      hugeInt1.ptr[ i ] = hugeInt2.ptr[ i ];
}

void reset( HugeInt &hugeInt )
{
   hugeInt.size = 1;
   delete[] hugeInt.ptr;
   hugeInt.ptr = new int[ 1 ]();
}