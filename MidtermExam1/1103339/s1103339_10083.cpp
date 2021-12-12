// Huge integer division
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

#include<cstring>
using std::memset;

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// --hugeInt
void decrement( int hugeInt[], int &size );

// multiplicand *= multiplier
void multiAssign( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
   int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// product = multiplicand * multiplier * ( 10 ^ multiplierPos )
void multiplication( int multiplicand[], int multiplier, int product[],
   int multiplicandSize, int multiplierPos, int &productSize );

// minuend -= subtrahend
void subtraAssign( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize );

const int arraySize = 200;

int main(){

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
         int dividend[ arraySize ] = {};
         int divisor[ arraySize ] = {};
         int quotient[ arraySize ] = {};
         int remainder[ arraySize ] = {};

         int dividendSize = 1;
         int divisorSize = 1;
         int quotientSize = 1;
         int remainderSize = 1;

         // put all digits of t into base
         int base[ arraySize ] = {};
         int baseSize = 0;
         for( int i = t; i > 0; i /= 10 )
            base[ baseSize++ ] = i % 10;

         // dividend = pow( t, a )
         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiAssign( dividend, base, dividendSize, baseSize );
            if( dividendSize > arraySize )
               break;
         }

         if( dividendSize > arraySize )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
               multiAssign( divisor, base, divisorSize, baseSize );

            decrement( dividend, dividendSize ); // --dividend
            decrement( divisor, divisorSize );   // --divisor

            division( dividend, divisor, quotient, remainder,
               dividendSize, divisorSize, quotientSize, remainderSize );

            // quotient is an integer with less than 100 digits
            if( quotientSize < 100 && isZero( remainder, remainderSize ) )
               for( int i = quotientSize - 1; i >= 0; i-- )
                  cout << quotient[ i ];
            else
               cout << "is not an integer with less than 100 digits.";
            cout << endl;
         }
      }
   }
}

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size )
{
   for( int i = 0; i < size; i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )//ok?
{
    int check = 0;

    if (size1 < size2)
        check = 1;
    else if (size1 > size2)
        check = 0;
    else
        for (int i = size1 - 1; i >= 0; i--)
        {
            if (hugeInt1[i] < hugeInt2[i])
            {
                check = 1;
                break;
            }
            else if (hugeInt1[i] > hugeInt2[i])
            {
                check = 0;
                break;
            }
        }


    return check;

}

// --hugeInt
void decrement( int hugeInt[], int &size )//ok
{
    hugeInt[0]--;
    
    for (int i = 0; i < size; i++)
    {
        if (hugeInt[i] < 0)
        {
            hugeInt[i + 1]--;
            hugeInt[i] += 10;
        }
    }

    for (int i = size - 1; i >= 0; i--)
    {
        if (hugeInt[i] == 0)
            size--;
        else
            break;
    }


}

// multiplicand *= multiplier
void multiAssign( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize )//ok
{
    //initialize product
    int product[arraySize] = {};
    int productSize = multiplicandSize + multiplierSize; 


    //multiplication
    for (int i = 0; i < multiplicandSize; i++)
        for (int j = 0; j < multiplierSize; j++)
        {
            product[i + j] += multiplicand[i] * multiplier[j];
        }

    //upward
    for (int i = 0; i < productSize; i++)
    {
        if (product[i] > 9)
        {
            product[i + 1] += product[i] / 10;
            product[i] %= 10;
        }
    }

    //get rid of zero
    for (int i = productSize - 1; i >= 0; i--)
    {
        if (product[i] == 0)
            productSize--;
        else
            break;
    }

    //multiplicand = product
    multiplicandSize = productSize;
    for (int i = 0; i < productSize; i++)
        multiplicand[i] = product[i];

}

void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
    if (isZero(dividend, dividendSize))
    {
        memset(quotient, 0, 200);
        memset(remainder, 0, 200);
        return;
    }

    //remainder = dividend
    remainderSize = dividendSize;
    for (int i = 0; i < dividendSize; i++)
    {
        remainder[i] = dividend[i];
    }

    //if dividend < divisor
    if (less(dividend, divisor, dividendSize, divisorSize))
    {
        memset(quotient, 0, 200);
        return;
    }

    int n = dividendSize - divisorSize;

    //initialize buffer & buffer = divisor shift left by n positions
    int buffer[arraySize] = {};
    int bufferSize = divisorSize + n;
    multiplication(divisor, 1, buffer, divisorSize, n, bufferSize);

    //quotient and quotientSize setting
    quotientSize = n;
    if (!less(dividend, buffer, dividendSize, bufferSize))
    {
        quotientSize++;
    }
    memset(quotient, 0, 200);

    int a = divisor[divisorSize - 1];
    int j = dividendSize - 1;
    for (int i = dividendSize - divisorSize; i >= 0; i--, j--)
    {
        int b = 10 * remainder[j + 1] + remainder[j];
        if (a <= b)
        {
            quotient[i] = b / a;
            multiplication(divisor, quotient[i], buffer, divisorSize, i, bufferSize);
            while (less(remainder, buffer, remainderSize, bufferSize))
            {
                quotient[i]--;
                multiplication(divisor, quotient[i], buffer, divisorSize, i, bufferSize);
            }
            subtraAssign(remainder, buffer, remainderSize, bufferSize);
        }
    }

}

void multiplication( int multiplicand[], int multiplier, int product[],
   int multiplicandSize, int multiplierPos, int &productSize )
{
    //initialize buffer
    int buffer[arraySize] = {};
    int bufferSize = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (multiplier == 0)
            break;
        else
        {
            buffer[i] = multiplier % 10;
            multiplier /= 10;
            bufferSize++;
        }
    }

    //buffer *= Pos
    int ten10[2] = { 0 , 1 };
    for (int i = 0; i < multiplierPos; i++)
    {
        multiAssign(buffer, ten10, bufferSize, 2);
    }

    //product = multiplicand
    productSize = multiplicandSize;
    for (int i = 0; i < multiplicandSize; i++)
    {
        product[i] = multiplicand[i];
    }

    multiAssign(product, buffer, productSize, bufferSize);
}

void subtraAssign( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize )
{
    //minis
    for (int i = 0; i < subtrahendSize; i++)
    {
        minuend[i] -= subtrahend[i];
    }

    //downward
    for (int i = 0; i < minuendSize; i++)
    {
        while (minuend[i] < 0)
        {
            minuend[i + 1]--;
            minuend[i] += 10;
        }
    }

    //get rid of leading zeros
    for (int i = minuendSize - 1; i >= 0; i--)
    {
        if (minuend[i] == 0)
            minuendSize--;
        else
            break;
    }
}