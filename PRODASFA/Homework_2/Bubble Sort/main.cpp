#include <iostream>
#include <vector>

using namespace std;

// Computational complexity of the bubble sort = O(n^2)

vector <int> bubbleSort(vector <int> input){

    bool keep_on = true; // Flag to keep on

    while (keep_on){ // Continue until everything is sorted

        keep_on = false; // Flag to keep on turned off

        for (int i=0; i<input.size()-1; i++){ // Iterates trough the vector
            if(input[i+1] < input[i]){ // Compares the iterated element with the next one and if it is greater they swap
                int temp = input[i];
                input[i] = input[i+1]; // Swap method
                input[i+1] = temp;

                keep_on = true; // If it has to swap it isn't sorted
            }
        }
    }

    return input; // Returns the ordered vector
}

int main(){

    vector <int> a = {1, 4, 2, 9, 7, 8, 10}; // Test vector

    vector <int> b = bubbleSort(a); // Result

    for (auto e:b){
        cout << e << " "; // Prints the elements of the new vector
    }

}