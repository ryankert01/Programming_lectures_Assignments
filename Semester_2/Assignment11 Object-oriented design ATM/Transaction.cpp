// Transaction.cpp
// Member-function definitions for class Transaction.
#include <iostream>
#include <iomanip>
using namespace std;

#include "Transaction.h" // Transaction class definition
#include "BankDatabase.h" // BankDatabase class definition

// constructor initializes common features of all Transactions
Transaction::Transaction( int userAccountNumber, BankDatabase &atmBankDatabase )
   : accountNumber( userAccountNumber ),
     bankDatabase( atmBankDatabase )
{
   // empty body
}

// return account number 
int Transaction::getAccountNumber() const
{
   return accountNumber; 
}

// return reference to bank database
BankDatabase& Transaction::getBankDatabase() const
{
   return bankDatabase;
}