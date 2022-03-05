# include <iostream>
# include <limits>
using namespace std;

// ǰ������
class Genealogy;

// �ڵ���
template<class T>
struct LinkNode {
	T data;
	LinkNode <T>* link;
	LinkNode(LinkNode<T>* ptr = NULL) : link(ptr) {}; // ���캯��
	LinkNode(const T& tem, LinkNode<T>* ptr = NULL) : data(tem), link(ptr) {}; // ���캯��
};

// ջ
template <class T>
class LinkedStack {
public:
	LinkedStack() : top(NULL) {} // ���캯��
	~LinkedStack() { makeEmpty(); } // ��������
	void Push(const T& x); // ��ջ
	bool Pop(T& x); // ��ջ
	bool getTop(T& x) const; // �õ�ջ��Ԫ��
	bool IsEmpty() const { return top == NULL; } // �ж��Ƿ�ջ��
	int getSize() const; // ����ջ��Ԫ�ظ���
	void makeEmpty(); // ջ�ÿ�
private:
	LinkNode<T>* top;  // ջ��Ԫ��
};

// ջ�ÿ�
template <class T>
void LinkedStack<T>::makeEmpty() {
	LinkNode<T>* p;

	// ��ڵ��ͷ�
	while (top != NULL) {
		p = top;
		top = top->link;
		delete p;
	}
}

// ��ջ
template <class T>
void LinkedStack<T>::Push(const T& x) {
	top = new LinkNode<T>(x, top); // ��Ԫ�س�Ϊջ������֮ǰԪ������
}

// ��ջ
template <class T>
bool LinkedStack<T>::Pop(T& x) {
	if (IsEmpty()) return false; // ջ�գ� ֱ�ӷ���false
	LinkNode<T>* p = top;
	top = top->link; // ����ջ��Ԫ��
	x = p->data;
	delete p;
	return true;
}

// �õ�ջ��Ԫ��
template <class T>
bool LinkedStack<T>::getTop(T& x) const {
	if (IsEmpty()) return false;  // ջ�գ� ֱ�ӷ���false
	x = top->data; // ��ջ��Ԫ�ظ�ֵ�� x
	return true;
}

// ����ջ��Ԫ�ظ���
template <class T>
int LinkedStack<T>::getSize() const {
	LinkNode<T>* p = top;
	int k = 0;

	// ����Ԫ�ز�����
	while (p != NULL) {
		p = p->link;
		++k;
	}
	return k;
}

// ����
template <class T>
class LinkedQueue {
private:
	LinkNode<T>* front, * rear;
public:
	LinkedQueue() : front(NULL), rear(NULL) {} // ���캯��
	~LinkedQueue() { makeEmpty(); } // ��������
	bool EnQueue(const T& x); // �������
	bool DeQueue(T& x); // ������
	bool getFront(T& x) const; // ���� front
	void makeEmpty(); // �ÿ�
	bool IsEmpty() const { return front == NULL; } // �ж϶����Ƿ�Ϊ��
	int getSize() const; // ���ض���Ԫ�ظ���

	 // ��Ԫ������ ʵ�ֶ������
	friend ostream& operator << (ostream& os, const LinkedQueue<T>& Q) {
		LinkNode<T>* p = Q.front;
		while (p != NULL) {
			os << p->data << "    ";
			p = p->link;
		}
		return os;
	}
};

// �ÿ�
template <class T>
void LinkedQueue<T>::makeEmpty() {
	LinkNode<T>* p;

	// ��Ԫ���ͷ�
	while (front != NULL) {
		p = front;
		front = front->link;
		delete p;
	}
}

// �������
template <class T>
bool LinkedQueue<T>::EnQueue(const T& x) {
	// ������Ϊ��
	if (IsEmpty()) {
		front = rear = new LinkNode<T>(x);
		if (front == NULL) return false;
	}
	else {  // �����в�Ϊ��
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL) return false;
		rear = rear->link;
	}
	return true;
}

// ������
template <class T>
bool LinkedQueue<T>::DeQueue(T& x) {
	if (IsEmpty()) return false; // ����Ϊ�գ� ���� false
	LinkNode<T>* p = front;
	x = front->data;
	front = front->link; // ���� front
	delete p;
	return true;
}

// �õ� front ��ֵ
template <class T>
bool LinkedQueue<T>::getFront(T& x) const {
	if (IsEmpty()) return false; // ����Ϊ�գ� ���� false
	x = front->data;
	return true;
}

// ���ض���Ԫ�ظ���
template <class T>
int LinkedQueue<T>::getSize() const {
	LinkNode<T>* p = front;
	int k = 0;

	// ����������
	while (p != 0) {
		p = p->link;
		k++;
	}
	return k;
}

// �������ڵ���
template <class T>
struct GenealogyTreeNode{
	T data;
	GenealogyTreeNode<T>* pre, *son, *brother; // �ֱ�ָ����һ�ڵ㣨���׻��߸�磩�����ӣ��ܵ�
	GenealogyTreeNode() : pre(NULL), son(NULL), brother(NULL) {} // ���캯��
	GenealogyTreeNode(T& newData, GenealogyTreeNode<T>* p = NULL, GenealogyTreeNode<T>* s = NULL, GenealogyTreeNode<T>* b = NULL) : data(newData), pre(p), son(s), brother(b) {} // ���캯��
	~GenealogyTreeNode() {} // ��������
	bool operator < (const GenealogyTreeNode<T>& GTN) { return this->data < GTN.data; } // ����С�ڷ���
	bool operator > (const GenealogyTreeNode<T>& GTN) { return this->data > GTN.data; } // ���ش��ڷ���
	bool operator == (const GenealogyTreeNode<T>& GTN) { return this->data == GTN.data; } // ���� == ����
};

// ��������
template <class T>
class GenealogyTree{
private :
	GenealogyTreeNode<T>* root;
	void makeEmpty(GenealogyTreeNode<T>*& ptr); // �ÿ�
public :
	GenealogyTree() : root(NULL) {}  // ���캯��
	~GenealogyTree() { makeEmpty(root); } // ��������
	bool IsEmpty() { return root == NULL; } // ����Ƿ�Ϊ��
	void SetRoot(GenealogyTreeNode<T>*& R); // ���ø��ڵ�
	bool Insert(GenealogyTreeNode<T>*& d, GenealogyTreeNode<T>*& fa); // ����ڵ�
	bool Remove(GenealogyTreeNode<T>*& d); // ɾ���ڵ�
	void Show(); //��ӡ������
};

// �ÿ�
template <class T>
void GenealogyTree<T>::makeEmpty(GenealogyTreeNode<T>*& ptr) {
	if (ptr == NULL) return;

	// �ݹ��ͷ��ӽڵ�
	if (ptr->son != NULL) {
		makeEmpty(ptr->son);
	}

	// �ݹ��ͷ��ֵܽڵ�
	if (ptr->brother != NULL) {
		makeEmpty(ptr->brother);
	}
	delete ptr; // �ͷŸýڵ�
}

// ���ø��ڵ�
template <class T>
void GenealogyTree<T>::SetRoot(GenealogyTreeNode<T>*& R) {
	root = R;
}

// ����
template <class T>
bool GenealogyTree<T>::Insert(GenealogyTreeNode<T>*& d, GenealogyTreeNode<T>*& fa) {
	// ���丸�ڵ�ԭ���޶��ӣ� �ýڵ��Ϊ�丸�ڵ㳤��
	if (fa->son == NULL) {
		fa->son = d;
		d->pre = fa;
	}
	else { 
		// ���� �ҵ������һ���ֵܽڵ㣬 Ȼ�������ں���
		GenealogyTreeNode<T>* pr = fa->son;
		while (pr->brother != NULL) {
			pr = pr->brother;
		}
		pr->brother = d;
		d->pre = pr;
	}
	return true;
}

// ɾ��
template <class T>
bool GenealogyTree<T>::Remove(GenealogyTreeNode<T>*& d) {
	// ǰ���޽ڵ㣨��Ϊ���ڵ㣩
	if (d->pre == NULL) {
		makeEmpty(d->son);
		delete d;
		root = NULL;
		return true;
	}
	// ��Ϊ�丸�ڵ�ĳ��ӽڵ㣬 ��Ҫ�����һ���ֵܱ�ɳ���
	if (d->pre->son == d) {
		d->pre->son = d->brother;
		if (d->brother != NULL) d->brother->pre = d->pre;
		makeEmpty(d->son);
		delete d;
		return true;
	}
	else {
		// ���� ��ֱ�ӰѸýڵ�ǰ���ֵܽڵ���������
		d->pre->brother = d->brother;
		if (d->brother != NULL) d->brother->pre = d ->pre;
		makeEmpty(d->son);
		delete d;
		return true;
	}
}

// ��ӡ
template <class T>
void GenealogyTree<T>::Show() {
	if (root == NULL) {
		cout << "�������ѱ���գ� ���������Ϣ��" << endl << endl;
		return;
	}

	GenealogyTreeNode<T>* cur = NULL;
	LinkedQueue<GenealogyTreeNode<T>*> LQ;
	LQ.EnQueue(root); // �ö��б��ڷִ���ӡ

	cout << "======================================================" << endl;
	int count = 1;

	// ������ӡ�� ֱ������Ϊ��
	while (!LQ.IsEmpty()) {
		cout << "�� " << count << " ����";
		
		int nums = LQ.getSize(); // ��ȡ��ǰ���г���

		// ��ӡ��һ����Ů����Ϣ�� �������ǵ��ӽڵ������
		for (int i = 0; i < nums; i++) {
			LQ.DeQueue(cur);
			cout << cur->data << "    ";

			// ���ýڵ�������ӽڵ������
			cur = cur->son;
			while (cur != NULL) {
				LQ.EnQueue(cur);
				cur = cur->brother;
			}
		}
		count++;
		cout << endl;
	}
	cout << "======================================================" << endl;
}

// AVL���Ľڵ���
template <class K>
struct AVLNode{
	K key;
	int bf;
	AVLNode<K>* left, *right;
	AVLNode() : bf(0), left(NULL), right(NULL) {} // ���캯��
	AVLNode(K newKey, AVLNode<K>* newLeft = NULL, AVLNode<K>* newRight = NULL) : key(newKey), bf(0), left(newLeft), right(newRight) {} // ���캯��
	~AVLNode() {} // ��������

	// �������رȽ�������ĺ���
	bool operator < (const AVLNode<K>& AN) { return this->key < AN.key; }
	bool operator > (const AVLNode<K>& AN) { return this->key > AN.key; }
	bool operator == (const AVLNode<K>& AN) { return this->key == AN.key; }
};

// AVL����
template <class K>
class AVLTree {
private :
	AVLNode<K>* root;
	bool Insert(AVLNode<K>*& ptr, K& d); // ����
	bool Remove(AVLNode<K>*& ptr, K& d); // ɾ��
	void RotateL(AVLNode<K>*& ptr); // ����ת
	void RotateR(AVLNode<K>*& ptr); // �ҵ���ת
	void RotateLR(AVLNode<K>*& ptr); // ���������ת
	void RotateRL(AVLNode<K>*& ptr); // ���Һ�����ת
	AVLNode<K>* Search(K& d, AVLNode<K>*& ptr); // ���Һ���
	void makeEmpty(AVLNode<K>*& ptr); // �ÿ�
public :
	AVLTree() : root(NULL) {} // ���캯��
	~AVLTree() { makeEmpty(root); } // ��������
	AVLNode<K>* Search(K& d) { return Search(d, root); } // ����
	bool Insert(K& d) { return Insert(root, d); } // ����
	bool Remove(K& d, bool tag); // ɾ��
	bool Update(K& curData, K& newData); // ����
	void SetRoot(K& d); // ���ø��ڵ�
};

// ����ת
template <class K>
void AVLTree<K>::RotateL(AVLNode<K>*& ptr) {
	AVLNode<K>* subL = ptr; // Ҫ����ת�Ľڵ�
	ptr = subL->right; // ԭ�ڵ������Ů
	subL->right = ptr->left; // ��ȥ�����Ů
	ptr->left = subL; // ��ת
	ptr->bf = subL->bf = 0; // ���� bf
}

// �ҵ���ת
template <class K>
void AVLTree<K>::RotateR(AVLNode<K>*& ptr) {
	AVLNode<K>* subR = ptr; // Ҫ��ת���ҽڵ�
	ptr = subR->left; // ԭ�ڵ������Ů
	subR->left = ptr->right; // ��ȥ�ұ���Ů
	ptr->right = subR; // ��ת
	ptr->bf = subR->bf = 0; // ���� bf
}

// ���������ת
template <class K>
void AVLTree<K>::RotateLR(AVLNode<K>*& ptr) {
	AVLNode<K>* subR = ptr, * subL = subR->left;
	ptr = subL->right;
	subL->right = ptr->left;  // ��ȥ�����Ů
	ptr->left = subL; // ����ת
	if (ptr->bf <= 0) subL->bf = 0; // �����½ڵ����������
	else subL->bf = -1; // ����
	subR->left = ptr->right; // ��ȥ�ұ���Ů
	ptr->right = subR; // �ҵ���ת

	 // ���� bf
	if (ptr->bf == -1) subR->bf = 1;
	else subR->bf = 0;
	ptr->bf = 0;
}

// ���Һ�����ת
template <class K>
void AVLTree<K>::RotateRL(AVLNode<K>*& ptr) {
	AVLNode<K>* subL = ptr, * subR = ptr->right;
	ptr = subR->left;
	subR->left = ptr->right; // ��ȥ�ұ���Ů
	ptr->right = subR; // �ҵ���ת
	if (ptr->bf >= 0) subR->bf = 0; // �����½ڵ����������
	else subR->bf = 1; // ����
	subL->right = ptr->left; // ��ȥ�����Ů
	ptr->left = subL; // ����ת

	 // ���� bf
	if (ptr->bf == 1) subL->bf = -1;
	else subL->bf = 0;
	ptr->bf = 0;
}

// �޸Ľڵ�
template <class K>
bool AVLTree<K>::Update(K& curData, K& newData) {
	// ���޸ĺ�������ѱ�ʹ��
	if (Search(newData, root) != NULL) {
		return false;
	}

	// ���Ƴ�ԭ�ڵ㣬 �޸�ֵ���ٴβ��룬 ȷ����Ȼ�Ƿ��϶�����������
	Remove(root, curData);
	curData->data = newData->data;
	Insert(curData);
	return true;
}

// ���ø��ڵ�
template <class K>
void AVLTree<K>::SetRoot(K& d) {
	this->root = new AVLNode<K>;
	this->root->key = d;
}

// �ÿ�
template <class K>
void AVLTree<K>::makeEmpty(AVLNode<K>*& ptr) {
	if (ptr == NULL) return;

	// �ݹ��ÿ�������
	if (ptr->left != NULL) {
		makeEmpty(ptr->left);
	}

	// �ݹ��ÿ������� 
	if (ptr->right != NULL) {
		makeEmpty(ptr->right);
	}
	delete ptr; // ɾ���ýڵ�
}

template <class K>
bool AVLTree<K>::Insert(AVLNode<K>*& ptr, K& d) {
	AVLNode<K>* pr = NULL, * p = ptr, * q;
	int n;
	LinkedStack<AVLNode<K>*> st;

	// Ѱ�Ҳ���λ��
	while (p != NULL) {
		if (*d == *(p->key)) return false; // ���Ѵ��ڹؼ�����ȵĽڵ㣬 ����ʧ��
		pr = p;
		st.Push(pr); // ��ջ�洢���ҵ�·��
		if (*d < *(p->key)) p = p->left;
		else p = p->right;
	}

	// �����½ڵ�
	p = new AVLNode<K>;
	p->key = d;

	// ��֮ǰΪ����
	if (pr == NULL) {
		ptr = p;
		return true;
	}

	// �½ڵ����
	if (*d < *(pr->key)) pr->left = p;
	else pr->right = p;

	// ����ƽ�� AVL ��
	while (!st.IsEmpty()) {
		st.Pop(pr);  // ��ջ�е������ڵ�
		if (p == pr->left) pr->bf--;  // ����ƽ������
		else pr->bf++;
		if (pr->bf == 0) break; // ����Ҫ������ �Ѿ�ƽ��
		if (pr->bf == 1 || pr->bf == -1) p = pr;  // ������ƽ�⣬ ������������Ľڵ��Ƿ�ƽ��
		else {  // �������Ѿ�ʧ��
			n = (pr->bf < 0) ? -1 : 1; // ����˫��ת�ı�־

			 // ����ת���
			if (p->bf == n) {
				if (n == -1) RotateR(pr);
				else RotateL(pr);
			}
			// ˫��ת���
			else {
				if (n == -1) RotateLR(pr);
				else RotateRL(pr);
			}
			break;
		}
	}

	// �Ѿ����������ڵ�
	if (st.IsEmpty()) ptr = pr;
	// �м���������
	else {
		st.getTop(q);
		if (*(q->key) > *(pr->key)) q->left = pr;
		else q->right = pr;
	}
	return true;
}

// ɾ��
template <class K>
bool AVLTree<K>::Remove(K& d, bool tag) {
	if (d == NULL) return false;

	// ɾ������
	if (d->son != NULL) {
		Remove(d->son, tag);
	}

	// �� tag Ϊ true�� ��ɾ������ֵܽڵ�
	if (tag && d->brother != NULL) {
		Remove(d->brother, tag);
	}
	Remove(root, d); // ɾ���ýڵ�
}

template <class K>
bool AVLTree<K>::Remove(AVLNode<K>*& ptr, K& d) {
	AVLNode<K>* pr = NULL, * p = ptr, * q, * ppr = NULL;
	int n, nn = 0;
	LinkedStack<AVLNode<K>*> st;

	// Ѱ��ɾ��λ��
	while (p != NULL) {
		if (*d == *(p->key)) break; // �ɹ��ҵ��� ֹͣ����
		pr = p;
		st.Push(pr); // ��ջ����·��
		if (*d < *(p->key)) p = p->left;
		else p = p->right;
	}

	if (p == NULL) return false; // δ�ҵ��� ȡ��ɾ������

	 // ����ɾ�ڵ���������Ů�� ��������
	if (p->left != NULL && p->right != NULL) {
		pr = p;
		st.Push(pr);
		q = p->left;
		while (q->right != NULL) {
			pr = q;
			st.Push(pr);
			q = q->right;
		}
		p->key = q->key; // �� q ��ֵ� p
		p = q; // ��ɾ�ڵ�ת�� 
	}

	// ��ɾ�ڵ�ֻ��һ����Ů
	bool leftTag = false;
	if (p->left != NULL) q = p->left;
	else q = p->right;
	if (pr == NULL) ptr = q; // ����ɾ�ڵ�Ϊ���ڵ�
	else {
		if (pr->left == p) pr->left = q, leftTag = true; // ����
		else pr->right = q;

		// ����ƽ�� AVL ��
		while (!st.IsEmpty()) {
			st.Pop(pr);  // ��ջ���˳����ڵ�
			if (leftTag || pr->left == q) pr->bf++, leftTag = false; // ����ƽ������
			else pr->bf--;
			if (!st.IsEmpty()) {
				st.getTop(ppr);
				nn = (ppr->left == pr) ? -1 : 1;
			}
			else nn = 0; // ջ�գ� ��������
			if (pr->bf == 1 || pr->bf == -1) break; // ���ص��������

			 // ����ʧ������
			if (pr->bf != 0) {
				if (pr->bf < 0) {
					n = -1;
					q = pr->left;
				}
				else {
					n = 1;
					q = pr->right;
				}
				if (q->bf == 0) {
					if (n == -1) {
						RotateR(pr);
						pr->bf = 1;
						pr->left->bf = -1;
					}
					else {
						RotateL(pr);
						pr->bf = -1;
						pr->right->bf = 1;
					}
					break;
				}

				// ����ת���
				if (q->bf == n) {
					if (n == -1) RotateR(pr);
					else RotateL(pr);
				}
				// ˫��ת���
				else {
					if (n == -1) RotateLR(pr);
					else RotateRL(pr);
				}
				if (nn == -1) ppr->left = pr;
				else if (nn == 1) ppr->right = pr; // ����
			}

			// ����δʧ�⣬ ����Ҫ���ϼ��
			q = pr;
		}
		if (st.IsEmpty()) ptr = pr; // ���������ڵ�
	}
	delete p;
	return true;
}

// ����
template <class K>
AVLNode<K>* AVLTree<K>::Search(K& d, AVLNode<K>*& ptr) {
 	if (ptr == NULL) return NULL;
	if (*d < *(ptr->key)) return Search(d, ptr->left); // �ؼ���С�ڴ˽ڵ㣬 �����������в���
	else if (*d > *(ptr->key)) return Search(d, ptr->right); // �ؼ�����ڴ˽ڵ㣬 �����������в���
	else return ptr; // �ؼ�����ȣ� �ɹ��ҵ��� ���ظýڵ�
}

// ������
class Genealogy{
private :
	GenealogyTree<string>* Tree; // �������� ���ڴ�����г�Ա��Ϣ�� ���������ǵı��ֹ�ϵ
	AVLTree<GenealogyTreeNode<string>*>* AVLGenealogy; // AVL �������� ��ƽ���������������ʽ������г�Ա��Ϣ�� ���Լ��ٲ�����ʱ�临�Ӷ�
public :
	Genealogy(); // ���캯��
	~Genealogy(); // ��������
	void Complete(); // ���Ƽ�ͥ
	void AddMember(); // ��ӳ�Ա
	void DeleteFamily(); // ��ɢ�Ӽ�ͥ
	void SearchMember(); // Ѱ�ҳ�Ա
	void ChangeMember(); // �޸ĳ�Ա
	void ShowGenealogy(); // ��ӡ����
	void Loop(); // ��ѭ������
};

// ���캯��
Genealogy::Genealogy() {
	Tree = new GenealogyTree<string>;
	AVLGenealogy = new AVLTree<GenealogyTreeNode<string>*>;
}

// ��������
Genealogy::~Genealogy() {
	delete Tree;
	delete AVLGenealogy;
}

// ���Ƽ�ͥ
void Genealogy::Complete() {
	cout << "������Ҫ������ͥ���˵�������";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// �����Ա�Ƿ����
	while ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "�ó�Ա�����ڣ����������룺";
		delete temTN;
		cin >> name;
		temTN = new GenealogyTreeNode<string>(name);
	}

	// ɾ����ʱ�ڵ㣬 �����Ϊ����ʵ�ġ��������ڵ�
	delete temTN;
	temTN = temAN->key;

	// ������Ů�� ȡ�����β���
	if (temTN->son != NULL) {
		cout << "�ó�Ա������Ů�� �޷�ִ�иò����� ���������Ů�� ���˳���ִ��������" << endl;
		return;
	}

	// ȷ��������Ů����
	cout << "������ " << name << " �Ķ�Ů������";
	int nums;
	cin >> nums;
	while (nums < 1) {
		cout << "��������Ϊ������" << endl;
		cin >> nums;
	}

	// ��һ��ջ���洢�����������Ů��Ϣ
	LinkedQueue<string>* nameQueue = new LinkedQueue<string>;
	cout << "���������� " << name << " �Ķ�Ů��������" << endl;

	// ���β���
	for (int i = 0; i < nums; i++) {
		string temName;
		cin >> temName;
		GenealogyTreeNode<string>* inTN = new GenealogyTreeNode<string>(temName);

		// ����һ�β���
		if (AVLGenealogy->Insert(inTN)) {
			// ����ɹ��� ���½ڵ����丸�ڵ����������� �������
			Tree->Insert(inTN, temTN);
			nameQueue->EnQueue(temName);
			cout << "�� " << i + 1 << " ����Ů����ɹ���" << endl;
		}
		else {
			// ����ʧ�ܣ� ��������
			cout << "�� " << i + 1 << " ����Ů����ʧ�ܣ��������������Ů�����Ժ����Ů������";
			i--;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	// ���ö��д�ӡ���β������Ů��Ϣ
	cout << name << "�ĵ�һ�������ǣ�";
	cout << *nameQueue << endl;
	delete nameQueue;
}

// ��ӳ�Ա
void Genealogy::AddMember() {
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// ���鸸�ڵ��Ƿ����
	while ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "�ó�Ա�����ڣ����������룺";
		delete temTN;
		cin >> name;
		temTN = new GenealogyTreeNode<string>(name);
	}

	delete temTN;
	temTN = temAN->key;

	cout << "������ " << name << " ����ӵĶ��ӣ���Ů������������" << endl;
	string temName;
	cin >> temName;
	GenealogyTreeNode<string>* inTN = new GenealogyTreeNode<string>(temName);
	
	// ���Բ���
	while(!AVLGenealogy->Insert(inTN)) {
		cout << " ����ʧ�ܣ��������������Ů��������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> temName;
		delete inTN;
		inTN = new GenealogyTreeNode<string>(temName);
	}
	Tree->Insert(inTN, temTN);
	cout << "����ɹ���" << endl;

	// ��ӡ���һ����Ů
	cout << name << "�ĵ�һ�������ǣ�";
	GenealogyTreeNode<string>* p = temTN->son;
	while (p != NULL) {
		cout << p->data << "    ";
		p = p->brother;
	}
	cout << endl;
}

// ɾ��
void Genealogy::DeleteFamily() {
	cout << "������Ҫ��ɢ�ļ�ͥ���˵�������";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// Ѱ���Ƿ����
	while ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "�ó�Ա�����ڣ����������룺";
		delete temTN;
		cin >> name;
		temTN = new GenealogyTreeNode<string>(name);
	}

	delete temTN;
	temTN = temAN->key;

	// ���Ҫ��ɢ�ļ�ͥ����Ϣ
	cout << "Ҫ��ɢ�ļ�ͥ�����ǣ�" << name << endl;
	cout << name << "�ĵ�һ�������ǣ�";
	GenealogyTreeNode<string>* p = temTN->son;
	while (p != NULL) {
		cout << p->data << "    ";
		p = p->brother;
	}
	cout << endl;
	
	// ��ɾ���ýڵ���ӽڵ�������ӽڵ���ֵܽڵ��Ѿ����ӽڵ㱾��
	AVLGenealogy->Remove(temTN->son, true);
	// ��ɾ���ýڵ�������ӽڵ㣨��ɾ���ֵܽڵ㣩
	AVLGenealogy->Remove(temTN, false);
	// �ڼ�����������������ؽڵ�
	Tree->Remove(temTN);
}

// ����
void Genealogy::SearchMember() {
	cout << "������Ҫ���ҵ��˵�������";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// �� AVL ���в���
	 // ����ʧ��
	if ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "�ó�Ա�����ڣ�" << endl;
		delete temTN;
		return;
	}

	delete temTN;
	temTN = temAN->key;

	// ���ҳɹ��� ��ӡ�����Ϣ
	cout << name << "���ڣ�" << endl;
	cout << name << "�ĵ�һ�������ǣ�";
	GenealogyTreeNode<string>* p = temTN->son;
	while (p != NULL) {
		cout << p->data << "    ";
		p = p->brother;
	}
	cout << endl;
}

// �޸ĳ�Ա��Ϣ
void Genealogy::ChangeMember() {
	cout << "������Ҫ�޸ĵ��˵�������";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// �����Ƿ����
	while ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "�ó�Ա�����ڣ����������룺";
		delete temTN;
		cin >> name;
		temTN = new GenealogyTreeNode<string>(name);
	}

	delete temTN;
	temTN = temAN->key;

	cout << "Ҫ�޸ĵ����ǣ�" << name << endl;
	cout << "�����޸ĺ�����֣�" << endl;
	string newName;
	cin >> newName;
	GenealogyTreeNode<string>* newTN = new GenealogyTreeNode<string>(newName);
	AVLNode< GenealogyTreeNode<string>*>* newAN = NULL;

	// �����������Ƿ��Ѿ���ʹ��
	while ((newAN = AVLGenealogy->Search(newTN)) != NULL) {
		cout << "�������Ѵ��ڣ����������룺";
		delete newTN;
		cin >> newName;
		newTN = new GenealogyTreeNode<string>(newName);
	}

	// ���½ڵ���Ϣ
	AVLGenealogy->Update(temTN, newTN);
	cout << "�޸ĳɹ���" << endl;

	// �ͷ����õ���ʱ�ڵ�
	delete newTN;
}

// ��ӡ������
void Genealogy::ShowGenealogy() {
	cout << endl << "��ǰ����Ϊ��" << endl << endl;
	Tree->Show(); // ���ü������Ĵ�ӡ����
	cout << endl;
}

// ��ѭ������
void Genealogy::Loop() {
	cout << "**                   ���׹���ϵͳ                   **" << endl;
	cout << "======================================================" << endl;
	cout << "**               ��ѡ��Ҫִ�еĲ�����               **" << endl;
	cout << "**                  A --- ���Ƽ���                  **" << endl;
	cout << "**                B --- ��Ӽ�ͥ��Ա                **" << endl;
	cout << "**                C --- ��ɢ�ֲ���ͥ                **" << endl;
	cout << "**                D --- ���Ҽ�ͥ��Ա                **" << endl;
	cout << "**              E --- ���ļ�ͥ��Ա����              **" << endl;
	cout << "**                S --- �鿴��ͥ��Ա                **" << endl;
	cout << "**                  Z --- �˳�����                  **" << endl;
	cout << "======================================================" << endl;

	// �����ü��׵����Ƚڵ�
	cout << "�����뽨��һ�����ף�" << endl << "����������������" << endl;
	string ancestor;
	cin >> ancestor;
	GenealogyTreeNode<string>* t = new GenealogyTreeNode<string>(ancestor);

	// �ֱ�Ϊ AVL ���ͼ��������ø��ڵ�
	AVLGenealogy->SetRoot(t);
	Tree->SetRoot(t);
	cout << "�˼��׵������ǣ�" << ancestor << endl;

	// ����ѯ���û����������ʵ��
	char op;
	while (true) {
		cout << "������Ҫִ�еĲ�����" << endl;
		cin >> op;
		switch (op) {
		case 'A': 
			// ���Ƽ�ͥ����
			Complete();
			//ShowGenealogy();
			break;
		case 'B':
			// ��ӳ�Ա����
			AddMember();
			//ShowGenealogy();
			break;
		case 'C':
			// ��ɢ�Ӽ�ͥ����
			DeleteFamily();
			//ShowGenealogy();
			break;
		case 'D':
			// ���ҳ�Ա����
			SearchMember();
			//ShowGenealogy();
			break;
		case 'E':
			// �޸ĳ�Ա��Ϣ����
			ChangeMember();
			//ShowGenealogy();
			break;
		case 'S':
			// ��ӡ����������
			ShowGenealogy();
			break;
		case 'Z':
			// �˳�����
			cout << "���γ�������� ��ӭ�´ι��٣�" << endl << endl;
			//ShowGenealogy();
			return;
			break;
		default:
			// ������Чָ��
			cout << "��Чָ� ���������룡";
			break;
		}

		// ��ջ�����
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// �������Ƿ�ɾ�գ� ��ɾ�����˳�����
		if (Tree->IsEmpty()) {
			cout << "�������ѱ���գ� ���β��������� ��ӭ�´ι��٣�" << endl << endl;
			return;
		}
	}
}

int main() {
	// ʵ����һ��������
	Genealogy MyGenealogy;

	// ������ѭ��ʵ����Ӧ����
	MyGenealogy.Loop();

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}