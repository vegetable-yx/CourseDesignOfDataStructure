#include "LinkedList.hpp"
using namespace std;

int main() {
	LinkedList<int> l;
	//l.output();
	//cout << l.IsEmpty() << endl;
	//l.input();
	//l.output();
	//cout << l.isFull() << endl;
	int x = 1;
	l.Insert(0, x);
	x = 2;
	l.Insert(0, x);
	l.output();
	

	return 0;
}