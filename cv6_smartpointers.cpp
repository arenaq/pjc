/* 
 * File:   main.cpp
 * Author: Petr Kuška
 *
 * Created on 10. listopadu 2015, 12:52
 */

#include <iostream>
#include <memory>

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

void test(Number *ptr) {
    cout << ptr->value << endl;
    delete ptr;
}

void test(shared_ptr<Number> ptr) {
    cout << ptr->value << endl;
}

int main() {
    shared_ptr<Number> smart(new Number(123));
    test(smart);
    
    /*Number *ptr = new Number(123);
    test(ptr);
    delete ptr; //2x*/
//    unique_ptr<Number> smart(new Number(123));
//    cout << smart->value << endl;
    return 0;
}

