#include "pch.h"
#include <iostream>
using namespace std;

#include "Heap.hpp"

int main() {
	int A[10] = { 16, 14, 10, 8, 7, 19, 3, 2, 4, 1 };
	char B[14] = { 'A','X', 'T', 'U', 'J', 'K', 'D', 'F', 'M', 'R', 'G', 'Y', 'A', 'I' };
	int n = 14;
	print(B, n);
	//buildMaxHeap(A, 10);
	cout << endl;
	heapsort(B, n);
	print(B, n);
	return 0;
	
}