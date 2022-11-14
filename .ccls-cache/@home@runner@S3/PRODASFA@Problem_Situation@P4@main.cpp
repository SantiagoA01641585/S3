#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

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

    pair <int, int> max_in_degree;
    pair <int, int> max_out_degree;
  
  public:
    // Constructor
    Graph(int V){
      numVertices = V;
  
      adjMatrix = new int *[V];
      for (int x = 0; x < V; x++){
        adjMatrix[x] = new int[V];
        for (int y = 0; y < V; y++)
          adjMatrix[x][y] = false;
      }
  
      visited = new bool[V];

      arr_nodes = new Node[V];
    }

  // Destructor
  ~Graph(){
    delete[] visited;
  }

  // Methods
  void addEdge(int, int);
  void printMatrix();
  void ResetVisited();
  void setNodes(int[]);
};

// Add Edge Function - Complexity O(1)
void Graph::addEdge(int s, int d){
  this->adjMatrix[s][d] = true;
}

// Print Matrix Function - Complexity O(V^2)
void Graph::printMatrix(){
  for (int i = 0; i < this->numVertices; i++){
    cout << i << " : ";
    for (int j = 0; j < this->numVertices; j++){
      cout << this->adjMatrix[i][j] << " ";
    }
    cout << endl;
  }
}

// Reset Visited Function - Complexity O(n)
void Graph::ResetVisited(){
  for (int i = 0; i < this->numVertices; i++)
    this->visited[i] = false;
}

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
vector<int> getIP(string line) // Separates the IP from the strings given by the document
{
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

void Graph::setNode(string line){
  vector<int> ip =  getIP(line);
  int first = 0;
  int sec = 1;
}

int main(){
  ifstream infile;
  ofstream outfile;

  std::vector<std::string> lines;
  string line;

  // Open the input file
  infile.open("bitacora.txt");

  // If the file is open
  while (getline(infile, line)){ 
    
  }

  // Close the input file
  infile.close();
  
  Graph graph(1000);
  
}