// Programa con SHA-256

#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//-------------------------------------------------------------------------

// Complexity O(n)
vector<int> separateIP(string ip) // Separates an IP, from a string into a vector
{
    istringstream iss(ip);
    std::vector<int> tokens;
    std::string token;
    while (std::getline(iss, token, '.')) // Fetches for the "."
    {
        if (!token.empty())
            tokens.push_back(stoi(token)); // Pushes the token back
    }

    return tokens; // Returns the vector
}

int ipStringToInt(string ip){
  vector <int> arr = separateIP(ip);

  int res = 0;
  for (int  i = 0; i<arr.size(); i++){
    switch (i){
      case 0:
        res += arr[0] * 10000000;
        break;

      case 1:
        res += arr[1] * 100000;
        break;

      case 2:
        res += arr[2] * 100;
        break;

      case 3:
        res += arr[3];
        break;
      
      default:
        break;
    }
  }

  return res;
}

// Complexity O(n)
vector<string> getData(string line)
{
    int count = 0;
    string fecha = "";
    string ip = "";
    string dominio = "";
    bool isDominio = false;

    for (int i = 0; i < line.length(); i++) // Iterates the string
    {
        if (line[i] == ' ') // Counts if there is a space
        {
            count++;
        }

        if (count < 3)
        {
            fecha += line[i];
        }
        else if (count == 3)
        {
            if (!isDominio && line[i] != ':')
                ip += line[i];
            else if (line[i] != ':')
                dominio += line[i];

            if (line[i] == ':')
                isDominio = true;
        }
    }

    return {fecha, ip, dominio}; // Returns the vector
}

//------------------------------------------------------------------

class Nodo{
  private:
    // Atributes
    string ip;
    int num_accesos;
    vector <string> accesos;
    vector <int> puertos;

  public:
    // Constructor
    Nodo(){
      this->ip = "NULL";
      this->num_accesos = 0;
      this->accesos.clear();
      this->puertos.clear();
    }

    Nodo(vector<string> values){
      this->ip = values[1];
      this->num_accesos = 1;

      this->accesos.clear();
      this->puertos.clear();
      this->accesos.push_back(values[0]);
      this->puertos.push_back(stoi(values[2]));
    }

    // Getters & Setters
    string getIP(){
      return this->ip;
    }

    void setIP(string ip){
      this->ip = ip;
    }

    int getNumAccesos(){
      return this->num_accesos;
    }

    void setNumAccesos(int num_accesos){
      this->num_accesos = num_accesos;
    }

    vector <string> getAccesos(){
      return this->accesos;
    }

    vector <int> getPuertos(){
      return this->puertos;
    }

    void increaseData(vector<string> data){
      this->num_accesos++;
      this->accesos.push_back(data[0]);
      this->puertos.push_back(stoi(data[2]));
    }
};

class quadraticHashTable{ // Hash table that resolves colissions with quadratic probing
    private:
        // Atributes
        int capacity;
        Nodo* table;

        int c1, c2; // Constants for the probing

        int elements;

    public:
        // Constructors
        quadraticHashTable(int capacity, int c1, int c2){ // Sets the capacity and the constants
            this->capacity = getPrime(capacity); 
            this->c1 = getPrime(c1);
            this->c2 = getPrime(c2);
            table = new Nodo[this->capacity];

            this->elements=0;
        }

        // Getters & Setters
        int getCapacity() const{
            return this->capacity;
        }

        void setCapacity(int capacity){
            this->capacity = capacity;
        }

        Nodo* getTable(){
            return this->table;
        }

        void setTable(Nodo* table){
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
            while(table[key].getIP() != "NULL"){ // Increasses the iterable until it finds a free space
                key = (hashFunction(val) + i*c1 + i*i*c2) % capacity; // Get the next key using the quadratic probing algorithm
                
                i++;
            }

            return key; // 
        }

        void insert(Nodo val){ // Inserts a new value - Complexity O(1 + n/m)
            int key = getKey(ipStringToInt(val.getIP())); // Gets the key

            if (key == -1) return; // If full, it exits

            this->elements++; // Increasses the number of elements in the table

            this->table[key] = val; // Inserts the value at the adress given by the key
        }

        void printIPData(string ip){
          int value = ipStringToInt(ip);
          int key = hashFunction(value);

          int i=1;
          while(table[key].getIP() != ip){ // Increasses the iterable until it finds a free space
                key = (hashFunction(value) + i*c1 + i*i*c2) % this->capacity; // Get the next key using the quadratic probing algorithm
                
                i++;
          }

          if (table[key].getIP() == "NULL"){
            cout << "Dato no encontrado" << endl;
            return;
          }

          cout << "Slot " << key << ": " << table[key].getIP();
          cout << " - " << table[key].getNumAccesos() << endl;

        
          vector <int> port = table[key].getPuertos();
          vector <string> access = table[key].getAccesos();
          for (int j=0; j<port.size(); j++){
            cout << "\t" << port[j] << " - " << access[j] << endl;
          }
          
        }

        void printHashTable(){ // Prints the hash table - Complexity O(n)
            for (int i=0; i<capacity; i++){
                cout << "Slot " << i << ": " << table[i].getIP();
                cout << " - " << table[i].getNumAccesos() << endl;

              
                vector <int> port = table[i].getPuertos();
                vector <string> access = table[i].getAccesos();
                for (int j=0; j<port.size(); j++){
                  cout << "\t" << port[j] << " - " << access[j] << endl;
                }
            }
        }

};

int main(){
  ifstream infile;
  ofstream outfile;

  std::vector<std::string> lines;
  string line;

  quadraticHashTable table(4, 5, 8);

  
  vector <string> arr1 = getData("Aug 28 23:07:49 897.53.984.6:6710 Failed password for root");
  vector <string> arr2 = getData("Aug 28 23:07:49 897.53.984.6:8462 Failed password for root");
  
  Nodo n1(arr1);

  n1.increaseData(arr2);

  table.insert(n1);

  table.printIPData("897.53.984.6");

  /*// Open the input file
  infile.open("bitacora.txt");

  // If the file is open
  while (getline(infile, line)){
    vector<string> values = getData(line);
    // Hashear IP (hashFunction(values[1]))
    // Ver si ya existe un nodo en la hash table
    // Si ya existe, incementar el numero de accesos 
    // y añadir a la lista los accesos y puertos 
    // nodo.increaseData(values);
    // de lo contrario crear un nuevo nodo
    Nodo *newNode = new Nodo(values);
    // E insertar nodo en hash table
    //hashTable.insert()
  }*/

  cout << endl;
  return 0;
}