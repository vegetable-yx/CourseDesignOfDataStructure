# include <time.h>
# include "PQueue.hpp"
using namespace std;

int main() {
	PQueue<int> pq;
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		int r = rand();
		cout << r << ", ";
		pq.Insert(r);
	}
	cout << endl;
	cout << pq << endl;
	int x;
	pq.RemoveMin(x);
	cout << x << endl;
	pq.RemoveMin(x);
	cout << x << endl;
	pq.RemoveMin(x);
	cout << x << endl;

	cout << pq << endl;


	return 0;
}