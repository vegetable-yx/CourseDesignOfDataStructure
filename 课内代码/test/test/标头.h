# ifndef _LIST_H_
# define _LIST_H_
# include <iostream>

struct ListNode { //嵌套链表结点类
public:
	int data;
	ListNode* link;
	ListNode(int x = 0, ListNode* p = NULL) : data(x), link(p) {}
};

class List {
public :
	List() :first(NULL), last(NULL) {}
	int Insert(const int x, int i);
private:
	ListNode* first, * last;
};

# endif