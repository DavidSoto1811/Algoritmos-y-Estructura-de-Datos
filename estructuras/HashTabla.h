#pragma once
#include "HashEntidad.h"
template<class t>
class HashTable {
private:
	class HashEntidad {
	private:
		int key;
		t value;
	public:
		HashEntidad(int key, t value) {
			this->key = key;
			this->value = value;
		}
		int getKey() { return key; }
		t getValue() { return value; }
	};

	HashEntidad** tabla;
	int numElementos;
	int TABLE_SIZE;
public:
	HashTable(int TABLE_SIZE = 100) {
		this->TABLE_SIZE = TABLE_SIZE;
		tabla = new HashEntidad*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; ++i) {
			tabla[i] = nullptr;
		}
		numElementos = 0;
	}
	~HashTable() {}
	//Direccionamiento según Prueba Lineal
	void insertar(int key, t value) {
		//Hash prima
		int base, step, hash;
		//validar si la tabla está llena
		if (numElementos == TABLE_SIZE) return;
		//Función Hash1
		base = key % TABLE_SIZE;
		hash = base;
		//constante para Hash2
		step = 0;
		while (tabla[hash] != nullptr) {
			//Función Hash2
			hash = (base + step) % TABLE_SIZE;
			step++;
		}
		//almacenarlo en la tabla
		HashEntidad* he = new HashEntidad(key, value);
		tabla[hash] = he;
		numElementos++;
	}
	int buscar(int key) {
		int step = 0;
		int i, base;
		i = base = key % TABLE_SIZE; //hash1 es = a hash2 cuando step=0;
		while (true)
		{
			if (tabla[i] == nullptr) return -1;
			else if (tabla[i]->getKey() == key) {
				return i;
			}
			else step++;

			i = (base + step) % TABLE_SIZE;
		}
	}
	int size() { return TABLE_SIZE; }
	int sizeactual() { return numElementos; }
	t getvalue(int i) { return tabla[i]->getValue(); }
};

