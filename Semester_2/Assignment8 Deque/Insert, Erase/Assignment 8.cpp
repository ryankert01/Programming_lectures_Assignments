#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "deque.h"

void testCopyConstructor();
void testCopyConstructor1();
void testCopyConstructor2();
void testDeque1(size_t size);
void testDeque2(size_t size);
void testDeque3(size_t size);
void testDeque4(size_t size);
void testDeque5();
bool equal(std::deque< int >& deque1, deque< int >& deque2);
void printDeque1(std::deque< int > de);
void testInsert1();
void MixedTestDeque1();





const unsigned int number = 200;

int main()
{

    /**//**/
    for (unsigned int seed = 1; seed <= 10; seed++)
    {
        srand(seed);
        testCopyConstructor();
        testCopyConstructor1();
        testCopyConstructor2();
    }

    cout << endl;

    for (size_t i = 1; i <= 100; i++)
    {
        testDeque1(8 * i);
        testDeque2(8 * i);
        testDeque3(8 * i);
        testDeque4(8 * i);
    }

    cout << endl;

    for (unsigned int seed = 1; seed <= 500; seed++)
    {
        srand(seed);
        testDeque5();
    }


    testInsert1();

    for (unsigned int seed = 1; seed <= 1000; seed++)
    {
        srand(seed);
        MixedTestDeque1();
    }
 

   


    


    cout << endl;

    system("pause");
}

void testCopyConstructor()
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

        std::deque< int > deque3(deque1);
        deque< int > deque4(deque2);

        if (equal(deque3, deque4))
            numErrors--;
    }

    cout << "There are " << numErrors << " errors\n";
}

void testDeque1(size_t size)
{
    unsigned int numErrors = 8;
    for (unsigned int k = 0; k < 4; k++)
    {
        std::deque< int > deque1;
        unsigned int i; i = 1;
        /**/  for (i = 1; i <= 4 * (size / 2 - 1) + k; i++)
            deque1.push_back(i);
        for (; i <= 4 * (size - 1) + k; i++)
            deque1.push_front(i);


        deque< int > deque2;
        unsigned int j; j = 1;
        for (j = 1; j <= 4 * (size / 2 - 1) + k; j++)
            deque2.push_back(j);
        //deque2.print();
        for (; j <= 4 * (size - 1) + k; j++)
            deque2.push_front(j);/**/
         /**/
         //deque2.print();

        if (equal(deque1, deque2))
            numErrors--;

        deque1.push_front(i);
        deque2.push_front(j);
        //deque2.print();
        if (equal(deque1, deque2))
            numErrors--;
    }
    cout << "There are " << numErrors << " errors.\n";
}

void testDeque2(size_t size)
{
    unsigned int numErrors = 8;
    for (unsigned int k = 0; k < 4; k++)
    {
        std::deque< int > deque1;
        unsigned int i;
        for (i = 1; i <= 4 * (size / 2 - 1) + k; i++)
            deque1.push_back(i);
        for (; i <= 4 * (size - 1) + k; i++)
            deque1.push_front(i);

        deque< int > deque2;
        unsigned int j;
        for (j = 1; j <= 4 * (size / 2 - 1) + k; j++)
            deque2.push_back(j);
        for (; j <= 4 * (size - 1) + k; j++)
            deque2.push_front(j);

        if (equal(deque1, deque2))
            numErrors--;

        deque1.push_back(i);
        deque2.push_back(j);

        if (equal(deque1, deque2))
            numErrors--;
    }
    cout << "There are " << numErrors << " errors.\n";
}

void testDeque3(size_t size)
{
    unsigned int numErrors = 8;
    for (unsigned int k = 0; k < 4; k++)
    {
        std::deque< int > deque1;
        unsigned int i;
        for (i = 1; i <= 4 * (size / 2 - 1) + k; i++)
            deque1.push_front(i);
        for (; i <= 4 * (size - 1) + k; i++)
            deque1.push_back(i);

        deque< int > deque2;
        unsigned int j;
        for (j = 1; j <= 4 * (size / 2 - 1) + k; j++)
            deque2.push_front(j);
        for (; j <= 4 * (size - 1) + k; j++)
            deque2.push_back(j);

        if (equal(deque1, deque2))
            numErrors--;

        deque1.push_back(i);
        deque2.push_back(j);

        if (equal(deque1, deque2))
            numErrors--;
    }
    cout << "There are " << numErrors << " errors.\n";
}

void testDeque4(size_t size)
{
    unsigned int numErrors = 8;
    for (unsigned int k = 0; k < 4; k++)
    {
        std::deque< int > deque1;
        unsigned int i;
        for (i = 1; i <= 4 * (size / 2 - 1) + k; i++)
            deque1.push_front(i);
        for (; i <= 4 * (size - 1) + k; i++)
            deque1.push_back(i);

        deque< int > deque2;
        unsigned int j;
        for (j = 1; j <= 4 * (size / 2 - 1) + k; j++)
            deque2.push_front(j);
        for (; j <= 4 * (size - 1) + k; j++)
            deque2.push_back(j);

        if (equal(deque1, deque2))
            numErrors--;

        deque1.push_front(i);
        deque2.push_front(j);

        if (equal(deque1, deque2))
            numErrors--;
    }
    cout << "There are " << numErrors << " errors.\n";
}

void MixedTestDeque1()
{
    std::deque< int > deque1;
    deque< int > deque2;

    unsigned int numErrors = 5001;
    if (equal(deque1, deque2))
        numErrors--;

    int value; int flag = 0; int a; int pos;
    for (unsigned int i = 0; i < 5000; i++)
    {
        a = rand() % 6;
        switch (a)
        {
        case 0:
            value = 1 + rand() % 99;
            deque1.push_front(value);
            deque2.push_front(value);
            break;
        case 1:
            if (deque1.size() > 0)
            {
                deque1.pop_front();
                deque2.pop_front();
            }
            break;
        case 2:
            value = 1 + rand() % 99;
            deque1.push_back(value);
            deque2.push_back(value);
            break;
        case 3:
            if (deque1.size() > 0)
            {
                deque1.pop_back();
                deque2.pop_back();
            }
            break;
        case 4:
            value = 1 + rand() % 99;
            pos = deque1.size() > 0 ? rand() % deque1.size() : 0;
            deque1.insert(deque1.begin() + pos, value);
            deque2.insert(deque2.begin() + pos, value);
            break;
        case 5:
            if (deque1.size() > 0)
            {
                value = 1 + rand() % 99;
                pos = deque1.size() > 0 ? rand() % deque1.size() : 0;
                deque1.erase(deque1.begin() + pos);
                deque2.erase(deque2.begin() + pos);                
            }

            break;
        }


        if (equal(deque1, deque2))
            numErrors--;/**/
        else if (!equal(deque1, deque2) || flag) {
            cout << "wrong!\n";
            cout << "case: " << a << endl;
            printDeque1(deque1);
            deque2.printDeque();
            flag = 1;
        }
    }
    //deque2.print();

    cout << "There are " << numErrors << " errors.\n";
}

void testDeque5()
{
    std::deque< int > deque1;
    deque< int > deque2;

    unsigned int numErrors = 1001;
    if (equal(deque1, deque2))
        numErrors--;

    int value; int flag = 0; int a;
    for (unsigned int i = 0; i < 1000; i++)
    {
        a = rand() % 4;
        switch (a)
        {
        case 0:
            value = 1 + rand() % 99;
            deque1.push_front(value);
            deque2.push_front(value);
            break;
        case 1:
            if (deque1.size() > 0)
            {
                deque1.pop_front();
                deque2.pop_front();
            }
            break;
        case 2:
            value = 1 + rand() % 99;
            deque1.push_back(value);
            deque2.push_back(value);
            break;
        case 3:
            if (deque1.size() > 0)
            {
                deque1.pop_back();
                deque2.pop_back();
            }
            break;
        }

        if (equal(deque1, deque2))
            numErrors--;/**/
        else if (!equal(deque1, deque2) || flag) {
            cout << "wrong!\n";
            cout << "case: " << a << endl;
            printDeque1(deque1);
            deque2.printDeque();
            flag = 1;
        }
    }
    //deque2.print();

    cout << "There are " << numErrors << " errors.\n";
}

void testInsert1()
{
    std::deque< int > deque1;
    deque< int > deque2;


    for (int i = 1; i <= 60; i++)
    {
        deque1.insert(deque1.begin(), i);
        deque2.insert(deque2.begin(), i);
        if (equal(deque1, deque2))
            cout << "Correct!\n\n";
        else
            cout << "Incorrect!\n\n";
    }




    deque1.insert(++deque1.begin(), 100);
    deque2.insert(deque2.begin()+1, 100);

    if (equal(deque1, deque2))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";
}

void printDeque1(std::deque< int > de) {
    for (auto i : de)
        cout << i << " ";
    cout << endl;
}

void testCopyConstructor1()
{
    std::deque< int > deque1;
    deque< int > deque2;

    deque1.push_front(1);
    deque2.push_front(1);

    for (int i = 2; i <= 60; i++)
    {
        deque1.push_back(i);
        deque2.push_back(i);
    }

    for (int i = 1; i <= 32; i++)
    {
        deque1.pop_front();
        deque2.pop_front();
    }

    if (equal(deque1, deque2))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";

    for (int i = 61; i <= 92; i++)
    {
        deque1.push_back(i);
        deque2.push_back(i);
    }

    if (equal(deque1, deque2))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";

    for (int i = 1; i <= 59; i++)
    {
        deque1.pop_front();
        deque2.pop_front();
    }

    if (equal(deque1, deque2))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";

    std::deque< int > deque3(deque1);
    deque< int > deque4(deque2);

    if (equal(deque3, deque4))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";
}

void testCopyConstructor2()
{
    std::deque< int > deque1;
    deque< int > deque2;

    deque1.push_front(1);
    deque2.push_front(1);

    for (int i = 2; i <= 125; i++)
    {
        deque1.push_back(i);
        deque2.push_back(i);
    }

    for (int i = 1; i <= 96; i++)
    {
        deque1.pop_front();
        deque2.pop_front();
    }

    if (equal(deque1, deque2))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";

    for (int i = 126; i <= 221; i++)
    {
        deque1.push_back(i);
        deque2.push_back(i);
    }

    if (equal(deque1, deque2))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";

    for (int i = 1; i <= 124; i++)
    {
        deque1.pop_front();
        deque2.pop_front();
    }

    if (equal(deque1, deque2))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";

    std::deque< int > deque3(deque1);
    deque< int > deque4(deque2);

    if (equal(deque3, deque4))
        cout << "Correct!\n\n";
    else
        cout << "Incorrect!\n\n";
}

bool equal(std::deque< int >& deque1, deque< int >& deque2)
{
    int** map1 = *(reinterpret_cast<int***> (&deque1) + 1);
    size_t mapSize1 = *(reinterpret_cast<size_t*>(&deque1) + 2);
    size_t myOff1 = *(reinterpret_cast<size_t*>(&deque1) + 3);
    size_t mySize1 = *(reinterpret_cast<size_t*>(&deque1) + 4);

    int** map2 = *(reinterpret_cast<int***> (&deque2));
    size_t mapSize2 = *(reinterpret_cast<size_t*>(&deque2) + 1);
    size_t myOff2 = *(reinterpret_cast<size_t*>(&deque2) + 2);
    size_t mySize2 = *(reinterpret_cast<size_t*>(&deque2) + 3);

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
        return false; ;
    }



    if (mySize1 != mySize2) {
        cout << "mySize wrong!\n";
        return false;
    }

    size_t row, col;
    for (size_t i = myOff1; i < myOff1 + mySize1; ++i/*, ++it2*/)
    {
        row = (i / 4) % mapSize1;
        if (map1[row] != nullptr && map2[row] == nullptr)
            return false;

        if (map1[row] == nullptr && map2[row] != nullptr)
            return false;

        if (map1[row] != nullptr && map2[row] != nullptr)
        {
            col = i % 4;
            if (map1[row][col] != map2[row][col])
                return false;
        }
    }

    return true;
}