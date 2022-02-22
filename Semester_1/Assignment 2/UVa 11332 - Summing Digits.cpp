#include <iostream>
using namespace std;


int g(int n){
    int sum = 0;
    while (n > 9)
        
    {
        sum = 0;
        while (n != 0) {
            sum = sum + n % 10;
            n = n / 10;
        }
        n = sum;
    }
    return n;
}
int main(){
    int input;
    while(cin >> input && input != 0){
        cout<<g(input)<<endl;
    }
}