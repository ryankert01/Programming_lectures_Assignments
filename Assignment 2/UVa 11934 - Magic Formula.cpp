#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int a, b, c, d, L;
	while (cin >> a >> b >> c >> d >> L) {
		if (!(a+b+c+d+L)) {
			break;
		}
		int t=0;
		for (int i=0; i <= L; ++i) {
			if ((i * i * a + i * b + c) % d == 0) {
				t++;
			}
		}
		cout << t << endl;
	}
	return 0;
}