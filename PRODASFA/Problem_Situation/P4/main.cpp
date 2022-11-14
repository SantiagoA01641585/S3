#include <iostream>
#include <list>

using namespace std;

class Graph
{
private:
    int numVertices;
    list<int> *adjLists;
    int **adjMatrix;
    bool *visited;

public:
    Graph(int V)
    {
        numVertices = V;
        adjLists = new list<int>[V];

        adjMatrix = new int *[V];
        for (int i = 0; i < V; i++)
        {
            adjMatrix[i] = new int[V];
            for (int j = 0; j < V; j++)
                adjMatrix[i][j] = false;
        }

        visited = new bool[V];
    }

    ~Graph()
    {
        delete[] adjLists;
        delete[] visited;
    }

    void addEdge(int, int);
    void printGraph();
    void printMatrix();
    void ResetVisited();

    void DFS(int);
    void BFS(int);
};

// Add Edge Function - Complexity O(1)
void Graph::addEdge(int s, int d)
{
    this->adjLists[s].push_back(d);
    this->adjMatrix[s][d] = true;
}

// Print Graph Function - Complexity O(V + E)
void Graph::printGraph()
{
    for (int i = 0; i < this->numVertices; i++)
    {
        cout << "\nVertex " << i << ":";
        for (auto x : this->adjLists[i])
            cout << " -> " << x;
        cout << endl;
    }
}

// Print Matrix Function - Complexity O(V^2)
void Graph::printMatrix()
{
    for (int i = 0; i < this->numVertices; i++)
    {
        cout << i << " : ";
        for (int j = 0; j < this->numVertices; j++)
        {
            cout << this->adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Reset Visited Function - Complexity O(n)
void Graph::ResetVisited()
{
    for (int i = 0; i < this->numVertices; i++)
        this->visited[i] = false;
}