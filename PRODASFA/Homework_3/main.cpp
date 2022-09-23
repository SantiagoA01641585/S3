#include <iostream>

using namespace std;

// Crear la clase Nodo
template <class T> class Node {
    private:
        T data; // Datos contenidos en el nodo

        Node <T> *prev; // Nodo previo
        Node <T> *next; // Nodo siguiente       

    public:

        // Constructores
        Node(){ // Constructor default
            this->data = 0;
            this->next = NULL;
            this->prev = NULL;
        }

        Node(T data){ // Constructor dado un dato
            this->data = data;
            this->next = NULL;
            this->prev = NULL;
        }

        Node(T data, Node <T> *next, Node <T> *prev){ // Constructor dado un nodo siguiente y previo
            this->data = data;
            this->next = next;
            this->prev = prev;
        }

        // Getters y setters
        void setData(T data){
            this->data = data; // Modificar el contenido
        }
        
        T getData(){
            return this->data; // Obtener el contenido
        }

        void setNext(Node <T> *next){
            this->next = next; // Modificar el nodo siguiente
        }

        Node <T> *getNext(){
            return this->next; // Obtener el nodo siguiente
        }

        void setPrev(Node <T> *prev){
            this->prev = prev; // Modificar el nodo siguiente
        }

        Node <T> *getPrev(){
            return this->prev; // Obtener el nodo siguiente
        }
};

template <class T> class DoubleLinkedList { // Clase para la lista doblemente ligada
    private:
        Node <T> *head; // Crear la cabeza de la lista

    public:
        // Constructores
        DoubleLinkedList(){
            head = NULL; // Constructor default
        }

        DoubleLinkedList(T val){
            head = new Node <T> (val); // Constructor con un valor nuevo
        }

        // Métodos
        void insertAfter(int pos, T value){ // Insertar un valor al lado derecho de una posición
            Node <T> *current = new Node <T>; // Nodo para recorrer la lista
            current = this->head;

            int cont = 0;
            while(current && cont<pos){ // Mientras el dato no sea nulo y el contador no exceda el número a buscar
                cont++;
                current = current->getNext(); // Se vuelve el siguiente elemento
            }

            if (!current) return; // Si no encuentra el elemento abandona la función

            Node <T> *n_node = new Node <T> (value); // Nuevo nodo a insertar

            n_node->setNext(current->getNext()); // Se enlaza el nuevo nodo al elemento a la derecha de la posición
            n_node->setPrev(current); // Se enlaza el nuevo nodo al elemento de la posición
            
            if (n_node->getNext()) n_node->getNext()->setPrev(n_node); // Si no se esta en un borde se enlaza la posición derecha al nuevo nodo
            if (n_node->getPrev()) n_node->getPrev()->setNext(n_node); // Si no se esta en un borde se enlaza la posición izquierda al nuevo nodo

            current->setNext(n_node); // Se guarda el nuevo nodo a la derecha del elemento de la posición

            while(current->getPrev()){ // Se regresa al elemento inicial
                current = current->getPrev();
            }

            head = current; // La cabeza (es decir, la lista) se vuelve el nuevo nodo que eventualmente sera referenciado por otro elemento ligado a la cabeza o ella misma
        }

        void insertBefore(int pos, T value){ // Insertar un valor al lado derecho de una posición
            Node <T> *current = new Node <T>; // Nodo para recorrer la lista
            current = this->head;

            int cont = 0;
            while(current && cont<pos){ // Mientras el dato no sea nulo y el contador no exceda el número a buscar
                cont++;
                current = current->getNext(); // Se vuelve el siguiente elemento
            }

            if (!current) return; // Si no encuentra el elemento abandona la función

            Node <T> *n_node = new Node <T> (value); // Nuevo nodo a insertar

            n_node->setPrev(current->getPrev()); // Se enlaza el nuevo nodo al elemento izquierdo de la posición
            n_node->setNext(current); // Se enlaza el nuevo nodo a la posición

            if (n_node->getNext()) n_node->getNext()->setPrev(n_node); // Si no se esta en un borde se enlaza la posición derecha al nuevo nodo
            if (n_node->getPrev()) n_node->getPrev()->setNext(n_node); // Si no se esta en un borde se enlaza la posición izquierda al nuevo nodo

            current->setPrev(n_node); // Se enlaza el nuevo nodo al lado izquierdo de la posición

            while(current->getPrev()){ // Se regresa al elemento inicial
                current = current->getPrev();
            }

            head = current; // La cabeza (es decir, la lista) se vuelve el nuevo nodo que eventualmente sera referenciado por otro elemento ligado a la cabeza o ella misma
        }

        Node <T>* searchPos(int pos){ // Buscar un nodo por posición
            Node <T> *current = new Node <T>; // Nodo para recorrer la lista
            current = this->head;

            int cont = 0;
            while(current && cont<pos){ // Mientras el dato no sea nulo y el contador no exceda el número a buscar
                cont++;
                current = current->getNext(); // Se vuelve el siguiente elemento
            }

            if (!current) throw invalid_argument("No se encontro el elemento"); // Si no se encuentra se arroja un error

            return current; // Regresa el nodo encontrado
        }

        Node <T>* searchValue(T value){ // Buscar un nodo por valor
            Node <T> *current = new Node <T>; // Nodo para recorrer la lista
            current = this->head;

            while(current && current->getData() != value){ // Mientras el dato no sea nulo y el contador no sea igual al valor a buscar 
                current = current->getNext(); // Se vuelve el siguiente elemento
            }

            if (!current) throw invalid_argument("No se encontro el elemento"); // Si no se encuentra se arroja un error

            return current; // Regresa el nodo encontrado
        }

        void update(int pos, T value){ // Modificar un valor dada una posición
            Node <T> *current = new Node <T>; // Nodo para recorrer la lista
            current = this->head;

            int cont = 0;
            while(current && cont<pos){ // Mientras el dato no sea nulo y el contador no exceda el número a buscar
                cont++;
                current = current->getNext(); // Se vuelve el siguiente elemento
            }

            if (!current) return; // Si no encuentra el elemento abandona la función

            current->setData(value); // Modifica el nodo encontrado

            while(current->getPrev()){ // Regresa al elemento inicial
                current = current->getPrev();
            }

            head = current; // La cabeza (es decir, la lista) se vuelve el nuevo nodo que eventualmente sera referenciado por otro elemento ligado a la cabeza o ella misma
        }

        void delByPos(int pos){ // Borrar un elemento dada una posición
            Node <T> *current = new Node <T>; // Nodo para recorrer la lista
            current = this->head;

            int cont = 0;
            while(current && cont<pos){ // Mientras el dato no sea nulo y el contador no exceda el número a buscar
                cont++;
                current = current->getNext(); // Se vuelve el siguiente elemento
            }

            if (!current) return; // Si no encuentra el elemento abandona la función

            Node <T>* left = current->getPrev(); // Obtiene el nodo izquierdo
            Node <T>* right = current->getNext(); // Obtiene el nodo derecho

            delete current; // Borra el nodo encontrado

            Node <T>* n_node = new Node <T>; // Crea un nuevo nodo para alamacenar el nodo izquierdo y el derecho (paso opcional)
            n_node = left; // Vuelve el nuevo nodo el lado izquierdo
            right->setPrev(n_node); // Enlaza el lado derecho al nodo
            n_node->setNext(right); // Enlaza el nodo al lado derecho

            while(n_node->getPrev()){ // Regresa al elemento inicial
                n_node = n_node->getPrev();
            }

            head = n_node;  // La cabeza (es decir, la lista) se vuelve el nuevo nodo que eventualmente sera referenciado por otro elemento ligado a la cabeza o ella misma
        }

        void print(){ // Imprime todos los elementos
            Node <T> *current = this->head; // Nuevo nodo es igual a la cabeza

            while (current){ // Itera por la lista hasta que llegue al elemento nulo
                cout << current->getData() << endl; // Imprime el contenido del nodo
                current = current->getNext(); // Pasa al siguiente nodo
            }
        }

};

int main(){
    
    DoubleLinkedList <int> lista(14);
    lista.insertAfter(0, 10);
    lista.insertAfter(0, 5);
    lista.insertBefore(1, 7);
    lista.insertBefore(0, 9);
    lista.insertBefore(0, 11);

    Node <int> *eval = lista.searchPos(3);

    cout << eval->getData() << endl;

    eval = lista.searchValue(7);

    cout << eval->getData();

    cout << "\n-----------" << endl;
    lista.print();
    cout << "\n-----------" << endl;

    lista.update(3, 4);

    cout << "\n-----------" << endl;
    lista.print();
    cout << "\n-----------" << endl;

    lista.delByPos(3);

    cout << "\n-----------" << endl;
    lista.print();
    cout << "\n-----------" << endl;
}