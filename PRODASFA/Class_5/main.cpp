#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *left, *right;
    
    Node (): data(0), left(NULL), right(NULL){}
    Node (int d): data(d), left(NULL), right(NULL){}
};

class BST{
    private:
        Node *root;
        void insert(int &, Node *&);
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
        void insert(int &value){insert(value, root);}
        void InOrder(){InOrder(root);}
        void PreOrder(){PreOrder(root);}
        void PostOrder(){PostOrder(root);}

        void print(){print(root);}

        void DeleteBST(Node *&);
};

void BST::insert(int &value, Node *&root){
    if(root==NULL){
        root = new Node(value);
    }
    else{
        if(value < root->data){
            insert(value, root->left);
        }
        else if(value > root->data){
            insert(value, root->right);
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
        cout << root->data << endl;

        if(root->left) cout << root->left->data << " ";
        if(root->right) cout << root->right->data;

        cout << endl;

        if(root->left->left) print(root->left->left);
        cout << " ";
        if(root->left->right) print(root->left->right);
        cout << " ";
        if(root->right->left) print(root->right->left);
        cout << " ";
        if(root->right->right) print(root->right->right);
    }
}

void BST::DeleteBST(Node *& root){
    if(root){
        DeleteBST(root->left);
        DeleteBST(root->right);

        delete root;
        return;
    }

    return;
}

int main(){
    BST tree;

    int val = 5;
    tree.insert(val);
    val = 6;
    tree.insert(val);
    val = 3;
    tree.insert(val);
    val = 9;
    tree.insert(val);
    val = 4;
    tree.insert(val);
    val = 1;
    tree.insert(val);
    val = 11;
    tree.insert(val);

    tree.print();


}