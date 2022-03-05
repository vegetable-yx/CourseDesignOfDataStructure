# ifndef _MIN_HEAP_H_
# define _MIN_HEAP_H
# include <iostream>
# include "..\..\StackAndQueue\PQueue\PQueue.hpp"
using namespace std;

# define DefaultSize 10

template <class T, class E>
class MinHeap {
public :
	MinHeap(int sz = DefaultSize);
	MinHeap(E arr[], int n);
	~MinHeap() { delete []heap; }
	bool Insert(const E& x);
	bool RemoveMin(E& x);
	bool IsEmpty() const { return currentSize == 0; }
	bool IsFull() const { return currentSize == maxHeapSize; }
	void MakeEmpty() { currentSize = 0; }
	friend ostream& operator << (ostream& out, MinHeap<T, E>& H) {
		for (int i = 0; i < H.currentSize; i++) out << H.heap[i] << " ";
		out << endl;
		return out;
	}
private :
	E* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int satrt);
};

template <class T, class E>
MinHeap<T, E>::MinHeap(int sz) {
	maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new E[maxHeapSize];
	if (heap == NULL) {
		cerr << "¶Ñ´æ´¢·ÖÅäÊ§°Ü £¡" << endl;
		exit(1);
	}
	currentSize = 0;
}

template <class T, class E>
MinHeap<T, E>::MinHeap(E arr[], int n) {
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new E[maxHeapSize];
	if(heap == NULL) {
		cerr << "¶Ñ´æ´¢·ÖÅäÊ§°Ü £¡" << endl;
		exit(1);
	}
	for (int i = 0; i < n; i++) heap[i] = arr[i];
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0) {
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

template <class T, class E>
void MinHeap<T, E>::siftDown(int start, int m) {
	int i = start, j = 2 * i + 1;
	E tem = heap[i];
	while (j <= m) {
		if (j < m && heap[j + 1] <= heap[j]) j++;
		if (tem <= heap[j]) break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = tem;
}

template <class T, class E>
void MinHeap<T, E>::siftUp(int start) {
	int j = start, i = (j - 1) / 2;
	E tem = heap[j];
	while (j > 0) {
		if (heap[i] <= tem) break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
		heap[j] = tem;
	}
}

template <class T, class E>
bool MinHeap<T, E>::Insert(const E& x) {
	if (currentSize == maxHeapSize) {
		cerr << "Heap FUll" << endl;
		return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template <class T, class E>
bool MinHeap<T, E>::RemoveMin(E& x) {
	if (!currentSize) {
		cerr << "Heap Empty" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}


# endif