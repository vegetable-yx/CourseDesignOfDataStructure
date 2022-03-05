# include <iostream>
# include "bitSet.h"
using namespace std;

int main() {
	int len = 20;
	bitSet<int> a(len), b(len), c(len), d(len), e(len), f(len);
	for (int i = 0; i < 9; i++) {
		a.addMember(i);
		b.addMember(i + 7);
	}
	cout << a.Contains(5) << endl;
	c = a + b,  d = a * b, e = a - b;
	f = a.delMember(5);
	cout << a.Contains(5) << endl;
	cout << a << b << c << d << e << f;


	return 0;
}