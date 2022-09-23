#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int dateToInt(string month){
    vector<string> months = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dic" };

    for (int i = 0; i < months.size(); i++){
        if (month == months[i]){
            return i + 1;
        }
    }

    return -1;
}

string getMonth(string date){
    string month = date.substr(0, 3);
    return month;
}

int getDate(string date){
    string day = date.substr(4, 2);
    return stoi(day);
} 

vector<string> merge(vector<string> left, vector<string> right) {
    vector<string> result;
    
    while (left.size() > 0 || right.size() > 0) {
        if (left.size() > 0 && right.size() > 0) {
            if (dateToInt(getMonth(left.front())) < dateToInt(getMonth(right.front()))) {
                result.push_back(left.front());
                left.erase(left.begin());
            } 
            else if (dateToInt(getMonth(left.front())) == dateToInt(getMonth(right.front()))){
                if (getDate(left.front()) <= getDate(left.front())){
                    result.push_back(left.front());
                    left.erase(left.begin());
                }
                else{
                    result.push_back(right.front());
                    right.erase(right.begin());
                }
            }
            else {
                result.push_back(right.front());
                right.erase(right.begin());
            }
        } else if (left.size() > 0) {
            for (int i = 0; i < left.size(); i++) {
                result.push_back(left[i]);
            }
            break;
        } else if (right.size() > 0) {
            for (int i = 0; i < right.size(); i++) {
                result.push_back(right[i]);
            }
            break;
        }
    }
    
    return result;
}

vector<string> mergeSort(vector<string> array) {
    if (array.size() == 1) {
        return array;
    }

    vector<string> left, right;

    for (int i = 0; i < array.size() / 2; i++) {
        left.push_back(array[i]);
    }
    for (int i = array.size() / 2; i < array.size(); i++) {
        right.push_back(array[i]);
    }

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

// Binary Search - Complexity: O(log n)
int binarySearch(vector<int> A, int k){
    int l = 0;
    // Se obtiene el tamaño del vector
    int r = A.size() - 1;

    while (l <= r){
        // Se obtiene el punto medio del vector
        int m = (l + r) / 2;
        // Si el elemento se encuentra en el punto medio, se regresa el punto medio
        if (k == A[m]) {
            return m;
        }
        // Si el elemento es menor que el punto medio, se busca en la mitad izquierda
        else if (k < A[m]) r = m - 1;
        // Si el elemento es mayor que el punto medio, se busca en la mitad derecha
        else l = m + 1;
    }

    return -1;
}

// closest element to left
int closestToLeft(vector<string> &arr, int n, int x){
    int l = 0, r = n - 1, res = -1;
    while (l <= r){
        int m = (l + r) / 2;
        if (dateToInt(getMonth(arr[m])) < x){
            res = m;
            l = m + 1;
        }
        else{
            r = m - 1;
        }
    }
    return res;
}

// void printVector(vector<string> vec){
//     string listString = "";

//     for (int i = 0; i < vec.size(); i++){
//         cout << vec[i] << endl;
//     }  
// }

vector <int> separateDate(string input){
    vector <int> out;

    string res;

    for(auto c:input){

        if(c=='/'){

            int p1 = stoi(res);
            
            out.push_back(p1);

            res.clear();

            continue;

        }

        res += c;        
    }

    int p2 = stoi(res);

    out.push_back(p2);

    return out;
}

// Binary Search with ceil adjustment - Complexity: O(nlog n)
int searchtoCeil(vector <int> search, vector <string> input){

    int ID = input.size()/2;
    int low = 0;
    int high = input.size();

    int masternum_search = search[1]*31 + search[0];

    while (true)
    {

        int masternum_test = dateToInt(getMonth(input[ID]))*31 + getDate(input[ID]);


        if (masternum_test == masternum_search){

            int cont = 0;

            do{

                if(ID+cont < input.size()) masternum_test = dateToInt(getMonth(input[ID + cont]))*31 + getDate(input[ID + cont]);
                else return ID + cont;

                cont ++;

            } while(masternum_test <= masternum_search);

            return ID + cont - 1;
            
        }

        if (low == ID || high == ID){

            if (ID == 0) return 0;

            return ID + 1;

        }

        if (masternum_test > masternum_search) high = ID; // If the actual number is greater, the higher limit is brought down
        else if (masternum_test < masternum_search) low = ID;

        ID = (high + low) / 2;
    }
    
}

// Binary Search with floor adjustment - Complexity: O(nlog n)
int searchtoFloor(vector <int> search, vector <string> input){

    int ID = input.size()/2;
    int low = 0;
    int high = input.size();

    int masternum_search = search[1]*31 + search[0];

    while (true)
    {

        int masternum_test = dateToInt(getMonth(input[ID]))*31 + getDate(input[ID]);


        if (masternum_test == masternum_search){

            int cont = 0;

            do{

                if(ID+cont >= 0) masternum_test = dateToInt(getMonth(input[ID + cont]))*31 + getDate(input[ID + cont]);
                else return ID + cont + 1;

                cont --;

            } while(masternum_test >= masternum_search);

            return ID + cont + 2;
            
        }

        if (low == ID || high == ID){

            if (ID == 0) return 0;

            return ID + 1;

        }

        if (masternum_test > masternum_search) high = ID; // If the actual number is greater, the higher limit is brought down
        else if (masternum_test < masternum_search) low = ID;

        ID = (high + low) / 2;
    }
    
}

int main() {
    ifstream infile;
    ofstream outfile;

    std::vector<std::string> lines;
    string line;

    infile.open("bitacora.txt");

    while (getline(infile, line)){ 
        lines.push_back(line);
    }

    infile.close();

    for (int i = 0; i < lines.size(); i++) {
        if (lines[i][4] >= '0' && lines[i][4] <= '9' && lines[i][5] == ' ') {
            lines[i].insert(4, "0");
        }
    }

    sort(lines.begin() + 3, lines.end());

    cout << "Sorting...\n" << endl;

    vector <string> lineSorted = mergeSort(lines);

    cout << "Creating new file...\n" << endl;

    outfile.open("sorted.txt");
    for (int i = 0; i < lineSorted.size(); i++){
        outfile << lineSorted[i] << endl;
    }
    outfile.close();

    string start, end;

    cout << "Sorted file created!\n" << endl;

    cout << "---------\n" << endl;

    cout << "Please input the start date (DD/MM):\n\n";

    cout << ">> ";

    cin >> start;

    cout << "\n\nPlease input the end date (DD/MM):\n\n";

    cout << ">> ";

    cin >> end;

    cout << endl << endl;

    vector <int> startV = separateDate(start);

    vector <int> endV = separateDate(end);

    int ID_low = searchtoCeil(startV, lineSorted);

    int ID_high = searchtoFloor(endV, lineSorted);

    for (int i = ID_low; i < ID_high; i++){
        cout << lineSorted[i] << endl;
    }    

    return 0;
}