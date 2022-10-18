#include <iostream>
#include <queue>

using namespace std;

class Node{
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

class MinHeapQueue{
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
        void push(int n_val){
            node_amount++;

            if (!head){
                head = new Node(n_val);
                last_input = head;
                return;
            } 

            bool exit = false;

            Node* n_node = new Node(n_val);
            queue <Node*> node_list;

            node_list.push(head);

            while(node_list.size() > 0 && !exit){

                node_list.push(NULL);
                while(node_list.front() != NULL && !exit){

                    if(node_list.front()->getLeft()) node_list.push(node_list.front()->getLeft());
                    if(node_list.front()->getRight()) node_list.push(node_list.front()->getRight());

                    if(!node_list.front()->getLeft()){
                        node_list.front()->setLeft(n_node);
                        n_node->setParent(node_list.front());

                        last_input = n_node;
                        exit = true;
                        continue;
                    } 

                    if(!node_list.front()->getRight()){
                        node_list.front()->setRight(n_node);
                        n_node->setParent(node_list.front());

                        last_input = n_node;
                        exit = true;
                        continue;
                    } 

                    node_list.pop();
                }

                node_list.pop();
            }

            Node* current = n_node;

            while(current->getParent() && current->getValue() < current->getParent()->getValue()){
                current->setValue(current->getParent()->getValue());
                current->getParent()->setValue(n_val);

                current = current->getParent();
            }
        }

        void pop(){
            node_amount--;

            if (!head) return;

            queue <Node*> node_list;

            node_list.push(head);

            while(node_list.size() > 0){

                node_list.push(NULL);
                while(node_list.front()){

                    if(node_list.front()->getLeft()){
                        node_list.push(node_list.front()->getLeft());
                        last_input = node_list.back();
                    } 
                    if(node_list.front()->getRight()){
                        node_list.push(node_list.front()->getRight());
                        last_input = node_list.back();
                    }

                    node_list.pop();
                }

                node_list.pop();
            }

            head->setValue(last_input->getValue());

            Node* last_input_parent = last_input->getParent();
            if(last_input_parent->getLeft() == last_input) last_input_parent->setLeft(NULL);
            if(last_input_parent->getRight() == last_input) last_input_parent->setRight(NULL);

            delete last_input;

            last_input = last_input_parent;

            Node* current = head;

            bool exit = false;

            while(!exit){
                if (current->getLeft() && current->getRight()){
                    if (current->getValue() > current->getLeft()->getValue() || current->getValue() > current->getRight()->getValue()){
                        if (current->getLeft()->getValue() <= current->getRight()->getValue()){
                            int val = current->getValue();

                            current->setValue(current->getLeft()->getValue());
                            current->getLeft()->setValue(val);

                            current = current->getLeft();
                            continue;
                        }

                        if (current->getLeft()->getValue() > current->getRight()->getValue()){
                            int val = current->getValue();

                            current->setValue(current->getRight()->getValue());
                            current->getRight()->setValue(val);

                            current = current->getRight();
                            continue;
                        }

                    }

                    exit = true;
                    continue;
                }

                if (current->getLeft()){
                    if (current->getValue() > current->getLeft()->getValue()){

                        int val = current->getValue();

                        current->setValue(current->getLeft()->getValue());
                        current->getLeft()->setValue(val);

                        current = current->getLeft();
                        continue;
                    }

                    exit = true;
                    continue;
                }

                if (current->getRight()){
                    if (current->getValue() > current->getRight()->getValue()){
                        int val = current->getValue();

                        current->setValue(current->getRight()->getValue());
                        current->getRight()->setValue(val);

                        current = current->getRight();
                        continue;
                    }

                    exit = true;
                    continue;
                }

                return;                
            }
        }

        int top(){
            if (head) return head->getValue();

            return 0;
        }

        bool empty(){
            if (!head) return true;

            return false;
        }

        int size(){
            if (head) return this->node_amount;

            return 0;
        }

        void print(){
            queue <Node*> node_list;

            node_list.push(head);

            while(node_list.size() > 0){

                node_list.push(NULL);
                while(node_list.front()){
                    if(!node_list.front()->getParent()) cout << node_list.front()->getValue() << "<-MAIN";
                    else cout << node_list.front()->getValue() << "<-" << node_list.front()->getParent()->getValue() << " ";

                    if(node_list.front()->getLeft()) node_list.push(node_list.front()->getLeft());
                    if(node_list.front()->getRight()) node_list.push(node_list.front()->getRight());

                    node_list.pop();
                }

                cout << endl;

                node_list.pop();
            }
        }
};

int main(){

    MinHeapQueue lista(2);

    cout << "Push Heap Queue:\n";

    lista.push(8);
    lista.push(4);
    lista.push(9);
    lista.push(5);
    
    lista.print();

    cout << "\n----------------------------\n";
    cout << "Push Heap Queue:\n";
    
    lista.push(9);
    lista.push(7);
    lista.push(1);

    lista.print(); 

    cout << "\n----------------------------\n";
    cout << "Pop Heap Queue:\n";

    lista.pop();
    lista.pop();
    lista.pop();

    lista.print(); 

    cout << "\n----------------------------\n";
    cout << "Top of Heap Queue: " << lista.top() << endl; 

    cout << "\n----------------------------\n";
    cout << "Is Heap Queue empty: " << lista.empty() << endl; 

    cout << "\n----------------------------\n";
    cout << "Size of Heap Queue: " << lista.size() << endl;



}