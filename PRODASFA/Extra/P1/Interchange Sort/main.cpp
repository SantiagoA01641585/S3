#include <iostream>

using namespace std;

int main(){

    int tam = 11;
    int arr[11] = {1, 4, 2, 8, 6, 2, 3, 8, 6, 9, 1};

    for (int i=0; i<tam-1; i++){
        for(int k=i+1; k<tam; k++){
            if(arr[i]>arr[k] && k!=i){
                int tmp = arr[i];
                arr[i] = arr[k];
                arr[k] = tmp;
            }
        }
    }

    for(auto e:arr){
        cout << e << " - ";
    }
}