# include "AString.h"
using namespace std;

int main() {
	char ch1[] = "abbabaa", ch2[] = "aba";
	AString a(ch1), b(ch2), c(a), d;
	cout << (a == b) << (a != c) << !b << !d << endl;
	cout << d.Length() << endl;
	d = c;
	d += b;
	for (int i = 0; i < d.Length(); i++) cout << d[i];
	cout << endl;
	AString e = d(3, 2);
	for (int i = 0; i < e.Length(); i++) cout << e[i];
	cout << endl;
	AString f("aaab");
	cout << a.Find(b, 0) << "  " << a.Find(c, 0) << "  " << a.Find(f, 1) << endl;
	cout << a.KMPFind(b, 0) << "  " << a.KMPFind(c, 0) << "  " << a.KMPFind(f, 1) << endl;


	return 0;
}