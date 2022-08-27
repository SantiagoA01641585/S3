#include <iostream>
#include <vector>

using namespace std;

int main(){

    int n;

    vector <vector <char>> map;

    cin >> n;

    for (int i=0; i<n; i++){

        map.assign(8, vector <char> (8));

        // Leer lineas
        for(int y=0; y<8; y++){

            string line;

            cin >> line;

            for (int x=0; x<8; x++){
                map[x][y] = line[x];
            }
        }

        // Buscar interseccion
        for (int y=1; y<7; y++){
            for (int x=1; x<7; x++){
                if(map[x-1][y-1] == '#' && map[x+1][y-1] == '#' && map[x+1][y+1] == '#' && map[x-1][y-1] == '#'){
                    cout << y+1 << " " << x+1 << endl;
                }
            }
        }

        map.clear();
    }
    

    
    
}