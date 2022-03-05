# ifndef _BST_H_
# define _BST_H_
# include <iostream>
using namespace std;

template <class E, class K>
struct BSTNode {
	E data;
	BSTNode<E, K>* left, * right;
	BSTNode() :left(NULL), right(NULL) {}
	BSTNode(const E d, BSTNode<E, K>* L = NULL, BSTNode<E, K>* R = NULL) : data(d), left(L), right(R) {}
	~BSTNode() {}
	void setData(E d) { data = d; }
	E getData() { return data; }
	bool operator < (const E& x) { return data.key < x.key; }
	bool operator > (const E& x) { return data.key > x.key; }
	bool operator ==(const E& x) { return data.key == x.key; }
};

template <class E, class K>
class BST {
public :
	BST() :root(NULL) {}
	BST(K value);
	~BST() {}
	bool Search(const K x) const { return Search(x, root) != NULL; }
	BST<E, K>& operator = (const BST<E, K>& R);
	void makeEmpty() {
		makeEmpty(root);
		root = NULL;
	}
	void PrintTree() const { PrintTree(root); }
	E Min() { return Min(root)->data; }
	E Max() { return Max(root)->data; }
	bool Insert(const E& e1) { return Insert(e1, root); }
	bool Remove(const K x) { return Remove(x, root); }
	void OpticBST(int p[], int q[], E a[], int n);
protected:
	BSTNode<E, K>* root;
	K RefValue;
	BSTNode<E, K>* Search(const K x, BSTNode<E, K>* ptr);
	void makeEmpty(BSTNode<E, K>*& ptr);
	void PrintTree(BSTNode<E, K>* ptr) const;
	BSTNode<E, K>* Copy(const BSTNode<E, K>* ptr);
	//BSTNode<E, K>* Min(BSTNode<E, K>* ptr) const;
	//BSTNode<E, K>* Min(BSTNode<E, K>* ptr) const;
	bool Insert(const E& e1, BSTNode<E, K>*& ptr);
	bool Remove(const K x, BSTNode<E, K>*& ptr);
};

template <class E, class K>
BSTNode<E, K>* BST<E, K>::Search(const K x, BSTNode<E, K>* ptr) {
	if (ptr == NULL) return NULL;
	if (x < ptr->data) return Search(x, ptr->left);
	else if (x > ptr->data) return Search(x, ptr->right);
	else return ptr;
}

template <class E, class K>
bool BST<E, K>::Insert(const E& e1, BSTNode<E, K>*& ptr) {
	if (ptr == NULL) {
		ptr = new BSTNode<E, K>(e1);
		if (ptr == NULL) {
			cerr << "Out of space" << endl;
			exit(1);
		}
		return true;
	}
	else if (e1 < ptr->data) Insert(e1, ptr->left);
	else if (e1 > ptr->data) Insert(e1, ptr->right);
	else return false;
}

template <class E, class K>
BST<E, K>::BST(K value) {
	E x;
	root = NULL;
	RefValue = value;
	cin >> x;
	while (x.key != RefValue) {
		Insert(x, root);
		cin >> x;
	}
}

template <class E, class K>
bool BST<E, K>::Remove(const K x, BSTNode<E, K>*& ptr) {
	BSTNode<E, K>* temp;
	if (ptr == NULL) return false;
	if (x < ptr->data) Remove(x, ptr->left);
	else if (x > ptr->data) Remove(x, ptr->right);
	else if (ptr->left != NULL && ptr->right != NULL) {
		temp = ptr->right;
		while (temp->left != NULL) temp = temp->left;
		ptr->data = temp->data;
		Remove(ptr->data, temp);
	}
	else {
		temp = ptr;
		if (ptr->left == NULL) ptr = ptr->right;
		else ptr = ptr->left;
		delete temp;
		return true;
	}
	return false;
}

template <class E, class K>
void BST<E, K>::OpticBST(int p[], int q[], E a[], int n) {
	int R[10][10], C[10][10], W[10][10];
	int l, j, k, m, min, u;
	for (int i = 0; i < n; i++) {
		W[i][i] = q[i];
		C[i][i] = R[i][i] = 0;
		W[i][i + 1] = W[i][i] + p[i + 1] + q[i + 1];
		R[i][i + 1] = i + 1;
		C[i][i + 1] = W[i][i + 1];
	}
	W[n][n] = q[n];
	R[n][n] = C[n][n] = 0;
	for (m = 2; m <= n; m++) {
		for (int i = 0; i <= n - m; i++) {
			j = i + m;
			W[i][j] = W[i][j - 1] + p[j] + q[j];
			min = C[i + 1][j];
			u = i + 1;
			for (k = i + 2; k <= j; k++)
				if (C[i][k - 1] + C[k][j] < min) {
					min = C[i][k - 1] + C[k][j];
					u = k;
				}
			C[i][j] = W[i][j] + min;
			R[i][j] = u;
		}
	}
}

# endif