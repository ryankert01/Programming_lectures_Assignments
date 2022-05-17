#include <iostream>
#include <iomanip>
using namespace std;

#include "BankDatabase.h" // BankDatabase class definition
#include "Transaction.h" // Transaction class definition
#include "BalanceInquiry.h" // BalanceInquiry class definition
#include "Withdrawal.h" // Withdrawal class definition
#include "Deposit.h" // Deposit class definition

void authenticateUser( bool &, int &, BankDatabase & ); // attempts to authenticate user
void performTransactions( int &, BankDatabase & ); // performs transactions
int displayMainMenu(); // displays main menu

int main()
{
   bool userAuthenticated = false; // whether user is authenticated
   int currentAccountNumber = 0; // current user's account number

   // welcome and authenticate user; perform transactions
   while ( true )
   {
      BankDatabase bankDatabase; // account information database

      // loop while user is not yet authenticated
      while ( !userAuthenticated ) 
      {
         cout << "\nWelcome!" << endl;
         authenticateUser( userAuthenticated, currentAccountNumber, bankDatabase ); // authenticate user
      }
      
      performTransactions( currentAccountNumber, bankDatabase ); // user is now authenticated 
      userAuthenticated = false; // reset before next ATM session
      currentAccountNumber = 0; // reset before next ATM session 
      cout << "\nThank you! Goodbye!" << endl;
   }   
}

// attempt to authenticate user against database
void authenticateUser( bool &userAuthenticated, int &currentAccountNumber, BankDatabase &bankDatabase ) 
{
   cout << "\nPlease enter your account number: ";
   int accountNumber;
   cin >> accountNumber;
   cout << "\nEnter your PIN: ";
   int pin;
   cin >> pin;
   
   // set userAuthenticated to bool value returned by database
   userAuthenticated = bankDatabase.authenticateUser( accountNumber, pin );
   
   // check whether authentication succeeded
   if ( userAuthenticated )
      currentAccountNumber = accountNumber; // save user's account #
   else
      cout << "Invalid account number or PIN. Please try again." << endl;
}

// display the main menu and perform transactions
void performTransactions( int &currentAccountNumber, BankDatabase &bankDatabase ) 
{
   // enumeration constants represent main menu options
   enum class MenuOption { BALANCE_INQUIRY = 1, WITHDRAWAL, DEPOSIT, EXIT };

   // local pointer to store transaction currently being processed
   Transaction *currentTransactionPtr;

   bool userExited = false; // user has not chosen to exit

   // loop while user has not chosen option to exit system
   while ( !userExited )
   {     
      // show main menu and get user selection
      MenuOption mainMenuSelection = static_cast< MenuOption >( displayMainMenu() );

      // decide how to proceed based on user's menu selection
      switch( mainMenuSelection )
      {
         // user chose to perform one of three transaction types
      case MenuOption::BALANCE_INQUIRY:
         // create new BalanceInquiry transaction
         currentTransactionPtr = new BalanceInquiry( currentAccountNumber, bankDatabase );
         currentTransactionPtr->execute(); // execute transaction
         delete currentTransactionPtr; // free the space for the dynamically allocated Transaction
         break;
      case MenuOption::WITHDRAWAL:
         // create new Withdrawal transaction
         currentTransactionPtr = new Withdrawal( currentAccountNumber, bankDatabase );
         currentTransactionPtr->execute(); // execute transaction
         delete currentTransactionPtr; // free the space for the dynamically allocated Transaction
         break;
      case MenuOption::DEPOSIT:
         // create new Deposit transaction
         currentTransactionPtr = new Deposit( currentAccountNumber, bankDatabase );
         currentTransactionPtr->execute(); // execute transaction
         delete currentTransactionPtr; // free the space for the dynamically allocated Transaction
         break;
      case MenuOption::EXIT: // user chose to terminate session
         cout << "\nExiting the system..." << endl;
         userExited = true; // this ATM session should end
         break;
      default: // user did not enter an integer from 1-4
         cout << "\nYou did not enter a valid selection. Try again." << endl;
         break;
      }
   }
}

// display the main menu and return an input selection
int displayMainMenu()
{
   cout << "\nMain menu:" << endl;
   cout << "1 - View my balance" << endl;
   cout << "2 - Withdraw cash" << endl;
   cout << "3 - Deposit funds" << endl;
   cout << "4 - Exit\n" << endl;
   cout << "Enter a choice: ";
   int choice;
   cin >> choice;
   return choice; // return user's selection
}