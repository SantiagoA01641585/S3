#include <iostream>
#include <vector>

using namespace std;

string binaryStride(vector <int> &arr, int fetch){
    int pot = 1;
    int id = 0;

    bool exit = false;

    while(!exit){
        if (arr[id] == fetch) return "YES";
        if (arr[id] < fetch){

            if (id + pot > arr.size() - 1){
                id = arr.size() - 1;

                exit = true;
                continue;
            }

            id += pot;
            pot *= 2;

            continue;
        }

        exit = true;
    }

    pot /= 4;

    while (exit){
        if (pot == 0) return "NO";

        if (arr[id] == fetch) return "YES";

        if (arr[id - pot] < fetch){
            pot /= 2;
            continue;
        }

        id -= pot;
    }
}

int main(){
    int n, k;

    cin >> n >> k;

    vector <int> arr;
    vector <int> quer;

    for (int i=0; i<n; i++){
        int el;

        cin >> el;

        arr.push_back(el);
    }

    for (int i=0; i<k; i++){
        int el;

        cin >> el;

        cout << binaryStride(arr, el) << endl;
    }
}