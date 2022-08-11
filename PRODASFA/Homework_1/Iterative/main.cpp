#include <iostream>

using namespace std;

int main(){
    int n;

    cout << "Iterative sum of numbres to n program:\n" << endl;
    cout << ">> ";

    cin >> n;

    cout << "\n" << endl;

    int sum = 0; // Saves the total of the sum

    for(int i=1; i<=n; i++){ // Iterates summing the counter to the sum
        sum += i;
    }

    cout << sum << endl;
}