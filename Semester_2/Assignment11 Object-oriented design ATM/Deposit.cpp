// Deposit.cpp
// Member-function definitions for class Deposit.
#include <iostream>
#include <iomanip>
using namespace std;

#include "Deposit.h" // Deposit class definition
#include "BankDatabase.h" // BankDatabase class definition

static const int CANCELED = 0; // constant representing cancel option 

// Deposit constructor initializes class's data members
Deposit::Deposit( int userAccountNumber, BankDatabase &atmBankDatabase )
   : Transaction( userAccountNumber, atmBankDatabase ),
     amount( 0.0 )
{
   // empty body
}

// performs transaction; overrides Transaction's pure virtual function 
void Deposit::execute()
{
   BankDatabase &bankDatabase = getBankDatabase(); // get reference

   amount = promptForDepositAmount(); // get deposit amount from user

   if (amount != CANCELED)
   {
       bankDatabase.credit(getAccountNumber(), amount);
   }


}

// prompt user to enter a deposit amount in cents 
double Deposit::promptForDepositAmount() const
{
   // display the prompt and receive input
   cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";
   int input; // receive input of deposit amount
   cin >> input;
   
   // check whether the user canceled or entered a valid amount
   if ( input == CANCELED ) 
      return CANCELED;
   else
      return static_cast< double >( input ) / 100; // return dollar amount 
}