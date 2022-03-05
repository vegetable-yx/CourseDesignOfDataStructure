# include<iostream>
# include "sparseMatrix.hpp"
using namespace std;

int main() {
	SparseMatrix<int> a, b, c;
	cin >> a >> b;
	c = a.Add(b);
	cout << a << endl << b << endl << c << endl;
	a = a.Transpose(), b = b.FastTranspose();
	cout << a << endl << b << endl;
	cout << "------------------------------------" << endl;
	cin >> a >> b;
	c = a.Multiply(b);
	cout << c << endl;


	return 0;
}