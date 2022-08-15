#include <iostream>

using namespace std;

int main(){

    int tam = 11;
    int arr[11] = {1, 4, 2, 8, 6, 2, 3, 8, 6, 9, 1};

    int srtID = 0;

    for (int i=0; i<tam; i++){

        for (int j=i; j<tam; j++){
            if (arr[j]<=arr[srtID]){
                 srtID = j;
            }
        }

        int tmp = arr[srtID];
        arr[srtID] = arr[i];
        arr[i] = tmp;

    }

    for(auto e:arr){
        cout << e << " - ";
    }
}