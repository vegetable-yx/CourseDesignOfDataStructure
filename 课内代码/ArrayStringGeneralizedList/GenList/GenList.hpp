# ifndef _GEN_LIST_H_
# define _GEN_LIST_H_
# include <iostream>
# include <assert.h>
# include <stdlib.h>
# include "..\..\LinearList\LinearList\SeqList.hpp"
using namespace std;

template <class T>
class GenList;

template <class T>
class GenListNode { 
	friend class GenList<T>;
	friend void delval(GenListNode<T>*, T);
	friend istream& operator >> (istream& in, GenList<T>& L);
public:
	GenListNode() :utype(0), tlink(NULL) { info.ref = 0; }
	GenListNode(GenListNode<T>& RL) {
		utype = RL.utype;
		tlink = RL.tlink;
		info = RL.info;
	}
	GenListNode<T>& operator = (const GenListNode<T>& n) {
		utype = n.utype;
		tlink = n.tlink;
		info = n.info;
	}
private:
	int utype;
	GenListNode<T>* tlink;
	union {
		int ref;
		T value;
		GenListNode<T>* hlink;
	} info;
};

template <class T>
struct Items {
	int utype;
	union {
		int ref;
		T value;
		GenListNode<T>* hlink;
	} info;
	Items() {
		utype = 0, info.ref = 0;
	}
	Items(Items<T>& RL) { 
		utype = RL.utype; 
		info = RL.info;
	}
};

template <class T>
class GenList {
public :
	GenList();
	~GenList();
	bool Head(Items<T>& x);
	bool Tail(GenList<T>& lt);
	GenListNode<T>* First();
	GenListNode<T>* Next(GenListNode<T>* elem);
	void Copy(const GenList<T>& R);
	void delval(GenListNode<T>*, T);
	int Length();
	int depth();
	friend istream& operator >> (istream& in, GenList<T>& L) {
		int n;
		cout << "广义表字符串的字符个数 ： " << endl;
		in >> n;
		SeqList<T> Ls1(n);
		SeqList<GenListNode<T>*> Ls2(n);
		L.CreateList(in, L.first, Ls1, Ls2);
		GenListNode<T>* p = L.first;
		L.first = L.first->info.hlink;
		/*delete[] Ls1;
		delete[] Ls2;*/
		delete p;
	}
private :
	GenListNode<T>* first;
	GenListNode<T>* Copy(GenListNode<T>* ls);
	int Length(GenListNode<T>* ls);
	int depth(GenListNode<T>* ls);
	bool equal(GenListNode<T>* s, GenListNode<T>* t);
	void Remove(GenListNode<T>* ls);
	void CreateList(istream& in, GenListNode<T>* ls, SeqList<T>& L1, SeqList<GenListNode<T>*>& L2);
};

template <class T>
GenList<T>::GenList() {
	first = new GenListNode<T>;
	assert(first != NULL);
}

template <class T>
bool GenList<T>::Head(Items<T>& x) {
	if (first->tlink == NULL) return false;
	else {
		x.utype = first->tlink->utype;
		x.info = first->tlink->utype;
		return true;
	}
}

template <class T>
bool GenList<T>::Tail(GenList<T>& lt) {
	if (first->tlink == NULL) return false;
	else {
		lt.first->utype = 0;
		lt.first->info.ref = 0;
		lt.first->tlink = Copy(first->tlink->tlink);
		return true;
	}
}

template <class T>
GenListNode<T>* GenList<T>::First(){
	if (first->tlink == NULL) return NULL;
	else return first->tlink;
}

template <class T>
GenListNode<T>* GenList<T>::Next(GenListNode<T>* elem) {
	if (elem->tlink == NULL) return NULL;
	else return elem->tlink;
}

template <class T>
void GenList<T>::Copy(const GenList<T>& R) {
	first = Copy(R.first);
}

template <class T>
GenListNode<T>* GenList<T>::Copy(GenListNode<T>* ls) {
	GenListNode<T>* q = NULL;
	if (ls != NULL) {
		q = new GenListNode<T>;
		q->utype = ls->utype;
		switch (ls->utype) {
		case 0:
			q->info.ref = ls->info.ref;
			break;
		case 1:
			q->info.value = ls->info.value;
			break;
		case 2:
			q->info.hlink = Copy(ls->info.hlink);
			break;
		}
		q->tlink = Copy(ls->tlink);
	}
	return q;
}

template <class T>
int GenList<T>::Length() {
	return Length(first);
}

template <class T>
int GenList<T>::Length(GenListNode<T>* ls) {
	if (ls != NULL) return 1 + Length(ls->tlink);
	else return 0;
}

template <class T>
int GenList<T>::depth() {
	return depth(first);
}

template <class T>
int GenList<T>::depth(GenListNode<T>* ls) {
	if (ls->tlink == NULL) return 1;
	GenListNode<T>* tem = ls->tlink;
	int m = 0, n;
	while (tem != NULL) {
		if (tem->utype == 2) {
			n = depth(tem->info.hlink);
			if (m < n) m = n;
		}
		tem = tem->tlink;
	}
	return m + 1;
}

template <class T>
bool  GenList<T>::equal(GenListNode<T>* s, GenListNode<T>* t) {
	int x;
	if (s->tlink == NULL && t->tlink == NULL) return true;
	if (s->tlink != NULL && t->tlink != NULL && s->tlink->utype == t->tlink->utype) {
		if (s->tlink->utype == 1) x = (s->tlink->info.value == t->tlink->info.value) ? 1 : 0;
		else if (s->tlink->utype == 2) x = equal(s->tlink->info.hlink, t->tlink->info.hlink);
		if (x == 1) return equal(s->tlink, t->tlink);
	}
	return false;
}

template <class T>
void  GenList<T>::delval(GenListNode<T>* ls, T x) {
	if (ls->tlink != NULL) {
		GenListNode<T>* p = ls->tlink;
		while (p != NULL && (p->utype == 1 && p->info.value == x)) {
			ls->tlink = p->tlink;
			delete p;
			p = ls->tlink;
		}
		if (p != NULL) {
			if (p->utype == 2) delval(p->info.hlink, x);
			delval(p, x);
		}
	}
}

template <class T>
GenList<T>::~GenList() {
	Remove(first);
}

template <class T>
void GenList<T>::Remove(GenListNode<T>* ls) {
	ls->info.ref--;
	if (ls->info.ref <= 0) {
		GenListNode<T>* q;
		while (ls->tlink != NULL) {
			q = ls->tlink;
			if (q->utype == 2) {
				Remove(q->info.hlink);
				if (q->info.hlink->info.ref <= 0) delete q->info.hlink;
			}
			ls->tlink = q->tlink;
			delete q;
		}
	}
}

template <class T>
void GenList<T>::CreateList(istream& in, GenListNode<T>* ls, SeqList<T>& L1, SeqList<GenListNode<T>*>& L2) {
	T chr;
	in >> chr;
	if (isalpha(chr) && isupper(chr) || chr == '(') {
		ls = new GenListNode<T>;
		ls->utype = 2;
		if (isalpha(chr) && isupper(chr)) {
			int n = L1.Length();
			int m = L1.Search(chr);
			if (m != 0) {
				GenListNode<T>* p = L2.getData(L2.Locate(m));
				p->ref++;
			}
			else {
				L1.Insert(n, chr);
				L2.Insert(n, ls);
			}
			in >> chr;
			if (chr != '(') exit(1);
		}
		ls->info.hlink = new GenListNode<T>;
		ls->info.hlink->utype = 0;
		ls->info.hlink->ref = 1;
		CreateList(in, ls->info.hlink->tlink, L1, L2);
		CreateList(in, ls, L1, L2);
	}
	else if (isalpha(chr) && islower(chr)) {
		ls = new GenListNode<T>;
		ls->utype = 1;
		ls->info.value = chr;
		CreateList(in, ls, L1, L2);
	}
	else if (chr == ',') CreateList(in, ls->tlink, L1, L2);
	else if (chr == ')') ls->tlink = NULL;
	else if (chr == '#') ls = NULL;
}


# endif