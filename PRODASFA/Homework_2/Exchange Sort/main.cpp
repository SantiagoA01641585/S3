#include <iostream>
#include <vector>

using namespace std;

vector <int> exchangeSort(vector <int> input){

    for(int i=0; i<input.size(); i++){ // Iterates trough the vector
        for(int j=i+1; j<input.size(); j++){ // Goes trough the rest of the vector on the right
            if(input[j]<input[i]){ // Compares both numbers and if the second one is greater they swap
                int temp = input[i]; // Exchange method
                input[i] = input[j];
                input[j] = temp;
            }
        }
    }

    return input;
}

int main(){

    vector <int> a = {1, 4, 2, 9, 7, 8, 10}; // Test vector

    vector <int> b = exchangeSort(a); // Result

    for (auto e:b){
        cout << e << " "; // Prints the elements of the new vector
    }

}