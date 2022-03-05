# ifndef _P_QUEUE_H_
# define _P_QUEUE_H_
# include <assert.h>
# include <iostream>
using namespace std;
const int DefaultPQSize = 50;

template <class T>
class PQueue {
protected :
	T* pqelements;
	int count;
	int maxSize;
	void Adjust();
public :
	PQueue(int sz = DefaultPQSize);
	~PQueue() { delete[] pqelements; }
	bool Insert(const T& x);
	bool RemoveMin(T& x);
	bool getFront(T& x) const;
	void makeEmpty() { count = 0; }
	bool IsEmpty() const { return count == 0; }
	bool IsFull() const { return count == maxSize; }
	int getSize() const { return count; }
	friend ostream& operator << (ostream& os, const PQueue<T>& pq) {
		os << "The number of PQueue is : " << pq.getSize() << endl;
		for (int i = 0; i < pq.getSize(); i++) os << "#" << i << " : " << pq.pqelements[i] << endl;
		return os;
	}
};

template <class T>
PQueue<T>::PQueue(int sz) : count(0), maxSize(sz) {
	pqelements = new T[maxSize];
	assert(pqelements != NULL);
}

template <class T>
bool PQueue<T>::Insert(const T& x) {
	if (count == maxSize) return false;
	pqelements[count++] = x;
	Adjust();
}

template <class T>
void PQueue<T>::Adjust() {
	T tem = pqelements[count - 1];
	int j;
	for (j = count - 2; j >= 0; j--) {
		if (pqelements[j] <= tem) break;
		else pqelements[j + 1] = pqelements[j];
	}
	pqelements[j + 1] = tem;
}

template <class T>
bool PQueue<T>::RemoveMin(T& x) {
	if (count == 0) return false;
	x = pqelements[0];
	for (int i = 1; i < count; i++) pqelements[i - 1] = pqelements[i];
	count--;
	return true;
}

template <class T>
bool PQueue<T>::getFront(T& x) const {
	if (count == 0) return false;
	else x = pqelements[0];
	return true;
}


# endif