# include <iostream>
# include <string>
# include <limits>
using namespace std;

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

// AVL���Ľڵ���
template <class K>
struct AVLNode {
	K key;
	int bf;
	AVLNode<K>* left, * right;
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
private:
	AVLNode<K>* root;
	bool Insert(AVLNode<K>*& ptr, K& d); // ����
	bool Remove(AVLNode<K>*& ptr, K& d); // ɾ��
	void RotateL(AVLNode<K>*& ptr); // ����ת
	void RotateR(AVLNode<K>*& ptr); // �ҵ���ת
	void RotateLR(AVLNode<K>*& ptr); // ���������ת
	void RotateRL(AVLNode<K>*& ptr); // ���Һ�����ת
	AVLNode<K>* Search(K& d, AVLNode<K>*& ptr); // ���Һ���
	void makeEmpty(AVLNode<K>*& ptr); // �ÿ�
	void Show(AVLNode<K>*& ptr); // ���
public:
	AVLTree() : root(NULL) {} // ���캯��
	~AVLTree() { makeEmpty(root); } // ��������
	AVLNode<K>* Search(K& d) { return Search(d, root); } // ����
	bool Insert(K& d) { return Insert(root, d); } // ����
	bool Remove(K& d) { return Remove(root, d); }; // ɾ��
	void SetRoot(K& d); // ���ø��ڵ�
	void Show() { Show(root); } // ���
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
		if (d == p->key) return false; // ���Ѵ��ڹؼ�����ȵĽڵ㣬 ����ʧ��
		pr = p;
		st.Push(pr); // ��ջ�洢���ҵ�·��
		if (d < p->key) p = p->left;
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
	if (d < pr->key) pr->left = p;
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
		if (q->key > pr->key) q->left = pr;
		else q->right = pr;
	}
	return true;
}

template <class K>
bool AVLTree<K>::Remove(AVLNode<K>*& ptr, K& d) {
	AVLNode<K>* pr = NULL, * p = ptr, * q, * ppr = NULL;
	int n, nn = 0;
	LinkedStack<AVLNode<K>*> st;

	// Ѱ��ɾ��λ��
	while (p != NULL) {
		if (d == p->key) break; // �ɹ��ҵ��� ֹͣ����
		pr = p;
		st.Push(pr); // ��ջ����·��
		if (d < p->key) p = p->left;
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

			 // ��Ҫ���������
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
	if (d < ptr->key) return Search(d, ptr->left); // �ؼ���С�ڴ˽ڵ㣬 �����������в���
	else if (d > ptr->key) return Search(d, ptr->right); // �ؼ�����ڴ˽ڵ㣬 �����������в���
	else return ptr; // �ؼ�����ȣ� �ɹ��ҵ��� ���ظýڵ�
}

// ���
template <class K>
void AVLTree<K>::Show(AVLNode<K>*& ptr) {
	if (ptr == NULL) return;
	if (ptr->left != NULL) {
		Show(ptr->left);
		cout << " -> ";
	}
	cout << ptr->key;
	if (ptr->right != NULL) {
		cout << " -> ";
		Show(ptr->right);
	}
}

// ϵͳ��
class System{
private :
	AVLTree<int>* Tree;
public :
	System(); // ���캯��
	~System(); // ��������
	bool BuildTree(); // ������
	void Show(); // չʾ
	bool Insert(); // ����
	bool Remove(); // ɾ��
	bool Search(); // Ѱ��
	void Loop(); // ��ѭ��
};

// ���캯��
System::System() {
	Tree = new AVLTree<int>;
}

// ��������
System::~System() {
	delete Tree;
}

// ������
bool System::BuildTree() {
	// ��ɾ��ԭ�������� ���½���һ������
	delete Tree;
	Tree = new AVLTree<int>;

	cout << "Please input keys to create tree ( input '#' to stop ) : ";
	string temNum;
	cin >> temNum;

	// ���϶��룬 ֱ������Ϊ #
	while (temNum != "#") {
		// ������� # �� ����ת��Ϊ����
		int num = stoi(temNum);

		// ���Բ��룬 ��ʧ��˵�����и�Ԫ��
		if (!Tree->Insert(num)) {
			cout << "The key ( " << num << " ) is repeated ! " << endl;
		}
		cin >> temNum;
	}

	return true;
}

// չʾ
void System::Show() {
	cout << "The Tree is : " << endl;

	// ���� AVL �����������������ӡ��Ϣ
	Tree->Show();
	cout << endl << endl;
}

// ����
bool System::Insert() {
	cout << "Please input key which inserted : ";
	int num;
	cin >> num;

	// ���Բ��룬 ��ʧ�ܣ� ˵���Ѿ����ڸ�Ԫ��
	if (Tree->Insert(num)) {
		cout << "Successfully inserted ! " << endl;
		return true;
	}
	else {
		cout << num << " is repeated !  " << endl;
		return false;
	}
}

// ɾ��
bool System::Remove() {
	cout << "Please input key which removed : ";
	int num;
	cin >> num;

	// ����ɾ���� ��ʧ��˵����Ԫ�ز�����
	if (Tree->Remove(num)) {
		cout << "Successfully removed ! " << endl;
		return true;
	}
	else {
		cout << num << " is not in !  " << endl;
		return false;
	}
}

// ��ѯ
bool System::Search() {
	cout << "Please input key which searched : ";
	int num;
	cin >> num;

	// ���� AVL�� �Ĳ�ѯ������������
	if (Tree->Search(num)) {
		cout << "Successfully searched ! " << endl;
		return true;
	}
	else {
		cout << "No this key ! " << endl;
		return false;
	}
}

// ��ѭ��
void System::Loop() {
	cout << "**                    ����������                    **" << endl;
	cout << "======================================================" << endl;
	cout << "**               ��ѡ��Ҫִ�еĲ�����               **" << endl;
	cout << "**               1 --- ��������������               **" << endl;
	cout << "**               2 --- ����Ԫ��                     **" << endl;
	cout << "**               3 --- ɾ��Ԫ��                     **" << endl;
	cout << "**               4 --- ����Ԫ��                     **" << endl;
	cout << "**               5 --- �鿴������                   **" << endl;
	cout << "**               6 --- �˳�����                     **" << endl;
	cout << "======================================================" << endl << endl;

	// ���Ͻ����û�����
	while (true) {
		int choice;
		cout << "Please select : ";
		cin >> choice;

		switch (choice) {
		case 1 :
			// ������
			BuildTree();
			Show();
			break;
		case 2:
			// ����
			Insert();
			Show();
			break;
		case 3:
			// ɾ��
			Remove();
			Show();
			break;
		case 4 :
			// ����
			Search();
			Show();
			break;
		case 5:
			// ��ʾ
			Show();
			break;
		case 6 :
			// �˳�����
			cout << "Welcome back soon ! " << endl << endl;
			return;
			break;
		default:
			// ���Ϸ�����
			cout << "Illigal input ! " << endl;

			// ��ջ�����
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
}

int main() {
	// ʵ����һ��ϵͳ
	System sys;

	// ������ѭ������
	sys.Loop();

# ifdef _WIN32
	system("pause");
#endif

	return 0;
}