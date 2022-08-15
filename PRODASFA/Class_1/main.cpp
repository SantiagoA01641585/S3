#include <iostream>

template <typename T> T myMax(T x, T y){
    return (x>y)? x: y;
}

int main(){
    myMax <int> (1, 2);

    std::cout << myMax <double> (1.2, 3.5);
}