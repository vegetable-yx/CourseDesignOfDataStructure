# include "��ͷ.h"

using namespace std;


int List::Insert(const int x, const int i) {
	//������� i ����㴦������Ԫ�� x
	ListNode* p = first; int k = 0;
	while (p != NULL && k < i - 1)
	{
		p = p->link; k++;
	} //�ҵ�i-1�����
	if (p == NULL && first != NULL) {
		cout << "��Ч�Ĳ���λ��!\n";
		return 0;
	}
	ListNode* newnode = new ListNode(x, NULL);
	//�����½��,������Ϊx,ָ��Ϊ0
	if (first == NULL || i == 0) { //���ڱ�ǰ
		newnode->link = first;
		if (first == NULL) last = newnode;
		first = newnode;
	}
	else { //���ڱ��л�ĩβ
		newnode->link = p->link;
		if (p->link == NULL) last = newnode; p->link = newnode;
	}
	return 1;
}