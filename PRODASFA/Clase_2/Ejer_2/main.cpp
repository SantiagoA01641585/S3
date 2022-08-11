#include <iostream>

using namespace std;

int fact(int nfact){

    if (nfact > 1) return nfact + fact(nfact - 1);

    return 1;
}

int main(){

    cout << fact(4);

}