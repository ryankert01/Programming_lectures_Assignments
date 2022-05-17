// BankDatabase.h
// BankDatabase class definition. Represents the bank's database.
#ifndef BANK_DATABASE_H
#define BANK_DATABASE_H

#include <vector> // class uses vector to store Account objects
#include <fstream>
using namespace std;

#include "Account.h" // Account class definition

class BankDatabase
{
public:
   // read account informations for all accounts from the binary file "Accounts.dat"
   BankDatabase(); // constructor initializes accounts

   // write account informations for all accounts to the binary file "Accounts.dat"
   ~BankDatabase();

   // determine whether account number and PIN match those of an Account
   bool authenticateUser( int userAccountNumber, int userPIN ); // returns true if Account authentic

   double getAvailableBalance( int userAccountNumber ); // get an available balance
   double getTotalBalance( int userAccountNumber ); // get an Account's total balance
   void credit( int userAccountNumber, double amount ); // add amount to Account balance
   void debit( int userAccountNumber, double amount ); // subtract amount from Account balance
private:
   vector< Account > accounts; // vector of the bank's Accounts

   // private utility function
   Account* getAccount( int accountNumber ); // get pointer to Account object
};

#endif // BANK_DATABASE_H