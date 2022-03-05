# include "标头.h"

using namespace std;


int List::Insert(const int x, const int i) {
	//在链表第 i 个结点处插入新元素 x
	ListNode* p = first; int k = 0;
	while (p != NULL && k < i - 1)
	{
		p = p->link; k++;
	} //找第i-1个结点
	if (p == NULL && first != NULL) {
		cout << "无效的插入位置!\n";
		return 0;
	}
	ListNode* newnode = new ListNode(x, NULL);
	//创建新结点,其数据为x,指针为0
	if (first == NULL || i == 0) { //插在表前
		newnode->link = first;
		if (first == NULL) last = newnode;
		first = newnode;
	}
	else { //插在表中或末尾
		newnode->link = p->link;
		if (p->link == NULL) last = newnode; p->link = newnode;
	}
	return 1;
}