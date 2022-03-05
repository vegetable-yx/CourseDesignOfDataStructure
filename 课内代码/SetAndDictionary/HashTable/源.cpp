# include "HashTable.h"
using namespace std;

int main() {
	HashTable<int, int> H(11, 12);
	//cout << H << endl;

	for (int i = 0; i < 12; i++) {
		int t = i;
		H.Insert(t);
	}
	int i = 3, num;
	H.Remove(i, num);
	i = 13;
	H.Insert(i);
	cout << H << endl;

	return 0;
}