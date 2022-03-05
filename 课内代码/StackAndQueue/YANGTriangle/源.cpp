# include <iostream>
# include "../LinkedQueue/LinkedQueue.hpp"
using namespace std;

void YANGTriangle(int n) {
	LinkedQueue<int> q;
	int one = 1;
	q.EnQueue(one), q.EnQueue(one);
	for (int i = 1; i < n; i++) {
		cout << endl;
		int left = 0, right = 0;
		q.EnQueue(left);
		for (int j = 0; j < i + 2; j++) {
			q.DeQueue(right);
			int num = left + right;
			q.EnQueue(num);
			left = right;
			if (j != i + 1) cout << right << "  ";
		}
	}
}

int main() {
	int n = 5;
	YANGTriangle(n);

	return 0;
}