# ifndef _SQE_QUEUE_H_
# define _SEQ_QUEUE_H_
# include <iostream>
# include <assert.h>
# include "Queue.h"
using namespace std;

template <class T>
class SeqQueue : public Queue<T> {
protected :
	int rear, front;
	T* elements;
	int maxSize;
public : 
	SeqQueue(int sz = 20);
	~SeqQueue() { delete[] elements; }
	bool EnQueue(const T& x);
	bool DeQueue(T& x);
	bool getFront(T& x) const ;
	void makeEmpty() { front = rear = 0; }
	bool IsEmpty() const { return front == rear; }
	bool IsFull() const { return (rear + 1) % maxSize == front; }
	int getSize() const { return (rear - front + maxSize) % maxSize; }
	friend ostream& operator << (ostream& os, const SeqQueue<T>& Q) {
		os << "front = " << Q.front << " , rear = " << Q.rear << endl;
		for (int i = Q.front; i != Q.rear; i = (i + 1) % Q.maxSize) os << "#" << i << " : " << Q.elements[i] << endl;
		return os;
	}
};

template <class T>
SeqQueue<T>::SeqQueue(int sz) : front(0), rear(0), maxSize(sz){
	elements = new T[maxSize];
	assert(elements != NULL);
}

template <class T>
bool SeqQueue<T>::EnQueue(const T& x) {
	if (IsFull()) return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}

template <class T>
bool SeqQueue<T>::DeQueue(T& x) {
	if (IsEmpty()) return false;
	x = elements[front];
	front = (front + 1) % maxSize;
	return true;
}

template <class T>
bool SeqQueue<T>::getFront(T& x) const {
	if (IsEmpty()) return false;
	x = elements[front];
	return true;
}

# endif