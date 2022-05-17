// Transaction.h
// Transaction abstract base class definition.
#ifndef TRANSACTION_H
#define TRANSACTION_H

class BankDatabase; // forward declaration of class BankDatabase

class Transaction
{
public:
   // constructor initializes common features of all Transactions
   Transaction( int userAccountNumber, BankDatabase &atmBankDatabase );

   virtual ~Transaction() // virtual destructor with empty body
   {
   }

   int getAccountNumber() const; // return account number

   BankDatabase &getBankDatabase() const; // return reference to database

   // pure virtual function to perform the transaction
   virtual void execute() = 0; // overridden in derived classes
private:
   int accountNumber; // indicates account involved
   BankDatabase &bankDatabase; // reference to the account info database
};

#endif // TRANSACTION_H