// HugeInteger test program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstdlib>
using std::srand;
using std::rand;

#include <string>
using std::string;

#include <ctime>
using std::time;

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
    using value_type = ValueType;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

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
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = Ty&;
    using const_reference = const Ty&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

private:
    using ScaryVal = VectorVal< Ty >;

public:
    using iterator = value_type*;
    using const_iterator = const value_type*;

    // empty container constructor (default constructor)
    // Constructs an empty container, with no elements.
    vector()
        : myData()
    {
    }

    // fill constructor
    // Constructs a container with "count" elements.
    // Each element is initialized as 0.
    vector(const size_type count)
        : myData()
    {
        myData.myFirst = new value_type[count]();
        myData.myLast = myData.myEnd = myData.myFirst + count;

    }

    // copy constructor
    // Constructs a container with a copy of each of the elements in "right",
    // in the same order.
    vector(const vector& right)
        : myData()
    {
        int size = right.size();
        int capacity = right.capacity();
        myData.myFirst = new value_type[capacity]();
        for (int i = 0; i < capacity; i++)
            myData.myFirst[i] = right.myData.myFirst[i];
        myData.myEnd = myData.myLast = myData.myFirst + size;
    }

    // Vector destructor
    // Destroys the container object.
    // Deallocates all the storage capacity allocated by the vector.
    ~vector()
    {
        if (myData.myFirst != nullptr)
            delete[] myData.myFirst;
    }

    // The vector is extended by inserting a new element before the element
    // at the specified position, effectively increasing the container size by one.
    // This causes an automatic reallocation of the allocated storage space
    // if and only if the new vector size surpasses the current vector capacity.
    // Relocates all the elements that were after "where" to their new positions.
    iterator insert(const_iterator where, const value_type& val)
    {
        if (where >= myData.myFirst && where <= myData.myLast)
        {
            size_type originalSize = size();
            size_type originalCapacity = capacity();
            if (originalSize == originalCapacity)
            {
                size_type newCapacity;
                if (originalCapacity <= 1)
                    newCapacity = originalCapacity + 1;
                else
                    newCapacity = originalCapacity * 3 / 2;
                pointer temp = myData.myFirst;
                myData.myFirst = new value_type[newCapacity]();
                iterator it2 = myData.myFirst;
                for (const_iterator it = temp; it != where; it++, it2++)
                    *it2 = *it;
                *it2 = val;
                iterator ans = it2;
                it2++;
                for (const_iterator it = where; it != myData.myLast; it++, it2++)
                    *it2 = *it;
                myData.myLast = myData.myFirst + originalSize + 1;
                myData.myEnd = myData.myFirst + newCapacity;
                delete[]temp;
                return ans;


            }
            else
            {
                iterator it = myData.myLast - 1;
                for (; it >= where; it--)
                    *(it + 1) = *it;
                it++;
                *it = val;
                myData.myLast = myData.myFirst + originalSize + 1;
                return it;

            }
        }
        else
            return nullptr;
    }

    // Removes from the vector either a single element (where).
    // This effectively reduces the container size by one, which is destroyed.
    // Relocates all the elements after the element erased to their new positions.
    iterator erase(const_iterator where)
    {
        if (where >= myData.myFirst && where < myData.myLast)
        {
            int there = where - myData.myFirst;
            for (int i = there; i < size() - 1; i++)
                myData.myFirst[i] = myData.myFirst[i + 1];
            myData.myLast--;

            return iterator(where);
        }
        else
            return nullptr;
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
        return const_iterator(myData.myFirst);
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
        return const_iterator(myData.myLast);
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
        return static_cast<size_type>(myData.myLast - myData.myFirst);
    }

    // Returns the size of the storage space currently allocated for the vector,
    // expressed in terms of elements.
    // This capacity is not necessarily equal to the vector size.
    // It can be equal or greater, with the extra space allowing to accommodate
    // for growth without the need to reallocate on each insertion.
    size_type capacity() const
    {
        return static_cast<size_type>(myData.myEnd - myData.myFirst);
    }

    // Returns a reference to the element at position "pos" in the vector container.
    value_type& operator[](const size_type pos)
    {
        if (pos >= static_cast<size_type>(myData.myLast - myData.myFirst))
        {
            cout << "vector subscript out of range\n";
            exit(1);
        }

        return myData.myFirst[pos];
    }

    // Returns a reference to the element at position "pos" in the vector container.
    const value_type& operator[](const size_type pos) const
    {
        if (pos >= static_cast<size_type>(myData.myLast - myData.myFirst))
        {
            cout << "vector subscript out of range\n";
            exit(1);
        }

        return myData.myFirst[pos];
    }

private:
    ScaryVal myData;
};

// determine if two Arrays are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const vector< Ty >& left, const vector< Ty >& right)
{
    if (left.size() != right.size())
        return false;
    for (int i = 0; i < left.size(); i++)
        if (left[i] != right[i])
            return false;
    return true;


}


template< typename T >
class HugeInteger
{
    template< typename U >
    friend ostream& operator<<(ostream& output, HugeInteger< U > hugeInteger);
public:
    HugeInteger(unsigned int n = 0); // constructor; construct a zero HugeInteger with size n

    // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
    HugeInteger(const HugeInteger& integerToCopy);

    // Constructs a HugeInteger with right.size() elements.
    // Each element is initialized as the correcponding element in right.
    HugeInteger(string buf);

    ~HugeInteger(); // destructor; destroys the HugeInteger

    bool operator==(const HugeInteger& right) const; // less than or equal to

    bool operator<(const HugeInteger& right) const;  // less than

    bool operator<=(const HugeInteger& right) const; // less than or equal to

    HugeInteger square(); // the square of HugeInteger
    HugeInteger squareRoot(); // the square root of HugeInteger

    bool isZero() const;           // return true if and only if all digits are zero
private:
    vector< T > integer;

    const T tenThousand = 10000;

    //   const T thousand = 1000;
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
    : integer((n == 0) ? 1 : n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger< T >& integerToCopy)
    : integer(integerToCopy.integer)
{
}

// Constructs a HugeInteger with right.size() elements.
// Each element is initialized as the correcponding element in right.
template< typename T >
HugeInteger< T >::HugeInteger(string buf)
{
    T digits[1011] = {};
    size_t last = buf.size() - 1;
    for (size_t i = 0; i <= last; ++i)
        digits[i] = static_cast<T>(buf[last - i]) - '0';

    for (size_t i = 0; i <= last; i += 4)
    {
        T bigDigit = digits[i] +
            digits[i + 1] * 10 +
            digits[i + 2] * 100 +
            digits[i + 3] * 1000;

        integer.insert(integer.end(), bigDigit);
    }
}

/*
template< typename T >
HugeInteger< T >::HugeInteger( string buf )
{
   T digits[ 1011 ] = {};
   size_t last = buf.size() - 1;
   for( size_t i = 0; i <= last; ++i )
      digits[ i ] = static_cast< T >( buf[ last - i ] ) - '0';

   for( size_t i = 0; i <= last; i += 3 )
   {
      T bigDigit = digits[ i ] + digits[ i + 1 ] * 10 + digits[ i + 2 ] * 100;

      integer.insert( integer.end(), bigDigit );
   }
}
*/

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(const HugeInteger< T >& right) const
{
    return (integer == right.integer);
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<(const HugeInteger< T >& right) const
{
    /*    if (right.integer[0] == 4)
            cout << integer.size() << " " << right.integer.size() << endl;*/
    if (integer.size() != right.integer.size())
        return integer.size() < right.integer.size();
    for (int i = integer.size() - 1; i >= 0; i--)
        if (integer[i] != right.integer[i])
            return integer[i] < right.integer[i];
    return 0;
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(const HugeInteger< T >& right) const
{
    return (*this == right || *this < right);
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square()
{
    HugeInteger zero;
    if (isZero())
        return zero;

    size_t squareSize = 2 * integer.size();
    HugeInteger< T > square(squareSize);

    for (int i = 0; i < integer.size(); i++)
        for (int j = 0; j < integer.size(); j++)
        { 
            if (square.integer[i + j] > 2000000000)
            {
                square.integer[i + j + 1] += square.integer[i + j] / 10000;
                square.integer[i + j] %= 10000;
            }
            square.integer[i + j] += integer[i] * integer[j];
        }//modified
    for (int i = 0; i < squareSize - 1; i++)
        if (square.integer[i] > 10000)
        {
            square.integer[i + 1] += square.integer[i] / 10000;
            square.integer[i] %= 10000;
        }
    while (square.integer[square.integer.size() - 1] == 0)
        square.integer.erase(square.integer.end() - 1);
    HugeInteger< T > square1(square.integer.size());
    for (int i = 0; i < square.integer.size(); i++)
        square1.integer[i] = square.integer[i];
    return square1;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot()
{
    HugeInteger zero;
    if (isZero())
        return zero;

    size_t sqrtSize = (integer.size() + 1) / 2;
    HugeInteger< T > sqrt(sqrtSize);


    HugeInteger< T > low(sqrtSize);
    HugeInteger< T > high(sqrtSize);



    for (int n = sqrt.integer.size() - 1; n >= 0; n--)
    {

        high.integer[n] = 9999;
        low.integer[n] = 0;


        //4 space thung...
        while (low.integer[n] <= high.integer[n]) {
            sqrt.integer[n] = (high.integer[n] + low.integer[n]) / 2;
            HugeInteger< T > sqrtMiddle(sqrt.square());
            if (sqrtMiddle.integer == integer)
                return sqrt;
            if (*this < sqrtMiddle)
                high.integer[n] = sqrt.integer[n];
            else
                low.integer[n] = sqrt.integer[n];
            if (low.integer[n] + 1 == high.integer[n]) {
                sqrt.integer[n] = low.integer[n];
                break;
            }
        }
    }











    return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero() const
{
    typename vector< T >::const_iterator it = integer.begin();
    for (; it != integer.end(); ++it)
        if (*it != 0)
            return false;

    return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
    typename vector< T >::iterator it = hugeInteger.integer.end() - 1;
    output << *it;
    for (--it; it != hugeInteger.integer.begin() - 1; --it)
        output << setw(4) << setfill('0') << *it;

    return output; // enables cout << x << y;
}

/*
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename vector< T >::iterator it = hugeInteger.integer.end() - 1;
   output << *it;
   for( --it; it != hugeInteger.integer.begin() - 1; --it )
      output << setw( 3 ) << setfill( '0' ) << *it;

   return output; // enables cout << x << y;
}
*/

template< typename T >
void testHugeInteger()
{
    int numCases;
    cin >> numCases;
    for (int i = 1; i <= numCases; ++i)
    {
        string buf;
        cin >> buf;

        HugeInteger< T > hugeInteger(buf);

        cout << hugeInteger.squareRoot() << endl;

        if (i < numCases)
            cout << endl;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    switch ( 1 + rand() % 6 )
    {
    case 1:
        testHugeInteger< int >();
        break;
    case 2:
        testHugeInteger< unsigned int >();
        break;
    case 3:
        testHugeInteger< long int >();
        break;
    case 4:
        testHugeInteger< unsigned long int >();
        break;
    case 5:
        testHugeInteger< long long int >();
        break;
    case 6:
        testHugeInteger< unsigned long long int >();
        break;
    default:
        cout << "Program should never get here!";
    }

    system("pause");
}
