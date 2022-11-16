#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Iker Ochoa Villaseñor - A01640984
// Santiago Vera Espinoza - A01641585

class Node{
private:
    // Atributes
    int in_degree;
    int out_degree;

public:
    // Constructor
    Node(){
        this->in_degree = 0;
        this->out_degree = 0;
    }

    // Getters & Setters
    int getInDegree() const{
        return this->in_degree;
    }

    void setInDegree(int in_degree){
        this->in_degree = in_degree;
    }

    int getOutDegree() const{
        return this->out_degree;
    }

    void setOutDegree(int out_degree){
        this->out_degree = out_degree;
    }
};

class Graph{
private:
    // Atributes
    int numVertices;
    int **adjMatrix;
    Node *arr_nodes;
    bool *visited;

    pair<int, int> max_in_degree;  // First element is ip, second is degree
    pair<int, int> max_out_degree; // First element is ip, second is degree

public:
    // Constructor
    Graph(int V){
        numVertices = V;

        // Create the adjacency matrix
        adjMatrix = new int *[V];
        for (int x = 0; x < V; x++){
            adjMatrix[x] = new int[V];
            for (int y = 0; y < V; y++)
                adjMatrix[x][y] = false;
        }

        // Create the array of bool
        visited = new bool[V];

        // Create the array of nodes
        arr_nodes = new Node[V];

        max_in_degree = {-1, -1};
        max_out_degree = {-1, -1};
    }

    // Destructor
    ~Graph(){
        delete[] visited;
    }

    // Methods
    void printMatrix();
    void ResetVisited();
    void setNode(string line);
    void setNodes(int[]);

    pair<int, int> getMaxInDegree();
    pair<int, int> getMaxOutDegree();
};

// Print Matrix Function - Complexity O(V^2)
void Graph::printMatrix(){
    // Print matrix
    for (int i = 0; i < this->numVertices; i++)
    {
        // Print row
        cout << i << " : ";

        for (int j = 0; j < this->numVertices; j++)
        {
            // Print column
            cout << this->adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Reset Visited Function - Complexity O(n)
void Graph::ResetVisited(){
    // Reset visited array
    for (int i = 0; i < this->numVertices; i++)
        this->visited[i] = false;
}

// Complexity O(n)
vector<int> separateIP(string ip){ // Separates an IP, from a string into a vector
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
vector<int> getIP(string line){ // Separates the IP from the strings given by the document
    int count = 0;
    string ip = "";

    for (int i = 0; i < line.length(); i++) // Iterates the string
    {
        if (line[i] == ' ') // Counts if there is a space
        {
            count++;
        }

        if (count == 3) // When it reaches 3, it saves that string
        {
            ip += line[i];
        }
    }

    return separateIP(ip); // Returns the vector
}

// Set Node Function - Complexity O(n)
void Graph::setNode(string line){
    // Get IPs in a Vector int
    vector<int> ip = getIP(line);

    for (int i = 0; i < ip.size() - 1; i++){
        // If Node does not exist
        if (!this->adjMatrix[ip[i]][ip[i + 1]]){
            // Set true in Adjacent Matrix
            adjMatrix[ip[i]][ip[i + 1]] = true;

            // Increase Out degree by 1 to the current node in i
            arr_nodes[ip[i]].setOutDegree(arr_nodes[ip[i]].getOutDegree() + 1);
            // Increase In degree by 1 to the next node of the current node in i
            arr_nodes[ip[i + 1]].setInDegree(arr_nodes[ip[i + 1]].getInDegree() + 1);

            // Check if the current node in i has a higher out degree than the max
            if (this->arr_nodes[ip[i]].getOutDegree() > this->max_out_degree.second)
                this->max_out_degree = {ip[i], this->arr_nodes[ip[i]].getOutDegree()};
            // Check if the next node of the current node in i has a higher in degree than the max
            if (this->arr_nodes[ip[i + 1]].getInDegree() > this->max_in_degree.second)
                this->max_in_degree = {ip[i + 1], this->arr_nodes[ip[i + 1]].getInDegree()};
        }
    }
}

pair<int, int> Graph::getMaxInDegree(){ // Gives the max in degree - Complexity O(1)
    return this->max_in_degree;
}

pair<int, int> Graph::getMaxOutDegree(){ // Gives the max out degree - Complexity O(1)
    return this->max_out_degree;
}

int main()
{
    ifstream infile;
    ofstream outfile;

    std::vector<std::string> lines;
    string line;

    Graph graph(1000);

    // Open the input file
    infile.open("bitacora.txt");

    // If the file is open
    while (getline(infile, line)){
        graph.setNode(line);
    }

    // Close the input file
    infile.close();

    cout << "Max InDegree: " << graph.getMaxInDegree().first << " - " << graph.getMaxInDegree().second << endl; // Max In Degree
    cout << "Max OutDegree: " << graph.getMaxOutDegree().first << " - " << graph.getMaxOutDegree().second << endl;
}