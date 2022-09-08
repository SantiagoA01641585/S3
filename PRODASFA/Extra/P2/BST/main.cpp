#include <iostream>

using namespace std;

template <typename T>
class Node{
    template <typename U> friend class BST;
    public:
        T data;
        Node <T> *left;
        Node <T> *right;

    public:
        T getData(){
            return data;
        }
        void setData(T d){
            data = d;
        }
        Node(){
            this->left = NULL;
            this->right = NULL;
        }
        Node(T d){
            this->left = NULL;
            this->right = NULL;
            data = d;
        }
};

template <typename T>
class BST{
    public:
        Node <T> *root;
        BST(){
            root = NULL;
        }

        //Inorder Traversal
        void inorder(Node <T> *root2){
            if(root2 != NULL){
                //Traverse left
                inorder(root2->left);

                //Traverse root
                cout << root2->data << " -> ";

                //Trverse right  
                inorder(root2->right);          
                }
        }

};

int main(){

}