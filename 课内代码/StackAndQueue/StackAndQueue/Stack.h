# ifndef _STACK_H_
# define _STACK_H_

template <class T>
class Stack {
public:
	Stack() {};
	virtual void Push(const T& x) = 0;
	virtual bool Pop(T& x) = 0;
	virtual bool getTop(T& x) const = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;
	virtual int getSize() const = 0;
};

#endif