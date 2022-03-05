# ifndef _TREE_NEW_H_
# define _TREE_NEW_H_
# include <iostream>
using namespace std;

template <class T>
struct TreeNode {
	T data;
	TreeNode<T>* firstChild, nextSibling;
	TreeNode(T value = 0, TreeNode<T>* fc = NULL, TreeNode<T>* ns = NULL) : data(value), firstChild(fc), nextSibling(ns) {}
};

template <class T>
class Tree {
private :
	TreeNode<T>* root, * current;
	bool Find(TreeNode<T>* p, T value);
	void RemoveSubTree(TreeNode<T>* p);
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);
public :
	Tree() { root = current = NULL; }
	bool Root();
	bool IsEmpty() { return root == NULL; }
	bool FirstChild();
	bool NextSibling();
	bool Parent();
	bool Find(T target);
};

template <class T>
bool Tree<T>::Root() {
	if (root == NULL) {
		current = NULL;
		return false;
	}
	else {
		current = root;
		return true;
	}
}

template <class T>
bool Tree<T>::Parent() {
	TreeNode<T>* p = current;
	if (current == NULL || current == root) {
		current = NULL;
		return false;
	}
	return FindParent(root, p);
}

template <class T>
bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p) {
	TreeNode<T>* q = t->firstChild;
	bool succ;
	while (q != NULL && q != p) {
		if (succ = FindParent(q, p)) return succ;
		q = q->nextSibling;
	}
	if (q != NULL && q == p) {
		current = t;
		return true;
	}
	else {
		current = NULL;
		return false;
	}
}

template <class T>
bool Tree<T>::FirstChild() {
	if (current != NULL && current->firstChild != NULL) {
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return false;
}

template <class T>
bool Tree<T>::NextSibling() {
	if (current != NULL && current != NULL) {
		current = current->nextSibling;
		return true;
	}
	current = NULL;
	return false;
}

template <class T>
bool Tree<T>::Find(TreeNode<T>* p, T value) {
	if (IsEmpty()) return false;
	return Find(root, value);
}

template <class T>
bool Tree<T>::Find(TreeNode<T>* p, T value) {
	bool re = false;
	if (p->data == value) {
		re = true;
		current = p;
	}
	else {
		TreeNode<T>* q = p->firstChild;
		while (q != NULL && !(re = Find(q, value))) q = q->nextSibling;
	}
	return re;
}


# endif