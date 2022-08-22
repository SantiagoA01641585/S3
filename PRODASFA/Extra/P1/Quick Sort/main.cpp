#include <iostream>

using namespace std;

int Quick(int *A, int start, int end){
    int piv = A[end];
    int Pind = start;

    for (int i=start; i<end; i++){
        if(A[i] <= piv){
            swap(A[i], A[Pind]);
            Pind++;
        }
    }

    swap(A[Pind], A[end]);

    return Pind;
}

void QuickSort(int *A, int start, int end){
    if (start >= end) return;

    int Index = Quick(A, start, end);

    QuickSort(A, start, Index - 1);
    QuickSort(A, Index + 1, end);
}

int main(){
    int test[8] = {1, 5, 2, 7, 3, 6, 8, 4};

    QuickSort(test, 0, 8);

    for (auto e:test){
        cout << e << " - ";
    }
}