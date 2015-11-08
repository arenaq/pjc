/* 
 * File:   MiniUloha1.cpp
 * Author: Petr Kuška
 *
 * Created on 14. října 2015, 14:57
 */

#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    while (!cin.eof()) {
        int x;
        cin >> x;
        if (cin.good()) {
            cout << left << setfill(' ') << setw(10) << dec << x;
            cout << ' ';
            cout << left << setfill(' ') << setw(8) << hex << x;
            cout << ' ';
            cout << right << setfill(' ') << setw(8) << hex << x;
            cout << ' ';
            cout << right << setfill('0') << setw(8) << hex << x << endl;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Chybny vstup" << endl;
        }
    }
    return 0;
}
