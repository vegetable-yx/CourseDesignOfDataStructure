# include <iostream>
# include "../BST/BST.h"
# include "../../StackAndQueue/LinkedStack/LinkedStack.hpp"
using namespace std;

template <class E, class K>
struct AVLNode : public BSTNode<E, K> {
	int bf;
	AVLNode() :AVLNode<E, K>::left(NULL), AVLNode<E, K>::right(NULL), bf(0) {}
	AVLNode(E d, AVLNode<E, K>* l = NULL, AVLNode<E, K>* r = NULL) :AVLNode<E, K>::data(d), AVLNode<E, K>::left(l), AVLNode<E, K>::right(r), bf(0) {}
};

template <class E, class K>
class AVLTree : public BST<E, K> {
public :
	AVLTree() : AVLTree<E, K>::root(NULL) {}
	AVLTree(K Ref) {
		AVLTree<E, K>::RefValue = Ref;
		AVLTree<E, K>::root = NULL;
	}
	bool Insert(E& e1) { return Insert(this->root, e1); }
	bool Remove(K x, E& e1) { return Remove(this->root, x, e1); }
	void Traverse(AVLNode<E, K>* ptr, ostream& out) const ;
	friend istream& operator >> (istream& in, AVLTree<E, K>& Tree) {
		E item;
		cout << "Construct AVLTree : " << endl;
		cout << "Input Data : " << endl;
		in >> item;
		while (item.key != Tree.RefValue) {
			Tree.Insert(item);
			cout << "Input Data : " << endl;
			in >> item;
		}
		return in;
	}
	friend ostream& operator << (ostream& out, const AVLTree<E, K>& Tree) {
		out << "Inorder traversal of AVLTree : " << endl;
		Tree.Traverse(Tree.root, out);
		out << endl;
		return out;
	}
	int Height() const;
protected :
	AVLNode<E, K>* Search(K x, AVLNode<E, K>*& par) const;
	bool Insert(AVLNode<E, K>*& ptr, E& e1);
	bool Remove(AVLNode<E, K>*& ptr, K x, E& e1);
	void RotateL(AVLNode<E, K>*& ptr);
	void RotateR(AVLNode<E, K>*& ptr);
	void RotateLR(AVLNode<E, K>*& ptr);
	void RotateRL(AVLNode<E, K>*& ptr);
	int Height(AVLNode<E, K>* ptr) const;
};

template <class E, class K>
void AVLTree<E, K>::RotateL(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subL = ptr;
	ptr = subL->right;
	subL->right = ptr->left;
	ptr->left = subL;
	ptr->bf = subL->bf = 0;
}

template <class E, class K>
void AVLTree<E, K>::RotateR(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subR = ptr;
	ptr = subR->left;
	subR->left = ptr->right;
	ptr->right = subR;
	ptr->bf = subR->bf = 0;
}

template <class E, class K>
void AVLTree<E, K>::RotateLR(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subR = ptr, * subL = subR->left;
	ptr = subL->right;
	subL->right = ptr->left;
	ptr->left = subL;
	if (ptr->bf <= 0) subL->bf = 0;
	else subL->bf = -1;
	subR->left = ptr->right;
	ptr->right = subR;
	if (ptr->bf == -1) subR->bf = 1;
	else subR->bf = 0;
	ptr->bf = 0;
}

template <class E, class K>
void AVLTree<E, K>::RotateRL(AVLNode<E, K>*& ptr) {
	AVLNode<E, K>* subL = ptr, * subR = ptr->right;
	ptr = subR->left;
	subR->left = ptr->right;
	ptr->right = subR;
	if (ptr->bf >= 0) subR->bf = 0;
	else subR->bf = 1;
	subL->right = ptr->left;
	ptr->left = subL;
	if (ptr->bf == 1) subL->bf = -1;
	else subL->bf = 0;
	ptr->bf = 0;
}

template <class E, class K>
bool AVLTree<E, K>::Insert(AVLNode<E, K>*& ptr, E& e1) {
	AVLNode<E, K>* pr = NULL, * p = ptr, * q;
	int d;
	LinkedStack<AVLNode<E, K>*> st;
	while (p != NULL) {
		if (e1 == p->data) return false;
		pr = p;
		st.Push(pr);
		if (e1 < p->data) p = p->left;
		else p = p->right;
	}
	p = new AVLNode<E, K>(e1);
	if (p == NULL) {
		cerr << "´æ´¢¿Õ¼ä²»×ã£¡" << endl;
		exit(1);
	}
	if (pr == NULL) {
		ptr = p;
		return true;
	}
	if (e1 < pr->data) pr->left = p;
	else pr->right = p;
	while (!st.IsEmpty()) {
		st.Pop(pr);
		if (p == pr->data) pr->bf--;
		else pr->bf++;
		if (pr->bf == 0) break;
		if (pr->bf == 1 || pr->bf == -1) p = pr;
		else {
			d = (pr->bf < 0) ? -1 : 1;
			if (p->bf == d) {
				if (d == -1) RotateR(pr);
				else RotateL(pr);
			}
			else {
				if (d == -1) RotateLR(pr);
				else RotateRL(pr);
			}
			break;
		}
	}
	if (st.IsEmpty()) ptr = pr;
	else {
		st.getTop(q);
		if (q->data > pr->data) q->left = pr;
		else q->right = pr;
	}
	return true;
}

template <class E, class K>
void AVLTree<E, K>::Traverse(AVLNode<E, K>* ptr, ostream& out) const {
	if (ptr != NULL) {
		Traverse(ptr->left, out);
		out << ptr->data << "  ";
		Traverse(ptr->right, out);
	}
}

template <class E, class K>
bool AVLTree<E, K>::Remove(AVLNode<E, K>*& ptr, K x, E& e1) {
	AVLNode<E, K>* pr = NULL, * p = ptr, * q, * ppr;
	int d, dd = 0;
	LinkedStack<AVLNode<E, K>*> st;
	while (p != NULL) {
		if (x == p->data.key) break;
		pr = p;
		st.push(pr);
		if (x < p->data.key) p = p->left;
		else p = p->right;
	}
	if (p == NULL) return false;
	if (p->left != NULL && p->right != NULL) {
		pr = p;
		st.Push(pr);
		q = p->left;
		while (q->right != NULL) {
			pr = q;
			st.Push(pr);
			q = q->right;
		}
		p->data = q->data;
		p = q;
	}

	if (p->left != NULL) q = p->left;
	else q = p->right;
	if (pr == NULL) ptr = q;
	else {
		if (pr->left == p) pr->left = q;
		else pr->right = q;
		while (!st.IsEmpty()) {
			st.Pop(pr);
			if (pr->right == q) pr->bf--;
			else pr->bf++;
			if (!st.IsEmpty()) {
				st.getTop(ppr);
				dd = (ppr->left == pr) ? -1 : 1;
			}
			else dd = 0;
			if (pr->bf == 1 || pr->bf == -1) break;
			if (pr->bf != 0) {
				if (pr->bf < 0) {
					d = -1;
					q = pr->left;
				}
				else {
					d = 1;
					q = pr->right;
				}
				if (q->bf == 0) {
					if (d == -1) {
						RotateR(pr);
						pr->bf = 1;
						pr->left->bf = -1;
					}
					else {
						RotateL(pr);
						pr->bf = -1;
						pr->right->bf = 1;
					}
					break;
				}
				if (q->bf == d) {
					if (d == -1) RotateR(pr);
					else RotateL(pr);
				}
				else {
					if (d == -1) RotateLR(pr);
					else RotateRL(pr);
				}
				if (dd = -1) ppr->left = pr;
				else if (dd == 1) ppr->right = pr;
			}
			q = pr;
		}
		if (st.IsEmpty()) ptr = pr;
	}
	delete p;
	return true;
}