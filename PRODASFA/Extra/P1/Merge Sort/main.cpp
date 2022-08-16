#include <iostream>
#include <vector>

using namespace std;

vector <int> mergeVector(vector<int> a, vector <int> b){
    int conta = 0;
    int contb = 0;

    vector <int> res;

    while (conta<a.size() || contb<b.size()){
        if(a[conta]<b[contb]){
            if(conta<a.size()) res.push_back(a[conta]);
            conta++;
            continue;
        }
        if(contb<b.size()) res.push_back(b[contb]);
        contb++;
    }

    return res;
}

vector <int> mergeSort(vector <int> input){

    if(input.size()>1){
        int middleId = input.size()/2 - 1;

        vector <int> p1, p2;

        for(int i=0; i<=middleId + 1; i++){
            if (i<middleId + 1) p1.push_back(input[i]);
            if (middleId + i + 1 < input.size()) p2.push_back(input[middleId + i + 1]);
        }

        vector <int> a = mergeSort(p1);
        vector <int> b = mergeSort(p2);

        return mergeVector(a, b);
    }

    return input;

}

int main(){

    vector <int> arr = {1, 4, 2, 8, 6, 2, 3, 8, 6, 9, 1};

    vector <int> d = mergeSort(arr);

    for (auto i:d){
        cout << i << " - ";
    }

}