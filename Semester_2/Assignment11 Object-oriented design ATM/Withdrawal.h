// Withdrawal.h
// Withdrawal class definition. Represents a withdrawal transaction.
#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include "Transaction.h" // Transaction class definition

class Withdrawal : public Transaction
{
public:
   Withdrawal( int userAccountNumber, BankDatabase &atmBankDatabase );
   virtual void execute(); // perform the transaction
private:
   int amount; // amount to withdraw
   static int remainingBills;
   int displayMenuOfAmounts() const; // display the withdrawal menu
};

#endif // WITHDRAWAL_H