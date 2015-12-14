#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Mobility {
	virtual string type() = 0;
public:
	virtual bool is_wheeled() { return false; }
	virtual bool is_tracked() { return false; }
	virtual bool is_foot() { return false; }
};


class Unit : public Mobility {
public:
	string type() {
		if (is_wheeled()) {
			return "wheeled";
		} else if (is_tracked()) {
			return "tracked";
		} else if (is_foot()) {
			return "foot";
		}
	}
	virtual string name() = 0;
	void salut() {
		cout << "I am " << name() << ". My mobility is " << type() << "." << endl;
	}
};

class Attack : public Unit {
};

class Harvest : public Unit {
};

class Harvester : public Harvest {
public:
	bool is_wheeled() { return false; }
	bool is_tracked() { return true; }
	bool is_foot() { return false; }
	string name() {
		return "harvester";
	}
};

class Infantry : public Attack {
public:
	bool is_wheeled() { return false; }
	bool is_tracked() { return false; }
	bool is_foot() { return true; }
	string name() {
		return "infantry";
	}
};

class Quad : public Attack {
public:
	bool is_wheeled() { return true; }
	bool is_tracked() { return false; }
	bool is_foot() { return false; }
	string name() {
		return "quad";
	}
};

class Trike : public Attack {
public:
	bool is_wheeled() { return true; }
	bool is_tracked() { return false; }
	bool is_foot() { return false; }
	string name() {
		return "trike";
	}
};


class UnitFactory {
public:
	Unit * create_quad() {
		return new Quad();
	}
	Unit * create_trike() {
		return new Trike();
	}
	Unit * create_infantry() {
		return new Infantry();
	}
	Unit * create_harvester() {
		return new Harvester();
	}
};


int main(void) {
	UnitFactory uf;
	std::vector<Unit *> units;

	for (int i = 0; i < 10; i++) {
		units.push_back(uf.create_quad());
		units.push_back(uf.create_trike());
		units.push_back(uf.create_infantry());
		units.push_back(uf.create_harvester());
	}

	for (Unit* u : units)
		u->salut(); //I am infantry. My mobility is foot.

	//uklid pameti
	for (Unit* u : units)
		delete u;
	units.clear();

	getchar();
	return 0;
}