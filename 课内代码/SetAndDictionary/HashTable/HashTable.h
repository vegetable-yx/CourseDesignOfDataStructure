# ifndef _HASH_TABLE_H_
# define _HASH_TABLE_H_
# include <iostream>
using namespace std;

const int DefaultSize = 100;
enum KindOfStatus { Activate, Empty, Deleted };

template <class E, class K>
class HashTable {
public :
	HashTable(const int d, int sz = DefaultSize);
	~HashTable() { delete[]ht, delete[]info; }
	HashTable<E, K>& operator = (const HashTable<E, K>& ht2);
	bool Search(const K k1, E& e1) const;
	bool Insert(const E& e1);
	bool Remove(const K k1, E& e1);
	void makeEmpty();
	friend ostream& operator << (ostream& out, const HashTable<E, K>& HT) {
		for (int i = 0; i < HT.TableSize; i++) {
			out << HT.ht[i] << '\t';
		}
		out << endl;
		for (int i = 0; i < HT.TableSize; i++) {
			out << HT.info[i] << '\t';
		}
		return out;
	}
private :
	int divitor;
	int CurrentSize, TableSize;
	E* ht;
	KindOfStatus* info;
	int FindPos(const K k1) const;
	int operator == (E& e1) { return *this == e1; }
	int operator != (E& e1) { return *this != e1; }
};

template <class E, class K>
HashTable<E, K>::HashTable(const int d, int sz) {
	divitor = d;
	TableSize = sz;
	CurrentSize = 0;
	ht = new E[TableSize];
	info = new KindOfStatus[TableSize];
	for (int i = 0; i < TableSize; i++) info[i] = Empty;
}

template <class E, class K>
int HashTable<E, K>::FindPos(const K k1) const {
	int i = k1 % divitor;
	int j = i;
	do {
		if (info[j] == Empty || info[j] == Activate && ht[j] == k1) return j;
		j = (j + 1) % TableSize;
	} while (j != i);
	return j;
}

template <class E, class K>
bool HashTable<E, K>::Search(const K k1, E& e1) const {
	int i = FindPos(k1);
	if (info[i] != Activate || ht[i] != k1) return false;
	e1 = ht[i];
	return true;
}

template <class E, class K>
void HashTable<E, K>::makeEmpty() {
	for (int i = 0; i < TableSize; i++) info[i] = Empty;
	CurrentSize = 0;
}

template <class E, class K>
HashTable<E, K>& HashTable<E, K>::operator = (const HashTable<E, K>& ht2) {
	if (this != &ht2) {
		delete[]ht;
		delete[]info;
		TableSize = ht2.TableSize;
		ht = new E[TableSize];
		info = new KindOfStatus[TableSize];
		for (int i = 0; i < TableSize; i++) {
			ht[i] = ht2.ht[i];
			info[i] = ht2.info[i];
		}
		CurrentSize = ht2.CurrentSize;
	}
	return *this;
}

template <class E, class K>
bool HashTable<E, K>::Insert(const E& e1) {
	K k1 = e1;
	int i = FindPos(k1);
	if (info[i] != Activate) {
		ht[i] = e1;
		info[i] = Activate;
		CurrentSize++;
		return true;
	}
	if (info[i] == Activate && ht[i] == e1) {
		cout << "表中已有此元素，不能插入！" << endl;
		return false;
	}
	cout << "表已满，不能插入！" << endl;
}

template <class E, class K>
bool HashTable<E, K>::Remove(const K k1, E& e1) {
	int i = FindPos(k1);
	if (info[i] == Activate) {
		info[i] = Deleted;
		CurrentSize--;
		return true;
	}
	return false;
}




# endif