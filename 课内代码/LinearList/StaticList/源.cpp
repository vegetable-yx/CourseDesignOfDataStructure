# include "StaticList.h"
using namespace std;

int main() {
	StaticList<int> sl;
	sl.InitList();
	for (int i = 0; i < 10; ++i) sl.Append(i);
	sl.Insert(3, 30), sl.Insert(6, 60), sl.Insert(10, 100);
	cout << sl.Length() << endl;
	sl.Insert(0, 0);
	cout << sl.Length() << endl;
	cout << sl.IsEmpty() << endl << sl.Locate(5) << endl << sl.Search(60) << endl;
	sl.Remove(2), sl.Remove(6);
	cout << sl.Length();

	return 0;
}