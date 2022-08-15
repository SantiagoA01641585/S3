#include <iostream>

using namespace std;

int fibo(int i){
    // cout << "Entering to compute f" << i << endl;
    //Base step
    if (i<=2) return 1;

    //Induction
    return fibo(i-1) + fibo(i-2);
}

int main(){
    cout << fibo(8);
    return 0;
}
