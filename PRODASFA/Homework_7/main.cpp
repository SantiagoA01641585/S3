#include <iostream>
#include <queue>

using namespace std;

template <typename T> class Node{
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
        void updateBalanceFactor(){
            if (this->left && this->right) balance_factor = this->left->height - this->right->height;
            else if (this->left) balance_factor = this->left->height;
            else if (this->right) balance_factor = -this->right->height;
            else balance_factor = 0;
        }

        void leftRotate(){
            if (this->getPrev()->getRight() != this) return;

            Node <T>* y = this;
            Node <T>* x = this->getPrev();

            if (y->getLeft()) x->setRight(y->getLeft());
            else x->setRight(NULL);
            if (x->getRight()) x->getRight()->setPrev(x);

            if (x->getPrev()){
                if(x->getPrev()->getRight() == x) x->getPrev()->setRight(y);
                if(x->getPrev()->getLeft() == x) x->getPrev()->setLeft(y);
            }
            y->setPrev(x->getPrev());

            y->setLeft(x);
            x->setPrev(y); 

            int new_x_s = 0;
            if (x->getLeft()) new_x_s += x->getLeft()->getSize() + 1;
            if (x->getRight()) new_x_s += x->getRight()->getSize() + 1;
            x->setSize(new_x_s);

            int new_y_s = 0;
            if (y->getLeft()) new_y_s += y->getLeft()->getSize() + 1;
            if (y->getRight()) new_y_s += y->getRight()->getSize() + 1;
            y->setSize(new_y_s);

            if (x->getLeft() && x->getRight()){
                if (x->getLeft()->getHeight() >= x->getRight()->getHeight())
                    x->setHeight(x->getLeft()->getHeight() + 1);
                if (x->getLeft()->getHeight() < x->getRight()->getHeight())
                    x->setHeight(x->getRight()->getHeight() + 1);
            } 
            else if (x->getLeft())
                x->setHeight(x->getLeft()->getHeight() + 1);
            else if (x->getRight())
                x->setHeight(x->getRight()->getHeight() + 1);
            else 
                x->setHeight(1);

            if (y->getLeft() && y->getRight()){
                if (y->getLeft()->getHeight() >= y->getRight()->getHeight())
                    y->setHeight(y->getLeft()->getHeight() + 1);
                if (y->getLeft()->getHeight() < y->getRight()->getHeight())
                    y->setHeight(y->getRight()->getHeight() + 1);
            } 
            else if (y->getLeft())
                y->setHeight(y->getLeft()->getHeight() + 1);
            else if (y->getRight())
                y->setHeight(y->getRight()->getHeight() + 1);
            else
                y->setHeight(1);

            x->updateBalanceFactor();
            y->updateBalanceFactor();

        }

        void rightRotate(){
            if (this->getPrev()->getLeft() != this) return;

            Node <T>* x = this;
            Node <T>* y = this->getPrev();

            y->setLeft(x->getRight());
            if (x->getRight()) x->getRight()->setPrev(x);

            if (y->getPrev()){
                if(y->getPrev()->getRight() == y) y->getPrev()->setRight(x);
                if(y->getPrev()->getLeft() == y) y->getPrev()->setLeft(x);
            }
            x->setPrev(y->getPrev());

            x->setRight(y);
            y->setPrev(x); 

            int new_y_s = 0;
            if (y->getLeft()) new_y_s += y->getLeft()->getSize() + 1;
            if (y->getRight()) new_y_s += y->getRight()->getSize() + 1;
            y->setSize(new_y_s);

            int new_x_s = 0;
            if (x->getLeft()) new_x_s += x->getLeft()->getSize() + 1;
            if (x->getRight()) new_x_s += x->getRight()->getSize() + 1;
            x->setSize(new_x_s);

            if (y->getLeft() && y->getRight()){
                if (y->getLeft()->getHeight() >= y->getRight()->getHeight())
                    y->setHeight(y->getLeft()->getHeight() + 1);
                if (y->getLeft()->getHeight() < y->getRight()->getHeight())
                    y->setHeight(y->getRight()->getHeight() + 1);
            } 
            else if (y->getLeft())
                y->setHeight(y->getLeft()->getHeight() + 1);
            else if (y->getRight())
                y->setHeight(y->getRight()->getHeight() + 1);
            else
            y->setHeight(1);
            
            if (x->getLeft() && x->getRight()){
                if (x->getLeft()->getHeight() >= x->getRight()->getHeight())
                    x->setHeight(x->getLeft()->getHeight() + 1);
                if (x->getLeft()->getHeight() < x->getRight()->getHeight())
                    x->setHeight(x->getRight()->getHeight() + 1);
            } 
            else if (x->getLeft())
                x->setHeight(x->getLeft()->getHeight() + 1);
            else if (x->getRight())
                x->setHeight(x->getRight()->getHeight() + 1);
            else
                x->setHeight(1);

            x->updateBalanceFactor();
            y->updateBalanceFactor();

        }
};

template <typename T> class AVL{
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
        void leftRotate(Node <T>* obj_node){
            obj_node->leftRotate();
        }

        void rightRotate(Node <T>* obj_node){
            obj_node->rightRotate();
        }

        void insert(T val){
            Node <T>* n_node = new Node(val);
            n_node->setBF(0);
            n_node->setHeight(1);

            if (!head){
                head = n_node;
                return;
            }

            Node <T>* current = head;
            bool has_been_inserted = false;

            while (!has_been_inserted){
                if (n_node->getData() == current->getData()) return;

                if (n_node->getData() < current->getData()){
                    if (current->getLeft()){
                        current->setSize(current->getSize() + 1);
                        current = current->getLeft();
                        continue;
                    }

                    current->setSize(current->getSize() + 1);
                    n_node->setPrev(current);
                    current->setLeft(n_node);
                    has_been_inserted = true;
                    continue;
                }

                if (n_node->getData() > current->getData()){

                    if (current->getRight()){
                        current->setSize(current->getSize() + 1);
                        current = current->getRight();
                        continue;
                    }

                    current->setSize(current->getSize() + 1);
                    n_node->setPrev(current);
                    current->setRight(n_node);
                    has_been_inserted = true;
                    continue;
                }
            }

            current = n_node;

            while (current->getPrev()){
                current = current->getPrev();
                if(current->getLeft() && current->getRight()){
                    if (current->getLeft()->getHeight() >= current->getRight()->getHeight()) 
                        current->setHeight(current->getLeft()->getHeight() + 1);
                    if (current->getLeft()->getHeight() < current->getRight()->getHeight())
                        current->setHeight(current->getRight()->getHeight() + 1);
                }
                else if(current->getLeft()){
                    current->setHeight(current->getLeft()->getHeight() + 1);
                }
                else{
                    current->setHeight(current->getRight()->getHeight() + 1);
                }

                current->updateBalanceFactor();

                if (current->getBF() > 1){
                    if(0 < current->getLeft()->getBF()) rightRotate(current->getLeft());
                    else{
                        if (current->getLeft()->getRight()) leftRotate(current->getLeft()->getRight());
                        rightRotate(current->getLeft());
                    }
                }
                else if (current->getBF() < -1){
                    if (0 > current->getRight()->getBF()) leftRotate(current->getRight());
                    else {
                        if (current->getRight()->getLeft()) rightRotate(current->getRight()->getLeft());
                        leftRotate(current->getRight());
                    }
                }

                current->updateBalanceFactor();

                cout << endl;
            }

            
            Node <int>* n_head = this->getToTop();
            this->head = n_head;
        }

        void del(){
            Node <T>* current = head;

            queue <Node<T>*> queue;
            vector <Node<T>*> elements;

            queue.push(current);
            elements.push_back(current);

            while(queue.size() > 0){

                queue.push(NULL);
                while (queue.front()){
                    if (queue.front()->getLeft()){
                        queue.push(queue.front()->getLeft());
                        elements.push_back(queue.front()->getLeft());
                    }
                    if (queue.front()->getRight()){
                        queue.push(queue.front()->getRight());
                        elements.push_back(queue.front()->getRight());
                    }

                    queue.pop();                    
                }

                queue.pop();
            }

            for (auto e:elements){
                delete e;
            }

            this->head = NULL;
        }

        bool find(int fetch){
            Node <T>* current = head;

            while (true){
                if (current->getData() == fetch) return true;

                if (fetch < current->getData()){
                    if (current->getLeft()) current = current->getLeft();
                    else return false;
                    continue;
                }

                if (fetch > current->getData()){
                    if (current->getRight()) current = current->getRight();
                    else return false;
                    continue;
                }

                return false;
            }

        }

        int size(){
            if (this->getHead()) return head->getSize() + 1;
            return 0;
        }

        void print(Node<T>* root){
            if (root->getLeft()) print(root->getLeft());
            cout << root->getData() << " ";
            if (root->getRight()) print(root->getRight());
        }

        void printLvL(){
            queue <Node<T>*> queue;
            queue.push(head);

            while (queue.size() > 0){
                queue.push(NULL);
                while (queue.front()){
                    cout << queue.front()->getData() << "(" << queue.front()->getBF() << ") ";
                    if(queue.front()->getLeft()) queue.push(queue.front()->getLeft());
                    if(queue.front()->getRight()) queue.push(queue.front()->getRight());
                    queue.pop();
                }
                cout << endl;
                queue.pop();
            }
        }

        Node <T>* getToTop(){
            Node <T>* current = head;
            while (current->getPrev()) current = current->getPrev();
            return current;
        }

};

int main(){

    AVL <int> avl;

    avl.insert(4);
    avl.insert(3);
    avl.insert(2);
    avl.insert(-1);
    avl.insert(0);
    avl.insert(5);
    avl.insert(7);
    avl.insert(8);

    avl.printLvL();

    cout << "---------------------\n";

    int f = 4;
    cout << "Finding " << 6 << "...\n The result is ";
    string resp = (avl.find(f))? "true\n" : "false\n";
    cout << resp;

    cout << "---------------------\n";
    
    avl.print(avl.getHead());

    cout << "\n---------------------\n";

    avl.del();

    cout << "------------\n";

    cout << avl.size();
}