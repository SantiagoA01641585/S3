#include <iostream>

using namespace std;

int recSum(int n){

    if (n >= 1) return n + recSum(n - 1);

    return 0;
}

int main(){

    int n;

    cout << "Recursive sum of numbres to n program:\n" << endl;
    cout << ">> ";

    cin >> n;

    cout << "\n" << endl;

    cout << recSum(n) << endl;

}