# ifndef _SEQ_STACK_H_
# define _SEQ_STACK_H_
# include <assert.h>
#include <iostream>
# include "Stack.h"
using namespace std;

const int stackIncreament = 2; // ջ���ʱ��չ�ռ������

template <class T>
class SeqStack : public Stack<T> {
public:
	SeqStack(int sz = 50);
	~SeqStack() { delete[] elements; }
	void Push(const T& x);
	bool Pop(T& x);
	bool getTop(T& x) const;
	bool IsEmpty() const { return top == -1; }
	bool IsFull() const { return top == maxSize - 1; }
	int getSize() const { return top + 1; }
	void MakeEmpty() {
		top = -1;
		~SeqStack();
	}
private:
	T* elements;
	int top;
	int maxSize;
	void overflowProcess(); // ջ���������
	friend ostream& operator << (ostream& os, const SeqStack<T>& s) { // ��������������Ԫ���������ǳ�Ա��������ֻ��������ʵ�֣����ܷŵ�����ʵ��
		os << "top = " << s.top << endl;
		for (int i = 0; i <= s.top; i++) os << "#" << i << " : " << s.elements[i] << endl;
		return os;
	}
};

template <class T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz) {
	elements = new T[maxSize];
	assert(elements != NULL); //���Ի���
}

template <class T>
void SeqStack<T>::overflowProcess() {
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == NULL) {
		cerr << "�洢�ڴ����ʧ�ܣ� " << endl;
		exit(1);
	}
	for (int i = 0; i <= top; i++) newArray[i] = elements[i];
	maxSize = maxSize + stackIncreament;
	delete[] elements;
	elements = newArray;
}

template <class T>
void SeqStack<T>::Push(const T& x) {
	if (IsFull()) overflowProcess();
	elements[++top] = x;
}

template <class T>
bool SeqStack<T>::Pop(T& x) {
	if (IsEmpty()) return false;
	x = elements[top--];
	return true;
}

template <class T>
bool SeqStack<T>::getTop(T& x) const {
	if (IsEmpty()) return false;
	x = elements[top];
	return true;
}

#endif