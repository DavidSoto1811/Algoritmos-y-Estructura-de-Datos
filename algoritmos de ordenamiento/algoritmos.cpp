#include "pch.h"
#include <iostream>
#include <windows.h>
using namespace std;

template<class t>
void ord_fisher_yates(t vector[], size_t n) {
	//ORDENAMIENTO FISHER-YATES 
	for (int i = n - 1; i > 0; i--) {
		int j = (rand() % (i + 1));
		swap(vector[j], vector[i]);
	}

}
template<class t>
void ord_inter(t vector[], size_t n) {
	for (int i = 0; i < n - 1; i++) {
		for (int k = i + 1; k < n; k++) {
			if (vector[i] > vector[k]) {
				swap(vector[i], vector[k]);
			}
		}
	}
}
template<class t>
void ord_bubble(t vector[], size_t n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - (i + 1); j++) {
			if (vector[j] > vector[j + 1]) {
				swap(vector[j], vector[j + 1]);
			}
		}
	}
}
template<class t>
void ord_select(t vector[], size_t n) {
	int k, menor;
	for (int i = 0; i < n - 1; i++) {
		k = i;
		menor = vector[i];
		for (int j = i + 1; j < n; j++) {
			if (vector[j] < menor) {
				menor = vector[j];
				k = j;
			}
		}
		vector[k] = vector[i];
		vector[i] = menor;
	}
}
template<class t>
void ord_insert(t vector[], size_t n) {
	int aux, k;
	for (int i = 1; i < n; i++) {
		aux = vector[i];
		k = i - 1;
		while (k >= 0 && aux < vector[k]) {
			vector[k + 1] = vector[k];
			k--;
		}
		vector[k + 1] = aux;
	}
}
template<class t>
void ord_shell(t vector[], size_t n) {
	int i, j, k, intervalo = n/2;
	while (intervalo > 0) {
		for (i = intervalo; i < n; i++) {
			j = i - intervalo;
			while (j >= 0) {
				k = j + intervalo;
				if (vector[j] <= vector[k]) { j = -1; }
				else {
					swap(vector[j], vector[k]);
					j -= intervalo;
				}
			}
		}
		intervalo /= 2;
	}
}
int main()
{
	int vector[] = { 1, 6, 8,2, 3, 5, 8};
	int n = 7;
	srand(time(NULL));
	ord_fisher_yates(vector, n);
	//ord_inter(vector, n);
	//ord_bubble(vector, n);
	//ord_select(vector, n);
	//ord_insert(vector, n);
	ord_shell(vector, n);

	for (int x = 0; x < n; x++) {
		cout << vector[x] << " ";
	}
	return 0;
}