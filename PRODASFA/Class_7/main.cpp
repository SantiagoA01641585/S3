#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph{
    private:
        int numVertices;
        list<int> *adjLists;
        bool *visited;

    public:
        Graph(int V){
            numVertices = V;
            adjLists = new list<int> [V];
            visited = new bool[V];
        }
        ~Graph(){
            delete []adjLists;
            delete []visited;
        }
        void addEdge(int, int);
        void printGraph();
        void resetVisited();

        void DFS(int);
        void BFS(int);
};

void Graph::addEdge(int s, int d){
    this->adjLists[s].push_back(d);
    this->adjLists[d].push_back(s);
}

void Graph::printGraph(){
    for (int i = 0; i < this->numVertices; i++){
        cout << "\nVertex " << i << ":";

        for (auto x : this->adjLists[i]){
            cout << " -> " << x;
        }
        cout << endl;
    }
}

void Graph::resetVisited(){
    for (int i = 0; i < numVertices; i++){
        visited[i] = false;
    }
}

void Graph::DFS(int vertex){
    this->visited[vertex] = true;
    list<int> adjVertex = this->adjLists[vertex];

    cout << vertex << " ";

    for (auto i: adjVertex){
        if (!this->visited[i])
            DFS(i);
    }
}

void Graph::BFS(int vertex){
    this->visited[vertex] = true;
    

    list<int> queue;
    queue.push_back(vertex);

    while (!queue.empty()){
        int curr_vertex = queue.front();

        cout << curr_vertex << " ";

        queue.pop_front();

        for (auto i: adjLists[curr_vertex]){
            if (!visited[i]){
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}

int main(){
    Graph G(5);

    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 3);
    G.addEdge(1, 2);
    G.addEdge(2, 4);

    G.printGraph();

    cout << "\nDFS: ";
    G.DFS(0);
    G.resetVisited();

    cout << "\nBFS: ";
    G.BFS(0);

    return 0;
}