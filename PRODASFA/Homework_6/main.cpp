#include <iostream>
#include <queue>

using namespace std;

class Node{ // A class for the node
    private:
        // Atributes
        int val;
        Node* left;
        Node* right;

        Node* parent;

    public: 
        // Constructors
        Node(){
            this->val = 0;
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
        }
        Node(int val){
            this->val = val;
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
        }

        // Getters & Setters
        int getValue() const{
            return this->val;
        }

        void setValue(int val){
            this->val = val;
        }

        Node* getLeft() const{
            return this->left;
        }

        void setLeft(Node* left){
            this->left = left;
        }

        Node* getRight() const{
            return this->right;
        }

        void setRight(Node* right){
            this->right = right;
        }

        Node* getParent() const{
            return this-> parent;
        }

        void setParent(Node* parent){
            this->parent = parent;
        }
};

class MinHeapQueue{ // Main class for the queue
    private:
        // Atributes
        Node* head;
        Node* last_input;

        int node_amount;

    public:
        // Constructors
        MinHeapQueue(){
            this->head = NULL;
            this->last_input = NULL;
            this->node_amount = 0;
        }
        MinHeapQueue(int val){
            this->head = new Node(val);
            this->last_input = head;
            this->node_amount = 1;
        }

        // Methods
        void push(int n_val){ // Pushes an element into the queue - Complexity O(n)
            node_amount++; // Increases the amount of elements

            if (!head){ // Checks if the queue is empty
                head = new Node(n_val);
                last_input = head;
                return;
            } 

            bool exit = false; // Exit flag

            Node* n_node = new Node(n_val); // New node to insert
            queue <Node*> node_list; // Normal queue for de DFS

            node_list.push(head); // Push the initial element

            while(node_list.size() > 0 && !exit){ // DFS with exit flag

                node_list.push(NULL); // Separates with a NULL
                while(node_list.front() != NULL && !exit){

                    if(node_list.front()->getLeft()) node_list.push(node_list.front()->getLeft()); // Pushes all the edges of the node
                    if(node_list.front()->getRight()) node_list.push(node_list.front()->getRight());

                    if(!node_list.front()->getLeft()){ // Checks if the new node has to be put at the left
                        node_list.front()->setLeft(n_node);
                        n_node->setParent(node_list.front());

                        last_input = n_node;
                        exit = true; // Exits the loop
                        continue;
                    } 

                    if(!node_list.front()->getRight()){// Checks if the new node has to be put at the right
                        node_list.front()->setRight(n_node);
                        n_node->setParent(node_list.front());

                        last_input = n_node;
                        exit = true; // Exits the loop
                        continue;
                    } 

                    node_list.pop(); // Pops the queue
                }

                node_list.pop(); // Pops the queue
            }

            Node* current = n_node; // Creates an iterator

            while(current->getParent() && current->getValue() < current->getParent()->getValue()){ // Returns to the top and swaps the nodes until the node is where it belongs
                current->setValue(current->getParent()->getValue());
                current->getParent()->setValue(n_val);

                current = current->getParent();
            }
        }

        void pop(){ // Pops the first element and orders the queue
        
            if (!head) return; // Flag to check if the queue has elements

            if (!head->getLeft() && !head->getRight()){ // Case for the last node
                head = NULL;
                last_input = NULL;

                return;
            }

            node_amount--; // Decreases the size

            queue <Node*> node_list; // Normal queue for the DFS

            node_list.push(head); // Pushes the initial element

            while(node_list.size() > 0){ // DFS

                node_list.push(NULL); // Separates with a NULL
                while(node_list.front()){

                    if(node_list.front()->getLeft()){ // Pushes all the edges of the node and updates the las inserted element
                        node_list.push(node_list.front()->getLeft());
                        last_input = node_list.back();
                    } 
                    if(node_list.front()->getRight()){
                        node_list.push(node_list.front()->getRight());
                        last_input = node_list.back();
                    }

                    node_list.pop(); // Pops the queue
                }

                node_list.pop(); // Pops the queue
            }

            head->setValue(last_input->getValue()); // The value of the head is now the last input's value

            Node* last_input_parent = last_input->getParent(); // Creates a pointer to the parent node of the last element
            if(last_input_parent->getLeft() == last_input) last_input_parent->setLeft(NULL); // If the last element is the left one, the pointer to it is set to NULL
            if(last_input_parent->getRight() == last_input) last_input_parent->setRight(NULL); // If the last element is the right one, the pointer to it is set to NULL

            delete last_input; // Deletes the last input

            last_input = last_input_parent; // The new las input is the parent

            Node* current = head; // An iterator is created at the new head

            bool exit = false; // Exit flag

            while(!exit){ // A while that depends on the exit flag
                if (current->getLeft() && current->getRight()){ // If it has both child nodes
                    if (current->getValue() > current->getLeft()->getValue() || current->getValue() > current->getRight()->getValue()){ // Checks if the current value is greater
                        if (current->getLeft()->getValue() <= current->getRight()->getValue()){ // Checks which is the leasser of both child nodes
                            int val = current->getValue(); // Swaps the nodes

                            current->setValue(current->getLeft()->getValue());
                            current->getLeft()->setValue(val);

                            current = current->getLeft(); // Iterates to the left
                            continue; // Returns to the start of the whole cycle
                        }

                        if (current->getLeft()->getValue() > current->getRight()->getValue()){ // Dual case for the right
                            int val = current->getValue(); // Swap

                            current->setValue(current->getRight()->getValue());
                            current->getRight()->setValue(val);

                            current = current->getRight(); // Iterates to the right
                            continue; // Returns to the start of the whole cycle
                        }

                    }

                    exit = true; // If any of those is lesser, it exits the cycle
                    continue;
                }

                if (current->getLeft()){ // If only the left node exists
                    if (current->getValue() > current->getLeft()->getValue()){ // Is the left node lesser?

                        int val = current->getValue(); // Swaps bothe values

                        current->setValue(current->getLeft()->getValue());
                        current->getLeft()->setValue(val);

                        current = current->getLeft(); // Iterates to the left
                        continue; // Returns to the start of the whole cycle
                    }

                    exit = true; // If it does not have a child it exits the cycle
                    continue;
                }

                if (current->getRight()){ // If only the right node exists, dual case for right
                    if (current->getValue() > current->getRight()->getValue()){
                        int val = current->getValue(); // Swaps

                        current->setValue(current->getRight()->getValue());
                        current->getRight()->setValue(val);

                        current = current->getRight(); // Iterates to the right
                        continue; // Returns to the start of the whole cycle
                    }

                    exit = true; // If conditions are not met, it exits the cycle
                    continue;
                }

                return; // Else it exits the functions, having or not met any condition          
            }
        }

        int top(){ // Function to see the highest priority node - Complexity O(1)
            if (head) return head->getValue(); // Checks if the queue exists

            return -1;
        }

        bool empty(){ // Function to see if the queue is empty - Complexity O(1)
            if (!head) return true; // Checks if the queue exists

            return false;
        }

        int size(){ // Function to see the size of the queue - Complexity O(1)
            if (head) return this->node_amount; // Checks if the queue exists, if so, returns the size variable

            return 0;
        }

        void print(){ // Prints the whole queue

            if (!head) return; // Checks if the queue exists

            queue <Node*> node_list; // Normal queue for the DFS

            node_list.push(head); // Push the initial element

            while(node_list.size() > 0){ // DFS

                node_list.push(NULL); // Separates with a NULL
                while(node_list.front()){
                    if(!node_list.front()->getParent()) cout << node_list.front()->getValue() << "<-MAIN"; // Prints diferent if it is the front of the queue
                    else cout << node_list.front()->getValue() << "<-" << node_list.front()->getParent()->getValue() << " "; // Prints the other elements

                    if(node_list.front()->getLeft()) node_list.push(node_list.front()->getLeft()); // Pushes all the edges of the node
                    if(node_list.front()->getRight()) node_list.push(node_list.front()->getRight());

                    node_list.pop(); // Pops the queue
                }

                cout << endl; // Separates with an end of line

                node_list.pop(); // Pops the queue
            }
        }
};

int main(){

    MinHeapQueue lista(2); // Create the Queue

    cout << "Push Heap Queue:\n";

    lista.push(8); // Push 4 elements
    lista.push(4);
    lista.push(9);
    lista.push(5);
    
    lista.print();

    cout << "\n----------------------------\n";
    cout << "Push Heap Queue:\n";
    
    lista.push(9); // Push 3 elements
    lista.push(7);
    lista.push(1);

    lista.print();

    cout << "\n----------------------------\n";
    cout << "Pop Heap Queue:\n";

    lista.pop(); // Pop the first element 3 times
    lista.pop();
    lista.pop();

    lista.print();

    cout << "\n----------------------------\n";
    cout << "Top of Heap Queue: " << lista.top() << endl; // Diplay the top of the queue

    cout << "\n----------------------------\n";
    cout << "Is Heap Queue empty: " << lista.empty() << endl; // Diplay if the queue is empty

    cout << "\n----------------------------\n";
    cout << "Size of Heap Queue: " << lista.size() << endl; // Diplay the size of the queue
}