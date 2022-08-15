#include <iostream>

using namespace std;

int main(){

    int tam = 11;
    int arr[11] = {1, 4, 2, 8, 6, 2, 3, 8, 6, 9, 1};

    int tamtmp = tam;
    bool continua = true;

    while (continua){

        continua = false;

        for (int i=0; i<tamtmp-1; i++){

            if(arr[i]>arr[i+1]){

                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;

                continua = true;
                
            }
        }

        tamtmp--;

    }

    for(auto e:arr){
        cout << e << " - ";
    }
}