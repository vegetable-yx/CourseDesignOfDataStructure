# include <iostream>
# include "LinkedSet.h"
using namespace std;

int main() {
	int len = 20;
	LinkedSet<int> a, b, c, d, e;
	for (int i = 0; i < 9; i++) {
		a.addMember(i);
		b.addMember(i + 7);
	}
	cout << a.Contains(5) << endl;
	c = a + b, d = a * b, e = a - b;
	bool f = a.delMember(5);
	cout << a.Contains(5) << endl;
	cout << a << b << c << d << e << f << endl;
	int x = 0;
	a.Max(x);
	cout << x << endl;
	a.Min(x);
	cout << x << endl;


	return 0;
}