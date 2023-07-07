#include <functional>
#include <queue>

template<class t>
class Tree {
	class Nodo {
	public:
		t elemento;
		Nodo* Eizq;
		Nodo* izq;
		Nodo* Eder;
		Nodo* der;
		Nodo(t e) : elemento(e), izq(nullptr), der(nullptr), Eizq(nullptr), Eder(nullptr) {}
	};
	Nodo* raiz;
	int(*comparar)(t,t);
	void(*mostrar)(t);
private:
	bool _insertar(Nodo*& nodo, t e) {
		if (nodo == nullptr) {
			nodo = new Nodo(e);
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return false; 
			else if (r < 0) {
				if (nodo->Eder == nullptr) {
					nodo->Eder = new Nodo(e);
				}
				else if (nodo->der == nullptr) {
					int f = comparar(nodo->Eder->elemento, e);
					if (f == 0) return false;
					nodo->der = new Nodo(e);
					if (f < 0) {
						swap(nodo->der, nodo->Eder);
					}
				}
				else {
					_insertar(nodo->Eder, e);
				}
			}
			else {
				if (nodo->Eizq == nullptr) {
					nodo->Eizq = new Nodo(e);
				}
				else if (nodo->izq == nullptr) {
					int f = comparar(nodo->Eizq->elemento, e);
					if (f == 0) return false;
					nodo->izq = new Nodo(e);
					if (f > 0) {
						swap(nodo->izq, nodo->Eizq);
					}
				}
				else {
					_insertar(nodo->Eizq, e);
				}
			}
		}
	}
	void _enOrden(Nodo* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->Eizq);
		_enOrden(nodo->izq);
		mostrar(nodo->elemento);
		_enOrden(nodo->der);
		_enOrden(nodo->Eder);
	}
	//bool _eliminar(Nodo*& nodo, t e) {}
public:
	Tree(int(*comparar)(t, t), void(*mostrar)(t)) {
		this->mostrar = mostrar;
		this->comparar = comparar;
		this->raiz = nullptr;
	}
	bool Insertar(t e) { return _insertar(raiz, e); }
	//bool Eliminar(t e) { return _eliminar(raiz, e); }
	void EnOrden() { _enOrden(raiz); }
};