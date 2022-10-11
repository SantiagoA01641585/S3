#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream> // std::istringstream
#include <string>

using namespace std;

void printVector(vector<int> array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << endl;
    }
}

vector<int> separateIP(string ip)
{
    istringstream iss(ip);
    std::vector<int> tokens;
    std::string token;
    while (std::getline(iss, token, '.'))
    {
        if (!token.empty())
            tokens.push_back(stoi(token));
    }

    return tokens;
}

vector<int> getIP(string line)
{
    int count = 0;
    string ip = "";

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ' ')
        {
            count++;
        }

        if (count == 3)
        {
            ip += line[i];
        }
    }

    // fillIP("1.22.33.1:000");
    //printVector(separateIP(ip));
    return separateIP(ip);
}

// Merge Function - Complexity O(n)
vector<string> merge(vector<string> left, vector<string> right)
{
    int i = 0;
    // Create a vector to store the sorted values
    vector<string> result;

    // While both vectors have elements
    while (left.size() > 0 || right.size() > 0)
    {
        // If both vectors have elements
        if (left.size() > 0 && right.size() > 0)
        {
            // Compare the first elements of each vector
            if (getIP(left.front())[0] < getIP((right.front()))[0])
            {
                result.push_back(left.front());
                left.erase(left.begin());
            }
            else if (getIP(left.front())[0] == getIP((right.front()))[0])
            {
                if (getIP(left.front())[1] < getIP((right.front()))[1])
                {
                    result.push_back(left.front());
                    left.erase(left.begin());
                }
                else if (getIP(left.front())[1] == getIP((right.front()))[1])
                {
                    if (getIP(left.front())[2] < getIP((right.front()))[2])
                    {
                        result.push_back(left.front());
                        left.erase(left.begin());
                    }
                    else
                    {
                        result.push_back(right.front());
                        right.erase(right.begin());
                    }
                }
                else
                {
                    result.push_back(right.front());
                    right.erase(right.begin());
                }
            }
            else
            {
                result.push_back(right.front());
                right.erase(right.begin());
            }
        }
        else if (left.size() > 0)
        {
            for (int i = 0; i < left.size(); i++)
            {
                result.push_back(left[i]);
            }
            break;
            // If only the right vector has elements
        }
        else if (right.size() > 0)
        {
            for (int i = 0; i < right.size(); i++)
            {
                result.push_back(right[i]);
            }
            break;
        }
    }

    return result;
}

// Merge Sort Function - Complexity O(n log n)
vector<string> mergeSort(vector<string> array)
{
    // If the array has 1 or 0 elements, it is already sorted
    if (array.size() == 1)
    {
        return array;
    }

    // Create a vector to store the left half of the array
    vector<string> left, right;

    // Add the first half of the array to the left vector
    for (int i = 0; i < array.size() / 2; i++)
    {
        left.push_back(array[i]);
    }
    // Add the second half of the array to the right vector
    for (int i = array.size() / 2; i < array.size(); i++)
    {
        right.push_back(array[i]);
    }

    // Sort the left and right vectors
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the left and right vectors
    return merge(left, right);
}

bool isGreaterThan(string input, string target){ // Datos: input es solo el ip, target es la linea completa. Es el input mas grande que el target?
    vector <int> vec_input = getIP(input);
    vector <int> vec_target = separateIP(target);

    if (vec_input[0] > vec_target[0]) return true;

    if (vec_input[0] == vec_target[0]){
        if (vec_input[1] > vec_target[1]) return true;

        if (vec_input[1] == vec_target[1]){
            if (vec_input[2] > vec_target[2]) return true;

            if (vec_input[2] == vec_target[2]){
                if (vec_input[3] > vec_target[3]) return true;
            }
        }
    }

    return false;
}

int binarySearch(string fetch, vector <string> arr){

    bool time_to_exit = false;

    int num_elev = 1;

    int ptr = 0;

    while(!isGreaterThan(arr[ptr], fetch) && !time_to_exit){
        ptr = num_elev;

        num_elev *= 2;

        if (ptr > arr.size()){
            ptr = arr.size()-1;
            num_elev /= 2;

            time_to_exit = true;
            continue;
        }
    }

    while (num_elev != 1){
        num_elev /= 2;

        while (isGreaterThan(arr[ptr - num_elev], fetch)){
            ptr -= num_elev;
        }
    }

    if (!isGreaterThan(arr[ptr], fetch)) return ptr + 1;

    return ptr;
}

//------------------------------------------------------------------------------

int main()
{
    ifstream infile;
    ofstream outfile;

    ifstream sortedin;

    std::vector<std::string> lines;
    string line;

    vector<string> lineSorted;

    // Open the input file
    infile.open("bitacora.txt");

    sortedin.open("sorted.txt");

    if (sortedin.is_open()){
        // // If the file is open
        while (getline(sortedin, line))
        {
            lineSorted.push_back(line);
        }
    }

    if (!sortedin.is_open()){
        // // If the file is open
        while (getline(infile, line))
        {
            lines.push_back(line);
        }

        // // Close the input file
        infile.close();

        lineSorted = mergeSort(lines);

        outfile.open("sorted.txt");

        // For each line in the sorted lines
        for (int i = 0; i < lineSorted.size(); i++)
        {
            outfile << lineSorted[i] << endl;
        }
    }

    string lim_izq, lim_der;

    cout << "Ingresa el IP minimo:\n";

    cout << endl << ">> ";
    cin >> lim_izq;

    cout << "Ingresa el IP maximo:\n";

    cout << endl << ">> ";
    cin >> lim_der;

    int id_izq = binarySearch(lim_izq, lineSorted);

    int id_der = binarySearch(lim_der, lineSorted) - 1;

    if (id_izq == lineSorted.size()) id_izq--;

    if (id_izq <= id_der){
        cout << "Resultado busqueda:" << endl;
        cout << "------------------------" << endl;
        for (int i=id_izq; i<=id_der; i++) {
            cout << lineSorted[i] << endl;
        }
    }
    else{
        cout << "\nDatos ingresados erroneos" << endl;
    }
    
    return 0;
}