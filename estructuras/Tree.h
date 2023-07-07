#include <functional>
#include <queue>

template<class t>
class Tree {
	class Nodo {
	public:
		t elemento;
		Nodo* izq;
		Nodo* der;
		Nodo(t e) : elemento(e), izq(nullptr), der(nullptr) {}
	};
	Nodo* raiz;
	function<int(t, t)> comparar;
	function<void(t)> mostrar;
	function<void(int, int)> cant_nivel;
private:
	bool _insertar(Nodo*& nodo, t e) {
		if (nodo == nullptr) {
			nodo = new Nodo(e);
			return true;
		}
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return false; //no se acepta nodos con elemento igual
			else if (r < 0) {
				return _insertar(nodo->der, e);
			}
			else {
				return _insertar(nodo->izq, e);
			}
		}
	}
	bool _buscar(Nodo* nodo, t e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return true;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	Nodo* _obtener(Nodo* nodo, t e) {
		if (nodo == nullptr) return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return nodo;
			else if (r < 0) {
				return _obtener(nodo->der, e);
			}
			else {
				return _obtener(nodo->izq, e);
			}
		}
	}
	void _enOrden(Nodo* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);//rojo
		mostrar(nodo->elemento);
		_enOrden(nodo->der);//verde
	}
	void _preOrden(Nodo* nodo) {
		if (nodo == nullptr) return;
		mostrar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}
	void _postOrden(Nodo* nodo) {
		if (nodo == nullptr)return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		mostrar(nodo->elemento);
	}
	bool _eliminar(Nodo*& nodo, t e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento, e);
			if (r < 0) {
				return _eliminar(nodo->der, e);
			}
			else if (r > 0) {
				return _eliminar(nodo->izq, e);
			}
			else { // r == 0 es porque se encontró el elemento e en el arbol
				if (nodo->der == nullptr && nodo->izq == nullptr) { //caso 1 //sin hijos
					nodo = nullptr;
					delete nodo;
					return true;
				}
				else if (nodo->izq == nullptr) { //caso 2 //solo hijo derecho
					Nodo* aux = nodo->der;
					nodo = nodo->der;
					aux = nullptr;
					delete aux;
					return true;
				}
				else if (nodo->der == nullptr) { //caso 3 //solo hijo izquierdo
					Nodo* aux = nodo->izq;
					nodo = nodo->izq;
					aux = nullptr;
					delete aux;
					return true;
				}
				else { //caso 4 //ambos hijos
					Nodo* aux = nodo->der; //Se establece buscar el menor elemento por la derecha
					while (aux->izq != nullptr) {
						aux = aux->izq; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					return _eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
				}
			}
		}
	}
	int _cantidad(Nodo* nodo) {
		if (nodo == nullptr) return 0;
		else {
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}
	}
	int _altura(Nodo* nodo) {
		if (nodo == nullptr) return 0;
		else {
			int ai, ad;
			ai = 1 + _altura(nodo->izq);
			ad = 1 + _altura(nodo->der);
			return ai > ad ? ai : ad;
		}
	}
	t _minimo(Nodo* nodo) {
		if (nodo->izq == nullptr) return nodo->elemento;
		else { return _minimo(nodo->izq); }
	}
	t _maximo(Nodo* nodo) {
		if (nodo->der == nullptr) return nodo->elemento;
		else { return _maximo(nodo->der); }
	}
public:
	Tree(function<void(t)> mostrar, function<int(t, t)> comparar, function<void(int, int)> cant_nivel) {
		this->mostrar = mostrar;
		this->comparar = comparar;
		this->cant_nivel = cant_nivel;
		this->raiz = nullptr;
	}
	bool Insertar(t e) { return _insertar(raiz, e); }
	bool Buscar(t e) { return _buscar(raiz, e); }
	t Obtener(t e) { return _obtener(raiz, e)->elemento; }
	bool Eliminar(t e) { return _eliminar(raiz, e); }
	void EnOrden() { _enOrden(raiz); }
	void PreOrden() { _preOrden(raiz); }
	void PostOrden() { _postOrden(raiz); }
	int Cantidad() { return _cantidad(raiz); }
	int Altura() { return _altura(raiz) - 1; }
	t Minimo() { return _minimo(raiz); }
	t Maximo() { return _maximo(raiz); }
	void _nodos_por_nivel() {
		if (raiz == nullptr) return;
		queue<Nodo*> q;
		q.push(raiz);
		int level = 0; //nivel
		while (!q.empty()) {
			int size = q.size(); //size = cantidad de nodos
			cant_nivel(level, size);

			for (int i = 1; i <= size; i++) {
				Nodo* current = q.front();
				q.pop();
				if (current->izq != nullptr) {
					q.push(current->izq);
				}
				if (current->der != nullptr) {
					q.push(current->der);
				}
				current = nullptr;
				delete current;
			}
			level++;
		}
	}
};