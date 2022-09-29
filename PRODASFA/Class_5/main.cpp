#include <iostream>
#include <queue>

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

        void SubstituteToMin(Node *&, Node *&);
        void DeleteNode(int &, Node *&);

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

        void DeleteNode(int &value){DeleteNode(value, root);}
        
        void BFT();

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

void BST::InOrder(Node *root){
    if(root == NULL)
        return;

    InOrder(root->left);
    cout << root->data << " ";
    InOrder(root->right);
}

void BST::PreOrder(Node *root){
    if(root == NULL)
        return;

    cout << root->data << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

void BST::PostOrder(Node *root){
    if(root == NULL)
        return;

    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->data << " ";
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

void BST::SubstituteToMin(Node *&root, Node *&apAux){
    if(root->left != NULL)
        SubstituteToMin(root->left, apAux);
    else{
        // Transfer data from the substitute node
        apAux->data = root->data;
        // Save the minValue node (to delete)
        apAux = root;
        // Swap place minValue-right (Node or NULL)
        root = root->right;
    }
}

void BST::DeleteNode(int &value, Node*&root){
    if(root == NULL)
        cout << "BST is empty" << endl << endl;
    else{
        if (value < root->data)
            DeleteNode(value, root->left);
        else if (value > root->data)
            DeleteNode(value, root->right);
        else{
            Node *apAux = root;

            if(apAux->right == NULL) // Only left child node
                root = apAux->left;
            if(apAux->left == NULL) // Only right child node
                root = apAux->right;
            if(apAux->left != NULL && apAux->right != NULL) // Two child nodes
                SubstituteToMin(root->right, apAux);

            cout << "\nThe key to delete: " << value << endl;
            cout << "The element was deleted with the key: " << apAux->data << endl;
            delete apAux;
        }
    }
}

void BST::BFT(){
    if(this->root == NULL){
        cout << "The BST is empty" << endl;
        return;
    }

    queue<Node*> Q;
    Q.push(this->root);

    Node *Aux;
    while (!Q.empty()){
        Q.push(NULL);

        Aux = Q.front();
        while(Aux != NULL){
            cout << Aux->data << " ";

            if(Aux->left != NULL)
                Q.push(Aux->left);
            if(Aux->right != NULL)
                Q.push(Aux->right);

            Q.pop();
            Aux = Q.front();
        }
        Q.pop();

        cout << endl;
    }
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
    val = 8;
    tree.insert(val);

    tree.PreOrder();

    cout << endl << endl;

    tree.BFT();

    cout << endl << endl;

    tree.BFT();

    return 0;
}