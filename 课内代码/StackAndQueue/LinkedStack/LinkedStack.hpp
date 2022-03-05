# ifndef _LINKED_STACK_H_
# define _LINKED_STACK_H_
# include <iostream>
# include <assert.h>
# include "..\StackAndQueue\Stack.h"
# include "..\..\LinearList\LinkedList\LinkedList.hpp"

template <class T>
class LinkedStack : public Stack<T> {
public:
	LinkedStack() : top(NULL) {}
	~LinkedStack() { makeEmpty(); }
	void Push(const T& x);
	bool Pop(T& x);
	bool getTop(T& x) const;
	bool IsEmpty() const { return top == NULL; }
	bool IsFull() const { return false; }
	int getSize() const;
	void makeEmpty();
	friend ostream& operator << (ostream& os, LinkedStack<T>& s) {
		os << "The number of datas in the stack : " << s.getSize() << endl;
		LinkNode<T>* p = s.top;
		int i = 0;
		while (p != NULL) {
			os << "#" << ++i << " : " << p->data << endl;
			p = p->link;
		}
		return os;
	}
private :
	LinkNode<T>* top;
};

template <class T>
void LinkedStack<T>::makeEmpty() {
	LinkNode<T>* p;
	while (top != NULL) {
		p = top;
		top = top->link;
		delete p;
	}
}

template <class T>
void LinkedStack<T>::Push(const T& x) {
	top = new LinkNode<T>(x, top);
	assert(top != NULL);
}

template <class T>
bool LinkedStack<T>::Pop(T& x) {
	if (IsEmpty()) return false;
	LinkNode<T>* p = top;
	top = top->link;
	x = p->data;
	delete p;
	return true;
}

template <class T>
bool LinkedStack<T>::getTop(T& x) const {
	if (IsEmpty()) return false;
	x = top->data;
	return true;
}

template <class T>
int LinkedStack<T>::getSize() const {
	LinkNode<T> *p = top;
	int k = 0;
	while (p != NULL) {
		p = p->link;
		++k;
	}
	return k;
}

# endif