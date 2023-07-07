#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<class t>
class Heap {
private:
    int size;
    vector<t> A;
    function<bool(t, t)> mayor;
    function<bool(t, t)> menor;
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
        if (l <= (n - 1) && mayor(A[l], A[i])) {
            largest = l;
        }
        else
            largest = i;
        if (r <= (n - 1) && mayor(A[r], A[largest])) {
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
    Heap(int  _size, function<bool(t, t)> _mayor, function<bool(t, t)> _menor) : size(_size), mayor(_mayor), menor(_menor) {
        A.resize(100);
    }
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
    void insert(t x) {
        size++;
        A[size - 1] = x;
        int i = size - 1;
        while (i > 0 && menor(A[parent(i)], A[i])) {
            swap(A[i], A[parent(i)]);
            i = parent(i);
        }
    }
    void mostrar(function<void(t)> print) {
        for (int i = 0; i < size; i++) {
            print(A[i]);
        }
        cout << endl;
    }
};