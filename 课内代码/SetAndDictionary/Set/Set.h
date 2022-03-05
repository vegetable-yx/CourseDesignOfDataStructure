# ifndef _SET_H_
# define _SET_H_
# include <iostream>

template <class T>
class Set {
public :
	virtual Set() = 0;
	virtual makeEmpty() = 0;
	virtual void addMember(const T x) = 0;
	virtual void delMember(const T x) = 0;
	virtual Set<T> intersectWith(const Set<T>& S) = 0;
	virtual Set<T> unionWith(const Set<T>& S) = 0;
	virtual Set<T> differenceFrom(const Set<T>& S) = 0;
	virtual bool Contains(const T x) = 0;
	virtual bool subSet(const Set<T>& S) = 0;
	virtual bool operator == (cosnt Set<T>& S) = 0;
};

# endif