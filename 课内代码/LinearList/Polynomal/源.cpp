# include "Polynomal.hpp"
using namespace std;

int main() {
	string s = "------------------------------------------------------------------";
	Term t1(0, 1), t2(1, 2), t3(3, 5);
	Polynomal p1, p2, p3, p4, p5, p6;
	cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
	Polynomal p[6] = { p1, p2, p3, p4, p5, p6 };
	cout << p1 << endl << p2 << endl << p3 << endl << p4 << endl << p5 << endl << p6 << endl;
	cout << s << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			cout << p[i] + p[j] << endl;
			cout << p[i] * p[j] << endl << s << endl;
		}
	}

	return 0;
}