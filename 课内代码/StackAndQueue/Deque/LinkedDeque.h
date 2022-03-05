# ifndef _LINKED_DEQUE_H_
# define _LINKED_DEQUE_H_
# include "..\LinkedQueue\LinkedQueue.hpp"
# include "Deque.h"
using namespace std;

template <class T>
class LinkedDeque : public LinkedQueue<T> {
public:
	LinkedDeque() { LinkedQueue<T>::LinkedQueue(); }
	bool getHead(T& x) const;
	bool getTail(T& x) const;
	bool EnQueueHead(const T& x);
	bool EnQueueTail(const T& x);
	bool DeQueueHead(T& x);
	bool DeQueueTail(T& x);
};

template <class T>
bool LinkedDeque<T>::getHead(T& x) const {
	T tem;
	bool tag = LinkedQueue<T>::getFront(tem);
	x = tem;
	return tag;
}

template <class T>
bool LinkedDeque<T>::EnQueueTail(const T& x) {
	return LinkedQueue<T>::EnQueue(x);
}

template <class T>
bool LinkedDeque<T>::DeQueueHead(T& x) {
	T tem;
	bool tag = LinkedQueue<T>::DeQueue(tem);
	x = tem;
	return tag;
}

template <class T>
bool LinkedDeque<T>::getTail(T& x) const {
	if (this->IsEmpty()) return false;
	x = this->rear->data;
	return true;
}

template <class T>
bool LinkedDeque<T>::EnQueueHead(const T& x) {
	LinkNode<T>* p = new LinkNode<T>(x);
	if (p == NULL) return false;
	if (this->IsEmpty()) {
		this->front = this->rear = p;
		if (this->front == NULL) return false;
	}
	else {
		p->link = this->front;
		this->front = p;
	}
	return true;
}

template <class T>
bool LinkedDeque<T>::DeQueueTail(T& x) {
	if (this->IsEmpty()) return false;
	LinkNode<T>* p = this->front;
	while (p->link != this->rear) p = p->link;
	x = this->rear->data;
	delete this->rear;
	p->link = NULL;
	this->rear = p;
	return true;
}


# endif