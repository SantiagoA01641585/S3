#include <iostream>
#include <vector>
#include <fstream>
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


//Merge Function
void merge(vector<string> &arr, int l, int m, int r){
    //Tamaño de los subarreglos a fucionar
    int n1 = m-l+1;
    int n2 = r-m;

    //SubArreglos temporales
    vector <string> L(n1), R(n2);

    //Copia el vector en los SubArreglos temporales
    for(int i = 0; i < n1;i++){
        L[i] = arr[l+i];
    }
    for(int j = 0; j <n2;j++){
        R[j] = arr[m+1+j];
    }

    //Fusion de los arreglos
    int i=0, j=0, k=l;
    while (i < n1 && j < n2){
        if (dateToInt(getMonth(L[i])) < dateToInt(getMonth(R[j]))){
            arr[k] = L[i];
            i++;
        }
        else if (dateToInt(getMonth(L[i])) == dateToInt(getMonth(R[j]))){
            if (getDate(L[i]) <= getDate(R[j])){
                arr[k] = L[i];
                i++;
            }
            else{
                arr[k] = R[j];
                j++;
            }
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //copia de los elementos restantes, si hay
    while(i < n1){ arr[k]=L[i]; i++; k++; }
    while(j <n2){ arr[k]=R[j]; j++; k++; }

}

//Merge Sort - Complexity: O(n log n)
vector<string> mergeSort(vector<string> &arr, int l, int r){
    if(l<r){
        // El Punto medio del vector
        int m = (l+r)/2; 

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        // Fusiona ambas mitades
        merge(arr,l,m,r); 
    }

    return arr;
}

void printVector(vector<string> vec){
    string listString = "";

    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << endl;
    }  
}

int main() {
    ifstream infile;
    ofstream outfile;

    std::vector<std::string> lines;
    string line;

    infile.open("bitacora.txt",std::ios::in);

    while (getline(infile, line)){ 
        lines.push_back(line);
    }

    infile.close();
    cout << "." << endl;

    sort(lines.begin() + 6, lines.end());
    vector<string> lineSorted = mergeSort(lines, 0, lines.size() - 1);

    cout << "." << endl;

    outfile.open("sorted.txt");
    for (int i = 0; i < lineSorted.size(); i++){
        outfile << lineSorted[i] << endl;
    }
    outfile.close();

    return 0;
}