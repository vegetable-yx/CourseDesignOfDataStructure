# include "HashTable2_0.h"
using namespace std;

int main() {
	HashTable<int, int> H(11, 13);
	//cout << H << endl;

	int j = 6;
	H.Insert(j);
	cout << H << endl << endl << endl;

	j = 5;
	H.Insert(j);
	cout << H << endl << endl << endl;

	j = 7;
	H.Insert(j);
	cout << H << endl << endl << endl;

	j = 2;
	H.Insert(j);
	cout << H << endl << endl << endl;

	j = 17;
	H.Insert(j);
	cout << H << endl << endl << endl;

	j = 5;
	int n;
	H.Remove(j, n);
	cout << H << endl << endl << endl;

	j = 17;
	H.Insert(j);
	cout << H << endl << endl << endl;
	
	int i = 3, num;
	H.Remove(i, num);
	cout << H << endl;
	i = 13;
	H.Insert(i);
	cout << H << endl;

	return 0;
}