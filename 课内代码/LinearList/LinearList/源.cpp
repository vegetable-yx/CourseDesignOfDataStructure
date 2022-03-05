#include "SeqList.hpp"
using namespace std;

int main() {
	SeqList<int> sl;
	sl.input();
	sl.output();
	sl.Sort();
	for (int i = 1; i <= sl.Length(); i++) cout << *(sl.getData(i)) << " ";
	int a;
	sl.Remove(2, a);
	cout << a << endl;
	sl.output();
	int x5 = 5, x4 = 4;
	cout << sl.Search(x5) << "  " << sl.Search(x4) << endl;

	return 0;
}