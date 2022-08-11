#include <iostream>

using namespace std;

int main(){

    int n;

    cout << "Direct sum of numbres to n program:\n" << endl;
    cout << ">> ";

    cin >> n;

    cout << "\n" << endl;

    if(n>=1) cout << (n*(n+1))/2 << endl; // Aplies the mathematical function to sum all the numbres to n
    else cout << 0 << endl;
}