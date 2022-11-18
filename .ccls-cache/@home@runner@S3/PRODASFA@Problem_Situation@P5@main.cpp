// Programa con SHA-256

#include <iostream>
#include <math.h>
#include <list>

using namespace std;

class Nodo{
  private:
    // Atributes
    string ip;
    int num_accesos;
    list <int> accesos;
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

int main(){

  
  cout << endl;
  return 0;
}