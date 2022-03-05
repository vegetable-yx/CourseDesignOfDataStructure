# include <iostream>
# include <time.h>
#include "LinkedDeque.h"
using namespace std;

int main() {
	LinkedDeque<int> d;
	srand(time(NULL));
	for (int i = 0; i < 8; i++) {
		int r = rand();
		cout << r << ", ";
		d.EnQueueHead(r);
	}
	cout << endl;
	cout << d << endl;
	int x;
	d.DeQueueTail(x);
	cout << x << endl;
	d.DeQueueTail(x);
	cout << x << endl;
	d.DeQueueTail(x);
	cout << x << endl;

	cout << d << endl;


	return 0;
}