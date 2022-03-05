#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include "../LinearList/LinearList.h"
#include <iostream>
using namespace std;

template<class T>
struct LinkNode {
	T data;
	LinkNode <T>* link;
	LinkNode(LinkNode<T>* ptr = NULL) : link(ptr) {};
	LinkNode(const T& tem, LinkNode<T>* ptr = NULL) : data(tem), link(ptr) {};
};

template<class T>
class LinkedList {
protected:
	LinkNode<T>* first;
public:
	LinkedList() { first = new LinkNode<T>; }
	LinkedList(const T& L) { first = new LinkNode<T>(L); }
	LinkedList(LinkedList<T>& L);
	~LinkedList() { makeEmpty(); }
	void makeEmpty();
	int Length() const;
	LinkNode<T>* getHead() const { return first; }
	void setHead(LinkNode<T>* node) { first = node; }
	LinkNode<T>* Search(T x);
	LinkNode<T>* Locate(int i);
	T* getData(int i);
	void setData(int i, T& x);
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty() const { return first->link == NULL; }
	bool isFull() const { return false; }
	void Sort();
	void input();
	void output();
	LinkedList<T>& operator=(LinkedList<T>& L);
};

template<class T>
LinkedList<T>::LinkedList(LinkedList<T>& L) {
	T value;
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* desptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {
		value = srcptr->link->data;
		desptr->link = new LinkNode<T>(value);
		desptr = desptr->link;
		srcptr = srcptr->link;
	}
	desptr->link = NULL;
}

template <class T>
void LinkedList<T>::makeEmpty() {
	LinkNode<T>* q;
	while (first->link != NULL) {
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

template <class T>
int LinkedList<T>::Length() const {
	LinkNode<T>* p = first->link;
	int count = 0;
	while (p->link != NULL) {
		p = p->link;
		++count;
	}
	return count;
}

template <class T>
LinkNode<T>* LinkedList<T>::Search(T x) {
	LinkNode<T>* current = first->link;
	while (current != NULL) {
		if (current->data == x) break;
		else current = current->link;
	}
	return current;
}

template <class T>
LinkNode<T>* LinkedList<T>::Locate(int i) {
	if (i < 0) return NULL;
	LinkNode<T>* current = first;
	int k = 0;
	while (current != NULL && k < i) {
		current = current->link;
		++k;
	}
	return current;
}

template <class T>
T* LinkedList<T>::getData(int i) {
	if (i <= 0) return NULL;
	LinkNode<T>* current = Locate(i);
	if (current == NULL) return NULL;
	else return current->data;
}

template <class T>
void LinkedList<T>::setData(int i, T& x) {
	if (i <= 0) return;
	LinkNode<T> current = Locate(i);
	if (current == NULL) return;
	else current->data = x;
}

template <class T>
bool LinkedList<T>::Insert(int i, T& x) {
	LinkNode<T>* current = Locate(i);
	if (current == NULL) return false;
	LinkNode<T>* newnode = new LinkNode<T>(x);
	if (newnode == NULL) {
		cerr << "´æ´¢·ÖÅä´íÎó£¡ " << endl;
		exit(1);
	}
	newnode->link = current->link;
	current->link = newnode;
	return true;
}

template <class T>
bool LinkedList<T>::Remove(int i, T& x) {
	LinkNode<T>* current = Locate(i - 1);
	if (current == NULL || current->link == NULL) return false;
	LinkNode<T> del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}

template <class T>
void LinkedList<T>::output() {
	LinkNode<T>* current = first->link;
	int i = 0;
	while (current != NULL) {
		++i;
		cout << "#" << i << ": " << current->data << endl;
		current = current->link;
	}
}

template <class T>
void LinkedList<T>::input() {
	LinkNode<T>* newnode, * last;
	T val;
	last = first;
	while (cin >> val) {
		newnode = new LinkNode<T>(val);
		if (newnode == NULL) {
			cerr << "´æ´¢·ÖÅä´íÎó£¡ " << endl;
			exit(1);
		}
		last->link = newnode;
		last = newnode;
	}
	last->link = NULL;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& L) {
	LinkedList(L);
	return *this;
}


#endif