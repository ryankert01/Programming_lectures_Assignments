#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		int max = 0;
		int min = 100;
		for (int i = 0; i < n; ++i) {
			int x;
			cin >> x;
			if (x > max) {
				max = x;
			}
			if (x < min) {
				min = x;
			}
		}
		cout << 2 * (max - min) << endl;
	}
}