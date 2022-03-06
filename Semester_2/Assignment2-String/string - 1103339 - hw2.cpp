#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
    : bx(),
    mySize(0),
    myRes(15)
{
}

string::string(const char* const ptr, const size_type count)
    : bx(),
    mySize(0),
    myRes(15)
{
    mySize = count;
    myRes = (mySize / 16) * 16 + 15;
    if (myRes < 16) {
        for (size_t i = 0; i <= mySize; i++) {
            bx.buf[i] = ptr[i];
        }
        bx.buf[mySize] = '\0';
    }
    else {
        bx.ptr = new value_type[myRes + 1]();
        for (size_t i = 0; i <= mySize; i++) {
            bx.ptr[i] = ptr[i];
        }
        bx.ptr[mySize] = '\0';
    }

}

string::string(const size_type count, const char ch)
    : bx(),
    mySize(0),
    myRes(15)
{
    // construct from count * ch
    mySize = count;
    if (count > 15)
    {
        myRes = (mySize / 16) * 16 + 15;
        bx.ptr = new value_type[myRes + 1]();
        for (size_t i = 0; i < mySize; i++) {
            bx.ptr[i] = ch;
        }
        bx.ptr[mySize] = '\0';
    }
    else {
        for (size_t i = 0; i < mySize; i++) {
            bx.buf[i] = ch;
        }
        bx.buf[mySize] = '\0';
    }


}

string::string(const string& right)
    : bx(),
    mySize(0),
    myRes(15)
{
    mySize = right.mySize;
    myRes = (mySize / 16) * 16 + 15;
    if (right.myRes < 16) {
        for (size_t i = 0; i < mySize; i++) {
            bx.buf[i] = right.bx.buf[i];
        }
        bx.buf[mySize] = '\0';
    }
    else {
        bx.ptr = new value_type[myRes + 1]();
        for (size_t i = 0; i < mySize; i++) {
            bx.ptr[i] = right.bx.ptr[i];
        }
        bx.ptr[mySize] = '\0';
    }

}

string::~string()
{
    if (myRes > 15)
        delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
    if (myRes < 16)
        return bx.buf;
    else
        return bx.ptr;
}

const string::value_type* string::myPtr() const
{
    if (myRes < 16)
        return bx.buf;
    else
        return bx.ptr;
}

string& string::assign(const string& right)
{
    if (this != &right)
    {
        if (right.mySize > myRes)
        {
            if (myRes > 15) delete[] bx.ptr;
            myRes = myRes * 3 / 2;
            if (myRes < (right.mySize / 16) * 16 + 15)
                myRes = (right.mySize / 16) * 16 + 15;
            bx.ptr = new value_type[myRes + 1]();

        }
        mySize = right.mySize;
        if (myRes < 16) {
            if (right.mySize < 16) {
                for (int i = 0; i <= mySize; i++) {
                    bx.buf[i] = right.bx.buf[i];
                }
            }
            else {
                for (int i = 0; i <= mySize; i++) {
                    bx.buf[i] = right.bx.ptr[i];
                }
            }

        }
        else {
            if (right.mySize < 16) {
                for (int i = 0; i <= mySize; i++) {
                    bx.ptr[i] = right.bx.buf[i];
                }
            }
            else {
                for (int i = 0; i <= mySize; i++) {
                    bx.ptr[i] = right.bx.ptr[i];
                }
            }
        }


    }

    return *this;
}

bool string::equal(const string& right)
{
    return 0;
}

string& string::erase(const size_type off, size_type count)
{
    if (off < mySize)
    {

        int t = 0, a = 0;
        for (size_t i = off; i + count < mySize; i++) {
            myPtr()[i] = myPtr()[i + count]; t = i + 1; a = 1;
        }
        if (a) mySize = t;
        else mySize = off;
        myPtr()[mySize] = '\0';
    }
    return *this;
}

void string::clear()
{
    mySize = 0;
    myPtr()[0] = value_type();
}

string::iterator string::begin()
{
    return myPtr();
}

string::const_iterator string::begin() const
{
    return const_iterator(myPtr());
}

string::iterator string::end()
{
    return myPtr() + static_cast<difference_type>(mySize);
}

string::const_iterator string::end() const
{
    return const_iterator(myPtr() + static_cast<difference_type>(mySize));
}

string::reference string::at(const size_type off)
{
    if (off > mySize)
    {
        cout << "string subscript out of range\n";
        exit(1);
    }

    return myPtr()[off];
}

string::const_reference string::at(const size_type off) const
{
    if (off > mySize)
    {
        cout << "string subscript out of range\n";
        exit(1);
    }

    return myPtr()[off];
}

void string::push_back(char ch)
{
    resize(mySize + 1);
    myPtr()[mySize - 1] = ch;
}

void string::pop_back()
{
    if (mySize > 0)
        --mySize;
}

string::reference string::front()
{
    return myPtr()[0];
}

string::const_reference string::front() const
{
    return myPtr()[0];
}

string::reference string::back()
{
    return myPtr()[mySize - 1];
}

string::const_reference string::back() const
{
    return myPtr()[mySize - 1];
}

const char* string::c_str() const
{
    return myPtr();
}

string::size_type string::size() const
{
    return mySize;
}

void string::resize(const size_type newSize, const char ch)
{
    // determine new length, padding with ch elements as needed
    if (newSize > mySize)
    {
        if (newSize > myRes)
        {
            pointer temp;
            size_type newMyRes = myRes * 3 / 2;
            if (newMyRes < (newSize / 16) * 16 + 15)
                newMyRes = (newSize / 16) * 16 + 15;

            if (myRes > 15) {
                temp = new value_type[newMyRes]();
                for (int i = 0; i <= mySize; i++) {
                    temp[i] = bx.ptr[i];
                }
                delete[] bx.ptr;
            }
            else {
                temp = new value_type[16]();
                for (int i = 0; i < 16; i++) {
                    temp[i] = bx.buf[i];
                }
            }
            bx.ptr = new value_type[newMyRes + 1]();
            for (int i = 0; i <= mySize; i++) {
                bx.ptr[i] = temp[i];
            }
            myRes = newMyRes;
            delete[] temp;
        }
        if (myRes < 16) {
            for (int i = mySize; i < 16; i++) {
                bx.buf[i] = ch;
            }
        }
        else {
            for (int i = mySize; i < myRes; i++) {
                bx.ptr[i] = ch;
            }
        }


    }

    mySize = newSize;
    if (myRes < 16) {
        bx.buf[mySize] = '\0';
    }
    else {
        bx.ptr[mySize] = '\0';
    }

}

string::size_type string::capacity() const
{
    return myRes;
}

bool string::empty() const
{
    return mySize == 0;
}