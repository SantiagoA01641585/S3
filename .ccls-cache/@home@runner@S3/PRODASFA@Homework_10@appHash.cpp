#include "tabla_hash.h"

using namespace std;

int main(){ // Main Function
    // First cases
    quadraticHashTable quadTable1(4, 5, 7); // Quadratic probing
    chainHashTable chainTable1(4); // Chaining

    quadTable1.insert(67);
    quadTable1.insert(9);
    quadTable1.insert(17);
    quadTable1.insert(2);
    quadTable1.insert(8);

    chainTable1.insert(7);
    chainTable1.insert(9);
    chainTable1.insert(2);
    chainTable1.insert(21);
    chainTable1.insert(64);

    cout << "Case 1:" << endl << endl;

    quadTable1.printHashTable();

    cout << endl;

    chainTable1.printHashTable();

    cout << endl << "----------------------------------------/n" << endl;

    // Second cases
    quadraticHashTable quadTable2(13, 17, 31); // Quadratic probing
    chainHashTable chainTable2(13); // Chaining

    quadTable2.insert(6);
    quadTable2.insert(14);
    quadTable2.insert(68);
    quadTable2.insert(2);
    quadTable2.insert(67);
    quadTable2.insert(61);
    quadTable2.insert(47);
    quadTable2.insert(1);
    quadTable2.insert(108);
    quadTable2.insert(8);
    quadTable2.insert(74);
    quadTable2.insert(46);
    quadTable2.insert(11);

    chainTable2.insert(0);
    chainTable2.insert(9);
    chainTable2.insert(19);
    chainTable2.insert(27);
    chainTable2.insert(49);
    chainTable2.insert(6);
    chainTable2.insert(97);
    chainTable2.insert(81);
    chainTable2.insert(2);
    chainTable2.insert(874);
    chainTable2.insert(66);
    chainTable2.insert(67);
    chainTable2.insert(1);

    cout << "Case 2:" << endl << endl;

    quadTable2.printHashTable();

    cout << endl;

    chainTable2.printHashTable();

    cout << endl << "----------------------------------------/n" << endl;

    // Third cases
    quadraticHashTable quadTable3(3, 2, 99); // Quadratic probing
    chainHashTable chainTable3(3); // Chaining

    quadTable3.insert(66);
    quadTable3.insert(97);
    quadTable3.insert(1);

    chainTable3.insert(67);
    chainTable3.insert(99);
    chainTable3.insert(1100);

    cout << "Case 3:" << endl << endl;

    quadTable3.printHashTable();

    cout << endl;

    chainTable3.printHashTable();

    cout << endl << "----------------------------------------/n" << endl;

    // Fourth cases
    quadraticHashTable quadTable4(7, 29, 64); // Quadratic probing
    chainHashTable chainTable4(7); // Chaining

    quadTable4.insert(61);
    quadTable4.insert(97);
    quadTable4.insert(11);
    quadTable4.insert(28);
    quadTable4.insert(98);
    quadTable4.insert(9);
    quadTable4.insert(16);
    quadTable4.insert(2);

    chainTable4.insert(69);
    chainTable4.insert(9);
    chainTable4.insert(111);
    chainTable4.insert(2);
    chainTable4.insert(84);
    chainTable4.insert(97);
    chainTable4.insert(1);
    chainTable4.insert(26);

    cout << "Case 4:" << endl << endl;

    quadTable4.printHashTable();

    cout << endl;

    chainTable4.printHashTable();

    cout << endl << "----------------------------------------/n" << endl;
}