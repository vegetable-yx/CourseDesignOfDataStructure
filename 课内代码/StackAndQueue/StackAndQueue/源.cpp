# include "SeqStack.hpp"
using namespace std;

int main() {
	SeqStack<int> ss(5);
	cout << ss.IsEmpty() << ss.IsFull() << endl;
	for (int i = 0; i < 10; i++) ss.Push(i);
	cout << ss.IsEmpty() << ss.IsFull() << endl;
	int x;
	ss.getTop(x);
	cout << x << ss.getSize() << endl;
	cout << ss << endl;
	for (int i = 0; i < 10; i++) {
		int y;
		ss.Pop(y);
		cout << y << "  ";
	}
	cout << endl;
	cout << ss.IsEmpty() << ss.IsFull() << endl;
	cout << ss << endl;

	return 0;
}