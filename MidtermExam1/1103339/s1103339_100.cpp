#include <iostream>
using namespace std;

// returns the maximum cycle-length over all integers
// between and including first and last
int maxCycleLength( int first, int last );

int cycleLength( int n ); // returns the cycle-length of n

int main()
{
   int i, j;
   while( cin >> i >> j )
   {
      cout << i << ' ' << j << ' ';

      if( i > j )
      {
         int buf = i;
         i = j;
         j = buf;
      }

      cout << maxCycleLength( i, j ) << endl; // i < j
   }
}

int maxCycleLength( int first, int last )
{
    if (first == last)
    {
        return cycleLength(first);
    }
    else if (cycleLength(first) > cycleLength(last))
    {
        return maxCycleLength(first, last - 1);
    }
    else
    {
        return maxCycleLength(first + 1, last);
    }


}

int cycleLength( int n )
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        if (n % 2 != 0)
        {
            return 1 + cycleLength(n * 3 + 1);
        }
        else
        {
            return 1 + cycleLength(n / 2);
        }
    }

}