// BalanceInquiry.cpp
// Member-function definitions for class BalanceInquiry.
#include <iostream>
#include <iomanip>
using namespace std;

#include "BalanceInquiry.h" // BalanceInquiry class definition
#include "BankDatabase.h" // BankDatabase class definition

// BalanceInquiry constructor initializes base-class data members
BalanceInquiry:: BalanceInquiry( int userAccountNumber, BankDatabase &atmBankDatabase )
   : Transaction( userAccountNumber, atmBankDatabase )
{
   // empty body
}

// performs transaction; overrides Transaction's pure virtual function
void BalanceInquiry::execute()
{
   // get references to bank database and screen
   BankDatabase &bankDatabase = getBankDatabase();

   // get the available balance for the current user's Account
   double availableBalance = bankDatabase.getAvailableBalance( getAccountNumber() );

   // get the total balance for the current user's Account
   double totalBalance = bankDatabase.getTotalBalance( getAccountNumber() );
   
   // display the balance information on the screen
   cout << "\nBalance Information:" << endl;
   cout << " - Available balance: ";
   cout << fixed << setprecision( 2 ) << "$" << availableBalance;
   cout << "\n - Total balance:     ";
   cout << fixed << setprecision( 2 ) << "$" << totalBalance;
   cout << endl;
}