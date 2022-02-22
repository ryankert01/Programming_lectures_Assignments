#include<iostream>
#include<cstring>
#include<cmath>
using std::cin; // addition
using std::cout;
using std::endl;

// returns true if and only if the specified huge integer is zero
bool isZero(int hugeInt[], int size);

// returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int size1, int size2);

// --hugeInt
void decrement(int hugeInt[], int size);

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction(int minuend[], int subtrahend[], int& minuendSize, int subtrahendSize);

// multiplicand *= multiplier
void multiplication(int multiplicand[], int multiplier[], int& multiplicandSize, int multiplierSize);

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendSize, int divisorSize, int& quotientSize, int& remainderSize);

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10(int hugeInt[], int& size);

const int arraySize = 200;

int main()
{
    int t, a, b;
    while (cin >> t >> a >> b)
    {
        cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

        if (t == 1)
            cout << "is not an integer with less than 100 digits.\n";
        else if (a == b)
            cout << "1\n";
        else if (a < b)
            cout << "is not an integer with less than 100 digits.\n";
        else if (a % b != 0)
            cout << "is not an integer with less than 100 digits.\n";
        else if ((a - b) * static_cast<int>(log10(t)) > 95)
            cout << "is not an integer with less than 100 digits.\n";
        else
        {
            int dividend[arraySize] = {};
            int divisor[arraySize] = {};
            int quotient[arraySize] = {};
            int remainder[arraySize] = {};

            int dividendSize = 1;
            int divisorSize = 1;
            int quotientSize = 1;
            int remainderSize = 1;

            // put all digits of t into base
            int base[arraySize] = {};
            int baseSize = 0;
            for (int i = t; i > 0; i /= 10)
                base[baseSize++] = i % 10;

            // dividend = pow( t, a )
            dividend[0] = 1;
            for (int i = 0; i < a; ++i)
            {
                multiplication(dividend, base, dividendSize, baseSize);
                if (dividendSize > arraySize)
                    break;
            }

            if (dividendSize > arraySize)
                cout << "is not an integer with less than 100 digits.\n";
            else
            {
                // divisor = pow( t, b )
                divisor[0] = 1;
                for (int i = 0; i < b; ++i)
                    multiplication(divisor, base, divisorSize, baseSize);

                decrement(dividend, dividendSize); // --dividend
                decrement(divisor, divisorSize);   // --divisor

                division(dividend, divisor, quotient, remainder,
                    dividendSize, divisorSize, quotientSize, remainderSize);

                // quotient is an integer with less than 100 digits
                if (quotientSize < 100 && isZero(remainder, remainderSize))
                    for (int i = quotientSize - 1; i >= 0; i--)
                        cout << quotient[i];
                else
                    cout << "is not an integer with less than 100 digits.";
                cout << endl;
            }
        }
    }
}

// returns true if and only if the specified huge integer is zero
bool isZero(int hugeInt[], int size)
{
    for (int i = 0; i < size; i++)
        if (hugeInt[i] != 0)
            return false;
    return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int size1, int size2)
{
    int bo = 0;
    if (size1 < size2)
        bo = 1;
    else if (size1 > size2)
        bo = 0;
    else
        for (int i = size1 - 1; i >= 0; i--)
        {
            if (hugeInt1[i] < hugeInt2[i])
            {
                bo = 1;
                break;
            }
            else if (hugeInt1[i] > hugeInt2[i])
            {
                bo = 0;
                break;
            }
            else
                continue;

        }
    return bo;

}

// --hugeInt
void decrement(int hugeInt[], int size)
{
    hugeInt[0]--;
    for (int i = 0; i < size; i++) //借位
    {
        while (hugeInt[i] < 0)
        {
            hugeInt[i + 1] -= 1;
            hugeInt[i] += 10;
        }
    }

    int miniss = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        if (hugeInt[i] == 0)
            miniss++;
        else
            break;
    }
    size -= miniss;

}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction(int minuend[], int subtrahend[], int& minuendSize, int subtrahendSize)
{
    int difference[arraySize] = {};
    int differenceSize = minuendSize + subtrahendSize;
    for (int i = 0; i < subtrahendSize; i++)
    {
        difference[i] = minuend[i] - subtrahend[i];
    }

    for (int i = minuendSize - 1; i >= subtrahendSize; i--)
    {
        difference[i] = minuend[i];
    }

    for (int i = 0; i < minuendSize; i++) //借位
    {
        while (difference[i] < 0)
        {
            difference[i + 1] -= 1;
            difference[i] += 10;
        }
    }

    int miniss = 0;
    for (int i = minuendSize - 1; i >= 0; i--)
    {
        if (difference[i] == 0)
            miniss++;
        else
            break;
    }
    differenceSize = minuendSize - miniss;

    for (int i = 0; i < arraySize; i++)
    {
        minuend[i] = difference[i];
    }
    minuendSize = differenceSize;

}

// multiplicand *= multiplier
void multiplication(int multiplicand[], int multiplier[], int& multiplicandSize, int multiplierSize)
{
    int product[arraySize] = {};
    int productSize = multiplicandSize + multiplierSize;
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
        if (product[i - 1] != 0)
        {
            productSize = i;
            break;
        }
        if (i - 1 == 0)
        {
            productSize = 1;
        }
    }
    for (int i = 0; i < productSize; i++)
    {
        multiplicand[i] = product[i];
    }
    multiplicandSize = productSize;
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendSize, int divisorSize, int& quotientSize, int& remainderSize)
{
    int buffer[arraySize] = {};
    int bufferSize = divisorSize;
    memset(remainder, 0, sizeof(remainder));
    if (less(dividend, divisor, dividendSize, divisorSize))
    {
        memset(quotient, 0, sizeof(quotient));
    }
    else
    {
        int i;
        int buffer[arraySize] = {};
        int bufferSize = divisorSize;
        remainderSize = dividendSize;

        for (i = 0; i < remainderSize; i++)
            remainder[i] = dividend[i];

        for (i = 0; i < divisorSize; i++)
            buffer[i] = divisor[i];

        if (less(dividend, divisor, dividendSize, divisorSize))
        {
            memset(quotient, 0, sizeof(quotient));
        }
        else
        {
            int n = dividendSize - divisorSize;
            int ten[] = { 0,1 };
            for (i = 0; i < n; i++) // buffer =divisor shift left by n positions 
            {
                multiplication(buffer, ten, bufferSize, 2);
            }
            quotientSize = dividendSize - divisorSize;

            if (less(dividend, buffer, dividendSize, bufferSize))
            {
                divideBy10(buffer, bufferSize);
            }
            else
                quotientSize++;

            memset(quotient, 0, sizeof(quotient));
            int k;
            for (k = quotientSize - 1; k >= 0; k--)
            {
                while (!less(remainder, buffer, remainderSize, bufferSize))
                {
                    subtraction(remainder, buffer, remainderSize, bufferSize);
                    quotient[k]++;
                    if (isZero(remainder, remainderSize))
                        return;
                }
                divideBy10(buffer, bufferSize);
            }
        }

    }
}


// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10(int hugeInt[], int& size)
{
    if (size == 1)
        hugeInt[0] = 0;
    else
    {
        for (int i = 1; i < size; i++)
            hugeInt[i - 1] = hugeInt[i];

        size--;
        hugeInt[size] = 0;
    }
}
