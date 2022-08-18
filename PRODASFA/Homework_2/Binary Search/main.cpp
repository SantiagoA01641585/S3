#include <iostream>
#include <vector>

using namespace std;

// Computational complexity of the merge sort = O(nlog(n))
// Computational complexity of the binary search = O(log(n))
// Total computational complexity = O(nlog(n) + log(n)) = O(nlog(n))

vector <int> mergeVectors(vector <int> a, vector <int> b){ // Function that merges two given ordered vectors

    int conta, contb; // Creates and initializates two counters for each vector
    conta = contb = 0;

    vector <int> c; // Creates a new vector for the result

    while (conta < a.size() || contb < b.size()){ // Remains executing until both counters reach their limit
        if(a[conta] <= b[contb]){ // Compares the elements from lowest to greatest in each vector
            if (conta < a.size()) c.push_back(a[conta]); // If the counter has not reached it's limit, it pushes back the content to the new vector
            conta++; // Adds one to the counter
            continue; // Goes back to the cicle evaluation
        }

        if (contb < b.size()) c.push_back(b[contb]); // If the counter has not reached it's limit, it pushes back the content to the new vector
        contb++; // Adds one to the counter
    }

    return c; // Returns the new vector
}

vector <int> mergeSort(vector <int> input){

    if (input.size() > 1) { // If the input vector is greater than 1 it starts the recursion

        int middle = input.size()/2; // Finds the middle ID

        vector <int> a, b; // Creates two vectors for the left and right part of the original input vector

        for (int i=0; i<middle; i++){ // Iterates trough the first part of the vector
            a.push_back(input[i]); // Pushes it's content to the left vector
        }

        for (int i=middle; i<input.size(); i++){ // Iterates trough the second part of the vector
            b.push_back(input[i]); // Pushes it's content to the right vector
        }

        vector <int> a1 = mergeSort(a); // Does recursion on the left part until the size is 1
        vector <int> b1 = mergeSort(b); // Does recursion on the right part until the size is 1

        vector <int> c = mergeVectors(a1, b1); // Merges and orders the two resultant ordered vectors

        return c; // Returns the ordered vector

    }

    return input; // If the size is 1, it returns the small vector
}

int binarySearch(int search, vector <int> input){

    int ID = input.size()/2; // Puts the ID in the middle
    int low = 0; // Puts the lowest point at 0
    int high = input.size(); // Puts the highest point at the size of the vector

    while (true){ // Repeats until the function returns something
        if (input[ID] == search) return ID; // If the searched numbver and the actual number are the same it returns it's ID

        if (low == ID || high == ID) return -1; // If the ID remains being either a low or a high point means the ID reached a limit, so it didn't find anything

        if (input[ID] > search) high = ID; // If the actual number is greater, the higher limit is brought down
        else if (input[ID] < search) low = ID; // If the actual number is lesser, the lower limit is brought up 

        ID = (high+low) / 2; // Average of the lower and higher points
    }

    return -1; // Returns -1 to avoid an annoing message at the start of compilation
}

int main(){

    vector <int> a = {1, 4, 2, 9, 7, 8, 10}; // Test vector

    vector <int> b = mergeSort(a); // Sorts the vector
    // 1 2 4 7 8 9 10

    int ans = binarySearch(2, b); // Result of the search

    if (ans > -1) { // If it is found say where in the console
        cout << "Number found at " << ans << "!";
    }
    else { // If not, say so
        cout << "Number not found.";
    }

}