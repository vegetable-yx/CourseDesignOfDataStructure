# ifndef _SORTED_CHAIN_H_
# define _SORTED_CHAIN_H_
# include <assert.h>
# include <iostream>
using namespace std;

template <class E, class K>
struct ChainNode {
	E data;
	ChainNode<E, K>* link;
	ChainNode() : link(NULL) {}
	ChainNode(E& e1, ChainNode<E, K>* next = NULL) : data(e1), link(next) {}
};

template <class E, class K>
class SortedChain {
private :
	ChainNode<E, K>* first;
public :
	SortedChain() {
		first = new ChainNode<E, K>;
		assert(first != NULL);
	}
	~SortedChain();
	ChainNode<E, K>* Search(const K k1) const;
	void Insert(const K k1, E& e1);
	bool Remove(const K k1, E& e1);
	ChainNode<E, K>* Begin() { return first->link; }
	ChainNode<E, K>* Next(ChainNode<E, K>* current) {
		if (current != NULL) return current->link;
		else return NULL;
	}
};

template <class E, class K>
ChainNode<E, K>* SortedChain<E, K>::Search(const K k1) const {
	ChainNode<E, K>* p = first->link;
	while (p != NULL && p->data < k1) p = p->link;
	if (p != NULL && p->data == k1) return p;
	else return NULL;
}

template <class E, class K>
void SortedChain<E, K>::Insert(const K k1, E& e1) {
	ChainNode<E, K>* p = first->link, * pre = first, * newNode;
	while (p != NULL && p->data < k1) {
		pre = p;
		p = p->link;
	}
	if (p != NULL && p->data == k1) {
		p->data = e1;
		return;
	}
	newNode = new ChainNode<E, K>(e1);
	if (newNode == NULL) {
		cerr << "´æ´¢·ÖÅäÊ§°Ü£¡ " << endl;
		exit(1);
	}
	newNode->link = p;
	pre->link = newNode;
}

template <class E, class K>
bool SortedChain<E, K>::Remove(const K k1, E& e1) {
	ChainNode<E, K>* p = first->link, * pre = first;
	while (p != NULL && p -> data < k1) {
		pre = p;
		p = p->link;
	}
	if (p != NULL && p->data == k1) {
		pre->link = p->link;
		e1 = p->data;
		delete p;
		return true;
	}
	else return false;
}

# endif