#include <iostream>

using namespace std;

struct Node{
    int value;
};

class Queue{
    private:
        Node *Q;
        int front, rear, N;
    public:
        Queue (int size){
            N = size;
            Q = new struct Node[N];
            rear = front = -1;
        }

        ~Queue (){
            cout << "Destructor: Erase Queue" << endl;
            delete [] Q;
        }

        void Enqueue(int);
        Node *Dequeue();
        void Display();
        bool IsEmpty();
};



int main(){
    
    cout << "Hola";
}