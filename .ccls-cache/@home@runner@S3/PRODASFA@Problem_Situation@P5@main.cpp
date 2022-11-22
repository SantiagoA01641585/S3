// Programa con SHA-256

#include <iostream>
#include <math.h>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Nodo{
  private:
    // Atributes
    string ip;
    int num_accesos;
    list <string> accesos;
    list <int> puertos;

  public:
    // Getters & Setters
    string getIP(){
      return this->ip;
    }

    void setIP(string ip){
      this->ip = ip;
    }

    int getNumAcceso(){
      return this->num_accesos;
    }

    void setNumAccesos(int num_accesos){
      this->num_accesos = num_accesos;
    }
};

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

int main(){

  
  cout << endl;
  return 0;
}