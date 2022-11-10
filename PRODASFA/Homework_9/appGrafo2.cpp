#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

template <int N_VERTICES> class Graph{ // Creates the graph class
    private:
        // Atributes
        int n_vertices = N_VERTICES;
        vector <int>* adjList;
        bool* visited;

        void DFS(int); // Private definitions for traversals
        void BFS(int);

        bool isTree(int); // Private methods
        void topologicalSort(int);
        bool bipartiteGraph(int start);

    public:
        // Constructors
        Graph();
        ~Graph();

        // Auxiliar methods
        void addEdge(int, int);
        void resetVisited();

        // Public auxiliar methods
        void DFS(){
            resetVisited();
            DFS(0);
        };
        void BFS(){
            resetVisited();
            BFS(0);
        };

        bool isTree(){
            resetVisited();
            return isTree(0);
        };

        void topologicalSort(){
            resetVisited();
            return topologicalSort(0);
        };

        void topologicalDFS(int, stack <int>&);

        bool bipartiteGraph(){
            resetVisited();
            return bipartiteGraph(0);
        };

        void printList();

};

// Constructor
template <int N_VERTICES> Graph<N_VERTICES>::Graph(){
    this->adjList = new vector <int> [N_VERTICES]; // Set the adjacency list size

    visited = new bool [N_VERTICES]; // Set the visited size

    this->resetVisited(); // Reset the visited (has to be done each search)
}

// Destructor
template <int N_VERTICES> Graph<N_VERTICES>::~Graph(){
    delete []adjList; // Destructs the adjacency list
}

// Methods
template <int N_VERTICES> void Graph<N_VERTICES>::addEdge(int s, int t){ // Ads an edge - Complexity O(1)
    this->adjList[s].push_back(t); // On the list
}

template <int N_VERTICES> void Graph<N_VERTICES>::resetVisited(){ // Resets all the visited elements (called each search) - Complexity O(n)
    for (int i=0; i<N_VERTICES; i++){ // Iterates
        visited[i] = false;
    }
}

template <int N_VERTICES> void Graph<N_VERTICES>::DFS (int start){ // DFS using the list - Complexity O(V + E)
    this->visited[start] = true; // Sets the start as visited
    vector <int> adjVertex = this->adjList[start]; // Gets the adjacency list of that node

    cout << start << " "; // Print format

    for (auto i : adjVertex){ // Iterates thorugh the adjacent nodes
        if (!this->visited[i]) // If not visited
            DFS(i); // Recursion
    }
}

template <int N_VERTICES> void Graph<N_VERTICES>::BFS(int start){ // BFS using the list - Complexity O(V + E)
    visited[start] = true; // Set the start as visited
    queue <int> queue; // Queue

    queue.push(start); // Pushes the start

    while (!queue.empty()){ // While the queue is not empty
        int currVertex = queue.front(); // Gets the current vertex

        cout << currVertex << " "; // Print format

        for (auto e:adjList[currVertex]){ // Goes through all the adjacent vertexes
            if (!visited[e]){ // If not visited
                queue.push(e); // Push to the queue
                visited[e] = true; // Set as visited
            }
        }

        queue.pop(); // Pop the queue
    }
}

template <int N_VERTICES> bool Graph<N_VERTICES>::isTree(int start){ // Checks if the graph is a tree using the list - Complexity O(V(V + E))
    for (int i=0; i<N_VERTICES; i++){ // For all the nodes
        if (!visited[i]){ // Wich ar not visited
            visited[start] = true; // Set the start as visited
            queue <int> queue; // Queue

            queue.push(start); // Pushes the start

            while (!queue.empty()){ // While the queue is not empty
                int currVertex = queue.front(); // Gets the current vertex

                for (auto e:adjList[currVertex]){ // Goes through all the adjacent vertexes
                    if (visited[e]) return false; // If already visited, return false

                    if (!visited[e]){ // If not visited
                        queue.push(e); // Push to the queue
                        visited[e] = true; // Set as visited
                    }
                }

                queue.pop(); // Pop the queue
            }
        }
    }
    
    return true; // Else it is a tree
}

template <int  N_VERTICES> void Graph<N_VERTICES>::topologicalSort(int start){ // Sorts the graph by topological order - Complexity O(V(V + E))
    stack <int> sort; // Creates an stack for the sorting
    
    topologicalDFS(start, sort); // Creates a DFS from the start node
    
    for (int i=0; i<N_VERTICES; i++){ // Iterates through all the vertexes
        if (!visited[i]){ // Checks if they are already visited
            topologicalDFS(i, sort); // If not, does a DFS
        }
    }

    while (!sort.empty()){ // Iterates thorugh the obtained stack
        cout << sort.top() << " "; // Prints the top of the stack
        sort.pop(); // Pops the top of the stack
    }
}

template <int  N_VERTICES> void Graph<N_VERTICES>::topologicalDFS(int start, stack <int> &sort){ // Internal DFS for the topological sort - Complexity O(V + E)
    this->visited[start] = true; // Sets the start as visited
    vector <int> adjVertex = this->adjList[start]; // Gets the adjacency list of that node

    for (auto i : adjVertex){ // Iterates thorugh the adjacent nodes
        if (!this->visited[i]){ // If not visited
            topologicalDFS(i, sort); // Recursion
        }
    }

    sort.push(start); // Pushes the start node to the stack
}

template <int N_VERTICES> bool Graph<N_VERTICES>::bipartiteGraph(int start){ // Cecks if the graph is bipartite - Complexity O(V(V + E))
    vector <bool> color(N_VERTICES); // Color for the vertexes

    for (int i=0; i<N_VERTICES; i++){ // Iterates through all the vertexes
        if (!visited[i]){ // If not visited
            visited[i] = true; // Set the start as visited
            if (adjList[i][0]) color[i] = !color[adjList[i][0]]; // If the vertex found has an adjacent vertex, it places a color contrary to the adjacent vertex
            else color[i] = 0; // Else it places the color as 0 for default

            queue <int> queue; // Queue

            queue.push(i); // Pushes the start

            while (!queue.empty()){ // While the queue is not empty
                int currVertex = queue.front(); // Gets the current vertex
                queue.pop(); // Pop the queue

                for (auto e:adjList[currVertex]){ // Goes through all the adjacent vertexes
                    if (!visited[e]){ // If not visited
                        visited[e] = true; // Set as visited
                        color[e] = !color[currVertex];

                        queue.push(e); // Push to the queue
                    }
                    else if (color[currVertex] == color[e]){ // If the color match for the current and next vertex, it is not bipartite
                        return false; // In that case it returns false
                    }
                }
            }
        }
    }

    return true; // Else returns true
}

template <int N_VERTICES> void Graph<N_VERTICES>::printList(){ // Prints the list - Complexity O(V + E)
    cout << endl; // Line jump
    for (int i=0; i<N_VERTICES; i++){ // Goes through all the vertexes
        cout << i << " |-| "; // Prints the main vertex
        for (auto conection : adjList[i]){ // Goes thorugh all it's adjacent vertexes
            cout << "-> " << conection << " "; // Prints the conection
        }
        cout << endl; // Line jump
    }
}

template <int T> Graph<T> loadGraph(int e){ // Loads the grapg as a 16 long graph    
    Graph <T> grafo; // Create graph - Size 9, 13, 9 and 11

    if (e == 0){
        grafo.addEdge(0, 1); // Adds all the edges
        grafo.addEdge(0, 5);
        grafo.addEdge(1, 5);
        grafo.addEdge(5, 2);
        grafo.addEdge(5, 4);
        grafo.addEdge(5, 7);
        grafo.addEdge(5, 8);
        grafo.addEdge(8, 6);
        grafo.addEdge(6, 2);
        grafo.addEdge(6, 3);

        return grafo; // Returns the graph
    }

    if (e == 1){
        grafo.addEdge(0, 3); // Adds all the edges
        grafo.addEdge(1, 3);
        grafo.addEdge(2, 0);
        grafo.addEdge(2, 1);
        grafo.addEdge(3, 6);
        grafo.addEdge(3, 7);
        grafo.addEdge(4, 0);
        grafo.addEdge(4, 3);
        grafo.addEdge(4, 5);
        grafo.addEdge(5, 9);
        grafo.addEdge(5, 10);
        grafo.addEdge(6, 8);
        grafo.addEdge(7, 8);
        grafo.addEdge(7, 9);
        grafo.addEdge(8, 11);
        grafo.addEdge(9, 11);
        grafo.addEdge(9, 12);
        grafo.addEdge(10, 9);

        return grafo; // Returns the graph
    }

    if (e == 2){
        grafo.addEdge(0, 1); // Adds all the edges
        grafo.addEdge(0, 2);
        grafo.addEdge(1, 3);
        grafo.addEdge(2, 3);
        grafo.addEdge(3, 4);
        grafo.addEdge(4, 5);
        grafo.addEdge(4, 6);
        grafo.addEdge(4, 7);
        grafo.addEdge(7, 8);

        return grafo; // Returns the graph
    }

    if (e == 3){
        grafo.addEdge(0, 1); // Adds all the edges
        grafo.addEdge(0, 2);
        grafo.addEdge(1, 3);
        grafo.addEdge(1, 4);
        grafo.addEdge(1, 5);
        grafo.addEdge(2, 6);
        grafo.addEdge(2, 7);
        grafo.addEdge(7, 8);
        grafo.addEdge(7, 9);
        grafo.addEdge(8, 10);

        return grafo; // Returns the graph
    }
    
    return grafo; // Otherwise returns the graph
}

int main(){

    Graph <9> grafo1 = loadGraph <9>(0); // Loads the first graph
    Graph <13> grafo2 = loadGraph <13>(1); // Loads the second graph
    Graph <9> grafo3 = loadGraph <9>(2); // Loads the third graph
    Graph <11> grafo4 = loadGraph <11>(3); // Loads the fourth graph
    
    //--------------------------------------------------------------

    // Results of 1st graph
    cout << "First graph:\n";
    if (grafo1.isTree()) cout << "The graph is a tree\n";
    else cout << "The graph is not a tree\n";

    cout << "The topological sort is:\n";
    grafo1.topologicalSort();
    cout << "\n";

    if (grafo1.bipartiteGraph()) cout << "The graph is bipartite\n";
    else cout << "The graph is not bipartite\n";

    //--------------------------------------------------------------

    // Results of 2nd graph
    cout << endl << "------------------------\n";
    cout << "Second graph:\n";
    if (grafo2.isTree()) cout << "The graph is a tree\n";
    else cout << "The graph is not a tree\n";

    cout << "The topological sort is:\n";
    grafo2.topologicalSort();
    cout << "\n";

    if (grafo2.bipartiteGraph()) cout << "The graph is bipartite\n";
    else cout << "The graph is not bipartite\n";
    
    //--------------------------------------------------------------

    // Results of 3rd graph
    cout << endl << "------------------------\n";
    cout << "Third graph:\n";
    if (grafo3.isTree()) cout << "The graph is a tree\n";
    else cout << "The graph is not a tree\n";

    cout << "The topological sort is:\n";
    grafo3.topologicalSort();
    cout << "\n";

    if (grafo3.bipartiteGraph()) cout << "The graph is bipartite\n";
    else cout << "The graph is not bipartite\n";
    
    //--------------------------------------------------------------

    // Results of 4th graph
    cout << endl << "------------------------\n";
    cout << "Fourth graph:\n";
    if (grafo4.isTree()) cout << "The graph is a tree\n";
    else cout << "The graph is not a tree\n";

    cout << "The topological sort is:\n";
    grafo4.topologicalSort();
    cout << "\n";

    if (grafo4.bipartiteGraph()) cout << "The graph is bipartite\n";
    else cout << "The graph is not bipartite\n";

}