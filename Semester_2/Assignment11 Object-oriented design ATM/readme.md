
Computer Programming II — Homework Assignment #11

Implement an ATM system whose requirements document is the same as that in Assignment #10. Your program must contain six classes: Account, BalanceInquiry, Deposit, Withdrawal, Transaction and BankDatabase defined in Account.h, BalanceInquiry.h, Deposit.h, Withdrawal.h, Transaction.h and BankDatabase.h respectively.

The record format of the binary file Accounts.dat:
   int accountNumber; // account number
   int pin; // PIN for authentication
   double availableBalance; // funds available for withdrawal
   double totalBalance; // funds available + funds waiting to clear 


The screen dialog #1:

Welcome!

Please enter your account number: 12345

Enter your PIN: 54321

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 4

Exiting the system...

Thank you! Goodbye!

Welcome!

Please enter your account number: 98765

Enter your PIN: 56789

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $200.00
 - Total balance:     $200.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 2

Withdrawal options:
1 - $20
2 - $40
3 - $60
4 - $100
5 - $200
6 - Cancel transaction

Choose a withdrawal option (1-6): 2

Please take your cash from the cash dispenser.

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $160.00
 - Total balance:     $160.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 4

Exiting the system...

Thank you! Goodbye!

Welcome!

Please enter your account number: 98765

Enter your PIN: 56789

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $160.00
 - Total balance:     $160.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 3

Please enter a deposit amount in CENTS (or 0 to cancel): 1000

Please insert a deposit envelope containing $10.00 in the deposit slot.

Your envelope has been received.
NOTE: The money deposited will not be available until we verify
the amount of any enclosed cash, and any enclosed checks clear.

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $160.00
 - Total balance:     $170.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 4

Exiting the system...

Thank you! Goodbye!

Welcome!

Please enter your account number: 98765

Enter your PIN: 56789

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $160.00
 - Total balance:     $170.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 4

Exiting the system...

Thank you! Goodbye!

Welcome!

Please enter your account number:

The screen dialog #2:

Welcome!

Please enter your account number: 12345

Enter your PIN: 54321

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $1000.00
 - Total balance:     $1200.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 2

Withdrawal options:
1 - $20
2 - $40
3 - $60
4 - $100
5 - $200
6 - Cancel transaction

Choose a withdrawal option (1-6): 3

Please take your cash from the cash dispenser.

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $940.00
 - Total balance:     $1140.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 4

Exiting the system...

Thank you! Goodbye!

Welcome!

Please enter your account number: 98765

Enter your PIN: 56789

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $200.00
 - Total balance:     $200.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 2

Withdrawal options:
1 - $20
2 - $40
3 - $60
4 - $100
5 - $200
6 - Cancel transaction

Choose a withdrawal option (1-6): 3

Insufficient cash available in the ATM.

Please choose a smaller amount.

Withdrawal options:
1 - $20
2 - $40
3 - $60
4 - $100
5 - $200
6 - Cancel transaction

Choose a withdrawal option (1-6): 2

Please take your cash from the cash dispenser.

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 1

Balance Information:
 - Available balance: $160.00
 - Total balance:     $160.00

Main menu:
1 - View my balance
2 - Withdraw cash
3 - Deposit funds
4 - Exit

Enter a choice: 4

Exiting the system...

Thank you! Goodbye!

Welcome!

Please enter your account number:

