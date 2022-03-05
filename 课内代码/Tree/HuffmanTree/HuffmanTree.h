# ifndef _HUFFMAN_TREE_H_
# define _HUFFMAN_TREE_H_
# include <iostream>
# include "..\MinHeap\MinHeap.h"
using namespace std;

const int defaultSize = 20;

template <class T, class E>
struct HuffmanNode {
	E data;
	HuffmanNode<T, E>* leftChild, * rightChild;
	/*HuffmanNode() : leftChild(NULL), rightChild(NULL), parent(NULL) {}
	HuffmanNode(E elem, HuffmanNode<T, E>* left = NULL, HuffmanNode<T, E>* right = NULL, HuffmanNode<T, E>* pr = NULL) : data(elem), leftChild(left), rightChild(right), parent(pr) {}*/
	void Copy(HuffmanNode<T, E>* SR, const HuffmanNode<T, E>* HN);
	void operator = (const HuffmanNode<T, E>& HN) {
		Copy(this, &HN);
	}
	bool operator <= (const HuffmanNode<T, E>& HN) {
		if (data <= HN.data) return true;
		return false;
	}
};

template <class T, class E>
void HuffmanNode<T, E>::Copy(HuffmanNode<T, E>* SR, const HuffmanNode<T, E>* HN) {
	if (HN == NULL) return;
	SR = new HuffmanNode<T, E>;
	SR->data = HN->data;
	Copy(HN->leftChild, HN->leftChild);
	Copy(HN->rightChild, HN->rightChild);
}

template <class T, class E>
class HuffmanTree {
public :
	HuffmanTree(E w[], int n);
	~HuffmanTree() { delete root; }
	friend ostream& operator << (ostream & out, HuffmanTree<T, E>& HT) {
		HuffmanNode<T, E>* current = HT.root;
		while (current != NULL && current->rightChild != NULL) {
			out << current->leftChild->data << " ";
			current = current->rightChild;
		}
		out << current->leftChild->data << " ";
		return out;
	}
private :
	HuffmanNode<T, E>* root;
	void deleteTree(HuffmanNode<T, E>* t);
	void mergeTree(HuffmanNode<T, E>& ht1, HuffmanNode<T, E>& ht2, HuffmanNode<T, E>*& parent);
};

template<class T, class E>
HuffmanTree<T, E>::HuffmanTree(E w[], int n) {
	MinHeap<T, HuffmanNode<T, E>> hp;
	HuffmanNode<T, E>first, second;
	HuffmanNode<T, E>* NodeList = new HuffmanNode<T, E>[n];
	for (int i = 0; i < n; i++) {
		NodeList[i].data = w[i];
		NodeList[i].leftChild = NULL;
		NodeList[i].rightChild = NULL;
		hp.Insert(NodeList[i]);
	}
	for (int i = 0; i < n - 1; i++) {
		HuffmanNode<T, E>* parent;
		hp.RemoveMin(first);
		hp.RemoveMin(second);
		mergeTree(first, second, parent);
		hp.Insert(*parent);
		root = parent;
	}
}

template <class T, class E>
void HuffmanTree<T, E>::mergeTree(HuffmanNode<T, E>& bt1, HuffmanNode<T, E>& bt2, HuffmanNode<T, E>*& parent) {
	parent = new HuffmanNode<T, E>;
	parent->leftChild = &bt1;
	parent->rightChild = &bt2;
	parent->data.key = bt1.data.key + bt2.data.key;
}


# endif