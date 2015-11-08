//============================================================================
// Jmeno       : Uloha1.cpp
// Author      : Petr Kuška
// Popis       : Uloha na procviceni trid a zakladnich rysu jazyka C++
//============================================================================

/*
 * Zadani ulohy
 *
 * Vasim ukolem je doplnit kod tridy Number tak, aby sel prelozit
 * a vypsal nasledujici vystup:
 *
 * Cvicna aplikace pro cviceni 3
 *
 * Error!
 * Error!
 * Binarni hodnota cisla 3000 je 101110111000
 * Binarni hodnota cisla 1000 je 1111101000
 *
 */


#include <iostream>	// Hlavickovy soubor potrebny pro praci se vstupem a vystupem
#include <bitset>

struct Number {
    int number;
    bool isSet;
    
    Number(int n) : number(n), isSet(true) {}
    Number() : isSet(false) {}
    
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
};


int main() {

	std::cout << "Cvicna aplikace pro cviceni 3" << std::endl << std::endl;

	Number n1;
    Number n2(1000); // Vytvori dalsi instanci tridy Number, tentokrat s konstruktorem

	n1.plus(n2); // Vypise chybovou hlasku "Error!", protoze v n1 neni zatim zadna hodnota
	n1.printBinary(); // Vypise chybovou hlasku "Error!", protoze v n1 neni zatim zadna hodnota
	n1.set(2000); // Do n1 je vlozena hodnota 1000
	n1.plus(n2); // K hodnote v n1 se pricte hodnota z n2
	n1.printBinary(); // Vytiskne hodnotu ulozenou v n1 v binarni podobe
	n2.printBinary(); // Vytiskne hodnotu ulozenou v n2 v binarni podobe

	return 0;
}
