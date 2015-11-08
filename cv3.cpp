/* 
 * File:   cv3.cpp
 * Author: arenaq
 *
 * Created on 20. října 2015, 13:02
 */

#include <iostream>

using namespace std;

/* class na defaultne privatni metody */
/* struct ma defaultne public metody */
/* typedef - vytváří nové pojmenování prodatový typ (ale jen pojmenovani) */
struct Number {
    int value;
    bool isSet;
    
private:
    Number() {
        cout << "volam konstruktor Number" << endl;
    }
public:    
    Number(int hodnota) : value(hodnota), isSet(false) {
        
    }
    
    void print() {
        cout << value << endl;
    }
};

typedef Number Cislo;

/*
 * 
 */
int main() {
    Number x(123);
    //Cislo y;
    x.print();
    return 0;
}

