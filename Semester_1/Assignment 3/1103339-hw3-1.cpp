#include <iostream>
#include <cstring>
using namespace std;

// product = multiplicand * multiplier
void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize );

int main()
{
   char strX[ 251 ];
   char strY[ 251 ];

   while( cin >> strX >> strY )
   {
      int multiplicand[ 250 ] = {};
      int multiplicandSize = strlen( strX );
      for( int i = 0; i < multiplicandSize; i++ )
         multiplicand[ multiplicandSize - i - 1 ] = strX[ i ] - '0';

      int multiplier[ 250 ] = {};
      int multiplierSize = strlen( strY );
      for( int i = 0; i < multiplierSize; i++ )
         multiplier[ multiplierSize - i - 1 ] = strY[ i ] - '0';

      int product[ 500 ] = {};
      int productSize = multiplicandSize + multiplierSize;

      multiplication( multiplicand, multiplier, product, multiplicandSize, multiplierSize, productSize );

      for( int i = productSize - 1; i >= 0; i-- )
         cout << product[ i ];
      cout << endl;
   }

   return 0;
}

void multiplication(int multiplicand[], int multiplier[], int product[],
    int multiplicandSize, int multiplierSize, int& productSize)
{
    for (int i = 0; i < multiplierSize; i++)
    {
        for (int n = 0; n < multiplicandSize; n++)
        {
            product[i + n] += multiplicand[n] * multiplier[i];
        }
    }
    for (int i = 0; i < productSize; i++)
    {
        product[i + 1] += product[i] / 10;
        product[i] %= 10;
    }

    
    for (int i = productSize; i > 0; i--)
    {
        if (product[i-1] != 0)
        {
            productSize = i;
            break;
        } 
        if (i-1 == 0)
        {
            productSize = 1;
        }
    }
}