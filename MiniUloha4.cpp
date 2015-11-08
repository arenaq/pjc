/* 
 * File:   MiniUloha4.cpp
 * Author: Petr Kuška
 *
 * Created on 8. listopadu 2015, 11:23
 */

#include <iostream>
#include <cstring>
using namespace std;

struct Vector { //jen nositel dat, zadne metody
  double *data; //ukazatel na dynamicke pole prvku
  int alloc; //realna velikost pole
  int size; //pocet prvku ulozenych v poli
};

void push_back(Vector &vec, double value) { //prida value do vec
    if (vec.size == vec.alloc) { // pokud je Vector plne obsazeny
        if (vec.alloc == 0) { // specialni pripad na zacatku - pokud 0, tak zvysit na 1, jinak vynasobit 2
            vec.alloc = 1;
        } else {
            vec.alloc = vec.alloc * 2;
        }
        double *extended = new double[vec.alloc];
        memcpy(extended, vec.data, vec.size * sizeof(double)); // zkopirujeme data do noveho zvetseneho pole prave o tolik, kolik je velikost aktualniho pole (nema smysl kopirovat vice)
        delete[] vec.data; // smazeme nepotrebna data ze stareho vektoru
        vec.data = extended; // priradime nove vyktorena data
    }
    vec.data[vec.size++] = value; // pokud jsme nedospěli na konec, tak jen přiřadíme prvek na pozici o jedno větší, než je poslední index, což je právě size a poté navýšíme size
}

void pop_back(Vector &vec) { //odstrani posledni prvek vec
    if (vec.size != 0) {
        vec.data[vec.size--] = 0;
        
        // inverzni operace k te pri vkladani prvku, jen podminka pro zmenseni je 1/4
        if (vec.size <= vec.alloc / 4) {
            vec.alloc = vec.alloc / 2;
            double *shrinked = new double[vec.alloc];
            memcpy(shrinked, vec.data, vec.size * sizeof(double));
            
            delete[] vec.data;
            vec.data = shrinked;
        }
    } else {
        return;
    }
}

double at(const Vector &vec, int index) { //vrati prvek na indexu
    if (vec.size > 0) {
        return vec.data[index];
    } else {
        return 0;
    }
}

double back(const Vector &vec) { //vrati posledni prvek
    return at(vec, vec.size);
}

int size(const Vector &vec) { //pocet prvku ulozenych v kontejneru
    return vec.size;
}

void destroy(Vector& vec) { //uklid pameti
    delete [] vec.data;
    vec.data = 0;
    vec.alloc = 0;
    vec.size = 0;
}

int main() {
  Vector v;
  v.data = 0;
  v.alloc = 0;
  v.size = 0;
  
  for (int i = 0; i < 12; ++i) {
      push_back(v, i);
      cout << "push " << size(v) << "/" << v.alloc << endl;
  }
  
  for (int i = 0; i < 9; ++i) {
      cout << "pop " << size(v) << "/" << v.alloc << endl;
      pop_back(v);
  }
  
  for (int i = 0; i < size(v); ++i) {
      cout << at(v, i) << endl;
  }
  
  destroy(v);

  return 0;
}
