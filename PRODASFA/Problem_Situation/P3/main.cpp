#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

template <typename T> class Node{ // Node Class
    private:
        // Atributes
        int key;
        T data; // Data
        Node <T>* left; // Left node
        Node <T>* right; // Right node
    
    public:
        // Constructors
        Node(){
            this->key = 0;
            this->data = 0;
            this->left = NULL;
            this->right = NULL;
        }

        Node(T data){
            this->key = 0;
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }

        Node(T data, Node<T>* left, Node<T>* right){
            this->key = 0;
            this->data = data;
            this->left = left;
            this->right = right;
        }

        // Getters & Setters
        int getKey(){
            return this->key;
        }

        void setKey(int key){
            this->key = key;
        }

        T getData() const{
            return this->data;
        }

        void setData(T data){
            this->data = data;
        }

        Node <T>* getLeft(){
            return this->left;
        }

        void setLeft(Node <T>* left){
            this->left = left;
        }

        Node <T>* getRight(){
            return this->right;
        }

        void setRight(Node <T>* right){
            this->right = right;
        }
};

template <typename T> class BST{ // BST Class
    private:
        // Atributes
        Node <T>* root; // Root of the BST

    public:
        // Constructors
        BST(){
            root = NULL;
        }

        BST(Node<T> root){
            this->root = root;
        }

        // Getters & Setters
        Node <T>* getRoot(){
            return this->root;
        }

        void setRoot(Node <T>* root){
            this->root = root;
        }

        // Methods
        void insertNode(Node <T>* n_node){ // Inserts node passing the value - Complexity O(n)

            if (root == NULL){ // Checks if the root is NULL
                root = n_node; // Points the root to a new node with the value given
                return;
            } 

            Node <T>* current = root; // Creates a node to traverse the tree and is set to point to the same direction as root

            while(true){ // Pseudo-infinite loop
                if (n_node->getData() == current->getData()) return; // If we find the value, we don't insert

                if (n_node->getData() < current->getData()){ // Check if the data fetched is lesser
                    if (current->getLeft()){
                        current = current->getLeft(); // Goes to the left node
                        continue;
                    }

                    current->setLeft(n_node); // Inserts the new node at the left
                    return;
                }

                if (n_node->getData() > current->getData()){ // Check if the data fetched is greater
                    if (current->getRight()){
                        current = current->getRight(); // Goes to the right
                        continue;
                    }

                    current->setRight(n_node); // Inserts the new node at the right
                    return;
                }
            }
        }

        void preOrder(Node <T>* root){ // PreOrder function - Complexity O(n)
            if (root == NULL) return; // If is NULL, return

            cout << root->getData() << " "; // Print
            preOrder(root->getLeft()); // Recursive left
            preOrder(root->getRight()); // Recursive right
        }

        void inOrder(Node <T>* root){ // InOrder function - Complexity O(n)
            if (root == NULL) return; // If is NULL, return

            inOrder(root->getLeft()); // Recursive left
            cout << root->getData() << " "; // Print
            inOrder(root->getRight()); // Recursive right
        }

        void postOrder(Node <T>* root){ // PostOrder function - Complexity O(n)
            if (root == NULL) return; // If is NULL, return

            postOrder(root->getLeft()); // Recursive left
            postOrder(root->getRight()); // Recursive right
            cout << root->getData() << " "; // Print
        }

        void levelByLevel(){ // Level By Level function - Complexity O(n)
            queue <Node <T>*> queue; // Creates a queue
            queue.push(root); // Pushes the root at the end

            while (queue.size() > 0){ // Loops while the queue has elements

                queue.push(NULL); // Pushes NULL to separate rows
                while (queue.front()){ // While the front of the queue is not NULL

                    cout << queue.front()->getData() << " "; // Print the data

                    if (queue.front()->getLeft()){ // Is there is a left node here?, push it into the queue (after NULL)
                        queue.push(queue.front()->getLeft());
                    }

                    if (queue.front()->getRight()){ // Is there is a right node here?, push it into the queue (after NULL)
                        queue.push(queue.front()->getRight());
                    }

                    queue.pop(); // Pops the element at the front
                }
                cout << endl; // Line jump

                queue.pop(); // Pops the element at the front
            }
        }

        void visit(int order_type){ // Visits the BST with diferent configurations - Complexity O(n)
            switch (order_type) {
                case 1:
                    cout << "Visit as preorder: "; // PreOrder case
                    preOrder(root);
                    break;

                case 2:
                    cout << "Visit as inorder: "; // InOrder case
                    inOrder(root);
                    break;

                case 3:
                    cout << "Visit as postorder: "; // PostOrder case
                    postOrder(root);
                    break;

                case 4:
                    cout << "Visit level by level: \n"; // Level By Level case
                    levelByLevel();
                
                default: // Default break
                    break;
            }
        }

        int height(){ // Obtain the total height of the BST - Complexity O(n)
            queue <Node <T>*> queue; // Creates a queue
            queue.push(root); // Pushes the root at the end

            int cont = 0; // Counter set at cero

            while (queue.size() > 0){ // Loops while the queue has elements

                queue.push(NULL); // Pushes NULL to separate rows
                cont++; // Counter increment at each level change
                while (queue.front()){ // While the front of the queue is not NULL

                    if (queue.front()->getLeft()){ // Is there a left node here?, push it into the queue (after NULL)
                        queue.push(queue.front()->getLeft());
                    }

                    if (queue.front()->getRight()){ // Is there a left node here?, push it into the queue (after NULL)
                        queue.push(queue.front()->getRight());
                    }

                    queue.pop(); // Pops the element at the front
                }

                queue.pop(); // Pops the element at the front
            }

            return cont; // Returns the counter (level)
        }

        void ancestors(int value){ // Searches a node and gets all the path the algorithm took - Complexity O(n)
            vector <Node <T>*> traceway; // Vector for the route of the algorithm

            Node <T>* current = new Node <T>(); // Iterable node
            current = root; // Sets the iterable at the root

            while (true){ // Endless cycle
                if (current->getData() == value) break; // If the value is the same, it exits the function

                if (current->getLeft() || current->getRight()){ // If there are any child node
                    if(value < current->getData()){ // If it is lesser it iterates left
                        traceway.push_back(current); // Pushes the new node to the route
                        current = current->getLeft(); // Iterates the iterable node
                        continue; // Returns to the start of the cycle
                    }
                    if(value > current->getData()){ // If it is greater it iterates right
                        traceway.push_back(current); // Pushes the new node to the route
                        current = current->getRight(); // Iterates the iterable node
                        continue; // Returns to the start of the cycle
                    }
                }
            }

            for (auto e:traceway) cout << "->" << e->getData() << endl; // Couts all the elements
        }

        int whatLevelAmI(int value){ // Returns at what level a node is - Complexity O(n)
            Node <T>* current = new Node <T>(); // Creates an iterable node
            current = root; // Sets the node at the root

            int level_cont = 1; // Creates a counter with the value 1

            while (true){ // Endless cycle
                if (value == current->getData()) return level_cont; // If the value is found, it returns the counter

                if (value < current->getData()){ // If the value is lesser, it iterates left
                    if (current->getLeft()) current = current->getLeft(); // If left exists, it iterates left
                    level_cont++; // Increase the counter by one
                    continue; // Returns to the evaluation of the cycle
                }

                if (value > current->getData()){ // If the value is greater, it iterates right
                    if (current->getRight()) current = current->getRight(); // If right exists, it iterates right
                    level_cont++; // Increase the counter by one
                    continue; // Returns to the evaluation of the cycle
                }

                return -1; // Else, it returns -1
            }

        }

};

string extractIP(string line){ // Extracts an IP from a line of text
    string ip; // The IP

    int spc_cont = 0;
    for(auto c:line){ // Goes trough the line
        if (c == ' ') spc_cont++; // Checks the spaces
        if (spc_cont > 3) break; // Breaks when it reaches 4 spaces

        if (spc_cont == 3){ // After space 3, everything is added to the ip
            ip += c;
        }
    }

    return ip; // Returns IP
}

long long int hashIP(string ip){ // Hash function given a string
    string aux; // Auxiliar string
    long long int res; // Int to store the ip

    int cont = 0; // Cont
    for(int i=0; i<ip.size(); i++){ // Iterates trough the ip
        if (ip[i] == '.' || ip[i] == ':'){ // Evades '.' and ':'
            cont++;
            if (cont == 1 || cont == 3){ // Corrections for when the numbers are low
                if (ip[i+2] == '.' || ip[i+2] == ':'){
                    aux += '0';
                    continue;
                }
            }
            if (cont == 2){
                if (ip[i+2] == '.'){
                    aux += "00";
                    continue;
                }
                if (ip[i+3] == '.'){
                    aux += '0';
                    continue;
                }
            }
            
            continue;
        }

        aux += ip[i]; // Gets the ip current char
    }

    res = stoll(aux); // Converts to int

    return res;
}

void inFileMain(string in_Adress, BST <long long int> &tree){ // Main Function for the insertion of the elements
    ifstream infile; // File
    string line; // Line gotten
    string prev_ip = " "; // The previous line gotten

    infile.open(in_Adress); // Open the file

    int contrl = 0; // Overall control cont
    int rep_cont = 1; // Counts the repetitions
    while (getline(infile, line)){
        string ip = extractIP(line);

        contrl++;

        if(contrl > 18000) break;

        if (prev_ip != " "){
            if (ip == prev_ip){
                rep_cont++;
                prev_ip = ip;
                continue;
            }

            long long int n_int = hashIP(prev_ip);
            //cout << n_int << " - " << rep_cont << endl;
            Node <long long int>* n_node = new Node <long long int>();
            n_node->setData(n_int);
            n_node->setKey(rep_cont);

            tree.insertNode(n_node);

            rep_cont = 1;
        }

        prev_ip = ip;
    }

    infile.close();
}

vector <pair <int, long long int>> findFiveLargest(BST <long long int> tree){
    vector <pair <int, long long int>> res;
    res.resize(5);
    res[0] = make_pair(1,6);

    Node <long long int>* curr = new Node <long long int> ();
    curr = tree.getRoot();
    while (curr->getRight()){
        if (curr->getKey() > res[0].first){
            if (curr->getKey() > res[1].first){
                if (curr->getKey() > res[2].first){
                    if (curr->getKey() > res[3].first){
                        if (curr->getKey() > res[4].first){
                            res[4] = make_pair(curr->getKey(), curr->getData());
                            curr = curr->getRight();
                            continue;
                        }

                        res[3] = make_pair(curr->getKey(), curr->getData());
                        curr = curr->getRight();
                        continue;
                    }

                    res[2] = make_pair(curr->getKey(), curr->getData());
                    curr = curr->getRight();
                    continue;
                }

                res[1] = make_pair(curr->getKey(), curr->getData());
                curr = curr->getRight();
                continue;
            }

            res[0] = make_pair(curr->getKey(), curr->getData());
            curr = curr->getRight();
            continue;
        }

        curr = curr->getRight();
    }

    return res;
}


int main(){

    BST <long long int> hash_map;

    inFileMain("sorted.txt", hash_map);

    vector <pair <int, long long int>> res;
    res = findFiveLargest(hash_map);

    for (auto e:res){
        cout << e.second << " |+| " << e.first << endl;
    }

}