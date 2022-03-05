#include <iostream>
# include <stdlib.h>
#include "LinearList.h"
using namespace std;
const int defaultSize = 100;

template<class T>
class SeqList : public LinearList<T> {
protected:
	T* data;
	int maxSize;
	int last;
	void reSize(int newSize);
public:
	SeqList(int sz = defaultSize);
	SeqList(SeqList<T>& L);
	~SeqList(){ delete[] data; }
	int Size() const { return maxSize; }
	int Length() const { return last + 1; }
	int Search(T& x) const;
	int Locate(int i) const;
	T* getData(int i) const { return (i > 0 && i <= last + 1) ? &data[i - 1] : NULL; }
	void setData(int i, T& x) { if (i > 0 && i <= last + 1) data[i - 1] = x; }
	bool Insert(int i, T& x);
	bool Remove(int i, T& x);
	bool IsEmpty() const { return (last == -1) ? true : false; }
	bool IsFull() const { return (last == maxSize - 1) ? true : false; }
	void Sort();
	void input();
	void output();
	SeqList<T> operator=(SeqList<T>& L);
};

template<class T>
SeqList<T>::SeqList(int sz) {
	if (sz > 0) {
		maxSize = sz;
		last = -1;
		data = new T[maxSize];
		if (data == NULL) {
			cerr << "存储分配错误 ！ " << endl;
			exit(1);
		}
	}
}

	template<class T>
	SeqList<T>::SeqList(SeqList<T>& L) {
		maxSize = L.Size();
		last = L.Length() - 1;
		data = new T[maxSize];
		if (data == NULL) {
			cerr << "存储分配错误 ！ " << endl;
			exit(1);
		}
		for (int i = 0; i <= last; i++) data[i] = L.getData();
	}

	template<class T>
	void SeqList<T>::reSize(int newSize) {
		if (newSize < 0) {
			cerr << "无效的数组大小 ！ " << endl;
			return;
		}
		if (newSize != maxSize) {
			T* newArray = new T[newSize];
			if (newArray == NULL) {
				cerr << "存储分配错误 ！" << endl;
				exit(1);
			}
			int n = last + 1;
			T* srcptr = data;
			T* desptr = newArray;
			while (n--) *desptr++ = *srcptr++;
			delete[] data;
			data = newArray;
			maxSize = newSize;
		}
	}

	template<class T>
	int SeqList<T>::Search(T& x) const {
		for (int i = 0; i <= last; i++) 
			if (data[i] == x) return i + 1;
		return 0;
	}

	template<class T>
	int SeqList<T>::Locate(int i) const {
		if (i >= 1 && i <= last + 1) return i;
		else return 0;
	}

	template<class T>
	bool SeqList<T>::Insert(int i, T& x) {
		if (last == maxSize - 1) return false;
		if (i < 0 || i > last + 1) return false;
		for (int j = last; j >= i; j--) data[j + 1] = data[j];
		data[i] = x;
		++last;
		return true;
	}

	template<class T>
	bool SeqList<T>::Remove(int i, T& x) {
		if (last == -1) return false;
		if (i < 1 || i > last + 1) return false;
		x = data[i - 1];
		for (int j = i; j <= last; j++) data[j - 1] = data[j];
		last--;
		return true;
	}

	template<class T>
	void SeqList<T>::Sort() {
		for (int i = 0; i < last; i++) {
			for (int j = 0; j < last; j++) {
				if (data[j] > data[j + 1]) {
					auto tem = data[j];
					data[j] = data[j + 1];
					data[j + 1] = tem;
				}
			}
		}
	}

	template<class T>
	void SeqList<T>::input() {
		cout << "开始建立顺序表，请输入元素个数： " << endl;
		while (true) {
			cin >> last;
			last--;
			if (last <= maxSize - 1) break;
			cout << "元素个数不得超过 " << maxSize - 1 << "：";
		}
		cout << "请分别输入元素： " << endl;
		for (int i = 0; i <= last; i++) cin >> data[i];
	}

	template<class T>
	void SeqList<T>::output() {
		cout << "顺序表当前元素最后位置为： " << last + 1 << endl;
		for (int i = 0; i <= last; i++) cout << "#" << i + 1 << "： " << data[i] << endl;
	}

	template<class T>
	SeqList<T> SeqList<T>::operator=(SeqList<T>& L) {
		SeqList(L);
	}