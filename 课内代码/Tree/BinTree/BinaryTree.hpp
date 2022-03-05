# ifndef _BINARY_TREE_H_
# define _BINARY_TREE_H_
# include <iostream>
# include "..\..\StackAndQueue\LinkedStack\LinkedStack.hpp"
# include "..\..\StackAndQueue\LinkedQueue\LinkedQueue.hpp"
using namespace std;

template <class T>
struct BinTreeNode {
	T data;
	BinTreeNode<T>* leftchild, * rightchild;
	BinTreeNode() : leftchild(NULL), rightchild(NULL) {}
	BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL) : data(x), leftchild(l), rightchild(r) {}
};

template <class T>
class BinaryTree {
public:
	BinaryTree() : root(NULL) {}
	BinaryTree(T value) : RefValue(value), root(NULL) {}
	BinaryTree(const BinaryTree<T>& s);
	~BinaryTree() { destroy(root); }
	bool IsEmpty() { return root == NULL; }
	BinTreeNode<T>* Parent(BinTreeNode<T>* current) { return (root == NULL || root == current ? NULL : Parent(root, current)); }
	BinTreeNode<T>* LeftChild(BinTreeNode<T>* current) { return current == NULL ? NULL : current->leftchild; }
	BinTreeNode<T>* RightChild(BinTreeNode<T>* current) { return current == NULL ? NULL : current->rightchild; }
	int Height() { return Height(root); }
	int Size() { return Size(root); }
	BinTreeNode<T>* getRoot() const { return root; }
	void preOrder(void (*visit) (BinTreeNode<T>* p)) { preOrder(root, visit); }
	void inOrder(void (*visit) (BinTreeNode<T>* p)) { inOrdert(root, visit); }
	void postOrder(void (*visit) (BinTreeNode<T>* p)) { postOrder(root, visit); }
	void PrintBTree(BinTreeNode<T>* BT);
	void levelOrder(void (*vist) (BinTreeNode<T>* p));
	BinTreeNode<T>* create(T* VLR, T* LVR, int n);
	//int Insert(const T item);
	//BinTreeNode<T>* Find(T item) const;
protected :
	BinTreeNode<T>* root;
	T RefValue;
	void CreateBinTree(istream& in, BinTreeNode<T>*& subTree);
	//bool Insert(BinTreeNode<T>*& subTree, const T& x);
	void destroy(BinTreeNode<T>*& subTree);
	bool Find(BinTreeNode<T>* subTree, const T& x) const;
	BinTreeNode<T>* Copy(BinTreeNode<T>* originnode);
	int Height(BinTreeNode<T>* subTree) const;
	int Size(BinTreeNode<T>*) const;
	BinTreeNode<T>* Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current);
	//BinTreeNode<T>* Find(BinTreeNode<T>* subTree, const T& x) const;
	void Traverse(BinTreeNode<T>* subTree, ostream& os);
	void preOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p));
	void inOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p));
	void postOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p));
	friend istream& operator >> (istream& in, BinaryTree<T>& Tree) {
		Tree.CreateBinTree(in, Tree.root);
		return in;
	}
	friend ostream& operator << (ostream& os, BinaryTree<T>& Tree) {
		os << "二叉树的前序遍历 ： " << endl;
		Tree.Traverse(Tree.getRoot(), os);
		return os;
	}
};

template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T>* &subTree) {
	if (subTree != NULL) {
		destroy(subTree->leftchild);
		destroy(subTree->rightchild);
		delete subTree;
	}
}

template <class T>
BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) {
	if (subTree == NULL) return NULL;
	if (subTree->leftChild == current || subTree->rightchild == current) return subTree;
	BinTreeNode<T>* p;
	if ((p = Parent(subTree->rightchild, current)) != NULL) return p;
	else return Parent(subTree->leftchild, current);
}

template <class T>
void BinaryTree<T>::Traverse(BinTreeNode<T>* subTree, ostream& os) {
	if (subTree != NULL) {
		os << subTree->data << " ";
		Traverse(subTree->leftchild, os);
		Traverse(subTree->rightchild, os);
	}
}

template <class T>
void BinaryTree<T>::CreateBinTree(istream& in, BinTreeNode<T>* &BT) {
	LinkedStack<BinTreeNode<T>*> s;
	BT = NULL;
	BinTreeNode<T>* p, * t;
	int k;
	char ch;
	in >> ch;
	while (ch != RefValue) {
		switch (ch) {
		case '(' :
			s.Push(p);
			k = 1; break;
		case ')' :
			s.Pop(t);
			break;
		case ',' :
			k = 2;
			break;
		default :
			p = new BinTreeNode<T>(ch);
			if (BT == NULL) BT = p;
			else if (k == 1) {
				s.getTop(t);
				t->leftchild = p;
			}
			else {
				s.getTop(t);
				t->rightchild = p;
			}
		}
		in >> ch;
	}
}

template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		inOrder(subTree->leftchild, visit);
		visit(subTree);
		inOrder(subTree->rightchild, visit);
	}
}

template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		visit(subTree);
		preOrder(subTree->leftchild);
		preOrder(subTree->rightchild);
	}
}

template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		postOrder(subTree->leftchild);
		postOrder(subTree->rightchild);
		visit(subTree);
	}
}

template <class T>
int BinaryTree<T>::Size(BinTreeNode<T>* subTree) const {
	if (subTree == NULL) return 0;
	else return 1 + Size(subTree->leftchild) + Size(subTree->rightchild);
}

template <class T>
int BinaryTree<T>::Height(BinTreeNode<T>* subTree) const {
	if (subTree == NULL) return 0;
	else {
		int LHeight = Height(subTree->leftchild);
		int RHeight = Height(subTree->rightchild);
		return LHeight < RHeight ? RHeight + 1 : LHeight + 1;
	}
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& s) {
	root = Copy(s.root);
}

template <class T>
BinTreeNode<T>* BinaryTree<T>::Copy(BinTreeNode<T>* orignode) {
	if (orignode == NULL) return NULL;
	BinTreeNode<T>* tem = new BinTreeNode<T>;
	tem->data = orignode->data;
	tem->leftchild = Copy(orignode->leftchild);
	tem->rightchild = Copy(orignode->rightchild);
	return tem;
}

template <class T>
int operator == (const BinaryTree<T>& s, const BinaryTree<T>& t) {
	return equal(s.root, t.root);
}

template <class T>
bool equal(BinTreeNode<T>* a, BinTreeNode<T>* b) {
	if (a == NULL && b == NULL) return true;
	if (a != NULL && b != NULL && a->data == b->data && equal(a->leftchild, b->leftchild) && equal(a->rightchild, b->rightchild)) return true;
	else return false;
}

//template <class T>
//void BinaryTree<T>::CreateBinTree(istream& in, BinTreeNode<T>*& subTree) {
//	T item;
//	if (!in.eof()) {
//		in >> item;
//		if (item != RefValue) {
//			subTree = new BinTreeNode<T>(item);
//			if (subTree == NULL) {
//				cerr << "Memory Allocating Error ！ " << endl;
//				exit(1);
//			}
//			CreateBinTree(in, subTree->leftchild);
//			CreateBinTree(in, subTree->rightchild);
//		}
//		else subTree = NULL;
//	}
//}

template <class T>
void BinaryTree<T>::PrintBTree(BinTreeNode<T>* BT) {
	if (BT != NULL) {
		cout << BT->data;
		if (BT->leftchild != NULL || BT->rightchild != NULL) {
			cout << '(';
			PrintBTree(BT->leftchild);
			cout << ',';
			if (BT->rightchild != NULL) PrintBTree(BT->rightchild);
			cout << ')';
		}
	}
}

template <class T>
void BinaryTree<T>::levelOrder(void (*visit) (BinTreeNode<T>* p)) {
	LinkedQueue<BinTreeNode<T>*> Q;
	BinTreeNode<T>* p = root;
	Q.EnQueue(p);
	while (!Q.IsEmpty()) {
		Q.DeQueue(p);
		visit(p);
		if (p->leftchild != NULL) Q.EnQueue(p->leftchild);
		if (p->rightchild != NULL) Q.EnQueue(p->rightchild);
	}
}

template <class T>
BinTreeNode<T>* BinaryTree<T>::create(T* LVR, T* VLR, int n) {
	if (n == 0) return NULL;
	int k = 0;
	while (LVR[0] != VLR[k]) ++k;
	BinTreeNode<T>* t = new BinTreeNode<T>(LVR[0]);
	t->leftchild = create(LVR + 1, VLR, k);
	t->rightchild = create(LVR + k + 1, VLR + k + 1, n - k - 1);
	return t;
}

# endif