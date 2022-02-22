#include <iostream>
#include <fstream>
using namespace std;

struct Account
{
   int accountNumber;    // account number
   int pin;              // personal identification number
   int availableBalance; // funds available for withdrawal
   int totalBalance;     // funds available + funds waiting to clear
};

// retrieve Account object (from Accounts.dat) containing specified accountNumber and pin,
// put this object to currentAccount,
// and put the record number (in Accounts.dat) of this object into recordNumber.
// if this object exists, returns true; otherwise returns false.
bool loadAccount( int accountNumber, int pin, Account &currentAccount, int &recordNumber );

// display the main menu and perform transactions
void performTransactions( Account &currentAccount, int &recordNumber, int &remainingBills );

// perform withdrawal transaction
void withdrawal( Account &currentAccount, int &remainingBills );

// perform deposit transaction
void deposit( Account &currentAccount );

// write currentAccount into the n-th record of Accounts.dat
void saveAccount( Account currentAccount, int n );

const int INITIAL_BILLS = 5; // the number bills loaded each day

int main()
{
   // the number of remaining bills in the cash dispenser
   int remainingBills = INITIAL_BILLS;
   int recordNumber;
   Account currentAccount;

   // welcome and authenticate user; perform transactions
   while ( true )
   {
      int accountNumber;
      int pin;

      do {
         cout << "Welcome!\n";
         cout << "\nPlease enter your account number: ";
         cin >> accountNumber;
         cout << "\nEnter your PIN: ";
         cin >> pin; // input PIN
      } while( !loadAccount( accountNumber, pin, currentAccount, recordNumber ) );
      
      performTransactions( currentAccount, recordNumber, remainingBills );
      cout << "\nThank you! Goodbye!\n\n";
   }
} // end function main

// retrieve Account object (from Accounts.dat) containing specified accountNumber and pin,
// put this object to currentAccount,
// and put the record number of this object into recordNumber.
// if this object exists, returns true; otherwise returns false.
bool loadAccount( int accountNumber, int pin, Account &currentAccount, int &recordNumber )
{


} // end function loadAccount

// display the main menu and perform transactions
void performTransactions( Account &currentAccount, int &recordNumber, int &remainingBills )
{


} // end function performTransactions

// perform withdrawal transaction
void withdrawal( Account &currentAccount, int &remainingBills )
{


} // end function withdrawal

// perform deposit transaction
void deposit( Account &currentAccount )
{
   cout << "\nPlease enter a deposit amount in dollars (or 0 to cancel): ";
   int amount;
   cin >> amount; // receive input of deposit amount

   // check whether user entered a deposit amount or canceled
   if( amount == 6 )
      cout << "\nCanceling transaction...\n";
   else // user canceled instead of entering amount
   {
      // request deposit envelope containing specified amount
      cout << "\nPlease insert a deposit envelope containing ";
      cout << "$" << amount;
      cout << " in the deposit slot.\n";

      cout << "\nYour envelope has been received."
         << "\nNOTE: The money deposited will not be available until we"
         << "\nverify the amount of any enclosed cash, and any enclosed checks clear.\n";

      // credit account to reflect the deposit
      currentAccount.totalBalance += amount; // add to total balance
   } // end if 
} // end function deposit

void saveAccount( Account currentAccount, int n )
{


}