#include "vector.h" // include definition of class vector 


// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
{
    myFirst = new value_type[count]();
    myLast = myEnd = &myFirst[count - 1] + 1;

}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{
    size_type rightSize = right.myLast - right.myFirst;
    size_type rightCapacity = right.myEnd - right.myFirst;
    myFirst = new value_type[rightCapacity]();
    for (int i = 0; i < rightSize; i++) myFirst[i] = *(right.myFirst+i);
    myEnd =myLast = myFirst + rightSize;
    // myFirst + rightCapacity;
    


}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// Adds a new element at the end of the vector, after its current last element.
// The content of val is copied to the new element.
// This effectively increases the vector size by one,
// which causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
void vector::push_back( const value_type &val )
{
   size_type originalSize = size();
   resize( originalSize + 1 );
   myFirst[ originalSize ] = val;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
      size_type rightSize = right.myLast - right.myFirst;
      if( rightSize > capacity() )
      {



         size_type newCapacity = capacity() * 3 / 2;
         if( newCapacity < rightSize )
            newCapacity = rightSize;
         delete[] myFirst;
         myFirst = new value_type[newCapacity + 1]();
         
         myEnd = myFirst + newCapacity;

         
      }
      for (int i = 0; i < rightSize; i++) myFirst[i] = *(right.myFirst + i);
      myLast = myFirst + rightSize;
      //for (int i = 0; i < rightSize; i++) cout << myFirst[i] << " ";
      //cout << endl;

   }

   return *this; // enables x = y = z, for example
}

// Resizes the vector so that it contains newSize elements.
// If newSize is smaller than the current vector size,
// the content is reduced to its first newSize elements, removing those beyond.
// If newSize is greater than the current vector size,
// the content is expanded by inserting at the end
// as many elements as needed to reach a size of newSize.
// The new elements are initialized as 0.
// If newSize is also greater than the current vector capacity,
// an automatic reallocation of the allocated storage space takes place.
void vector::resize( const size_type newSize )
{
   size_type originalSize = size();
   if( newSize > originalSize )
   {
      if( newSize > capacity() )
      {
         size_type newCapacity = capacity() * 3 / 2;
         if( newCapacity < newSize )
            newCapacity = newSize;
         value_type* tempPtr = myFirst;
         //for (int i = 0; i < originalSize; i++) cout << tempPtr[i] << " ";
         myFirst = new value_type[newCapacity+1]();
         for (int i = 0; i < originalSize; i++) myFirst[i] = *(tempPtr + i);
         //for (int i = 0; i < originalSize; i++) cout << myFirst[i] << " ";
         myEnd = myFirst + newCapacity;

         delete[] tempPtr;
      }
      


   }
   myLast = myFirst + newSize;
   /*
   cout << endl;
   for (int i = 0; i < newSize; i++) cout << myFirst[i] << " ";
   cout << endl;*/
}

// Removes the last element in the vector,
// effectively reducing the container size by one.
void vector::pop_back()
{
   if( size() > 0 )
      --myLast;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
   return myFirst;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
   return myLast;
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty()
{
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return static_cast< size_type >( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::at( const size_type pos )
{
   return myFirst[ pos ];
}
