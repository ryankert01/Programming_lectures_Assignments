// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "Transaction.h" // Transaction class definition

class Deposit : public Transaction
{
public:
   Deposit( int userAccountNumber, BankDatabase &atmBankDatabase );
   virtual void execute(); // perform the transaction
private:
   double amount; // amount to deposit
   double promptForDepositAmount() const; // get deposit amount from user
};

#endif // DEPOSIT_H