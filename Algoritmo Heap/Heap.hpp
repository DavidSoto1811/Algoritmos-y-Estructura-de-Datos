#ifndef __HEAP_HPP__
#define __HEAP_HPP__

#include <iostream>
using namespace std;


int parent(int i) {
	return (i - 1) / 2;
}
int left(int i) {
	return 2 * i + 1;
}
int rigth(int i) {
	return 2 * i + 2;
}
template<class t>
void maxHeapify(t A[], int n, int i) {
	int l = left(i);
	int r = rigth(i);
	int largest = 0;
	if (l <= (n - 1) && A[l] > A[i]) {
		largest = l;
	}
	else {
		largest = i;
	}
	if (r <= (n - 1) && A[r] > A[largest]) {
		largest = r;
	}
	if (largest != i) {
		swap(A[i], A[largest]);
		maxHeapify(A, n, largest);
	} 
}
template<class t>
void buildMaxHeap(t A[], int n) {
	for (int i = n / 2 - 1;i >= 0;--i) {
		maxHeapify(A, n, i);
	}
}

//aplicación de ordenamiento
template<class t>
void heapsort(t A[], int n) {
	buildMaxHeap(A, n);
	for (int i = n - 1;i > 0;--i) {
		swap(A[0], A[i]);
		i = i + 0; //ignore
		maxHeapify(A, --n, 0);
	}
}
template<class t>
void print(t A[], int n) {
	for (int i = 0;i < n;++i) {
		cout << A[i] << " ";
		//cout << endl;
	}
}
#endif 


