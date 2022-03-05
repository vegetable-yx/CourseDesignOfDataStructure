# include "MinHeap.h"
# include <time.h>
using namespace std;

int main() {
	int arr[10];
	srand(time(NULL));
	for (int i = 0; i < 10; i++) arr[i] = rand() % 21;
	MinHeap<int, int>H(arr, 10);
	cout << H.IsEmpty() << H.IsFull() << endl;
	cout << H;
	int tem;
	H.RemoveMin(tem);
	cout << tem << endl;
	H.RemoveMin(tem);
	cout << tem << endl;
	cout << H;
	tem = 10;
	H.Insert(tem);
	cout << H;

	return 0;
}