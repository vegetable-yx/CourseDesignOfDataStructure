# define _CRT_SECURE_NO_WARNINGS
# ifndef _A_STRING_H_
# define _A_STRING_H_
# include <iostream>
# include<string>
# define defaultSize 128
using namespace std;

class AString {
private :
	char* ch;
	int curLength;
	int maxSize;
	void getNext(int*);
public :
	AString(int sz = defaultSize);
	AString(const char* init);
	AString(const AString& ob);
	~AString() { delete[] ch; }
	int Length() const { return curLength; }
	AString operator() (int pos, int len);
	int operator == (AString& ob) const { return strcmp(ch, ob.ch) == 0; }
	int operator != (AString& ob) const { return strcmp(ch, ob.ch) != 0; }
	int operator ! () const { return curLength == 0; }
	AString& operator = (const AString& ob);
	AString& operator += (const AString& ob);
	char& operator [] (int i);
	int Find(AString& pat, int k) const;
	int KMPFind(AString& pat, int k) const;
};

AString::AString(int sz) {
	maxSize = sz;
	ch = new char[maxSize + 1];
	if (ch == NULL) {
		cerr << "Allocation Error ! " << endl;
		exit(1);
	}
	curLength = 0;
	ch[0] = '\0';
}

AString::AString(const char* init) {
	int len = strlen(init);
	maxSize = (len > defaultSize ? len : defaultSize);
	ch = new char[maxSize + 1];
	if (ch == NULL) {
		cerr << "Allocation Error ! " << endl;
		exit(1);
	}
	curLength = len;
	strcpy(ch, init);
}

AString::AString(const AString& ob) {
	maxSize = ob.maxSize;
	ch = new char[maxSize + 1];
	if (ch == NULL) {
		cerr << "Allocation Error ! " << endl;
		exit(1);
	}
	curLength = ob.curLength;
	strcpy(ch, ob.ch);
}

AString AString::operator () (int pos, int len) {
	AString tem;
	if (pos < 0 || pos + len - 1 >= maxSize || len < 0) {
		tem.curLength = 0;
		tem[0] = '\0';
	}
	else {
		if (pos + len - 1 >= curLength) len = curLength - pos;
		tem.curLength = len;
		for (int i = 0, j = pos; i < len; i++, j++) tem.ch[i] = ch[j];
		tem.ch[len] = '\0';
	}
	return tem;
}

AString& AString::operator = (const AString& ob) {
	if (&ob != this) this->AString::AString(ob);
	else { 
		cerr << "字符串赋值出错 ！ " << endl; 
		exit(1);
	}
	return *this;
}

AString& AString::operator += (const AString& ob) {
	char* tem = ch;
	int n = curLength + ob.curLength;
	int m = (maxSize > n) ? maxSize : n;
	ch = new char[m];
	if (ch == NULL) {
		cerr << "Allocation Error ! " << endl;
		exit(1);
	}
	maxSize = m;
	curLength = n;
	strcpy(ch, tem);
	strcat(ch, ob.ch);
	delete[] tem;
	return *this;
}

char& AString::operator [] (int i) {
	if (i < 0 || i >= curLength) {
		cerr << "字符串下标越界 ！ " << endl;
		exit(1);
	}
	return ch[i];
}

int AString::Find(AString& pat, int k) const {
	for (int i = k, j; i <= curLength - pat.curLength; i++) {
		for (j = 0; j < pat.curLength; j++) if (ch[i + j] != pat.ch[j]) break;
		if (j == pat.curLength) return i;
	}
	return -1;
}

int AString::KMPFind(AString& pat, int k) const {
	int posP = 0, posT = k;
	int lP = pat.curLength, lT = curLength;
	int* next = new int[lT];
	pat.getNext(next);
	while (posP < lP && posT < lT) {
		if (posP == -1 || pat.ch[posP] == ch[posT]) posP++, posT++;
		else posP = next[posP];
	}
	if (posP < lP) return -1;
	else return posT - lP;
}

void AString::getNext(int* next) {
	int j = 0, k = -1, len = curLength;
	next[0] = -1;
	while (j < len - 1) {
		if (k == -1 || ch[j] == ch[k]) {
			++j, ++k;
			next[j] = k;
		}
		else k = next[k];
	}
}

# endif