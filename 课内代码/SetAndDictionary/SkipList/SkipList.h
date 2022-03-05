# ifndef _SKIP_LIST_H_
# define _SKIP_LIST_H_
# include <iostream>
# include <assert.h>
using namespace std;

const int DefaultSize = 100;

template <class E, class K>
struct SkipNode {
	E data;
	SkipNode<E, K>** link;
	SkipNode(int sz = DefaultSize) {
		link = new SkipNode<E, K> * [sz];
		if (link == NULL) {
			cerr << "´æ´¢·ÖÅäÊ§°Ü£¡" << endl;
			exit(1);
		}
	}
	~SkipNode() { delete[]link; }
};

template <class E, class K>
class SkipList {
public :
	SkipList(K large, int maxLev = DefaultSize);
	~SkipList();
	bool Search(const K k1, E& e1) const;
	E& getData(SkipNode<E, K>* current) {
		if (current != NULL) return &current->data;
		else return NULL;
	}
	bool Insert(const K k1, E& e1);
	bool Remove(const K k1, E& e1);
private :
	int maxLevel;
	int Levels;
	K TailKey;
	SkipNode<E, K>* head, * tail;
	SkipNode<E, K>** last;
	int Level();
	SkipNode<E, K>* SaveSearch(const K k1);
};

template <class E, class K>
SkipList<E, K>::SkipList(K large, int maxLev) {
	maxLevel = maxLev;
	TailKey = large;
	Levels = 0;
	head = new SkipNode<E, K>(maxLevel + 1);
	tail = new SkipNode<E, K>(0);
	last = new SkipNode<E, K> * [maxLevel + 1];
	tail->data = large;
	for (int i = 0; i <= maxLevel; i++) head->link[i] = tail;
}

template <class E, class K>
SkipList<E, K>::~SkipList() {
	SkipNode<E, K>* next;
	while (head != tail) {
		next = head->link[0];
		delete head;
		head = next;
	}
	delete tail;
	delete[]last;
}

template <class E, class K>
bool SkipList<E, K>::Search(const K k1, E& e1) const {
	if (k1 > TailKey) return false;
	SkipNode<E, K>* p = head;
	for (int i = Levels; i >= 0; i--)
		while (p->link[i]->data < k1) p = p->link[i];
	e1 = p->link[0]->data;
	return e1 == k1;
}

template <class E, class K>
SkipNode<E, K>* SkipList<E, K>::SaveSearch(const K k1) {
	if (k1 > TailKey) return NULL;
	SkipNode<E, K>* p = head;
	for (int i = Levels; i >= 0; i--) {
		while (p->link[i]->data < k1) p = p->link[i];
		last[i] = p;
	}
	return p->link[0];
}

template <class E, class K>
int SkipList<E, K>::Level() {
	int lev = 0;
	while (rand() <= RAND_MAX / 2) lev++;
	return (lev < maxLevel) ? lev : maxLevel;
}

template <class E, class K>
bool SkipList<E, K>::Insert(const K k1, E& e1) {
	if (k1 >= TailKey) {
		cerr << "¹Ø¼üÂëÌ«´ó£¡" << endl;
		return false;
	}
	SkipNode<E, K>* p = SaveSeach(k1);
	if (p->data == e1) {
		cerr << "¹Ø¼üÂëÖØ¸´£¡" << endl;
		return false;
	}
	int lev = Level();
	if (lev > Levels) {
		lev = ++Levels;
		last[lev] = head;
	}
	SkipNode<E, K>* newNode = new SkipNode<E, K>(lev + 1);
	newNode->data = e1;
	for (int i = 0; i <= lev; i++) {
		newNode->link[i] = last[i]->link[i];
		last[i]->link[i] = newNode;
	}
	return true;
}

template <class E, class K>
bool SkipList<E, K>::Remove(const K k1, E& e1) {
	if (k1 > TailKey) {
		cerr << "¹Ø¼üÂëÌ«´ó" << endl;
		return false;
	}
	SkipNode<E, K>* p = SaveSearch(k1);
	if (p->data != k1) {
		cerr << "±»É¾³ýÔªËØ²»´æÔÚ£¡" << endl;
		return false;
	}
	for (int i = 0; i <= Levels && last[i]->link[i] == p; i++) last[i]->link[i] = p->link[i];
	while (Levels > 0 && head->link[Levels] == tail) Levels--;
	e1 = p->data;
	delete p;
	return true;
}

# endif
