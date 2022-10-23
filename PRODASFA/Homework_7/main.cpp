#include <iostream>
#include <queue>

using namespace std;

template <typename T> class Node{ // Node class
    private:
        // Atributes
        T data;
        int balance_factor;
        int size;
        int height;
        Node <T>* prev;
        Node <T>* left;
        Node <T>* right;

    public:
        // Constructors
        Node(){
            this->data = 0;
            this->balance_factor = 0;
            this->size = 0;
            this->prev = NULL;
            this->left = NULL;
            this->right = NULL;
        }

        Node(T data){
            this->data = data;
            this->balance_factor = 0;
            this->size = 0;
            this->prev = NULL;
            this->left = NULL;
            this->right = NULL;
        }

        // Getters & Setters
        T getData(){
            return this->data;
        }

        void setData(T data){
            this->data = data;
        }

        int getBF(){
            return this->balance_factor;
        }

        void setBF(T balance_factor){
            this->balance_factor = balance_factor;
        }

        int getSize(){
            return this->size;
        }

        void setSize(int size){
            this->size = size;
        }

        int getHeight(){
            return this->height;
        }

        void setHeight(int height){
            this->height = height;
        }

        Node <T>* getPrev(){
            return this->prev;
        }

        void setPrev(Node <T>* prev){
            this->prev = prev;
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

        // Methods
        void updateBalanceFactor(){ // Updates the balance fcator od a node - Complexity O(1)
            if (this->left && this->right) balance_factor = this->left->height - this->right->height; // Left height minus right height
            else if (this->left) balance_factor = this->left->height; // Method for one node on left
            else if (this->right) balance_factor = -this->right->height;  // Method for one node on right
            else balance_factor = 0; // If no nodes
        }

        void leftRotate(){ // Rotates to left a set o two nodes - Complexity O(1)
            if (this->getPrev()->getRight() != this) return; // Returns if can not be rotated

            Node <T>* y = this; // Lower node
            Node <T>* x = this->getPrev(); // Upper node

            if (y->getLeft()) x->setRight(y->getLeft()); // Separates nodes
            else x->setRight(NULL);
            if (x->getRight()) x->getRight()->setPrev(x);

            if (x->getPrev()){ // Links the upper node of x to the new node on y
                if(x->getPrev()->getRight() == x) x->getPrev()->setRight(y);
                if(x->getPrev()->getLeft() == x) x->getPrev()->setLeft(y);
            }
            y->setPrev(x->getPrev()); // Links y to the upper node of x

            y->setLeft(x); // Links x and y
            x->setPrev(y); 

            int new_x_s = 0; // Upates the new size of the lower node with both child or one
            if (x->getLeft()) new_x_s += x->getLeft()->getSize() + 1;
            if (x->getRight()) new_x_s += x->getRight()->getSize() + 1;
            x->setSize(new_x_s);

            int new_y_s = 0; // Updates the new size of the upper nodes with the lower node and/or the right child
            if (y->getLeft()) new_y_s += y->getLeft()->getSize() + 1;
            if (y->getRight()) new_y_s += y->getRight()->getSize() + 1;
            y->setSize(new_y_s);

            if (x->getLeft() && x->getRight()){ //Updates the height for both childs case
                if (x->getLeft()->getHeight() >= x->getRight()->getHeight())
                    x->setHeight(x->getLeft()->getHeight() + 1);
                if (x->getLeft()->getHeight() < x->getRight()->getHeight())
                    x->setHeight(x->getRight()->getHeight() + 1);
            } 
            else if (x->getLeft()) // Left child case
                x->setHeight(x->getLeft()->getHeight() + 1);
            else if (x->getRight()) // Right child case
                x->setHeight(x->getRight()->getHeight() + 1);
            else // No child case
                x->setHeight(1);

            if (y->getLeft() && y->getRight()){ //Updates the height for both childs case
                if (y->getLeft()->getHeight() >= y->getRight()->getHeight())
                    y->setHeight(y->getLeft()->getHeight() + 1);
                if (y->getLeft()->getHeight() < y->getRight()->getHeight())
                    y->setHeight(y->getRight()->getHeight() + 1);
            } 
            else if (y->getLeft()) // Left child case
                y->setHeight(y->getLeft()->getHeight() + 1);
            else if (y->getRight()) // Right child case
                y->setHeight(y->getRight()->getHeight() + 1);
            else // No child case
                y->setHeight(1);

            x->updateBalanceFactor(); // Updates the balance factors
            y->updateBalanceFactor();

        }

        void rightRotate(){ // Rotates to right a set o two nodes - Complexity O(1)
            if (this->getPrev()->getLeft() != this) return;

            Node <T>* x = this; // Lower node
            Node <T>* y = this->getPrev(); // Upper node

            y->setLeft(x->getRight()); //Separates the nodes
            if (x->getRight()) x->getRight()->setPrev(x);

            if (y->getPrev()){ // Links the upper node of y to the new node on x
                if(y->getPrev()->getRight() == y) y->getPrev()->setRight(x);
                if(y->getPrev()->getLeft() == y) y->getPrev()->setLeft(x);
            }
            x->setPrev(y->getPrev()); // Links x to the upper node of y

            x->setRight(y); // Links x and y
            y->setPrev(x); 

            int new_y_s = 0; // Upates the new size of the lower node with both child or one
            if (y->getLeft()) new_y_s += y->getLeft()->getSize() + 1;
            if (y->getRight()) new_y_s += y->getRight()->getSize() + 1;
            y->setSize(new_y_s);

            int new_x_s = 0; // Updates the new size of the upper nodes with the lower node and/or the right child
            if (x->getLeft()) new_x_s += x->getLeft()->getSize() + 1;
            if (x->getRight()) new_x_s += x->getRight()->getSize() + 1;
            x->setSize(new_x_s);

            if (y->getLeft() && y->getRight()){ //Updates the height for both childs case
                if (y->getLeft()->getHeight() >= y->getRight()->getHeight())
                    y->setHeight(y->getLeft()->getHeight() + 1);
                if (y->getLeft()->getHeight() < y->getRight()->getHeight())
                    y->setHeight(y->getRight()->getHeight() + 1);
            } 
            else if (y->getLeft()) // Left child case
                y->setHeight(y->getLeft()->getHeight() + 1);
            else if (y->getRight()) // Right child case
                y->setHeight(y->getRight()->getHeight() + 1);
            else // No child case
            y->setHeight(1);
            
            if (x->getLeft() && x->getRight()){ //Updates the height for both childs case
                if (x->getLeft()->getHeight() >= x->getRight()->getHeight())
                    x->setHeight(x->getLeft()->getHeight() + 1);
                if (x->getLeft()->getHeight() < x->getRight()->getHeight())
                    x->setHeight(x->getRight()->getHeight() + 1);
            } 
            else if (x->getLeft()) // Left child case
                x->setHeight(x->getLeft()->getHeight() + 1);
            else if (x->getRight()) // Right child case
                x->setHeight(x->getRight()->getHeight() + 1);
            else // No child case
                x->setHeight(1);

            x->updateBalanceFactor(); // Updates the balance factors
            y->updateBalanceFactor();

        }
};

template <typename T> class AVL{ // AVL class
    private:
        // Atributes
        Node <T>* head;

    public:
        // Constructors
        AVL(){
            this->head = NULL;
        }
        AVL(T val){
            this->head = new Node(val);
        }

        // Getters & Setters
        Node <T>* getHead(){
            return this->head;
        }

        void setHead(Node <T>* n_head){
            this->head = n_head;
        }

        // Methods
        void leftRotate(Node <T>* obj_node){ // Left rotates the node given
            obj_node->leftRotate();
        }

        void rightRotate(Node <T>* obj_node){ // Right rotates the node given
            obj_node->rightRotate();
        }

        void insert(T val){ // Inserts a value and balances the tree - Complexity O(2log(n))
            Node <T>* n_node = new Node(val); // Creates the new node
            n_node->setBF(0); // Sets the balance factor with 0
            n_node->setHeight(1); // Sets height at 1

            if (!head){ // Exit if no nodes
                head = n_node;
                return;
            }

            Node <T>* current = head; // Sets an iterative variable at head
            bool has_been_inserted = false; // Flag if the node has been inserted

            while (!has_been_inserted){ // Loop to insert
                if (n_node->getData() == current->getData()) return; // If the node already exists it exits the function

                if (n_node->getData() < current->getData()){ // Lower to the current case
                    if (current->getLeft()){ // Iterates to left
                        current->setSize(current->getSize() + 1); // Increments the size of the current node
                        current = current->getLeft(); // Goes to left
                        continue;
                    }
                    // If it finds a space
                    current->setSize(current->getSize() + 1); // Increments the size of the current node
                    n_node->setPrev(current); // Links both nodes and inserts
                    current->setLeft(n_node);
                    has_been_inserted = true; // Turn flag true
                    continue; // Returns to the evaluation to exit the cycle
                }

                if (n_node->getData() > current->getData()){ // Greater than the current case
                    if (current->getRight()){ // Iterates to right
                        current->setSize(current->getSize() + 1); // Increments the size of the current node
                        current = current->getRight(); // Goes to right
                        continue;
                    }
                    // If it finds a space
                    current->setSize(current->getSize() + 1); // Increments the size of the current node
                    n_node->setPrev(current); // Links both nodes and inserts
                    current->setRight(n_node);
                    has_been_inserted = true; // Turn flag true
                    continue; // Returns to the evaluation to exit the cycle
                }
            }

            current = n_node; // The current node is now the new node

            while (current->getPrev()){ // Goes to head to update and correct
                current = current->getPrev(); // Goes up
                if(current->getLeft() && current->getRight()){ // Height correction if the current node has two childs
                    if (current->getLeft()->getHeight() >= current->getRight()->getHeight()) 
                        current->setHeight(current->getLeft()->getHeight() + 1);
                    if (current->getLeft()->getHeight() < current->getRight()->getHeight())
                        current->setHeight(current->getRight()->getHeight() + 1);
                }
                else if(current->getLeft()){ // Case for left child
                    current->setHeight(current->getLeft()->getHeight() + 1);
                }
                else{ // Case for right chils
                    current->setHeight(current->getRight()->getHeight() + 1);
                } // No no child case, because the current node has at least the new node

                current->updateBalanceFactor(); // Update the balance factor

                // Rotations cases
                if (current->getBF() > 1){ // If the balance factor is greater than 1 (left subtree is heavier)
                    if(0 < current->getLeft()->getBF()) rightRotate(current->getLeft()); // Left child has positive balance, right rotation
                    else{ // Has negative balance
                        if (current->getLeft()->getRight()) leftRotate(current->getLeft()->getRight()); // Left rotation
                        rightRotate(current->getLeft()); // Right rotation
                    }
                }
                else if (current->getBF() < -1){ // If the balance factor is lesser than -1 (right subtree is heavier)
                    if (0 > current->getRight()->getBF()) leftRotate(current->getRight()); // Right child has negative balance, left rotation
                    else { // Has positive balance
                        if (current->getRight()->getLeft()) rightRotate(current->getRight()->getLeft()); // Right rotation
                        leftRotate(current->getRight()); // Left rotation
                    }
                }

                current->updateBalanceFactor(); // Updates the balance factor of current
            }

            this->head = current; // The new head is set at the top
        }

        void delTotal(){ // Deletes all the nodes - Complexity O(n)

            if (!head) return; // If no nodes

            Node <T>* current = head; // Iterble set at head

            queue <Node<T>*> queue; // Queue for dfs
            vector <Node<T>*> elements; // Elements to delete

            queue.push(current); // Pushes start node
            elements.push_back(current); // Pushes start node

            while(queue.size() > 0){ // While the queue has elements

                queue.push(NULL); // Separate levels
                while (queue.front()){ // While is not NULL
                    if (queue.front()->getLeft()){ // Left case
                        queue.push(queue.front()->getLeft()); // Adds left
                        elements.push_back(queue.front()->getLeft());
                    }
                    if (queue.front()->getRight()){ // Right case
                        queue.push(queue.front()->getRight()); // Adds right
                        elements.push_back(queue.front()->getRight());
                    }

                    queue.pop(); // Pops front             
                }

                queue.pop(); // Pops front
            }

            for (auto e:elements){ // Auto iterate trough the vector (lower nodes to higher nodes)
                delete e; // Deletes all
            }

            this->head = NULL; // Sets head as NULL
        }

        void del(int fetch){ // Function to delete an specific node - Complexity O(2log(n))

            if (!this->head) return; // Exit case if no nodes

            if (this->head->getSize() == 1){ // In case the head is the only node
                this->head = NULL;
                return;
            }

            Node <T>* current = head; // Iterable at head
            bool has_been_found = false; // Falg if node is found

            while (!has_been_found){ // Infinite loop
                if (current->getData() == fetch){ // Data found
                    has_been_found = true; // Sets the flag true
                    continue;
                }

                if (fetch < current->getData()){ // Data is more than fetched
                    if (current->getLeft()) current = current->getLeft(); // Goes left if there is another node
                    else return; // Else there is no node in AVL
                    continue;
                }

                if (fetch > current->getData()){ // Data is less than fetched
                    if (current->getRight()) current = current->getRight(); // Goes right if there is another node
                    else return; // Else there is no node in AVL
                    continue;
                }
            }

            Node <T>* leftmost = new Node <T> (); // Node for the lefmost from fetched

            if (!current->getRight()) leftmost = current; // If there is no right node, the leftmost is the current node
            else if (current->getRight()) leftmost = current->getRight(); // Else is goes to right

            while (leftmost->getLeft()) leftmost = leftmost->getLeft(); // Iterates left as much as it cans

            current->setData(leftmost->getData()); // The current gets the data of the leftmost

            Node <T>* antecesor = NULL; // Creates an antecesor if it is necesary to link the nodes separated by de deletion
            if (leftmost->getLeft()) antecesor = leftmost->getLeft(); // Stablish the antecesor if the node to delete has nodes
            else if (leftmost->getRight()) antecesor = leftmost->getRight();

            current = leftmost->getPrev(); // The current is now prior to the antecesor

            if (antecesor){ // If there is an antesecor the antecesor and the current link between each other
                antecesor->setPrev(current);
                if (!current->getLeft()) current->setLeft(antecesor);
                else current->setRight(antecesor);
                current = antecesor; // The current is now the antecesor
            }

            if (current->getLeft() == leftmost) current->setLeft(NULL); // If the current childs are the node to delete, those pointers are set to NULL
            else if (current->getRight() == leftmost) current->setRight(NULL);

            delete leftmost; // Deletes leftmost

            current->updateBalanceFactor(); // Updates the balance factor

            Node <T>* saved;
            while (current){ // Goes to head to update and correct

                if(current->getLeft() && current->getRight()){ // Height correction if the current node has two childs
                    if (current->getLeft()->getHeight() >= current->getRight()->getHeight()) 
                        current->setHeight(current->getLeft()->getHeight() + 1);
                    if (current->getLeft()->getHeight() < current->getRight()->getHeight())
                        current->setHeight(current->getRight()->getHeight() + 1);
                }
                else if(current->getLeft()){ // Case for left child
                    current->setHeight(current->getLeft()->getHeight() + 1);
                }
                else if (current->getRight()){ // Case for right chils
                    current->setHeight(current->getRight()->getHeight() + 1);
                }
                else{ // No nodes case
                    current->setHeight(1);
                }

                current->updateBalanceFactor(); // Update the balance factor

                // Rotations cases
                if (current->getBF() > 1){ // If the balance factor is greater than 1 (left subtree is heavier)
                    if(0 < current->getLeft()->getBF()) rightRotate(current->getLeft()); // Left child has positive balance, right rotation
                    else{ // Has negative balance
                        if (current->getLeft()->getRight()) leftRotate(current->getLeft()->getRight()); // Left rotation
                        rightRotate(current->getLeft()); // Right rotation
                    }
                }
                else if (current->getBF() < -1){ // If the balance factor is lesser than -1 (right subtree is heavier)
                    if (0 > current->getRight()->getBF()) leftRotate(current->getRight()); // Right child has negative balance, left rotation
                    else { // Has positive balance
                        if (current->getRight()->getLeft()) rightRotate(current->getRight()->getLeft()); // Right rotation
                        leftRotate(current->getRight()); // Left rotation
                    }
                }

                int new_s = 0; // Upates the new size of the lower node with both child or one
                if (current->getLeft()) new_s += current->getLeft()->getSize() + 1;
                if (current->getRight()) new_s += current->getRight()->getSize() + 1;
                current->setSize(new_s);

                current->updateBalanceFactor(); // Updates the balance factor of current
                
                saved = current; // Returns to be the saved node
                current = current->getPrev(); // Goes up
            }

            if (!current) current = saved;

            this->head = current; // The new head is set at the top
        }

        bool find(int fetch){ // Finds a value
            if (!head) return false; // Exit case if no nodes

            Node <T>* current = head; // Iterable at head

            while (true){ // Infinite loop
                if (current->getData() == fetch) return true; // Data found

                if (fetch < current->getData()){ // Data is more than fetched
                    if (current->getLeft()) current = current->getLeft(); // Goes left if there is another node
                    else return false; // Else there is no node in AVL
                    continue;
                }

                if (fetch > current->getData()){ // Data is less than fetched
                    if (current->getRight()) current = current->getRight(); // Goes right if there is another node
                    else return false; // Else there is no node in AVL
                    continue;
                }

                return false; // Return false as default
            }

        }

        int size(){ // Return the size of all the AVL - Complexity O(1)
            if (this->getHead()) return head->getSize() + 1; // If there are nodes, returns the size
            return 0; // Else, return 0
        }

        void print(Node<T>* root){ // Prin inorder
            if (root->getLeft()) print(root->getLeft()); // Recursive left
            cout << root->getData() << " "; // Print
            if (root->getRight()) print(root->getRight()); // Recursive right
        }

        void printLvL(){ // Print by Level - Complexity O(n)

            if (!this->head) return; // Exit function

            queue <Node<T>*> queue; // Queue for DFS
            queue.push(head); // Pushes head

            while (queue.size() > 0){ // If the queue has elements

                queue.push(NULL); // Separates with NULL
                while (queue.front()){ // While the queue is not NULL
                    cout << queue.front()->getData() << "(" << queue.front()->getBF() << ") "; // Prints the data with it's balance
                    if(queue.front()->getLeft()) queue.push(queue.front()->getLeft()); // Push left node
                    if(queue.front()->getRight()) queue.push(queue.front()->getRight()); // Push right node
                    queue.pop(); // Pops front
                }
                cout << endl; // Jumps line
                queue.pop(); // Pops front
            }
        }
};

int main(){ // Main function

    AVL <int> avl; // Creates a new avl

    avl.insert(4); // Node insertions
    avl.insert(3);
    avl.insert(2);
    avl.insert(-1);
    avl.insert(0);
    avl.insert(5);
    avl.insert(7);
    avl.insert(-2);

    avl.printLvL(); // Prin by level

    cout << "---------------------\n";

    int f = 4; // Find f
    cout << "Finding " << 6 << "...\n The result is "; // Display result
    string resp = (avl.find(f))? "true\n" : "false\n";
    cout << resp;

    cout << "---------------------\n";
    
    avl.print(avl.getHead()); // Prints inorder

    cout << "\n---------------------\n";
    
    avl.del(-1); // Deletes 2
    avl.del(0);
    avl.del(2);
    avl.del(-2);
    avl.del(5);
    avl.del(4);
    avl.del(7);
    avl.del(3);

    avl.printLvL(); // Prints all nodes

    cout << "---------------------\n";

    //avl.delTotal(); // Deletes all nodes

    cout << "------------\n";

    cout << avl.size(); // Prints total size of the avl
}