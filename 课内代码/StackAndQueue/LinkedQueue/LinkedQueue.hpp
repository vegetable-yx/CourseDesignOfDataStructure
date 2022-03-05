# ifndef _LINKED_QUEUE_H_
# define _LINKED_QUEUE_H_
# include <iostream>
# include "..\SeqQueue\Queue.h"
# include "..\LinkedStack\LinkedStack.hpp"

template <class T>
class LinkedQueue : public Queue<T> {
protected :
	LinkNode<T>* front, * rear;
public :
	LinkedQueue() : front(NULL), rear(NULL) {}
	~LinkedQueue() { makeEmpty(); }
	bool EnQueue(const T& x);
	bool DeQueue(T& x);
	bool getFront(T& x) const;
	void makeEmpty();
	bool IsEmpty() const { return front == NULL; }
	bool IsFull() const { return false; }
	int getSize() const;
	friend ostream& operator << (ostream& os, const LinkedQueue<T>& Q) {
		os << "The number of LinkedQueue is : " << Q.getSize() << endl;
		LinkNode<T>* p = Q.front;
		int i = 0;
		while (p != NULL) {
			os << "#" << i << " : " << p->data << endl;
			p = p->link;
			++i;
		}
		return os;
	}
};

template <class T>
void LinkedQueue<T>::makeEmpty() {
	LinkNode<T>* p;
	while (front != NULL) {
		p = front;
		front = front->link;
		delete p;
	}
}

template <class T>
bool LinkedQueue<T>::EnQueue(const T& x) {
	if (IsEmpty()) {
		front = rear = new LinkNode<T>(x);
		if (front == NULL) return false;
	}
	else {
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL) return false;
		rear = rear->link;
	}
	return true;
}

template <class T>
bool LinkedQueue<T>::DeQueue(T& x) {
	if (IsEmpty()) return false;
	LinkNode<T>* p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}

template <class T>
bool LinkedQueue<T>::getFront(T& x) const {
	if (IsEmpty()) return false;
	x = front->data;
	return true;
}

template <class T>
int LinkedQueue<T>::getSize() const {
	LinkNode<T>* p = front;
	int k = 0;
	while (p != 0) {
		p = p->link;
		k++;
	}
	return k;
}


# endif