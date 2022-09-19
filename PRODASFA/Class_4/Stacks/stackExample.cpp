#include <iostream>

using namespace std;

struct Node{
    int num;
};

class Stack{
    private:
        int N, TOP;
        Node *st;
    public:
        Stack(int size){
            N = size;
            TOP = -1;
            st = new struct Node[N];
        }
        ~Stack(){
            cout << "Destructor: Erase Stack" << endl;
            delete [] st;
        }
        void Push(int);
        struct Node *Pop();
        int *Peek();
        bool IsEmpty();
};

void Stack::Push(int NUM){
    if (TOP == N-1){
        cout << "The stack is full (Overflow)." << endl;
    }
    else
    {
        TOP++;
        st[TOP].num = NUM; 
    }
}

struct Node *Stack::Pop(void)
{
    if(TOP<0){
        cout<< "The stack is empty (Underflow)." << endl;
        return NULL;
    }
    TOP--;
    return &st[TOP+1];
};

bool Stack::IsEmpty(){
    if(TOP<0){
        return true;
    }
        return false;
}

int *Stack::Peek(void){
    if(TOP<0){
        return NULL;
    }
    return &(st[TOP].num);
}

int main(void){
    int size;
    cout << "Enter the size of the stack: ";
    cin >> size;

    Stack P(size);

    int x;
    for(int i = 0; i < size; i++){
        cout << "Enter a value: ";
        cin >> x;
        P.Push(x);
    }
    P.Push(100);

    int *v;
    v = P.Peek();
    cout << "The value at the TOP of the stack is: " << *v << endl;

    while (!P.IsEmpty()){
        cout << P.Pop()->num << endl;
    }

    return(0);
    
}