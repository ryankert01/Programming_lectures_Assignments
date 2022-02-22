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
   ifstream inFile("Accounts.dat", ios::binary);

   if(!inFile)
   {
      cout << "File could not be opened" << endl;
      system("pause");
      exit(1);
   }
   recordNumber = 0;

   while (!inFile.eof()) {
       //load file to currentAcount
       inFile.read(reinterpret_cast<char*>(&currentAccount.accountNumber), sizeof(currentAccount.accountNumber));
       inFile.read(reinterpret_cast<char*>(&currentAccount.pin), sizeof(currentAccount.pin));
       //cout << inFile.tellg() << "\n";
       inFile.read(reinterpret_cast<char*>(&currentAccount.availableBalance), sizeof(currentAccount.availableBalance));
       inFile.read(reinterpret_cast<char*>(&currentAccount.totalBalance), sizeof(currentAccount.totalBalance));
       recordNumber++;
       if (currentAccount.accountNumber == accountNumber && currentAccount.pin == pin) {
           inFile.close();
           return true;
       }
   }
   recordNumber = 0;
   inFile.close();
   cout << "\nInvalid account number or PIN. Please try again.\n\n";
   return false;
   
   

} // end function loadAccount

// display the main menu and perform transactions
void performTransactions( Account &currentAccount, int &recordNumber, int &remainingBills )
{
    cout << "\nMain menu:";
    cout << "\n1 - View my balance";
    cout << "\n2 - Withdraw cash";
    cout << "\n3 - Deposit funds";
    cout << "\n4 - Exit\n";
    cout << "\nEnter a choice: ";
    int choice1 = 0;
    cin >> choice1;

    if (choice1 == 1)
    {
        cout << "\nBalance Information:";
        cout << "\n - Available balance: $" << currentAccount.availableBalance;
        cout << "\n - Total balance:    $" << currentAccount.totalBalance;
        cout << "\n";
        performTransactions(currentAccount, recordNumber, remainingBills);
    }
    else if (choice1 == 2)
    {
        withdrawal(currentAccount, remainingBills);
        performTransactions(currentAccount, recordNumber, remainingBills);
    }
    else if (choice1 == 3)
    {
        deposit(currentAccount);
        performTransactions(currentAccount, recordNumber, remainingBills);
    }
    else if (choice1 == 4)
        cout << "\nExiting the system...\n";
    else
    {
        cout << "\nYou did not enter a valid selection. Try again.\n";
        performTransactions(currentAccount, recordNumber, remainingBills);
    }
    saveAccount(currentAccount, recordNumber);
        


} // end function performTransactions

// perform withdrawal transaction
void withdrawal( Account &currentAccount, int &remainingBills )
{
    cout << "\nWithdrawal options:";
    cout << "\n1 - $20";
    cout << "\n2 - $40";
    cout << "\n3 - $60";
    cout << "\n4 - $100";
    cout << "\n5 - $200";
    cout << "\n6 - Cancel transaction\n";
    cout << "\nChoose a withdrawal option (1~6): ";
    int option = 0;
    cin >> option;

    if (option >= 1 && option <= 5) {
        //assign amount value
        int amount = 0;
        if (option <= 3)
            amount = option * 20;
        else if (option == 4)
            amount = 100;
        else if (option == 5)
            amount = 200;

        //check if remaining is enough for the redrawal transaction

        if (remainingBills - amount / 20 < 0)
        {
            cout << "\nInsufficient funds in your account.\n";
            cout << "\nPlease choose a smaller amount.\n";
            withdrawal(currentAccount, remainingBills);
        }
        else
        {
            remainingBills -= amount / 10;
            currentAccount.availableBalance -= amount;
            currentAccount.totalBalance -= amount;
            cout << "\nPlease take your cash from the cash dispenser.\n";
        }

    }
    else if (option == 6)
        cout << "\nCanceling Transaction...\n";
    else
    {
        cout << "\nInvalid selection. Try again.\n";
        withdrawal(currentAccount, remainingBills);
    }

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
    fstream ioFile("Accounts.dat", ios::in | ios::out | ios::binary);

    if (!ioFile) {
        cout << "File could not be open.\n";
        system("pause");
        exit(1);
    }

    ioFile.seekg(8 + 16 * (n - 1), ios::beg);
    ioFile.write(reinterpret_cast<char*>(&currentAccount.availableBalance), sizeof(currentAccount.availableBalance));
    ioFile.write(reinterpret_cast<char*>(&currentAccount.totalBalance), sizeof(currentAccount.totalBalance));

    ioFile.close();

}