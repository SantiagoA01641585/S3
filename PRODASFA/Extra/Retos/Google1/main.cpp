#include <iostream>
#include <string>

using namespace std;

int main(){
    string input;

    cin >> input;

    int cont = 0;
    for (int i=0; i<input.size() - 1; i++){
        if (input[i] == 'a'){
            if (input[i+1] == 'b') continue;
            if (input[i+1] == 'a') cont += 2;
            if (input[i+1] == 'c') cont++;
        }
        if (input[i] == 'b'){
            if (input[i+1] == 'c') continue;
            if (input[i+1] == 'b') cont += 2;
            if (input[i+1] == 'a') cont++;
        }
        if (input[i] == 'c'){
            if (input[i+1] == 'a') continue;
            if (input[i+1] == 'c') cont += 2;
            if (input[i+1] == 'b') cont++;
        }
    }

    cout << endl << cont;
}