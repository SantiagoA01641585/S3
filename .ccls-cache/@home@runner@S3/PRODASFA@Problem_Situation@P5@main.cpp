// Programa con SHA-256

#include <fstream>
#include <iostream>
#include <list>
#include <math.h>
#include <sstream>
#include <vector>

using namespace std;

// Iker Ochoa Villaseñor - A01640984
// Santiago Vera Espinoza - A01641585
// Carlos Adrián Palmieri Álvarez - A01635776

//-------------------------------------------------------------------------

// Separate IP Function - Complexity O(n)
vector<long long int> separateIP(string ip)
{ // Separates an IP, from a string into a vector
    istringstream iss(ip);
    std::vector<long long int> tokens;
    std::string token;
    while (std::getline(iss, token, '.')) // Fetches for the "."
    {
        if (!token.empty())
            tokens.push_back(stoll(token)); // Pushes the token back
    }

    return tokens; // Returns the vector
}

// IP String To Int Funtion - Complexity O(n)
long long int ipStringToInt(string ip)
{
    vector<long long int> arr = separateIP(ip);
    // Converts the IP from string to int

    long long int res = 0;
    for (int i = 0; i < arr.size(); i++)
    { // Iterates through the vector
        switch (i)
        { // Switches the position of the IP
        case 0:
            res = arr[0] * 10000000;
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
    // Returns the IP in int
}

// Get Data Function - Complexity O(n)
vector<string> getData(string line)
{
    int count = 0;
    string fecha = "";
    string ip = "";
    string dominio = "";
    bool isDominio = false;
    // Variables to store the data

    for (int i = 0; i < line.length(); i++) // Iterates the string
    {                                       // Checks if the character is a space
        if (line[i] == ' ')
        {
            count++;
            // If it is, it adds 1 to the counter
        }

        if (count < 3)
        { // If the counter is less than 3, it is a date
            fecha += line[i];
        }
        else if (count == 3 && line[i] != ' ')
        { // If the counter is 3, it is an IP
            if (!isDominio && line[i] != ':')
                // If it is not a domain and there is not a colon, it is an IP
                ip += line[i];
            else if (line[i] != ':')
                // If it is a domain and there is a colon, it is a domain
                dominio += line[i];

            if (line[i] == ':')
                // If there is a colon, it is a domain
                isDominio = true;
        }
    }

    return {fecha, ip, dominio}; // Returns the vector
}

//------------------------------------------------------------------

class Nodo
{
private:
    // Atributes
    string ip;
    int num_accesos;
    vector<string> accesos;
    vector<int> puertos;

public:
    // Constructor
    Nodo()
    {
        this->ip = "NULL";
        this->num_accesos = 0;
        this->accesos.clear();
        this->puertos.clear();
    }

    Nodo(vector<string> values)
    {
        this->ip = values[1];
        this->num_accesos = 1;

        this->accesos.clear();
        this->puertos.clear();
        this->accesos.push_back(values[0]);
        this->puertos.push_back(stoi(values[2]));
    }

    // Getters & Setters
    string getIP() { return this->ip; }

    void setIP(string ip) { this->ip = ip; }

    int getNumAccesos() { return this->num_accesos; }

    void setNumAccesos(int num_accesos) { this->num_accesos = num_accesos; }

    vector<string> getAccesos() { return this->accesos; }

    vector<int> getPuertos() { return this->puertos; }

    void increaseData(vector<string> data)
    { // Increases the data of the node
        this->num_accesos++;
        this->accesos.push_back(data[0]);
        this->puertos.push_back(stoi(data[2]));
    }
};

class quadraticHashTable
{ // Hash table that resolves colissions with quadratic
  // probing
private:
    // Atributes
    int capacity;
    Nodo *table;

    int c1, c2; // Constants for the probing

    int elements;

public:
    // Constructors
    quadraticHashTable(int capacity, int c1,
                       int c2)
    { // Sets the capacity and the constants
        this->capacity = getPrime(capacity);
        this->c1 = getPrime(c1);
        this->c2 = getPrime(c2);
        table = new Nodo[this->capacity];

        for (int i = 0; i < this->capacity; i++)
        { // Initializes the table
            table[i].setIP("NULL");
        }

        this->elements = 0;
    }

    // Getters & Setters
    int getCapacity() const { return this->capacity; }

    void setCapacity(int capacity) { this->capacity = capacity; }

    Nodo *getTable() { return this->table; }

    void setTable(Nodo *table) { this->table = table; }

    // Methods
    bool checkPrime(int val)
    { // Checks if the value is a prime number -
      // Complexity O(sqrt(n))
        if (val == 0 || val == 1)
            return false;

        for (int i = 2; i * i <= val; i++)
        { // Iterates through the value
            if (val % i == 0)
                return false;
        }

        return true;
    }

    int getPrime(int val)
    { // Goes to the next prime number - Complexity
      // O((n^2)(sqrt(n))) (Given by Andrica's Conjecture)
        if (val % 2 == 0)
            val++; // Makes de value odd as all prime numbers after 2 have to be odd

        while (!checkPrime(val))
        {             // While the number is not a prime number
            val += 2; // Increasses by two
        }

        return val; // Returns the number
    }

    int hashFunction(long long int val)
    {                                // Hash function using division method -
                                     // Complexity O(1)
        float a = (sqrt(5) - 1) / 2; // A constant sugested by Knuth

        int key = val % capacity;

        return key; // Multiplication method
    }

    int getKey(Nodo val)
    { // Quadratic probing - Complexity O(1 + n/m)
        if (elements == capacity)
            return -1; // If the hash table is full

        string value_str = val.getIP();
        long long int value = ipStringToInt(value_str);
        int key = hashFunction(value); // Gets the initial key

        int i = 1;
        while (table[key].getIP() !=
               "NULL")
        { // Increasses the iterable until it finds a free space
            if (table[key].getIP() == value_str)
                return key;

            key = (hashFunction(value) + i * c1 + i * i * c2) %
                  capacity; // Get the next key using the quadratic probing algorithm

            i++;
        }

        return key; //
    }

    void insert(Nodo val)
    {                          // Inserts a new value - Complexity O(1 + n/m)
        int key = getKey(val); // Gets the key

        if (key == -1)
            return; // If full, it exits

        this->elements++; // Increasses the number of elements in the table

        if (this->table[key].getIP() != "NULL")
        { // If the key is already in the table
            Nodo colision = table[key];
            // Gets the colisioned value

            vector<string> datos = {val.getAccesos()[0], val.getIP(),
                                    to_string(val.getPuertos()[0])};
            // Increases the data of the colisioned value
            colision.increaseData(datos);

            // Sets the new value
            table[key] = colision;

            return;
        }

        // Inserts the value at the adress given by the key
        vector<string> datos = {val.getAccesos()[0], val.getIP(),
                                to_string(val.getPuertos()[0])};
        Nodo n_nodo(datos);
        // Creates a new node with the data
        table[key] = n_nodo;
        // Inserts the node in the table
    }

    void printIPData(string ip)
    { // Prints the data of the given ip - Complexity O(1 + n/m)
        if (elements > capacity)
        { // If the table is full
            cout << "Dato no encontrado" << endl;
            return;
        }

        long long int value = ipStringToInt(ip);
        // Gets the hash value value of the ip
        int key = hashFunction(value);
        // Gets the key of the ip

        int i = 1;
        while (table[key].getIP() !=
               ip)
        { // Increasses the iterable until it finds a free space
            // cout << key << endl;
            key = (hashFunction(value) + i * c1 + i * i * c2) %
                  this->capacity; // Get the next key using the quadratic probing
                                  // algorithm

            i++;
        }

        cout << "Slot " << key << ": " << table[key].getIP();
        cout << " - " << table[key].getNumAccesos() << endl;

        vector<int> port = table[key].getPuertos();
        vector<string> access = table[key].getAccesos();
        for (int j = 0; j < port.size(); j++)
        { // Prints the data of the ip
            cout << "\t" << port[j] << " - " << access[j] << endl;
        }
    }

    void printHashTable()
    { // Prints the hash table - Complexity O(n)
        for (int i = 0; i < capacity; i++)
        { // Goes through the table
            cout << "Slot " << i << ": " << table[i].getIP();
            cout << " - " << table[i].getNumAccesos() << endl;
            // Prints the data of the ip
            vector<int> port = table[i].getPuertos();
            vector<string> access = table[i].getAccesos();
            for (int j = 0; j < port.size(); j++)
            { // Prints the data of the ip
                cout << "\t" << port[j] << " - " << access[j] << endl;
            }
        }
    }

    void writeOnFile()
    { // Write hash table on file hashTable.txt - Complexity O(n)
        ofstream file;
        file.open("hashTable.txt");
        // Opens the file

        for (int i = 0; i < capacity; i++)
        {
            // Goes through the table
            file << "Slot " << i << ": " << table[i].getIP();
            file << " - " << table[i].getNumAccesos() << endl;
            // Prints the data of the ip
            vector<int> port = table[i].getPuertos();
            vector<string> access = table[i].getAccesos();
            for (int j = 0; j < port.size(); j++)
            { // Write the data of the ip on File
                file << "\t" << port[j] << " - " << access[j] << endl;
            }
        }

        file.close();
        // Closes the file
    }
};

int main()
{
    ifstream infile;

    std::vector<std::string> lines;
    string line;

    quadraticHashTable table(16807, 5, 8);

    // Open the input file
    infile.open("bitacora.txt");

    // If the file is open
    while (getline(infile, line))
    {
        vector<string> values = getData(line);
        Nodo newNode(values);
        table.insert(newNode);
    }

    table.printHashTable();
    table.writeOnFile();

    infile.close();

    cout << endl;
    return 0;
}