#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <int N_VERTICES> class Graph{
    private:
        // Atributes
        bool adjMatrix [N_VERTICES][N_VERTICES];
        vector <int>* adjList;
        bool* visited;

    public:
        // Constructor
        Graph(){
            for (int x=0; x<N_VERTICES; x++){ // Set all the amtrix as false
                for (int y=0; y<N_VERTICES; y++){
                    this->adjMatrix[x][y] = false;
                }
            }

            this->adjList = new vector <int> [N_VERTICES]; // Set the adjacency list size

            visited = new bool [N_VERTICES]; // Set the visited size

            this->resetVisited(); // Reset the visited (has to be done each search)
        }
        // Destructor
        ~Graph(){
            for (int x=0; x<N_VERTICES; x++){ // Destructs all elements in the matrix
                for (int y=0; y<N_VERTICES; y++){
                    bool* curr_slot = &adjMatrix[x][y];
                    delete curr_slot;
                }
            }

            delete []adjList; // Destructs the adjacency list
        }

        // Methods
        void addEdge(int s, int t){ // Ads an edge - Complexity O(1)
            this->adjMatrix[s][t] = true; // On the matrix

            this->adjList[s].push_back(t); // On the list
        }

        void resetVisited(){ // Resets all the visited elements (called each search) - Complexity O(n)
            for (int i=0; i<N_VERTICES; i++){ // Iterates
                visited[i] = false;
            }
        }

        void matrixDFS(int start){ // DFS using matrix - Complexity O(V^2)
            this->visited[start] = true; // Sets the start as visited

            cout << start << " "; // Print format

            for (int i=0; i<N_VERTICES; i++){ // Goes through all the vertexes adjacent to the main one
                if (adjMatrix[start][i] == 1 && !this->visited[i])
                    matrixDFS(i); // Recursion
            }
        }

        void listDFS (int start){ // DFS using the list - Complexity O(V + E)
            this->visited[start] = true; // Sets the start as visited
            vector <int> adjVertex = this->adjList[start]; // Gets the adjacency list of that node

            cout << start << " "; // Print format

            for (auto i : adjVertex){ // Iterates thorugh the adjacent nodes
                if (!this->visited[i]) // If not visited
                    listDFS(i); // Recursion
            }
        }

        void matrixBFS(int start){ // BFS using the matrix - Complexity O(V^2)
            visited[start] = true; // Sets the start as visited
            queue <int> queue; // Queue

            queue.push(start); // Push the start

            while (!queue.empty()){ // While the queue is not empty
                int currVertex = queue.front(); // Get the current vertex

                cout << currVertex << " "; // Print format

                for (int i=0; i<N_VERTICES; i++){ // Goes thorugh all the posible adjacent vertexes
                    if (adjMatrix[queue.front()][i] == 1 && !this->visited[i]){ // If they are adjacent and not visited
                        queue.push(i); // Push them to the queue
                        visited[i] = true; // Set them as visited
                    }
                }
                
                queue.pop(); // Pop the queue
            }
        }

        void listBFS(int start){ // BFS using the list - Complexity O(V + E)
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

        void printMatrix(){ // Prints the matrix - Complexity O(V^2)
            cout << endl; // Line jump
            for (int y=0; y<N_VERTICES; y++){ // Goes thorugh all the vertexes on y
                
                for (int x=0; x<N_VERTICES; x++){ // Goes thorugh all the vertexes on x
                    cout << "|" << adjMatrix[x][y] << "|"; // Couts the current state
                }
                cout << endl; // Line jump
            }
        }

        void printList(){ // Prints the list - Complexity O(V + E)
            cout << endl; // Line jump
            for (int i=0; i<N_VERTICES; i++){ // Goes through all the vertexes
                cout << i << " |-| "; // Prints the main vertex
                for (auto conection : adjList[i]){ // Goes thorugh all it's adjacent vertexes
                    cout << "-> " << conection << " "; // Prints the conection
                }
                cout << endl; // Line jump
            }
        }

};

Graph <16> loadGraph(){ // Loads the grapg as a 16 long graph
    Graph <16> grafo; // Create graph

    grafo.addEdge(0, 1); // Adds all the edges
    grafo.addEdge(1, 2);
    grafo.addEdge(2, 3);
    grafo.addEdge(3, 0);
    grafo.addEdge(3, 5);
    grafo.addEdge(3, 7);
    grafo.addEdge(4, 5);
    grafo.addEdge(5, 1);
    grafo.addEdge(5, 9);
    grafo.addEdge(6, 5);
    grafo.addEdge(6, 3);
    grafo.addEdge(7, 10);
    grafo.addEdge(8, 4);
    grafo.addEdge(8, 13);
    grafo.addEdge(9, 6);
    grafo.addEdge(9, 12);
    grafo.addEdge(10, 6);
    grafo.addEdge(11, 8);
    grafo.addEdge(12, 11);
    grafo.addEdge(12, 15);
    grafo.addEdge(13, 14);
    grafo.addEdge(14, 12);
    grafo.addEdge(15, 14);

    return grafo; // Returns the graph
}

int main(){

    Graph <16> grafo = loadGraph(); // Loads the graph

    // On 6
    cout << "DFS:\n";
    grafo.matrixDFS(6);
    grafo.resetVisited();
    cout << endl;

    grafo.listDFS(6);
    grafo.resetVisited();
    cout << endl;

    cout << "BFS:\n";
    grafo.matrixBFS(6);
    grafo.resetVisited();
    cout << endl;

    grafo.listBFS(6);
    grafo.resetVisited();
    cout << endl;

    cout << "----------------------\n";

    // On 9
    cout << "DFS:\n";
    grafo.matrixDFS(9);
    grafo.resetVisited();
    cout << endl;

    grafo.listDFS(9);
    grafo.resetVisited();
    cout << endl;

    cout << "BFS:\n";
    grafo.matrixBFS(9);
    grafo.resetVisited();
    cout << endl;

    grafo.listBFS(9);
    grafo.resetVisited();
    cout << endl;

    cout << "----------------------\n";

    // On 4
    cout << "DFS:\n";
    grafo.matrixDFS(4);
    grafo.resetVisited();
    cout << endl;

    grafo.listDFS(4);
    grafo.resetVisited();
    cout << endl;

    cout << "BFS:\n";
    grafo.matrixBFS(4);
    grafo.resetVisited();
    cout << endl;

    grafo.listBFS(4);
    grafo.resetVisited();
    cout << endl;

    cout << "----------------------\n";

    // On 11
    cout << "DFS:\n";
    grafo.matrixDFS(11);
    grafo.resetVisited();
    cout << endl;

    grafo.listDFS(11);
    grafo.resetVisited();
    cout << endl;

    cout << "BFS:\n";
    grafo.matrixBFS(11);
    grafo.resetVisited();
    cout << endl;

    grafo.listBFS(11);
    grafo.resetVisited();
    cout << endl;

    cout << "----------------------\n";

}