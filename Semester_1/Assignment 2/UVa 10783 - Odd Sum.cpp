#include <iostream>
using namespace std;

int main() {

    int t, a, b;
    cin >> t;

    for (int T = 0; T < t; T++) {

        cin >> a >> b;
        int sum = 0;
        if (a%2==0){
            a++;
        }
        if (b%2==0){
            b--;
        }
        sum = (a+b)/2*((b-a)/2+1);
        cout << "Case " << T + 1 << ": " << sum << endl;
    }
}