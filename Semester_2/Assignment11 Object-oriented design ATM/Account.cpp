// Account.cpp
// Member-function definitions for class Account.
#include "Account.h" // Account class definition

// Account constructor initializes attributes
Account::Account( int theAccountNumber, int thePIN, 
   double theAvailableBalance, double theTotalBalance )
   : accountNumber( theAccountNumber ),
     pin( thePIN ),
     availableBalance( theAvailableBalance ),
     totalBalance( theTotalBalance )
{
   // empty body
}

// determines whether a user-specified PIN matches PIN in Account
bool Account::validatePIN( int userPIN ) const
{ 
   if ( userPIN == pin )
      return true;
   else
      return false;
}

// returns available balance
double Account::getAvailableBalance() const
{
   return availableBalance;
}

// returns the total balance
double Account::getTotalBalance() const
{
   return totalBalance;
}

// credits an amount to the account
void Account::credit( double amount )
{
   totalBalance += amount; // add to total balance
}

// debits an amount from the account
void Account::debit( double amount )
{
   availableBalance -= amount; // subtract from available balance
   totalBalance -= amount; // subtract from total balance
}

// returns account number
int Account::getAccountNumber() const
{
   return accountNumber;  
}