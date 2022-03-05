# ifndef _SEQ_DEQUE_H_
# define _SEQ_DEQUE_H_
# include "..\SeqQueue\SeqQueue.hpp"
# include "Deque.h"
using namespace std;

template <class T>
class SeqDeque : public SeqQueue<T> {
public:
	SeqDeque(int sz = 50) { SeqQueue<T>::SeqQueue(sz); }
	bool getHead(T& x) const;
	bool getTail(T& x) const;
	bool EnQueueHead(const T& x);
	bool EnQueueTail(const T& x);
	bool DeQueueHead(T& x);
	bool DeQueueTail(T& x) ;
};

template <class T>
bool SeqDeque<T>::getHead(T& x) const {
	T tem;
	bool tag = SeqQueue<T>::getFront(tem);
	x = tem;
	return tag;
}

template <class T>
bool SeqDeque<T>::EnQueueTail(const T& x) {
	return SeqQueue<T>::EnQueue(x);
}

template <class T>
bool SeqDeque<T>::DeQueueHead(T& x) {
	T tem;
	bool tag = SeqQueue<T>::DeQueue(tem);
	x = tem;
	return tag;
}

template <class T>
bool SeqDeque<T>::getTail(T& x) const {
	if (this->IsEmpty()) return false;
	x = this->elements[(this->rear - 1 + this->maxSize) % this->maxSize];
	return true;
}

template <class T>
bool SeqDeque<T>::EnQueueHead(const T& x) {
	if (this->IsFull()) return false;
	this->front = (this->front - 1 + this->maxSize) % this->maxSize;
	this->elements[this->front] = x;
	return true;
}

template <class T>
bool SeqDeque<T>::DeQueueTail(T& x) {
	if (this->IsEmpty()) return false;
	this->rear = (this->rear - 1 + this->maxSize) % this->maxSize;
	x = this->elements[this->rear];
	return true;
}


# endif