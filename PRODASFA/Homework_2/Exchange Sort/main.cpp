#include <iostream>
#include <vector>

using namespace std;

vector <int> exchangeSort(vector <int> input){

    for(int i=0; i<input.size(); i++){ // Recorre todo el vector
        for(int j=i+1; j<input.size(); j++){ // Recorre el resto del vector hacia la derecha
            if(input[j]<input[i]){ // Compara el primer y el primer numero y si el posterior es menor se intercambian
                int temp = input[i]; // Método de intercambio
                input[i] = input[j];
                input[j] = temp;
            }
        }
    }

    return input;
}

int main(){

    vector <int> a = {1, 4, 2, 9, 7, 8, 10}; // Vector prueba

    vector <int> b = exchangeSort(a); // Resultado

    for (auto e:b){
        cout << e << " "; // Impresión de los elementos del nuevo vector
    }

}