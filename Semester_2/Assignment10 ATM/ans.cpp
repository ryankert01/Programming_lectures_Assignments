#include<iostream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;

class Account;
vector<Account>accounts;

class Account {
public:
	string account_num;
	string pin;
	double availBalance;
	double totalBalance;

	Account()
		:account_num(),
		pin(),
		availBalance(),
		totalBalance()
	{
	}

	Account(string a, string b, double c, double d)
		:account_num(a),
		pin(b),
		availBalance(c),
		totalBalance(d)
	{
	}

	bool isVaild()
	{
		for (Account i : accounts)
		{
			if (i.account_num == account_num && i.pin == pin)
				return true;
		}
		return false;
	}

	double findAccountAvail()
	{
		for (Account i : accounts)
		{
			if (i.account_num == account_num && i.pin == pin)
				return i.availBalance;
		}
		return -1;
	}

	double findAccountTotal()
	{
		for (Account i : accounts)
		{
			if (i.account_num == account_num && i.pin == pin)
				return i.totalBalance;
		}
		return -1;
	}

	void updateAccount()
	{
		for (Account i : accounts)
		{
			if (i.account_num == account_num && i.pin == pin)
			{
				i.availBalance = availBalance;
				i.totalBalance = totalBalance;
				break;
			}
		}
	}

	void showBalance()
	{
		cout << endl;
		cout << "Balance Information:" << endl;
		cout << " - Available balance : " << availBalance << endl;
		cout << " - Total balance : " << totalBalance << endl;
		cout << endl;

	}

	double getAvailBalance()
	{
		return availBalance;
	}

	double getTotalBalance()
	{
		return totalBalance;
	}

};

class ATM {
private:
	bool sign;
	int remainingBills;
	Account myData;
public:
	ATM()
		:sign(0),
		remainingBills(5),
		myData()
	{
	}

	void show()
	{
		cout << endl;
		cout << "Main menu :" << endl;
		cout << "1 - View my balance" << endl;
		cout << "2 - Withdraw cash" << endl;
		cout << "3 - Deposit funds" << endl;
		cout << "4 - Exit" << endl;

	}

	void showBalance()
	{
		myData.showBalance();
	}

	void withdraw()
	{
		int option;
		int bill[6] = { 0,20,40,60,100,200 };
		do {
			cout << endl;
			cout << "1 - $20 " << "  " << "2 - $40" << endl << endl;;
			cout << "3 - $60 " << "  " << "4 - $100" << endl << endl;
			cout << "5 - $200" << "  " << "6 - Cancel transaction" << endl << endl;
			cout << "Withdrawal options:";
			cin >> option;
			cout << endl;

			if (option > 6 || option < 1)
			{
				cout << "Invalid selection. Try again." << endl;
				continue;
			}
			else if (option == 6)
			{
				cout << "Canceling transaction..." << endl << endl;
				break;
			}
			else if (remainingBills < bill[option] / 20)
			{
				cout << "Insufficient funds in ATM" << endl;
				cout << "Please choose a smaller amount" << endl;
				continue;
			}
			else if (myData.availBalance < bill[option])
			{
				cout << "Insufficient funds in your account." << endl;
				cout << "Please choose a smaller amount" << endl;
				continue;
			}
			else
			{
				remainingBills -= bill[option] / 20;
				myData.availBalance -= bill[option];
				myData.totalBalance -= bill[option];
				cout << "Please take your cash from the cash dispenser" << endl << endl;
				break;
			}
		} while (1);

	}

	void deposit()
	{
		cout << endl;
		int cent;
		cout << "Please enter a deposit amount in CENTS(or 0 to cancel) : ";
		cin >> cent;
		if (cent)
		{
			cout << endl;
			cout << "Please insert a deposit envelope containing $" << cent / 100 << " in the deposit slot." << endl;

			cout << "Your envelope has been received." << endl;
			cout << "NOTE : The money deposited will not be available until we" << endl;
			cout << "verify the amount of any enclosed cash, and any enclosed checks clear." << endl;
			myData.totalBalance += cent / 100;
		}
	}

	void login()
	{

		do {
			cout << "Welcome" << endl << endl;;
			cout << "Please enter your account number : ";
			string acc, pin;
			cin >> acc;
			cout << endl;
			cout << "Enter your PIN : ";
			cin >> pin;
			myData.pin = pin;
			myData.account_num = acc;
			if (myData.isVaild())
			{
				myData.availBalance = myData.findAccountAvail();
				myData.totalBalance = myData.findAccountTotal();
				sign = 1;
			}


		} while (!isLogin());
	}

	void logout()
	{
		sign = 0;

		for(Account& i : accounts)
			if (i.account_num == myData.account_num)
			{
				i.totalBalance = myData.totalBalance;
				i.availBalance = myData.availBalance;
			}
	}

	bool isLogin()
	{
		return sign;
	}
};

int main() {
	ATM atm;

	Account user1("12345", "54321", 1000, 1200);
	Account user2("98765", "56789", 200, 200);
	accounts.push_back(user1);
	accounts.push_back(user2);


	while (1)
	{
		if (atm.isLogin())
		{
			int op;
			do
			{
				atm.show();
				cout << "Enter a choice : ";
				cin >> op;
				switch (op)
				{
				case 1:
					atm.showBalance();
					break;

				case 2:
					atm.withdraw();
					break;

				case 3:
					atm.deposit();
					break;

				case 4:
					atm.logout();
					break;

				default:
					cout << "You did not enter a valid selection. Try again." << endl;
					break;
				}
			} while (op != 4);
		}
		else
		{
			atm.login();
		}
	}

}
