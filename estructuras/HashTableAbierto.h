#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "HashEntidad.h"
using namespace std;

class HashTablaA {
private:
	vector<list<HashEntidad>> htable; // Tabla
	size_t currentSize;
	size_t myhash(const int key) const {
		size_t hashVal = key;
		hashVal %= htable.size();
		return hashVal ;
	}
public:
	HashTablaA(int size = 101) : currentSize{ 0 } { //current size = tamanio actual del hash table
		htable.resize(size);
		int g;
	}
	void makeEmpty() {
		for (auto& thisList : htable)
			thisList.clear();
	}
	bool insert(HashEntidad& x) {
		auto& whichtable = htable.at(myhash(x.getKey())); //asignando posicion del vector
		whichtable.push_back(x); //agrega la lista en esa posicion
		return true;
	}
	void DispAll() {
		int pos = 0;
		for (auto& algo : htable) {
			cout << "Key: " + to_string(pos) << " | ";
			for (auto& it : htable[pos]) {
				cout << it.getValue() << ",";
			}
			cout << endl;
			pos++;
		}
	}
};