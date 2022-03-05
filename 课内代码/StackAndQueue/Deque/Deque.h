# ifndef _DEQUE_H_
# define _DEQUE_H_
# include "..\SeqQueue\Queue.h"

template <class T>
class Deque : public Queue<T> {
public :
	virtual bool getHead(T& x) const = 0;
	virtual bool getTail(T& x) const = 0;
	virtual bool EnQueue(const T& x);
	virtual bool EnQueueHead(const T& x) = 0;
	virtual bool EnQueueTail(const T& x) = 0;
	virtual bool DeQueue(T& x);
	virtual bool DeQueueHead(T& x) = 0;
	virtual bool DeQueueTail(T& x) = 0;
};

template <class T>
bool Deque<T>::EnQueue(const T& x) {
	return EnQueueTail(x);
}

template <class T>
bool Deque<T>::DeQueue(T& x) {
	T tem;
	bool tag = DeQueueHead(tem);
	x = tem;
	return tag;
}


# endif