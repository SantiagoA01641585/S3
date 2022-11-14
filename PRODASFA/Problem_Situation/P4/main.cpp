#include <iostream>

using namespace std;

class Graph
{
private:
    int numVertices;
    list<int> *adjLists;
    bool **adjMatrix;
    bool *visited;

public:
    Graph(int V)
    {
        numVertices = V;
        adjLists = new list<int>[V];

        adjMatrix = new bool *[V];
        for (int i = 0; i < V; i++)
        {
            adjMatrix[i] = new bool[V];
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