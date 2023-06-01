#pragma once
#include <iostream>
#include <functional>
using namespace std;
template<class T>
class CircularDoubleLinkedList {
private:
	struct Nodo {
		T val;
		Nodo* next;
		Nodo* back;
		Nodo(T val) : val(val), next(nullptr), back(nullptr) {}
	};
	Nodo* head;
	Nodo* tail;
	size_t lon;
	function<void(T)> show;
public:
	CircularDoubleLinkedList(function<void(T)> _show) : head(nullptr), tail(nullptr), lon(0), show(_show) {}
	~CircularDoubleLinkedList() {
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
			head->back = tail;
			tail->next = head;
			lon++;
			return;
		}
		head->back = nuevo;
		tail->next = nuevo;
		nuevo->back = tail;
		nuevo->next = head;
		head = nuevo;
		lon++;
	}
	void push_back(T val) {
		Nodo* nuevo = new Nodo(val);
		if (lon == 0) {
			head = tail = nuevo;
			head->back = tail;
			tail->next = head;
			lon++;
			return;
		}
		tail->next = nuevo;
		nuevo->next = head;
		head->back = nuevo;
		nuevo->back = tail;
		tail = nuevo;
		lon++;

	}
	void insert_at(T val, size_t pos) {
		if (pos == 1) {
			push_front(val); return;
		}
		if (pos == lon + 1) {
			push_back(val);
		}
		if (pos > lon || pos < 1) {
			cout << "NOT POSIBLE"; return;
		}
		Nodo* aux = head;
		for (size_t i = 1; i < pos - 1; i++) {
			aux = aux->next;
		}
		Nodo* nuevo = new Nodo(val);
		nuevo->back = aux;
		nuevo->next = aux->next;
		aux->next = nuevo;
		nuevo->next->back = nuevo;
		lon++;
	}
	void pop_front() {
		if (lon == 0) return;
		if (lon == 1) {
			tail->next = nullptr;
			head->back = nullptr;
			delete head;
			head = tail = nullptr;
			lon--;
			return;
		}
		head->back = nullptr;
		head = head->next;
		tail->next = head;
		head->back->next = nullptr;
		delete head->back;
		head->back = tail;
		lon--;
	}
	void pop_back() {
		if (lon == 0) return;
		if (lon == 1) {
			tail->next = nullptr;
			head->back = nullptr;
			delete tail;
			tail = head = nullptr;
			lon--;
			return;
		}
		tail->next = nullptr;
		tail = tail->back;
		head->back = tail;
		tail->next->back = nullptr;
		delete tail->next;
		tail->next = head;
		lon--;
	}
	void erase_at(size_t pos) {
		if (pos == 1) {
			pop_front(); return;
		}
		if (pos == lon) {
			pop_back(); return;
		}
		if (pos > lon || pos < 1) {
			cout << "NOT POSIBLE"; return;
		}
		Nodo* aux = head;
		for (size_t i = 1; i < pos - 1; i++) {
			aux = aux->next;
		}
		Nodo* nerase = aux->next;
		aux->next = nerase->next;
		nerase->next->back = aux;
		nerase->next = nerase->back = nullptr;
		delete nerase;
		lon--;

	}
	void print() {
		Nodo* aux = head;
		if (aux == nullptr) { cout << "NO EXISTEN REGISTROS :("; return; }
		for (size_t i = 1; i <= lon; i++) {
			show(aux->val);
			aux = aux->next;
		}
	}
	void modify_at(size_t pos, function<void(T&)> modify) {
		if (pos < 1 || pos > lon) cout << "NO"; return;
		Nodo* aux = head;
		for (size_t i = 1; i < pos; ++i) aux = aux->next;
		modify(aux->val);
	}
	size_t getlon() { return lon; }
	void swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}
	void bubblesort(function<bool(T, T)> compare) {
		Nodo* aux = head;
		if (aux == nullptr) cout << "NO HAY REGISTROS :("; return;
		while (aux != tail) {
			if (compare(aux->val, aux->next->val)) {
				swap(aux->val, aux->next->val);
				if (aux != head) {
					aux = aux->back;
					continue;
				}
			}
			aux = aux->next;
		}
	}
};