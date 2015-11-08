//============================================================================
// Name        : Uloha3.cpp
// Author      : Petr Kuška
// Zadani      : Dokoncete zdrojovy kod. Trida Zasobnik implementuje zasobnik
//               na kladna cela cisla mensi nez _maxCislo a cely zasobnik ma
//               hloubku _hloubka. Do zasobniku se ukladaji cisla pomoci tridy 
//               Number z ulohy 2. Zasobnik ma navic metodu tiskni(), ktera
//               cely zasobnik vytiskne v tabulce z ulohy 1. Funkce main() prebira
//               z prikazove radky tri parametry. Prvnim je hloubka zasobniku,
//               druhym maximalni hodnota v zasobniku a tretim je soubor
//               s prikazy. Prikazy jsou dohromady tri a kazdy lezi vzdy na
//               jednom radku. Prvni je ve tvaru "PUSH cislo". Misto "cislo"
//               je uvedena samozrejme ciselna hodnota a prikaz rika, ze se ma
//               do zasobniku vlozit ono cislo. Druhy prikaz je "POP". Ten
//               pouze vytahne hodnotu z vrcholu zasobniku. Posledni prikaz je
//               "EXIT" a znamena konec prikazu.
//
//               Pri testovani spoustejte aplikaci s parametry:
//               ./Uloha3 5 20 prikazy.txt
/*               Soubor s prikazy prikazy.txt vypada takto:
PUSH 1
PUSH 30
PUSH 20
PUSH 3
PUSH 8
PUSH 19
PUSH 11
PUSH 13
POP
PUSH 13
POP
POP
POP
PUSH 18
EXIT
 *//*            Na tento vstup by mela aplikace reagovat takto:

1          1               1 00000001 00000000000000000000000000000001
20         14             14 00000014 00000000000000000000000000010100
18         12             12 00000012 00000000000000000000000000010010

*/
//============================================================================

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <bitset>

using namespace std;

void tiskniPouziti() {
    cout << endl << "Pouziti: Uloha3 velikostZasobniku maxCislo prikazovySoubor" << endl;
}

/****************************************************************************
 *  Tridu zasobnik dokoncete dle pokynu v zadani.
 ****************************************************************************/

struct Number {
    int number;
    bool isSet;

    Number(int n) : number(n), isSet(true) {
    }

    Number() : isSet(false) {
    }

    void plus(Number n) {
        this->number += n.number;
    }

    void set(int n) {
        this->number = n;
        this->isSet = true;
    }

    void printBinary() {
        if (isSet) {
            // std::string binaryString = std::bitset<CHAR_BIT * sizeof value>(this->value).to_string();
            // std::cout << "Binarni hodnota cisla " << this->value << " je " << binaryString.substr(binaryString.find('1')) << std::endl;
            std::cout << "Binarni hodnota cisla " << this->number << "je " << std::bitset<32>(this->number) << std::endl;
        } else {
            std::cout << "Error!" << std::endl;
        }
    }

    void print() {
        cout << left << setfill(' ') << setw(10) << dec << this->number;
        cout << ' ';
        cout << left << setfill(' ') << setw(8) << hex << this->number;
        cout << ' ';
        cout << right << setfill(' ') << setw(8) << hex << this->number;
        cout << ' ';
        cout << right << setfill('0') << setw(8) << hex << this->number;
        
        cout << left << setfill(' ') << setw(8) << std::bitset<32>(this->number) << endl;
    }
};

class Zasobnik {
    vector<Number> cisla;
    int kapacita, maxCislo;
public:

    Zasobnik(int _hloubka, int _maxCislo) {
        this->kapacita = _hloubka;
        this->maxCislo = _maxCislo;
    }

    void push(Number cislo) {
        if (this->cisla.size() < kapacita && cislo.number <= this->maxCislo) {
            this->cisla.push_back(cislo);
        }
    }

    Number pop() {
        Number n;
        if (!this->cisla.empty()) {
            n = this->cisla.back();
            this->cisla.pop_back();
            ;
        }
        return n;
    }

    void tiskni() {
        for (vector<Number>::iterator it = this->cisla.begin(); it != this->cisla.end(); it++) {
            Number n = *it;
            n.print();
        }
    }
};

int main(int argc, char **argv) {
    //stringstream ss;
    int hloubka;
    int maxCislo;
    ifstream prikazovySoubor;

    if (argc < 4) {
        tiskniPouziti();
        return 1;
    }

    /*************************************************************************
     *  Zde je treba zpracovat argumenty, tedy prvni dva prevest na cislo
     *  typu integer a pomoci tretiho otevrit soubor se vstupnimi daty.
     *************************************************************************/
    hloubka = atoi(argv[1]);
    maxCislo = atoi(argv[2]);
    prikazovySoubor.open(argv[3]);

    Zasobnik zasobnik(hloubka, maxCislo);

    /*************************************************************************
     *  Zde je treba zpracovat soubor s prikazy
     *************************************************************************/

    if (prikazovySoubor.is_open()) {
        string line;
        while (getline(prikazovySoubor, line)) {
            if (line.at(0) == 'E') {
                break;
            } else if (line.at(1) == 'O') {
                zasobnik.pop();
            } else {
                Number n = Number(atoi(line.substr(5, line.length() - 5).c_str()));
                zasobnik.push(n);
            }
        }
        prikazovySoubor.close();
    } else {
        cout << "Unable to open file" << endl;
        return 1;
    }

    zasobnik.tiskni();

    return 0;
}
