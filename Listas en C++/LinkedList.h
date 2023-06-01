#pragma once
#include <iostream>
#include <functional>
using namespace std;
template<class T>
class LinkedList {
private:
	struct Nodo {
		T val;
		Nodo* next;
		Nodo(T val) : val(val), next(nullptr) {}
	};
	Nodo* head;
	Nodo* tail;
	size_t lon;
	function<void(T)> show;
public:
	LinkedList(function<void(T)> _show) : show(_show), head(nullptr), tail(nullptr), lon(0) {}
	~LinkedList() {
		Nodo* aux = head;
		while (head != nullptr) {
			Nodo* aux = head;
			head = head->next;
			delete aux;
		}
	}
	void push_front(T val) {
		Nodo* nuevo = new Nodo(val);
		if (lon == 0) {
			head = tail = nuevo;
			lon++;
			return;
		}
		nuevo->next = head;
		head = nuevo;
		lon++;
	}
	void push_back(T val) {
		Nodo* nuevo = new Nodo(val);
		if (lon == 0) {
			head = tail = nuevo;
			lon++;
			return;
		}
		tail->next = nuevo;
		tail = nuevo;
		lon++;
	}
	void insert_at(T val, size_t pos) {
		if (pos == 1) {
			push_front(val); return;
		}
		if (pos == lon + 1) {
			push_back(val); return;
		}
		if (pos > lon || pos < 1) {
			cout << "NOT POSIBLE";
		}
		Nodo* aux = head;
		for (size_t i = 1; i < pos - 1; i++) {
			aux = aux->next;
		}
		Nodo* nuevo = new Nodo(val);
		nuevo->next = aux->next;
		aux->next = nuevo;
		lon++;
	}
	void pop_front() {
		if (lon == 0) return;
		if (lon == 1) {
			delete head;
			head = tail = nullptr;
			lon--;
			return;
		}
		Nodo* aux = head;
		head = head->next;
		delete aux;
		lon--;
	}
	void pop_back() {
		if (lon == 0) return;
		if (lon == 1) {
			delete tail;
			head = tail = nullptr;
			lon--;
			return;
		}
		Nodo* aux = head;
		for (size_t i = 1; i < lon - 1; i++) {
			aux = aux->next;
		}
		tail = aux;
		lon--;
		delete tail->next;
		tail->next = nullptr;
	}
	void erase_at(size_t pos) {
		if (pos == 1) {
			pop_front(); return;
		}
		if (pos == lon) {
			pop_back(); return;
		}
		if (pos > lon || pos < 1) {
			cout << "NOT POSIBLE";
		}
		Nodo* aux = head;
		for (size_t i = 1; i < pos - 1; i++) {
			aux = aux->next;
		}
		Nodo* nerase = aux->next;
		aux->next = nerase->next;
		delete nerase;
		lon--;
	}
	void print() {
		Nodo* aux = head;
		if (aux == nullptr) { cout << "NO EXISTEN REGISTROS :("; }
		while (aux != nullptr) {
			show(aux->val);
			aux = aux->next;
		}
	}
	void modify_at(size_t pos, function<void(T&)> modify) {
		if (pos < 1 || pos > lon) cout << "NO";
		Nodo* aux = head;
		for (size_t i = 1; i < pos; ++i) aux = aux->next;
		modify(aux->val);
	}
	size_t getlon() { return lon; }
};
