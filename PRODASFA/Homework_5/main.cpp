#include <iostream>
#include <queue>

using namespace std;

template <typename T> class Node{
    private:
        // Atributes
        T data;
        Node <T>* left;
        Node <T>* right;
    
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

template <typename T> class BST{
    private:
        Node <T>* root;

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
        void insertNode(T val){

            if (root == NULL){
                root = new Node <T>(val);
                return;
            } 

            Node <T>* n_node = new Node <T>(val);
            Node <T>* current = root;

            while(true){
                if (n_node->getData() == current->getData()) return;

                if (n_node->getData() < current->getData()){
                    if (current->getLeft()){
                        current = current->getLeft();
                        continue;
                    }

                    current->setLeft(n_node);
                    return;
                }

                if (n_node->getData() > current->getData()){
                    if (current->getRight()){
                        current = current->getRight();
                        continue;
                    }

                    current->setRight(n_node);
                    return;
                }
            }
        }

        void preOrder(Node <T>* root){
            if (root == NULL) return;

            cout << root->getData() << " ";
            preOrder(root->getLeft());
            preOrder(root->getRight());
        }

        void inOrder(Node <T>* root){
            if (root == NULL) return;

            inOrder(root->getLeft());
            cout << root->getData() << " ";
            inOrder(root->getRight());
        }

        void postOrder(Node <T>* root){
            if (root == NULL) return;

            postOrder(root->getLeft());
            postOrder(root->getRight());
            cout << root->getData() << " ";
        }

        void levelByLevel(){
            queue <Node <T>*> queue;
            queue.push(root);

            while (queue.size() > 0){

                queue.push(NULL);
                while (queue.front()){

                    cout << queue.front()->getData() << " ";

                    if (queue.front()->getLeft()){
                        queue.push(queue.front()->getLeft());
                    }

                    if (queue.front()->getRight()){
                        queue.push(queue.front()->getRight());
                    }

                    queue.pop();
                }
                cout << endl;

                queue.pop();
            }
        }

        void visit(int order_type){
            switch (order_type) {
                case 1:
                    preOrder(root);
                    break;

                case 2:
                    inOrder(root);
                    break;

                case 3:
                    postOrder(root);
                    break;

                case 4:
                    levelByLevel();
                
                default:
                    break;
            }
        }

        int height(){
            queue <Node <T>*> queue;
            queue.push(root);

            int cont = 0;

            while (queue.size() > 0){

                queue.push(NULL);
                cont++;
                while (queue.front()){

                    if (queue.front()->getLeft()){
                        queue.push(queue.front()->getLeft());
                    }

                    if (queue.front()->getRight()){
                        queue.push(queue.front()->getRight());
                    }

                    queue.pop();
                }

                queue.pop();
            }

            return cont;
        }

        void ancestors(int value){
            vector <Node <T>*> traceway;

            Node <T>* current = new Node <T>();
            current = root;

            while (true){
                if (current->getData() == value) break;

                if (current->getLeft() || current->getRight()){
                    if(value < current->getData()){
                        traceway.push_back(current);
                        current = current->getLeft();
                        continue;
                    }
                    if(value > current->getData()){
                        traceway.push_back(current);
                        current = current->getRight();
                        continue;
                    }
                }

                traceway.push_back(current);
            }

            for (int i=traceway.size()-1; i>0; i--){

                cout << "->" << traceway[i]->getData() << endl;
                traceway.pop_back();
            }
        }

};

int main(){

    BST <int> tree;

    tree.insertNode(6);
    tree.insertNode(2);
    tree.insertNode(7);
    tree.insertNode(5);
    tree.insertNode(9);
    tree.insertNode(11);
    tree.insertNode(1);
    tree.insertNode(8);
    tree.insertNode(14);

    tree.visit(4);

    cout << "\nTree height: " << tree.height() << endl;

    tree.ancestors(11);

}