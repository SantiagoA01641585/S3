#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *left, *right;

    Node (int d): data(d), left(NULL), right(NULL){}
};

class BST{
    private:
        Node *root;
        void Insert(int &, Node *&);
        void InOrder(Node *);
        void PreOrder(Node *);
        void PostOrder(Node *);

        void print(Node *);

    public:
        BST():root(NULL){}
        ~BST(){
            DeleteBST(root);
            cout << "\nDestructor: BST deleted";
        }

        // Functions
        void insert(int &value){Insert(value, root);}
        void InOrder(){InOrder(root);}
        void PreOrder(){PreOrder(root);}
        void PostOrder(){PostOrder(root);}

        void print(){print(root);}

        void DeleteBST(Node *&);
};

void BST::Insert(int &value, Node *&root){
    if(root==NULL){
        root = new Node(value);
    }
    else{
        if(value < root->data){
            Insert(value, root->left);
        }
        else if(value > root->data){
            Insert(value, root->right);
        }
        else{
            cout << "Repeated element.\n";
        }
    }
}

void BST::print(Node *root){
    if(root==NULL){
        return;
    }
    else{
        cout << root->data;

        if(root->left) print(root->left);
        if(root->right) print(root->right);
    }
}

int main(){
    BST tree;

    int val = 5;

    tree.insert(val);

    //tree.print();


}