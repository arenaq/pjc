#include <iostream>
#include <string>
using namespace std;

class FunnyString {
	string* str; //dynamicky alokovany string, MUSI BYT PRIVATE!!!
public:
	FunnyString(const string& ss) : str(new string(ss)) {}; //konstruktor
	FunnyString(const FunnyString& o) : str(new string(*o.str)) {}; //kopirujici konstruktor
	~FunnyString() { // destruktor
		delete str;
	};
	FunnyString& operator=(const FunnyString& o) { //operator prirazeni
		delete str;
		str = new string(*o.str);
		return *this;
	};

	char& operator[](int n) { //vrati referenci znaku na indexu n (od 0)
		return this->str->at(n);
	};
	FunnyString operator()(int i, int n) { //vrati n znaku od i (od 0)
		return FunnyString(this->str->substr(i, n));
	};

	//zde doplnte nektere operatory vcetne friendu
	FunnyString& operator++() {
		this->str->append("!");
		return *this;
	}

	FunnyString operator++(int dummy) {
		this->str->append("!");
		return *this;
	}

	friend FunnyString operator+(const FunnyString& x, const FunnyString& y);
	friend ostream& operator<<(ostream& out, const FunnyString& x);

};

//zde take budou operatory
FunnyString operator+(const FunnyString& x, const FunnyString& y) {
	return FunnyString(*x.str + *y.str);
}

ostream& operator<<(ostream& out, const FunnyString& x) {
	return out << *x.str;
}

int main() {
	FunnyString a("Ahoj"), s("svete!");
	FunnyString as = a + string(" ") + s;
	cout << as << endl; //Ahoj svete!

	as = as;

	as = string("Ibisek ") + s;
	as[7] = 'k';
	cout << as << endl; //Ibisek kvete!

	FunnyString b = as++;
	cout << b << endl; //Ibisek kvete!
	cout << as << endl; //Ibisek kvete!!

	b = ++as;
	cout << b << endl; //Ibisek kvete!!!
	cout << as << endl; //Ibisek kvete!!!

	cout << b(0, 6) << endl; //Ibisek

	return 0;
}