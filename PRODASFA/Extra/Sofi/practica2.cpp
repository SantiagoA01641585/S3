#include <iostream>
using namespace std;

int main(){
    int numeros[7] = {9,2,1,8,3,5,2};
    int i, j, aux;
    int tamano = 7;
    
    cout << "Arreglo original:" <<endl;
    for (i=0; i<tamano; i++){
        cout << numeros[i]<<" ";
    }

    
    cout<<endl;

    for (i=0; i < (tamano-1); i++){ // dar valor inicial a comparar
    //vector -1 poruqe al comparar el penultimo numero con el ultimo no necesitamos comparar el ultimo.
    
        for (int j=i+1; j<tamano; j++){ //recorrer el vector contrastando con el siguiente numero.
            if (numeros[i] < numeros[j]){ //ascendente
                aux= numeros[j];
                numeros[i]=numeros[j];
                numeros[j]=aux;
            }
        }
    }
    cout << "Arreglo arreglado:" <<endl;
    for (i=0; i<tamano; i++){
       cout << numeros[i]<<" ";
    }
    cout<<endl;
    
}