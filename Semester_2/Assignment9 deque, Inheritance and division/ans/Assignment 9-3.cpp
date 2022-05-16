#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <deque>
#include "deque.h"

void testAssignment1();
void testAssignment2();
void testAssignment3();
void testAssignment4();
void testAssignment();
bool equal( std::deque< int > &deque1, deque< int > &deque2 );

const unsigned int number = 200;

int main()
{
   testAssignment1();
   testAssignment2();
   testAssignment3();

   for (unsigned int seed = 1; seed <= 10; seed++)
   {
       srand(seed);
       testAssignment4();
   }
   cout << endl;
   

   for( unsigned int seed = 1; seed <= 10; seed++ )
   {
      srand( seed );
      testAssignment();
   }
   cout << endl;

   system( "pause" );
}

void testAssignment1()
{
   std::deque< int > deque1;
   deque< int > deque2;
   for( unsigned int j = 1; j <= 32; j++ )
   {
      deque1.push_back( j );
      deque2.push_back( j );
   }

   for( unsigned int i = 0; i < 3; i++ )
   {
      std::deque< int > deque3;
      deque< int > deque4;
      for( unsigned int j = 1; j <= 9 + i; j++ )
      {
         deque3.push_back( j );
         deque4.push_back( j );
      }

      for( unsigned int j = 10 + i; j <= 29 + i; j++ )
      {
         deque3.push_front( j );
         deque4.push_front( j );
      }


      deque3 = deque1;
      deque4 = deque2;

      if( equal( deque3, deque4 ) )
         cout << "Correct!\n\n";
      else
         cout << "Incorrect!\n\n";

      //deque4.print();
   }
}

void testAssignment2()
{
   std::deque< int > deque1;
   deque< int > deque2;
   for( unsigned int j = 1; j <= 32; j++ )
   {
      deque1.push_back( j );
      deque2.push_back( j );
   }

   std::deque< int > deque3;
   deque< int > deque4;
   for( unsigned int j = 1; j <= 11; j++ )
   {
      deque3.push_back( j );
      deque4.push_back( j );
   }

   for( unsigned int j = 12; j <= 31; j++ )
   {
      deque3.push_front( j );
      deque4.push_front( j );
   }

   deque3.push_back( 32 );
   deque4.push_back( 32 );


   deque3 = deque1;
   deque4 = deque2;

   if( equal( deque3, deque4 ) )
      cout << "Correct!\n\n";
   else
      cout << "Incorrect!\n\n";
}

void testAssignment3()
{
    unsigned int numErrors = number;
    unsigned int length;
    int value;
    for (unsigned int i = 0; i < number; i++)
    {
        std::deque< int > deque1;
        deque< int > deque2;
        length = rand() % 200;
        for (unsigned int j = 0; j < length; j++)
        {
            value = 1 + rand() % 99;
            deque1.push_front(value);
            deque2.push_front(value);
        }

        std::deque< int > deque3;
        deque< int > deque4;
        length = rand() % 200;
        for (unsigned int j = 0; j < length; j++)
        {
            value = 1 + rand() % 99;
            deque3.push_front(value);
            deque4.push_front(value);
        }

        deque3 = deque1;
        deque4 = deque2;

        if (equal(deque3, deque4))
            numErrors--;
    }

    cout << "There are " << numErrors << " errors\n";
}

void testAssignment4()
{
    unsigned int numErrors = number;
    unsigned int length;
    for (unsigned int i = 0; i < number; i++)
    {
        deque< int > deque1;
        length = rand() % 200;
        for (unsigned int j = 0; j < length; j++)
            deque1.push_front(1 + rand() % 99);

        deque< int > deque2;
        length = rand() % 200;
        for (unsigned int j = 0; j < length; j++)
            deque2.push_front(1 + rand() % 99);

        int** mapBefore = *(reinterpret_cast< int*** >(&deque2));
        size_t mapSizeBefore = *(reinterpret_cast< size_t * >(&deque2) + 1);
        size_t myOffBefore = *(reinterpret_cast< size_t * >(&deque2) + 2);
        size_t mySizeBefore = *(reinterpret_cast< size_t * >(&deque2) + 3);

        if (mapSizeBefore == 0 || mySizeBefore == 0)
        {
            numErrors--;
            continue;
        }

        size_t first = myOffBefore / 4 % mapSizeBefore;
        size_t last = (myOffBefore + mySizeBefore - 1) / 4 % mapSizeBefore;
        size_t numRows = (last - first + 1) % mapSizeBefore;

        int** addressBefore = new int* [mapSizeBefore]();

        size_t rowBefore = first;
        for (size_t i = 0; i < numRows; ++i)
        {
            addressBefore[rowBefore] = mapBefore[rowBefore];
            rowBefore = (rowBefore + 1) % mapSizeBefore;
        }

        deque2 = deque1;

        int** mapAfter = *(reinterpret_cast< int*** >(&deque2));
        size_t mapSizeAfter = *(reinterpret_cast< size_t * >(&deque2) + 1);
        size_t myOffAfter = *(reinterpret_cast< size_t * >(&deque2) + 2);
        size_t mySizeAfter = *(reinterpret_cast< size_t * >(&deque2) + 3);

        if (mapSizeAfter == 0 || mySizeAfter == 0)
        {
            numErrors--;
            continue;
        }

        last = (myOffAfter + mySizeAfter - 1) / 4 % mapSizeAfter;
        if (numRows >(last - first + 1) % mapSizeAfter)
            numRows = (last - first + 1) % mapSizeAfter;

        int** addressAfter = new int* [mapSizeAfter]();
        size_t rowAfter = first;
        for (size_t i = 0; i < numRows; ++i)
        {
            addressAfter[rowAfter] = mapAfter[rowAfter];
            rowAfter = (rowAfter + 1) % mapSizeAfter;
        }

        bool correct = true;
        rowBefore = first;
        rowAfter = first;
        for (size_t i = 0; i < numRows; ++i)
        {
            if (addressBefore[rowBefore] != addressAfter[rowAfter])
            {
                correct = false;
                break;
            }
            rowBefore = (rowBefore + 1) % mapSizeBefore;
            rowAfter = (rowAfter + 1) % mapSizeAfter;
        }

        if (correct)
            numErrors--;
    }

    cout << "There are " << numErrors << " errors.\n";
}

void testAssignment()
{
   unsigned int numErrors = number;
   unsigned int length;
   int value;
   for( unsigned int i = 0; i < number; i++ )
   {
      std::deque< int > deque1;
      deque< int > deque2;
      length = rand() % 200;
      //length = 30;
      for( unsigned int j = 0; j < length; j++ )
      {
         value = 1 + rand() % 99;
         deque1.push_front( value );
         deque2.push_front( value );
      }


      size_t mapSize1 = *(reinterpret_cast<size_t*>(&deque1) + 2);
      size_t mapSize2 = *(reinterpret_cast<size_t*>(&deque2) + 1);
      //cout << "mapSize : " << mapSize1 << " " << mapSize2 << endl;
      //deque2.print();
      size_t len1 = length;

      std::deque< int > deque3;
      deque< int > deque4;
      length = rand() % 200;
      //length = 24;
      for( unsigned int j = 0; j < length; j++ )
      {
         value = 1 + rand() % 99;
         deque3.push_front( value );
         deque4.push_front( value );
      }

      mapSize1 = *(reinterpret_cast<size_t*>(&deque3) + 2);
      mapSize2 = *(reinterpret_cast<size_t*>(&deque4) + 1);
      //cout << "mapSize : " << mapSize1 << " " << mapSize2 << endl;
      //deque4.print();


      size_t len2 = length;

      deque3 = deque1;
      deque4 = deque2;
      //deque4.print();
      

      if (equal(deque3, deque4))
          numErrors--;
      else{
          cout << len1 << " " << len2 << endl;deque4.printInfo();}
   }

   cout << "There are " << numErrors << " errors\n";
}

bool equal( std::deque< int > &deque1, deque< int > &deque2 )
{
   int **map1 = *( reinterpret_cast< int *** > ( &deque1 ) + 1 );
   size_t mapSize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 2 );
   size_t myOff1 = *( reinterpret_cast< size_t * >( &deque1 ) + 3 );
   size_t mySize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 4 );

   int **map2 = *( reinterpret_cast< int *** > ( &deque2 ) );
   size_t mapSize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 1 );
   size_t myOff2 = *( reinterpret_cast< size_t * >( &deque2 ) + 2 );
   size_t mySize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 3 );

   if (mapSize1 != mapSize2) {

       cout << "mapSize wrong!   ";
       cout << mapSize1 << " " << mapSize2 << endl;
       return false;
   }

   if (mapSize2 == 0)
       if (mySize2 == 0 && myOff2 == 0 && map2 == nullptr)
           return true;
       else { return false; }


   if (myOff1 != myOff2)
   {
       cout << mapSize1 << " " << mapSize2 << endl;
       cout << "OFf woring!";
       cout << myOff1 << " " << myOff2 << endl;
       cout << "mySize : " << mySize1 << " " << mySize2 << endl;
       return false; ;
   }



   if (mySize1 != mySize2) {
       cout << "mySize wrong!\n";
       return false;
   }

   size_t row, col;
   for( size_t i = myOff1; i < myOff1 + mySize1; ++i/*, ++it2*/ )
   {
      row = ( i / 4 ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % 4;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
      }
   }

   return true;
}