#include <iostream>

using namespace std;

int recSum(int n){

    if (n >= 1) return n + recSum(n - 1); // If the number given is greater or equal to 1 it returns the number plus the same method with the number minus 1 until it is lesser than 1

    return 0;
}

int main(){

    int n;

    cout << "Recursive sum of numbres to n program:\n" << endl;
    cout << ">> ";

    cin >> n;

    cout << "\n" << endl;

    cout << recSum(n) << endl; // Returns the recursive method

}