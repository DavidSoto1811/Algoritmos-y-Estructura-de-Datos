#pragma once
#include <iostream>
using namespace std;

template<class t>
class Heap {
private:
    int size;
    t *A;
    int parent(int i) {
        return (i - 1) / 2;
    }
    int left(int i) {
        return 2 * i + 1;
    }
    int rigth(int i) {
        return 2 * i + 2;
    }
    void maxHeapify(int z, int i) {
        int n = (z == 0) ? size : z;
        int l = left(i);
        int r = rigth(i);
        int largest(0);
        if (l <= (n - 1) && A[l] > A[i]) {
            largest = l;
        }
        else
            largest = i;
        if (r <= (n - 1) && A[r] > A[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(A[i], A[largest]);
            maxHeapify(n, largest);
        }
    }
    void buildMaxHeap() {
        for (int i = size / 2 - 1; i >= 0; i--) {
            maxHeapify(0, i);
        }
    }
    
public:
    Heap(t _A[], int  _size) : A(_A), size(_size) {}
    ~Heap() {}
    t maximum_heap() {
        return A[0];
    }
    void heapsort() {
        buildMaxHeap();
        for (int i = size - 1; i > 0; i--) {
            swap(A[0], A[i]);
            maxHeapify(i, 0);
        }
    }
    t heap_extract_max() {
        if (size < 1) {
            cout << "ERROR";
            return -1;
        }
        t max = A[0];
        A[0] = A[size - 1];
        size--;
        maxHeapify(0, 0);
        return max;
    }
    void insert(int x) {
        size++;
        A[size - 1] = x;
        int i = size - 1;
        while (i > 0 && A[parent(i)] < A[i]) {
            swap(A[i], A[parent(i)]);
            i = parent(i);
        }
    }
    void increase_key(int i, int x) {
        A[i] = max(A[i], x);
        while (i > 0 && A[parent(i)] < A[i]) {
            swap(A[parent(i)], A[i]);
            i = parent(i);
        }
    }
    void print() {
        for (int i = 0;i < size;i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }
};