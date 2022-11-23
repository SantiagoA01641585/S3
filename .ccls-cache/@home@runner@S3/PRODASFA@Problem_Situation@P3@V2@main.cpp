#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class ObjByIP{
    private:
        // Atributes
        long long int ip;
        int access;

    public:
        // Constructors
        ObjByIP(){
            this->ip = 0;
            this->access = 0;
        }
        ObjByIP(long long int ip){
            this->ip = ip;
            this->access = 1;
        }
        ObjByIP(long long int ip, int access){
            this->ip = ip;
            this->access = access;
        }

        // Getters & Setters
        long long int getIP(){
            return this->ip;
        }

        void setIP(long long int ip){
            this->ip = ip;
        }

        int getAccess(){
            return this->access;
        }

        void setAccess(int access){
            this->access = access;
        }

        // Operator overcharge
        bool operator > (const ObjByIP& otro){
            return this->ip > otro.ip;
        }

        bool operator < (const ObjByIP& otro){
            return this->ip < otro.ip;
        }

        bool operator >= (const ObjByIP& otro){
            return this->ip >= otro.ip;
        }

        bool operator <= (const ObjByIP& otro){
            return this->ip <= otro.ip;
        }

        bool operator == (const ObjByIP& otro){
            return this->ip == otro.ip;
        }

        friend std::ostream& operator << (ostream& salida, const ObjByIP& miIP){
            salida << miIP.ip << " - " << miIP.access;
            return salida;
        }
};

class ObjByAccess{
    private:
        // Atributes
        long long int ip;
        int access;

    public:
        // Constructors
        ObjByAccess(){
            this->ip = 0;
            this->access = 0;
        }
        ObjByAccess(int access){
            this->ip = 0;
            this->access = access;
        }
        ObjByAccess(long long int ip, int access){
            this->ip = ip;
            this->access = access;
        }

        // Getters & Setters
        long long int getIP(){
            return this->ip;
        }

        void setIP(long long int ip){
            this->ip = ip;
        }

        int getAccess(){
            return this->access;
        }

        void setAccess(int access){
            this->access = access;
        }

        // Operator overcharge
        bool operator > (const ObjByAccess& otro){
            return this->access > otro.access;
        }

        bool operator < (const ObjByAccess& otro){
            return this->access < otro.access;
        }

        bool operator >= (const ObjByAccess& otro){
            return this->access >= otro.access;
        }

        bool operator <= (const ObjByAccess& otro){
            return this->access <= otro.access;
        }

        bool operator == (const ObjByAccess& otro){
            return this->access == otro.access;
        }

        friend std::ostream& operator << (ostream& salida, const ObjByAccess& miIP){
            salida << miIP.ip << " - " << miIP.access;
            return salida;
        }
};

template <typename T> class Node{ // A class for the node
    private:
        // Atributes
        T val;
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
        Node(T val){
            this->val = val;
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
        }

        // Getters & Setters
        T getValue() const{
            return this->val;
        }

        void setValue(T val){
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

template <typename T> class MaxHeapQueue{ // Main class for the queue
    private:
        // Atributes
        Node <T>* head;
        Node <T>* last_input;

        int node_amount;

    public:
        // Constructors
        MaxHeapQueue(){
            this->head = NULL;
            this->last_input = NULL;
            this->node_amount = 0;
        }
        MaxHeapQueue(T val){
            this->head = new Node <T>(val);
            this->last_input = head;
            this->node_amount = 1;
        }

        bool checkTypeIP(){ // Checks if the typename is ObjByIP
            return (is_same<T, ObjByIP>::value); // Returns the result
        }

        // Methods
        void push(T n_val){ // Pushes an element into the queue - Complexity O(n)
            node_amount++; // Increases the amount of elements

            if (!head){ // Checks if the queue is empty
                head = new Node <T> (n_val);
                last_input = head;
                return;
            } 

            bool exit = false; // Exit flag

            Node <T>* n_node = new Node <T> (n_val); // New node to insert
            queue <Node <T>*> node_list; // Normal queue for de DFS

            node_list.push(head); // Push the initial element

            while(node_list.size() > 0 && !exit){ // DFS with exit flag

                node_list.push(NULL); // Separates with a NULL
                while(node_list.front() != NULL && !exit){ // Evaluates the exit flag and if the front of the queue is NULL
                    
                    if (this->checkTypeIP()){ // If the type is ObjByIP
                        if (node_list.front()->getValue() == n_node->getValue()){ // Checks if the current value is the same as the input
                            int curr_access = node_list.front()->getValue().getAccess(); // Sums the current number of accesses
                            curr_access++;
                            T n_IP = node_list.front()->getValue();
                            n_IP.setAccess(curr_access);

                            node_list.front()->setValue(n_IP);

                            return; // Exits the function
                        }

                        if (node_list.front()->getLeft()){ // If it has a left node
                            if (node_list.front()->getLeft()->getValue() == n_node->getValue()){ // Checks if the left node of the current value is the same as the input
                                int curr_access = node_list.front()->getLeft()->getValue().getAccess(); // Sums the number of accesses of the left node of the current node
                                curr_access++;
                                T n_IP = node_list.front()->getLeft()->getValue();
                                n_IP.setAccess(curr_access);

                                node_list.front()->getLeft()->setValue(n_IP);

                                return; // Exits the function
                            }
                        }

                        if (node_list.front()->getRight()){ // If it has a right node
                            if (node_list.front()->getRight()->getValue() == n_node->getValue()){ // Checks if the right node of the current value is the same as the input
                                int curr_access = node_list.front()->getRight()->getValue().getAccess(); // Sums the number of accesses of the right node of the current node
                                curr_access++;
                                T n_IP = node_list.front()->getRight()->getValue();
                                n_IP.setAccess(curr_access);

                                node_list.front()->getRight()->setValue(n_IP);

                                return; // Exits the function
                            }
                        }
                    }

                    if(node_list.front()->getLeft()){
                        node_list.push(node_list.front()->getLeft()); // Pushes all the edges of the node
                    } 
                    if(node_list.front()->getRight()){
                        node_list.push(node_list.front()->getRight());
                    } 

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

            Node <T>* current = n_node; // Creates an iterator

            while(current->getParent() && current->getValue() > current->getParent()->getValue()){ // Returns to the top and swaps the nodes until the node is where it belongs
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

            queue <Node <T>*> node_list; // Normal queue for the DFS

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

            Node <T>* last_input_parent = last_input->getParent(); // Creates a pointer to the parent node of the last element
            if(last_input_parent->getLeft() == last_input) last_input_parent->setLeft(NULL); // If the last element is the left one, the pointer to it is set to NULL
            if(last_input_parent->getRight() == last_input) last_input_parent->setRight(NULL); // If the last element is the right one, the pointer to it is set to NULL

            delete last_input; // Deletes the last input

            last_input = last_input_parent; // The new las input is the parent

            Node <T>* current = head; // An iterator is created at the new head

            bool exit = false; // Exit flag

            while(!exit){ // A while that depends on the exit flag
                if (current->getLeft() && current->getRight()){ // If it has both child nodes
                    if (current->getValue() < current->getLeft()->getValue() || current->getValue() < current->getRight()->getValue()){ // Checks if the current value is lesser
                        if (current->getLeft()->getValue() >= current->getRight()->getValue()){ // Checks which is the greater of both child nodes
                            T val = current->getValue(); // Swaps the nodes

                            current->setValue(current->getLeft()->getValue());
                            current->getLeft()->setValue(val);

                            current = current->getLeft(); // Iterates to the left
                            continue; // Returns to the start of the whole cycle
                        }

                        if (current->getLeft()->getValue() < current->getRight()->getValue()){ // Dual case for the right
                            T val = current->getValue(); // Swap

                            current->setValue(current->getRight()->getValue());
                            current->getRight()->setValue(val);

                            current = current->getRight(); // Iterates to the right
                            continue; // Returns to the start of the whole cycle
                        }

                    }

                    exit = true; // If any of those is greater, it exits the cycle
                    continue;
                }

                if (current->getLeft()){ // If only the left node exists
                    if (current->getValue() < current->getLeft()->getValue()){ // Is the left node greater?

                        T val = current->getValue(); // Swaps bothe values

                        current->setValue(current->getLeft()->getValue());
                        current->getLeft()->setValue(val);

                        current = current->getLeft(); // Iterates to the left
                        continue; // Returns to the start of the whole cycle
                    }

                    exit = true; // If it does not have a child it exits the cycle
                    continue;
                }

                if (current->getRight()){ // If only the right node exists, dual case for right
                    if (current->getValue() < current->getRight()->getValue()){
                        T val = current->getValue(); // Swaps

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

        T top(){ // Function to see the highest priority node - Complexity O(1)
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

            queue <Node <T>*> node_list; // Normal queue for the DFS

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

string extractIP(string line){ // Extracts an IP from a line of text - Complexity O(1)
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

long long int IP2Int(string ip){ // Hash function given a string - Complexity O(1)
    string aux; // Auxiliar string
    long long int res; // Int to store the ip

    int cont = 0; // Cont
    for(int i=0; i<ip.size(); i++){ // Iterates trough the ip
        if (ip[i] == '.' || ip[i] == ':'){ // Evades '.' and ':'
            cont++;

            if (ip[i] == ':'){
                res = stoll(aux); // Converts to int

                return res;
            }

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

int main(){
    ifstream infile; // File
    string line; // Line gotten

    ofstream outfile1; // Sorted file
    ofstream outfile2; // Most accessed ip's file

    MaxHeapQueue <ObjByIP> IPSort; // Heap queue of the sort

    infile.open("bitacoraHeap.txt"); // Open the file

    while (getline(infile, line)){ // Gets all the lines inside the file
        string ip = extractIP(line); // Extracts the ip on a string
        
        long long int n_ip = IP2Int(ip); // Hashes the IP

        ObjByIP ip_obj(n_ip); // Creates an object from the data

        IPSort.push(ip_obj); // Pushes to the queue
    }

    infile.close(); // Closes the file

    //-----------------------------------------------------------

    MaxHeapQueue <ObjByAccess> AccessSort; // Queue to sort by access
    outfile1.open("bitacora_ordenada.txt"); // Open the file

    while (!IPSort.empty()){ // While the queue is not empty
        ObjByIP curr = IPSort.top(); // Get the top of the queue

        ObjByAccess curr_access(curr.getIP(), curr.getAccess()); // Assign the values to an ObjByAccess object
        AccessSort.push(curr_access); // Pushes to the access queue

        outfile1 << curr << endl; // Write in the file

        IPSort.pop(); // Pop the first element
    }

    outfile1.close(); // Close the file

    //-----------------------------------------------------------

    outfile2.open("ips_con_mayor_acceso.txt"); // Open the file

    int cont = 0; // Control counter
    while (!AccessSort.empty() && cont < 5){ // While the access queue is not empty and the counter is less than 5
        ObjByAccess curr = AccessSort.top(); // Get the top of the queue

        outfile2 << curr << endl; // Write in the file

        AccessSort.pop(); // Pops the first element

        cont++; // Increasses the counter
    }

    outfile2.close(); // Close the file
    
}