# include "SeqQueue.hpp"
using namespace std;

int main() {
	SeqQueue<int> q;
	cout << q.IsEmpty() << q.IsFull() << q.getSize() << endl;
	for (int i = 0; i < 10; i++) q.EnQueue(i);
	cout << q.IsEmpty() << q.IsFull() << q.getSize() << endl;
	cout << q << endl;
	for (int i = 0; i < 10; i++) {
		int x;
		if (q.getFront(x)) cout << x << "  ";
		if (q.DeQueue(x)) cout << x << "  " << endl;
		cout << q.IsEmpty() << q.IsFull() << q.getSize() << endl;
	}
	cout << q.IsEmpty() << q.IsFull() << q.getSize() << endl;

	return 0;
}