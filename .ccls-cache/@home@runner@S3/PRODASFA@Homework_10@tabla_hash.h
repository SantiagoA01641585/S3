#include <iostream>
#include <list>
#include <math.h>

using namespace std;

class quadraticHashTable{ // Hash table that resolves colissions with quadratic probing
    private:
        // Atributes
        int capacity;
        int* table;

        int c1, c2; // Constants for the probing

        int elements;

    public:
        // Constructors
        quadraticHashTable(int capacity, int c1, int c2){ // Sets the capacity and the constants
            this->capacity = getPrime(capacity); 
            this->c1 = getPrime(c1);
            this->c2 = getPrime(c2);
            table = new int[this->capacity];

            this->elements=0;

            for (int i=0; i<=capacity; i++){
                table[i] = 0;
            }
        }

        // Getters & Setters
        int getCapacity() const{
            return this->capacity;
        }

        void setCapacity(int capacity){
            this->capacity = capacity;
        }

        int* getTable(){
            return this->table;
        }

        void setTable(int* table){
            this->table = table;
        }

        // Methods
        bool checkPrime(int val){ // Checks if the value is a prime number - Complexity O(sqrt(n))
            if (val==0 || val==1) return false;

            for (int i=2; i*i<=val; i++){
                if (val%i == 0) return false;
            }

            return true;
        }

        int getPrime(int val){ // Goes to the next prime number - Complexity O((n^2)(sqrt(n))) (Given by Andrica's Conjecture)
            if (val%2 == 0) val++; // Makes de value odd as all prime numbers after 2 have to be odd

            while (!checkPrime(val)){ // While the number is not a prime number
                val += 2; // Increasses by two
            }

            return val; // Returns the number
        }

        int hashFunction(int val){ // Hash function using multiplication method - Complexity O(1)
            float a = (sqrt(5) - 1) / 2; // A constant sugested by Knuth

            return (int)((fmod((float(val)*a), 1))*capacity); // Multiplication method
        }

        int getKey(int val){ // Quadratic probing - Complexity O(1 + n/m)
            if (elements==capacity) return -1; // If the hash table is full

            int key = hashFunction(val); // Gets the initial key

            int i=1;
            while(table[key]){ // Increasses the iterable until it finds a free space
                key = (hashFunction(val) + i*c1 + i*i*c2) % capacity; // Get the next key using the quadratic probing algorithm
                
                i++;
            }

            return key; // 
        }

        void insert(int val){ // Inserts a new value - Complexity O(1 + n/m)
            int key = getKey(val); // Gets the key

            if (key == -1) return; // If full, it exits

            this->elements++; // Increasses the number of elements in the table

            this->table[key] = val; // Inserts the value at the adress given by the key
        }

        void printHashTable(){ // Prints the hash table - Complexity O(n)
            for (int i=0; i<capacity; i++){
                cout << "Slot " << i << ": " << table[i] << endl;
            }
        }

};

class chainHashTable{ // Hash table that resolves colissions with chaining
    private:
        // Atributes
        int capacity;
        list<int>* table;

        int elements;

    public:
        // Constructors
        chainHashTable(int capacity){ // Sets the capacity
            this->capacity = getPrime(capacity);

            table = new list<int>[this->capacity];

            for (int i=0; i<this->capacity; i++){
                table[i].clear();
            }

            this->elements=0;
        }

        // Getters & Setters
        int getCapacity() const{
            return this->capacity;
        }

        void setCapacity(int capacity){
            this->capacity = capacity;
        }

        list<int>* getTable(){
            return this->table;
        }

        void setTable(list<int>* table){
            this->table = table;
        }

        // Methods
        bool checkPrime(int val){ // Checks if the value is a prime number - Complexity O(sqrt(n))
            if (val==0 || val==1) return false;

            for (int i=2; i*i<=val; i++){
                if (val%i == 0) return false;
            }

            return true;
        }

        int getPrime(int val){ // Goes to the next prime number - Complexity O((n^2)(sqrt(n))) (Given by Andrica's Conjecture)
            if (val%2 == 0) val++; // Makes de value odd as all prime numbers after 2 have to be odd

            while (!checkPrime(val)){ // While the number is not a prime number
                val += 2; // Increasses by two
            }

            return val; // Returns the number
        }

        int hashFunction(int val){ // Hash function using multiplication method - Complexity O(1)
            float a = (sqrt(5) - 1) / 2; // A constant sugested by Knuth

            return (int)((fmod((float(val)*a), 1))*capacity); // Multiplication method
        }

        void insert(int val){ // Inserts a new value - Complexity O(1 + n/m)
            int key = hashFunction(val); // Gets the key

            table[key].push_back(val); // Pushes it in the slot

            this->elements++; // Increasses the number of elements
        }

        void printHashTable(){ // Prints the hash table - Complexity O(n + n/m)
            for (int i=0; i<capacity; i++){ // Iterates through all the elements of the array
                cout << "Slot " << i << ":";

                for (auto e:table[i]){ // Iterates thorugh its sub-elements
                    cout << " <- " << e; 
                }

                cout << endl;
            }
        }

};