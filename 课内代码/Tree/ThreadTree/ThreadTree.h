# ifndef _THREAD_TREE_H_
# define _THREAD_TREE_H_
#include <iostream>
using namespace std;

template <class T>
struct ThreadNode {
	bool ltag, rtag;
	ThreadNode<T>* leftchild, rightchild;
	T data;
	ThreadNode(const T item) : data(item), leftchild(NULL), rightchild(NULL), ltag(0), rtag(0) {}
};

template <class T>
class ThreadTree {
protected :
	ThreadNode<T>* root;
	void createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre);
	ThreadNode<T>* parent(ThreadNode<T>* t);
public :
	ThreadTree() : root(NULL) {}
	void createInThread();
	ThreadNode<T>* First(ThreadNode<T>* current);
	ThreadNode<T>* Last(ThreadNode<T>* current);
	ThreadNode<T>* Next(ThreadNode<T>* current);
	ThreadNode<T>* Prior(ThreadNode<T>* current);
	void Inorder(void (*visit) (ThreadNode<T>* p));
	void Preorder(void (*visit) (ThreadNode<T>* p));
	void Postorder(void (*visit) (ThreadNode<T>* p));
	void InsertRight(ThreadNode<T>* s, ThreadNode<T>* r);
	void DeleteRight(ThreadNode<T>* s);
};

template <class T>
ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T>* current) {
	ThreadNode<T>* p = current;
	while (p->ltag == 0) p = p->leftchild;
	return p;
}

template <class T>
ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>* current) {
	ThreadNode<T>* p = current->rightchild;
	if (current->rtag == 0) return First(p);
	else return p;
}

template <class T>
ThreadNode<T>* ThreadTree<T>::Last(ThreadNode<T>* current) {
	ThreadNode<T>* p = current;
	while (p->rtag == 0) p = p->rtag;
	return p;
}

template <class T>
ThreadNode<T>* ThreadTree<T>::Prior(ThreadNode<T>* current) {
	ThreadNode<T>* p = current->leftchild;
	if (current->ltag == 0) return Last(p);
	else return p;
}

template <class T>
void ThreadTree<T>::Inorder(void (*visit) (ThreadNode<T>* p)) {
	ThreadNode<T>* p;
	for (p = First(root); p != NULL; p = Next(p)) visit(p);
}

template <class T>
void ThreadTree<T>::createInThread() {
	ThreadNode<T>* pre = NULL;
	if (root != NULL) {
		createInThread(root, pre);
		pre->rightchild = NULL;
		pre->rtag = 1;
	}
}

template<class T>
void ThreadTree<T>::createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre) {
	if (current == NULL) return;
	createInThread(current->leftchild, pre);
	if (current->leftchild == NULL) {
		current->leftchild = pre;
		current->ltag = 1;
	}
	if (pre != NULL && pre->rightchild == NULL) {
		pre->rightchild = current;
		pre->rtag = 1;
	}
	pre = current;
	createInThread(current->rightchild, pre);
}

template <class T>
void ThreadTree<T>::Preorder(void (*visit) (ThreadNode<T>* p)) {
	ThreadNode<T>* p = root;
	while (p != NULL) {
		visit(p);
		if (p->ltag == 0) p = p->leftchild;
		else if (p->rtag == 0) p = p->rightchild;
		else {
			while (p != NULL && p->rtag == 1) p = p->rightchild;
			if (p != NULL) p = p->rightchild;
		}
	}
}

template <class T>
void ThreadTree<T>::Postorder(void (*visit) (ThreadNode<T>* p)) {
	ThreadNode<T>* t = root;
	while (t->ltag == 0 || t->rtag == 0)
		if (t->ltag == 0) t = t->leftchild;
		else t = t->rightchild;
	visit(t);
	ThreadNode<T>* p;
	while ((p = parent(t)) != NULL) {
		if (p->rightchild == t || p->rtag == 1) t = p;
		else {
			t = p->rightchild;
			while (t->ltag == 0 || t->ltag == 0)
				if (t->rtag == 0) t = t->rightchild;
				else t = t->leftchild;
		}
		visit(t);
	}
}

template <class T>
ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T>* t) {
	ThreadNode<T>* p;
	if (t == root) return NULL;
	for (p = t; p->ltag == 0; p = p->leftchild);
	if (p->leftchild != NULL)
		for (p = p->leftchild; p != NULL && p->leftchild != t && p->rightchild != t; p = p->leftchild);
	if (p == NULL || p->leftchild == NULL) {
		for (p = t; p->rtag = 0; p = p->rightchild);
		for (p = p->rightchild; p != NULL && p->leftchild != t && p->rightchild != t; p = p->leftchild);
	}
	return p;
}

template <class T>
void ThreadTree<T>::InsertRight(ThreadNode<T>* s, ThreadNode<T>* r) {
	r->rightchild = s->rightchild;
	r->rtag = s->rtag;
	r->leftchild = s;
	r->ltag = 1;
	s->rightchild = r;
	s->rtag = 0;
	if (r->rtag == 0) {
		ThreadNode<T>* tem;
		tem = First(r->rightchild);
		tem->leftchild = r;
	}
}

template <class T>
void ThreadTree<T>::DeleteRight(ThreadNode<T>* s) {
	ThreadNode<T>* r = s->rightchild;
	if (r->rtag && r->ltag) {
		s->rightchild = r->rightchild;
		s->rtag = 1;
		return;
	}
	if (r->ltag) {
		ThreadNode<T>* fr = First(r->rightchild);
		fr->leftchild = s;
		s->rightchild = r->rightchild;
		return;
	}
	if (r->rtag) {
		ThreadNode<T>* la = Last(r->leftchild);
		la->rightchild = s;
		s->rightchild = r->leftchild;
		return;
	}
	ThreadNode<T>* la = Last(r->leftchild);
	la->rightchild = r->rightchild;
	la->rtag = r->rtag;
	s->rightchild = r->leftchild;
	ThreadNode<T>* fr = First(r->rightchild);
	fr->leftchild = la;
}

# endif