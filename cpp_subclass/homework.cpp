#include <iostream>
using namespace std;

class Moneybag {
public:
	static int sharedmoney;


	Moneybag() 
	:money(0)
	{
		sharedmoney = 0;
	}

	Moneybag(int dep)
		:money(dep)
	{
		sharedmoney = 0;
	}
	void costmoney(int cost) {
		money -= cost;
	}
	void depositmoney(int th) {
		money += th * 9 / 10;
		sharedmoney += th / 10;
	}
	void showmoney() {
		cout << money << endl;
	}
	void showsharedmoney() {
		cout << sharedmoney << endl;
	}
private:
	int money;
	
};
int Moneybag::sharedmoney;//!important

int main() {
	Moneybag A(100);
	Moneybag B(1000);
	A.depositmoney(1000);
	B.depositmoney(100);
	A.costmoney(500);
	B.costmoney(500);
	A.showmoney();
	B.showmoney();
	A.showsharedmoney();
}
