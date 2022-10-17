#include <iostream>
#include <queue> // Include queue

using namespace std;

template <typename T> class Node{ // Node Class
    private:
        // Atributes
        T data; // Data
        Node <T>* left; // Left node
        Node <T>* right; // Right node
    
    public:
        // Constructors
        Node(){
            this->data = 0;
            this->left = NULL;
            this->right = NULL;
        }

        Node(T data){
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }

        Node(T data, Node<T>* left, Node<T>* right){
            this->data = data;
            this->left = left;
            this->right = right;
        }

        // Getters & Setters
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
        void insertNode(T val){ // Inserts node passing the value - Complexity O(n)

            if (root == NULL){ // Checks if the root is NULL
                root = new Node <T>(val); // Points the root to a new node with the value given
                return;
            } 

            Node <T>* n_node = new Node <T>(val); // Creates a new node with the value chosen
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

int main(){

    BST <int> tree; // Create tree

    tree.insertNode(6); // Insert 6
    tree.insertNode(2); // Insert 2
    tree.insertNode(7); // Insert 7
    tree.insertNode(5); // Insert 5
    tree.insertNode(9); // Insert 9
    tree.insertNode(11); // Insert 11
    tree.insertNode(1); // Insert 1
    tree.insertNode(8); // Insert 8
    tree.insertNode(14); // Insert 14

    tree.visit(1); // Visit the tree with preconfiguration 1 (Preorder)
    tree.visit(2); // Visit the tree with preconfiguration 2 (Inorder)
    tree.visit(3); // Visit the tree with preconfiguration 3 (Postorder)
    tree.visit(4); // Visit the tree with preconfiguration 4 (LevelByLevel)

    cout << "\nTree height: " << tree.height() << endl; // Gets the tree height

    int srch_node = 1;
    cout << "\nTree ancestors at " << srch_node << ": \n"; // Gets the tree ancestors
    tree.ancestors(srch_node);

    int n = 14;
    cout << "\nWhat level is " << n << " at?\n"; // Searches at what level n is
    cout << "At level " << tree.whatLevelAmI(n) << endl;
}