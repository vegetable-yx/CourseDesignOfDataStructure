# ifndef _HASH_TABLE_2_0_H_
# define _HASH_TABLE_2_0_H_
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
	int k = 0, odd = 0, j, save;
	while (info[i] == Deleted || info[i] == Activate && ht[i] != k1) {
		if (odd == 0) {
			k++;
			save = i;
			i = (i + 4 * k - 3) % TableSize;
			odd = 1;
		}
		else {
			i = (save - 2 * k + 1) % TableSize;
			odd = 0;
			if (i < 0) i = i + TableSize;
		}
	}
	return i;
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

int IsPrime(int n) {
	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0) return 0;
	return 1;
}

int NextPrime(int n) {
	if (n % 2 == 0) n++;
	for (; !IsPrime(n); n += 2);
	return n;
}

template <class E, class K>
bool HashTable<E, K>::Insert(const E& e1) {
	K k1 = e1;
	int i = FindPos(k1), j, k;
	if (info[i] == Activate) return false;
	ht[i] = e1;
	info[i] = Activate;
	if (++CurrentSize < TableSize / 2) return true;
	E* OldHt = ht;
	KindOfStatus* OldInfo = info;
	int OldTableSize = TableSize;
	CurrentSize = 0;
	TableSize = NextPrime(2 * OldTableSize);
	divitor = TableSize;
	ht = new E[TableSize];
	if (ht == NULL) {
		cerr << "´æ´¢·ÖÅäÊ§°Ü£¡" << endl;
		return false;
	}
	info = new KindOfStatus[TableSize];
	if (info == NULL) {
		cerr << "´æ´¢·ÖÅäÊ§°Ü£¡" << endl;
		return false;
	}
	for (j = 0; j < TableSize; j++) info[j] = Empty;
	for (j = 0; j < TableSize; j++)
		if (OldInfo[j] == Activate)  Insert(OldHt[j]);
	delete[]OldHt;
	delete[]OldInfo;
	return true;
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