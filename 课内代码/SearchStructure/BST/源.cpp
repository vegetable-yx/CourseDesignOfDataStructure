# include "BST.h"
using namespace std;

struct D {
	string d;
	int key;
	D(string dd = "", int k = 0) :d(dd), key(k) {}
	friend istream& operator >> (istream& in, D& x) {
		in >> x.d;
		in >> x.key;
		return in;
	}
	bool friend operator < (const D& x1, const D& x2) { return x1.key < x2.key; }
	bool friend operator > (const D& x1, const D& x2) { return x1.key > x2.key; }
};

int main() {
	D d1("do", 1), d2("if", 2), d3("to", 3);
	BST<D, int>B(-1);
	int p[4] = { 0,50,10,5 };
	int q[4] = { 15,10,5,5 };
	D a[4] = { d1, d2, d3 };
	B.OpticBST(p, q, a, 3);


	return 0;
}