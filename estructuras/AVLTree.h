#pragma once

#include <functional>
template<class t>
class AVLTree {
private:
	class Nodo {
	public:
		t elemento;
		Nodo* izq;
		Nodo* der;
		int altura;
		Nodo(t _elemento) : elemento(_elemento), izq(nullptr), der(nullptr), altura(0){}
	};
	Nodo* raiz;
	void(*show)(t,t);
	int _altura(Nodo* nodo) {
		if (nodo == nullptr) return -1;
		return nodo->altura;
	}
	void _rotarDerecha(Nodo*& nodo) {
		Nodo* p = nodo->izq;
		nodo->izq = p->der;
		p->der = nodo;
		nodo = p;
		nodo->der->altura = max(_altura(nodo->der->der), _altura(nodo->der->izq)) + 1;
	}
	void _rotarIzquierda(Nodo*& nodo) {
		Nodo* p = nodo->der;
		nodo->der = p->izq;
		p->izq = nodo;
		nodo = p; 
		nodo->izq->altura = max(_altura(nodo->izq->der), _altura(nodo->izq->izq)) + 1;
	}
	void _balanceo(Nodo*& nodo) {
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;

		if (fb > 1) { //rotar a la izq
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			if (hhizq > hhder) { //verificar si aplica doble rotación
				_rotarDerecha(nodo->der);
			}
			_rotarIzquierda(nodo);
		}
		if (fb < -1) { //rotar a la der
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			if (hhizq < hhder) {//verificar si aplica doble rotación 
				_rotarIzquierda(nodo->izq);
			}
			_rotarDerecha(nodo);
		}
		//-1,0,1
		//Actualizar la altura del nodo raiz
		hizq = _altura(nodo->izq);
		hder = _altura(nodo->der);
		nodo->altura = 1 + ((hizq > hder) ? hizq : hder);
	}
	bool _insertar(Nodo*& nodo, t e) {
		if (nodo == nullptr) {
			nodo = new Nodo(e);
			return true;
		}
		else if (e == nodo->elemento) return false;
		else if (e < nodo->elemento) {
			_insertar(nodo->izq, e);
		}
		else if (e > nodo->elemento) {
			_insertar(nodo->der, e);
		}
		_balanceo(nodo);
		return true;
	}
	void _inOrdenH(Nodo* nodo) {
		if (nodo == nullptr) return;
		_inOrdenH(nodo->izq);
		show(nodo->elemento, nodo->altura);
		_inOrdenH(nodo->der);
	}
public:
	AVLTree(void(*_show)(t,t)) : show(_show), raiz(nullptr) {}
	bool Insertar(t e) { return _insertar(raiz, e); }
	void inOrdenH() { _inOrdenH(raiz); }
};