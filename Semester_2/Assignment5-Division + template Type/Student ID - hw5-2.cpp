// HugeInteger test program.
#include <iostream>
#include <cstddef>
#include <cmath>
#include <ctime>
using namespace std;

const int maxSize = 200;

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
      myLast(),
      myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = value_type *;
   using const_iterator = const value_type *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   vector()
      : myData()
   {
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   vector( const size_type count )
      : myData()
   {



   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   vector( const vector &right )
      : myData()
   {



   }

   // Vector destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the vector.
   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   // Adds a new element at the end of the vector, after its current last element.
   // The content of val is copied (or moved) to the new element.
   // This effectively increases the container size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const value_type &val )
   {
      size_type originalSize = size();
      resize( originalSize + 1 );
      myData.myFirst[ originalSize ] = val;
   }

   // overloaded assignment operator
   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   vector& operator=( const vector &right )
   {
      if( this != &right ) // avoid self-assignment
      {
         size_type rightSize = right.size();
         if( rightSize > capacity() )
         {



            size_type newCapacity = capacity() * 3 / 2;
            if( newCapacity < rightSize )
               newCapacity = rightSize;



         }



      }

      return *this; // enables x = y = z, for example
   }

   // Resizes the container so that it contains "newSize" elements.
   // If "newSize" is smaller than the current container size,
   // the content is reduced to its first "newSize" elements, removing those beyond.
   // If "newSize" is greater than the current container size,
   // the content is expanded by inserting at the end as many elements as needed
   // to reach a size of "newSize".
   // The new elements are initialized as 0.
   // If "newSize" is also greater than the current container capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( const size_type newSize )
   {
      size_type originalSize = size();
      if( newSize > originalSize )
      {
         if( newSize > capacity() )
         {
            size_type newCapacity = capacity() * 3 / 2;
            if( newCapacity < newSize )
               newCapacity = newSize;



         }



      }



   }

   // Removes the last element in the vector,
   // effectively reducing the container size by one.
   void pop_back()
   {
      if( size() > 0 )
         --myData.myLast;
   }

   // Removes all elements from the vector (which are destroyed),
   // leaving the container with a size of 0.
   // A reallocation is not guaranteed to happen,
   // and the vector capacity is not guaranteed to change due to calling this function.
   void clear() // erase all
   {
      myData.myLast = myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myFirst );
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   iterator end()
   {
      return myData.myLast;
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myLast );
   }

   // Returns whether the vector is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.
   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   // Returns a reference to the element at position "pos" in the vector container.
   value_type& operator[]( const size_type pos )
   {
      if( pos >= static_cast< size_type >( myData.myLast - myData.myFirst ) )
      {
         cout << "vector subscript out of range\n";
         exit( 1 );
      }

      return myData.myFirst[ pos ];
   }

   // Returns a reference to the element at position "pos" in the vector container.
   const value_type& operator[]( const size_type pos ) const
   {
      if( pos >= static_cast< size_type >( myData.myLast - myData.myFirst ) )
      {
         cout << "vector subscript out of range\n";
         exit( 1 );
      }

      return myData.myFirst[ pos ];
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& front()
   {
      return *myData.myFirst;
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& front() const
   {
      return *myData.myFirst;
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

// determine if two Arrays are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const vector< Ty > &left, const vector< Ty > &right )
{



}


template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   HugeInteger( size_type n = 0 ); // constructor; construct a zero HugeInteger with size n

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy );

   ~HugeInteger(); // destructor; destroys the HugeInteger

   const HugeInteger& operator=( const HugeInteger &right ); // assignment operator

   bool operator==( const HugeInteger &right ) const; // less than or equal to

   bool operator<( const HugeInteger &right ) const;  // less than

   bool operator<=( const HugeInteger &right ) const; // less than or equal to

   // addition operator; HugeInteger += HugeInteger
   void operator+=( HugeInteger &op2 );

   // subtraction operator; HugeInteger -= HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   void operator-=( HugeInteger &op2 );

   // multiplication operator; HugeInteger *= HugeInteger
   void operator*=( HugeInteger &op2 );

   // division operator; HugeInteger / HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator/( HugeInteger &op2 );

   // modulus operator; HugeInteger % HugeInteger
   // provided that the divisor is not equal to 0
   HugeInteger operator%( HugeInteger &op2 );

   HugeInteger& operator++();     // prefix increment operator

   HugeInteger operator++( int ); // postfix increment operator

   HugeInteger& operator--();     // prefix decrement operator

   HugeInteger operator--( int ); // postfix decrement operator

   void convert( const value_type &number ); // convert an integer into a HugeInteger

   // compute base raised to the power of expon
   void power( HugeInteger &base, const value_type &expon );

   size_type size();

   // return true if and only if there is only one digit and this digit is zero
   bool isZero();

   bool leadingZero(); // return true if and only if the leftmost digit is zero

private:
   T integer;

   void divideByTen();   // divides a HugeInteger by 10
   void helpIncrement(); // increments a HugeInteger by 1
   void helpDecrement(); // decrements a HugeInteger by 1

}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger( size_type n )
   : integer( ( n == 0 ) ? 1 : n )
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger( const HugeInteger< T > &integerToCopy )
   : integer( integerToCopy.integer )
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T > &HugeInteger< T >::operator=( const HugeInteger< T > &right )
{
   if( &right != this ) // avoid self-assignment
      integer = right.integer;

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==( const HugeInteger< T > &right ) const
{
   return ( integer == right.integer );
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<( const HugeInteger< T > &right ) const
{



} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=( const HugeInteger< T > &right ) const
{
   return ( *this == right || *this < right );
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
void HugeInteger< T >::operator+=( HugeInteger< T > &op2 )
{
   size_type op1Size = integer.size();
   size_type op2Size = op2.integer.size();
   size_type sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   typename T::iterator it1 = integer.begin();
   typename T::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   typename T::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         *it3 -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.pop_back();

   if( sum.leadingZero() )
      cout << "sum has a leading zero!\n";

   *this = sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
void HugeInteger< T >::operator-=( HugeInteger< T > &op2 )
{
   HugeInteger zero;

   if( *this == op2 )
   {
      *this = zero;
      return;
   }

   HugeInteger difference( *this );




   if( difference.leadingZero() )
      cout << "difference has a leading zero!\n";

   *this = difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
void HugeInteger< T >::operator*=( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( isZero() || op2.isZero() )
   {
      *this = zero;
      return;
   }

	HugeInteger< T > product( integer.size() + op2.integer.size() );
   



   if( product.leadingZero() )
      cout << "product has a leading zero!\n";

   *this = product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( *this < op2 )
      return zero;




   return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%( HugeInteger< T > &op2 )
{
   HugeInteger< T > zero;
   if( *this < op2 )
      return zero;




   return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
   helpIncrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++( int )
{
   HugeInteger temp = *this; // hold current state of object
   helpIncrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
   helpDecrement(); // increment integer
   return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--( int )
{
   HugeInteger temp = *this; // hold current state of object
   helpDecrement();

   // return unincremented, saved, temporary object
   return temp; // value return; not a reference return
}

// convert an integer into a HugeInteger
template< typename T >
void HugeInteger< T >::convert( const value_type &number )
{
   size_type numDigits = 0;
   for( value_type i = number; i > 0; i /= 10 )
      integer[ numDigits++ ] = i % 10;
   integer.resize( numDigits );
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
   typename T::iterator it = integer.begin() + 1;
   for( ; it != integer.end(); ++it )
      *( it - 1 ) = *it;
   integer.pop_back();
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
   typename T::iterator it = integer.begin();
   ( *it )++;
   typename T::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      if( *it == 10 )
      {
         *it = 0;
         ( *it2 )++;
      }

   if( ( *it ) == 10 )
   {
      *( it ) = 0;
      integer.push_back( 1 );
   }
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
   typename T::iterator it = integer.begin();
   for( ; *it == 0; ++it )
      *it = 9;

   --( *it );

   if( leadingZero() )
      integer.pop_back();
}

template< typename T >
void HugeInteger< T >::power( HugeInteger< T > &base, const value_type &expon )
{
   ++( *this );
   for( value_type i = 0; i < expon; ++i )
   {
      *this *= base;
      if( integer.size() > maxSize - base.integer.size() )
         break;
   }
}

template< typename T >
typename HugeInteger< T >::size_type HugeInteger< T >::size()
{
   return integer.size();
}

// returns true if and only if the specified huge integer is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
   return ( integer.size() == 1 && integer.front() == 0 );
}

template< typename T >
bool HugeInteger< T >::leadingZero()
{
   return ( integer.size() > 1 && integer.back() == 0 );
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}

template< typename T >
void solution( T t, T a, T b )
{
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
      else if( ( a - b ) * static_cast< T >( log10( t ) ) > 95 )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         HugeInteger< vector< T > > base( 10 );
         base.convert( t ); // put all digits of t into base

         HugeInteger< vector< T > > dividend( 1 );
         dividend.power( base, a ); // dividend = pow( t, a )

         if( dividend.size() > maxSize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            HugeInteger< vector< T > > divisor( 1 );
            divisor.power( base, b ); // divisor = pow( t, b )

            if( divisor.size() > maxSize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               --dividend; // pow( t, a ) - 1
               --divisor;  // pow( t, b ) - 1

               HugeInteger< vector< T > > quotient = dividend / divisor;
               HugeInteger< vector< T > > remainder = dividend % divisor;

               if( quotient.leadingZero() )
                  cout << "quotient has a leading zero!\n";

               if( remainder.leadingZero() )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size() < 100 && remainder.isZero() )
                  cout << quotient << endl;
               else
                  cout << "is not an integer with less than 100 digits.\n";
            }
         }
      }
   }
}

int main()
{
   srand( static_cast< int >( time( 0 ) ) );

   int t1 = 0, a1 = 0, b1 = 0;
   unsigned int t2 = 0, a2 = 0, b2 = 0;
   long int t3 = 0, a3 = 0, b3 = 0;
   unsigned long int t4 = 0, a4 = 0, b4 = 0;
   long long int t5 = 0, a5 = 0, b5 = 0;
   unsigned long long int t6 = 0, a6 = 0, b6 = 0;
   switch( 1 + rand() % 6 )
   {
   case 1:
      solution( t1, a1, b1 );
      break;
   case 2:
      solution( t2, a2, b2 );
      break;
   case 3:
      solution( t3, a3, b3 );
      break;
   case 4:
      solution( t4, a4, b4 );
      break;
   case 5:
      solution( t5, a5, b5 );
      break;
   case 6:
      solution( t6, a6, b6 );
      break;
   default:
      cout << "Program should never get here!";
   }

   system( "pause" );
}