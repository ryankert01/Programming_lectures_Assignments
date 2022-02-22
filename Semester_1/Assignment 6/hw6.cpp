// Polynomial division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::istream;
using std::ifstream;
using std::ios;

void input(istream& inFile, int*& polynomial, int& degree);

// outputs the specified polynomial
void output(int* polynomial, int degree);

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int* polynomial, int degree);

// returns true if and only if polynomial1 == polynomial2
bool equal(int* polynomial1, int* polynomial2, int degree1, int degree2);

// addend += adder
void addition(int* addend, int* adder, int& addendDegree, int adderDegree);

// minuend -= subtrahend
void subtraction(int* minuend, int* subtrahend, int& minuendDegree, int subtrahendDegree);

// product = multiplicand * multiplier
void multiplication(int* multiplicand, int* multiplier, int* product,
    int multiplicandDegree, int multiplierDegree, int productDegree);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendDegree >= divisorDegree
void division(int* dividend, int* divisor, int* quotient, int* remainder,
    int dividendDegree, int divisorDegree, int quotientDegree, int& remainderDegree);

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
    ifstream inFile("Polynomials.dat", ios::in | ios::binary);

    // exit program if ifstream could not open file
    if (!inFile)
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    int numErrors = numTestCases;
    for (int i = 0; i < numTestCases; i++)
    {
        int* dividend, * divisor;
        int dividendDegree, divisorDegree;

        input(inFile, dividend, dividendDegree);
        input(inFile, divisor, divisorDegree);

        cout << "dividend: ";
        output(dividend, dividendDegree);
        cout << "divisor:  ";
        output(divisor, divisorDegree);

        int quotientDegree = dividendDegree - divisorDegree;
        int* quotient = new int[quotientDegree + 1]();

        int remainderDegree = dividendDegree;
        int* remainder = new int[remainderDegree + 1]();

        // quotient = dividend / divisor; remainder = dividend % divisor
        // thus, dividend == divisor * quotient + remainder
        division(dividend, divisor, quotient, remainder,
            dividendDegree, divisorDegree, quotientDegree, remainderDegree);

        if (quotientDegree != 0 && quotient[quotientDegree] == 0)
            cout << "Leading zeroes not allowed!\n";

        cout << "quotient: ";
        output(quotient, quotientDegree);
        cout << "remainder:  ";
        output(remainder, remainderDegree);
        cout << endl;

        int bufferDegree = divisorDegree + quotientDegree;
        int* buffer = new int[bufferDegree + 1]();

        // buffer = divisor * quotient
        multiplication(divisor, quotient, buffer, divisorDegree, quotientDegree, bufferDegree);

        if (bufferDegree != 0 && buffer[bufferDegree] == 0)
            cout << "Leading zeroes not allowed!\n";

        // buffer = buffer + remainder = divisor * quotient + remainder
        addition(buffer, remainder, bufferDegree, remainderDegree);

        if (bufferDegree != 0 && buffer[bufferDegree] == 0)
            cout << "Leading zeroes not allowed!\n";

        // if buffer != dividend, an error occurred!
        if (equal(buffer, dividend, bufferDegree, dividendDegree))
            numErrors--;

        delete[] buffer;
        delete[] remainder;
        delete[] quotient;
    }

    inFile.close();

    cout << "\nThere are " << numErrors << " errors.\n\n";

    system("pause");
}

void input(istream& inFile, int*& polynomial, int& degree)
{
    int temp[arraySize] = {};

    // input dividend and divisor from the file Polynomials.dat
    inFile.read(reinterpret_cast<char*>(temp), 80);

    degree = arraySize - 1;
    while (degree > 0 && temp[degree] == 0)
        degree--;

    polynomial = new int[degree + 1]();
    for (int i = 0; i <= degree; i++)
        polynomial[i] = temp[i];
}

// outputs the specified polynomial
void output(int* polynomial, int degree)
{
    if (isZero(polynomial, degree)) // zero polynomial
        cout << 0;
    else
    {
        if (degree == 0) // constant polynomial
        {
            if (polynomial[0] < 0)
                cout << "-" << -polynomial[0];
            else if (polynomial[0] > 0)
                cout << polynomial[0];
        }
        else
        {
            if (degree == 1) // polynomial of degree 1
            {
                if (polynomial[1] < 0)
                    cout << "-" << -polynomial[1] << "x";
                else if (polynomial[1] > 0)
                    cout << polynomial[1] << "x";
            }
            else // polynomial of degree at least 2
            {
                // display the leading term
                if (polynomial[degree] < 0)
                    cout << "-" << -polynomial[degree] << "x^" << degree;
                else if (polynomial[degree] > 0)
                    cout << polynomial[degree] << "x^" << degree;

                // display all other terms
                for (int i = degree - 1; i > 1; i--)
                    if (polynomial[i] < 0)
                        cout << " - " << -polynomial[i] << "x^" << i;
                    else if (polynomial[i] > 0)
                        cout << " + " << polynomial[i] << "x^" << i;

                // display the term of degree 1
                if (polynomial[1] < 0)
                    cout << " - " << -polynomial[1] << "x";
                else if (polynomial[1] > 0)
                    cout << " + " << polynomial[1] << "x";
            }

            // display the constant term
            if (polynomial[0] < 0)
                cout << " - " << -polynomial[0];
            else if (polynomial[0] > 0)
                cout << " + " << polynomial[0];
        }
    }

    cout << endl;
}

// returns true if and only if the specified polynomial is zero polynomial
bool isZero(int* polynomial, int degree)
{  // leading term is 0
    if (degree == 0 && polynomial[0] == 0)
        return true;
    return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal(int* polynomial1, int* polynomial2, int degree1, int degree2)
{
    if (degree1 != degree2)
        return false;

    for (int i = 0; i <= degree1; i++)
        if (polynomial1[i] != polynomial2[i])
            return false;

    return true;
}

// addend += adder
void addition(int* addend, int* adder, int& addendDegree, int adderDegree)
{

    for (int i = 0; i < addendDegree + 1; i++)
    {
        addend[i] += adder[i];
    }

    for (int i = addendDegree; i >= 0; i--)
    {
        if (addend[i] == 0)
            addendDegree--;
        else
            break;
    }
}

// minuend -= subtrahend
void subtraction(int* minuend, int* subtrahend, int& minuendDegree, int subtrahendDegree)
{

    if (minuendDegree != 0 && minuend[minuendDegree] == 0)
        cout << "Leading zeroes not allowed!\n";

    for (int i = 0; i < minuendDegree + 1; i++)
    {
        minuend[i] -= subtrahend[i];
    }
    for (int i = minuendDegree; i > 0; i--)
    {
        if (minuend[i] == 0)
            minuendDegree--;
        else
            break;
    }
}

// product = multiplicand * multiplier
void multiplication(int* multiplicand, int* multiplier, int* product,
    int multiplicandDegree, int multiplierDegree, int productDegree)
{

    for (int i = 0; i < multiplierDegree + 1; i++)
    {
        for (int j = 0; j < multiplicandDegree + 1; j++)
        {
            product[i + j] += multiplicand[j] * multiplier[i];
        }
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendDegree >= divisorDegree
void division(int* dividend, int* divisor, int* quotient, int* remainder,
    int dividendDegree, int divisorDegree, int quotientDegree, int& remainderDegree)
{

    for (int i = 0; i < dividendDegree + 1; i++)
    {
        remainder[i] = dividend[i];
    }
    remainderDegree = dividendDegree;
    quotientDegree = dividendDegree - divisorDegree;

    for (int i = 0; i < quotientDegree + 1; i++)
    {
        //set up monomial and buffer
        if (remainderDegree < dividendDegree - i)
            continue;

        int monomialDegree = quotientDegree - i;
        int bufferDegree = remainderDegree;

        int* monomial = new int[monomialDegree + 1]();
        int* buffer = new int[bufferDegree + 1]();

        quotient[quotientDegree-i] = remainder[remainderDegree] / divisor[divisorDegree];
        if (quotient[quotientDegree - i] == 0)
            continue;


        monomial[monomialDegree] = quotient[monomialDegree];
        
        multiplication(monomial, divisor, buffer, monomialDegree, divisorDegree, bufferDegree);
        subtraction(remainder, buffer, remainderDegree, bufferDegree);

        delete[] buffer;
        delete[] monomial;

        if (isZero(remainder, remainderDegree))
        {
            break;
        }

    }

}