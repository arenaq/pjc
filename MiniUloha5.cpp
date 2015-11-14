/* 
 * File:   MiniUloha5.cpp
 * Author: Petr Kuška
 *
 * Created on 14. listopadu 2015, 15:24
 */

#include <iostream>
#include <cstring>
using namespace std;

class Vector { //jen nositel dat, zadne metody
    double *_data; //ukazatel na dynamicke pole prvku
    int _alloc; //realna velikost pole
    int _size; //pocet prvku ulozenych v poli
public:
    Vector() : _data(0), _alloc(0), _size(0){}
    
    void push_back(double value) { //prida value do vec
        if (_size == _alloc) { // pokud je Vector plne obsazeny
            if (_alloc == 0) { // specialni pripad na zacatku - pokud 0, tak zvysit na 1, jinak vynasobit 2
                _alloc = 1;
            } else {
                _alloc = _alloc * 2;
            }
            double *extended = new double[_alloc];
            memcpy(extended, _data, _size * sizeof (double)); // zkopirujeme data do noveho zvetseneho pole prave o tolik, kolik je velikost aktualniho pole (nema smysl kopirovat vice)
            delete[] _data; // smazeme nepotrebna data ze stareho vektoru
            _data = extended; // priradime nove vyktorena data
        }
        _data[_size++] = value; // pokud jsme nedospěli na konec, tak jen přiřadíme prvek na pozici o jedno větší, než je poslední index, což je právě size a poté navýšíme size
    }

    void pop_back() { //odstrani posledni prvek vec
        if (_size != 0) {
            _data[_size--] = 0;

            // inverzni operace k te pri vkladani prvku, jen podminka pro zmenseni je 1/4
            if (_size <= _alloc / 4) {
                _alloc = _alloc / 2;
                double *shrinked = new double[_alloc];
                memcpy(shrinked, _data, _size * sizeof (double));

                delete[] _data;
                _data = shrinked;
            }
        } else {
            return;
        }
    }

    double at(int index) { //vrati prvek na indexu
        if (_size > 0) {
            return _data[index];
        } else {
            return 0;
        }
    }

    double back() { //vrati posledni prvek
        return at(_size);
    }

    int size() { //pocet prvku ulozenych v kontejneru
        return _size;
    }
    
    int alloc() {
        return _alloc;
    }

    ~Vector() { //destruktor - uklizeni pameti
        delete [] _data;
        _data = 0;
        _alloc = 0;
        _size = 0;
    }
};

    int main() {
        Vector v;

        for (int i = 0; i < 12; ++i) {
            v.push_back(i);
            cout << "push " << v.size() << "/" << v.alloc() << endl;
        }

        for (int i = 0; i < 9; ++i) {
            cout << "pop " << v.size() << "/" << v.alloc() << endl;
            v.pop_back();
        }

        for (int i = 0; i < v.size(); ++i) {
            cout << v.at(i) << endl;
        }

        return 0;
    }
