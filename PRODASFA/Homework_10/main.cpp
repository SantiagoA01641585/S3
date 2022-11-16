#include <iostream>
#include <list>
#include <math.h>

using namespace std;

class quadraticHashTable{
    private:
        // Atributes
        int capacity;
        int* table;

        int c1, c2;

        int elements;

    public:
        // Constructors
        quadraticHashTable(int capacity, int c1, int c2){
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
        bool checkPrime(int val){
            if (val==0 || val==1) return false;

            for (int i=2; i*i<=val; i++){
                if (val%i == 0) return false;
            }

            return true;
        }

        int getPrime(int val){
            if (val%2 == 0) val++;

            while (!checkPrime(val)){
                val += 2;
            }

            return val;
        }

        int hashFunction(int val){
            float a = (sqrt(5) - 1) / 2;

            return (int)((fmod((float(val)*a), 1))*capacity);
        }

        int getKey(int val){
            if (elements==capacity) return -1;

            int key = hashFunction(val);

            int i=1;
            while(table[key]){
                key = (hashFunction(val) + i*c1 + i*i*c2) % capacity;
                
                i++;
            }

            return key;
        }

        void insert(int val){
            int key = getKey(val);

            if (key == -1) return;

            this->elements++;

            this->table[key] = val;
        }

        void printHashTable(){
            for (int i=0; i<capacity; i++){
                cout << "Slot " << i << ": " << table[i] << endl;
            }
        }

};

class chainHashTable{
    private:
        // Atributes
        int capacity;
        list<int>* table;

        int elements;

    public:
        // Constructors
        chainHashTable(int capacity){
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
        bool checkPrime(int val){
            if (val==0 || val==1) return false;

            for (int i=2; i*i<=val; i++){
                if (val%i == 0) return false;
            }

            return true;
        }

        int getPrime(int val){
            if (val%2 == 0) val++;

            while (!checkPrime(val)){
                val += 2;
            }

            return val;
        }

        int hashFunction(int val){
            float a = (sqrt(5) - 1) / 2;

            return (int)((fmod((float(val)*a), 1))*capacity);
        }

        void insert(int val){
            int key = hashFunction(val);

            table[key].push_back(val);

            this->elements++;
        }

        void printHashTable(){
            for (int i=0; i<capacity; i++){
                cout << "Slot " << i << ":";

                for (auto e:table[i]){
                    cout << " <- " << e; 
                }

                cout << endl;
            }
        }

};

int main(){
    quadraticHashTable quadTable(4, 5, 7);
    chainHashTable chainTable(4);

    quadTable.insert(6);
    quadTable.insert(9);
    quadTable.insert(1);
    quadTable.insert(2);
    quadTable.insert(8);

    chainTable.insert(6);
    chainTable.insert(9);
    chainTable.insert(1);
    chainTable.insert(2);
    chainTable.insert(8);

    quadTable.printHashTable();

    cout << endl;

    chainTable.printHashTable();
}