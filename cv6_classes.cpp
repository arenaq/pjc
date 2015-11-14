/* 
 * File:   main.cpp
 * Author: Petr Kuška
 *
 * Created on 10. listopadu 2015, 12:52
 */

#include <cstdlib>
#include <iostream>

using namespace std;

struct Number {
    int value;
    char *pole;
    
    Number(int val) : value(val), pole(new char[16]) {
        cout << "konstuktor " << val << endl;
    }
    
    /* destruktor */
    ~Number() {
        cout << "destruktor " << value << endl;
        delete[] pole;
    }
};
int main() {
    Number stat(123); //staticka alokace - vymaze se sama po ukonceni provadeni aktualniho bloku (mtody main))
    Number *dyn = new Number(456); // dynamicka

    delete dyn; // destruktor dynamickeho objektu
    return 0;
}

