#include <iostream>
#include <vector>

using namespace std;

// Computational complexity of the sequential search = O(n)

int sequentialSearch(int search, vector <int> input){ 

    for (int i=0; i<input.size(); i++){ // Iterates trough the vector
        if (input[i] == search) return i; // If the number chosen is found, the functions returns the ID
    }

    return -1; // Returns -1 otherwise
}

int main(){

    vector <int> a = {1, 4, 2, 9, 7, 8, 10}; // Test vector

    int ans = sequentialSearch(2, a); // Result of the search

    if (ans > -1) { // If it is found say where in the console
        cout << "Number found at " << ans << "!";
    }
    else { // If not, say so
        cout << "Number not found.";
    }

}