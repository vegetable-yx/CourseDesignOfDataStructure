# include <iostream>
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

// �������ڵ���
template <class T>
struct BinTreeNode {
	T data;
	bool tag; // ����һ����ǣ� ���ڱ���Ƿ���Ҫ�������Ŵ�ӡ
	BinTreeNode<T>* leftchild, * rightchild;
	BinTreeNode() : tag(0), leftchild(NULL), rightchild(NULL) {} // ���캯��
	BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL) : tag(0), data(x), leftchild(l), rightchild(r) {} // ���캯��
};

// ��������
template <class T>
class BinaryTree {
public:
	BinaryTree() : root(NULL) {} // ���캯��
	~BinaryTree() { destroy(root); } // ��������
	bool IsEmpty() { return root == NULL; } // �Ƿ�Ϊ��
	BinTreeNode<T>* Parent(BinTreeNode<T>* current) { return (root == NULL || root == current ? NULL : Parent(root, current)); } // �õ����ڵ�
	BinTreeNode<T>* LeftChild(BinTreeNode<T>* current) { return current == NULL ? NULL : current->leftchild; } // �õ����ӽڵ�
	BinTreeNode<T>* RightChild(BinTreeNode<T>* current) { return current == NULL ? NULL : current->rightchild; } // �õ����ӽڵ�
	int Height() { return Height(root); } // �õ��������߶�
	int Size() { return Size(root); } // �õ��������ڵ����
	BinTreeNode<T>* getRoot() const { return root; } // ���ظ��ڵ�
	void setRoot(BinTreeNode<T>* newRoot) { root = newRoot; } // ���ø��ڵ�
	void preOrder(void (*visit) (BinTreeNode<T>* p)) { preOrder(root, visit); } // ǰ�����
	void inOrder(void (*visit) (BinTreeNode<T>* p)) { inOrder(root, visit); } // �������
	void postOrder(void (*visit) (BinTreeNode<T>* p)) { postOrder(root, visit); } // �������
private:
	BinTreeNode<T>* root;
	void destroy(BinTreeNode<T>*& subTree); // �ͷ�һ������
	int Height(BinTreeNode<T>* subTree) const; // ���������߶�
	int Size(BinTreeNode<T>*) const; // ���������ڵ����
	BinTreeNode<T>* Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current); // ���ظ��ڵ�
	void preOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p)); // ǰ�����
	void inOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p)); // �������
	void postOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p)); // �������
};

// �ͷ�����
template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T>*& subTree) {
	// �ݹ��ͷ��������������������ͷŸ��ڵ�
	if (subTree != NULL) {
		destroy(subTree->leftchild);
		destroy(subTree->rightchild);
		delete subTree;
	}
}

// ���ظ��ڵ�
template <class T>
BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) {
	if (subTree == NULL) return NULL; // ��ǰ����Ϊ��

	 // �������ӽڵ�������ӽڵ�Ϊ����ڵ�
	if (subTree->leftChild == current || subTree->rightchild == current) return subTree;
	BinTreeNode<T>* p;

	// �ֱ������������в��Ҹõ�ĸ��ڵ�
	if ((p = Parent(subTree->rightchild, current)) != NULL) return p;
	else return Parent(subTree->leftchild, current);
}

// �������
template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		// ����ӡ���ű��Ϊ true�� ���ȴ�ӡ������
		if (subTree->tag) cout << "( ";

		// �ȱ����������� Ȼ������ýڵ㣬 Ȼ�����������
		inOrder(subTree->leftchild, visit);
		visit(subTree);
		inOrder(subTree->rightchild, visit);

		// ����ӡ���ű��Ϊ true�� ��������ӡ������
		if (subTree->tag) cout << ") ";
	}
}

// ǰ�����
template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		// ����ӡ���ű��Ϊ true�� ���ȴ�ӡ������
		if (subTree->tag) cout << "( ";

		// �ȱ����ýڵ㣬 Ȼ������������� Ȼ�����������
		visit(subTree);
		preOrder(subTree->leftchild, visit);
		preOrder(subTree->rightchild, visit);

		// ����ӡ���ű��Ϊ true�� ��������ӡ������
		if (subTree->tag) cout << ") ";
	}
}

// �������
template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		// ����ӡ���ű��Ϊ true�� ���ȴ�ӡ������
		if (subTree->tag) cout << "( ";

		// �ȱ����������� Ȼ������������� Ȼ������ýڵ�
		postOrder(subTree->leftchild, visit);
		postOrder(subTree->rightchild, visit);
		visit(subTree);

		// ����ӡ���ű��Ϊ true�� ��������ӡ������
		if (subTree->tag) cout << ") ";
	}
}

// ���������ڵ����
template <class T>
int BinaryTree<T>::Size(BinTreeNode<T>* subTree) const {
	if (subTree == NULL) return 0;
	// �ݹ飬 �ڵ���������������ڵ���� + �������ڵ���� + 1
	else return 1 + Size(subTree->leftchild) + Size(subTree->rightchild);
}

// ���������߶�
template <class T>
int BinaryTree<T>::Height(BinTreeNode<T>* subTree) const {
	if (subTree == NULL) return 0;
	// �����߶�Ϊ���������������е����߶� + 1
	else {
		int LHeight = Height(subTree->leftchild);
		int RHeight = Height(subTree->rightchild);
		return LHeight < RHeight ? RHeight + 1 : LHeight + 1;
	}
}

// ���� == �����
template <class T>
int operator == (const BinaryTree<T>& s, const BinaryTree<T>& t) {
	// ���� equal ����������ڵ�Ƚ�
	return equal(s.root, t.root);
}

// �Ƚ�
template <class T>
bool equal(BinTreeNode<T>* a, BinTreeNode<T>* b) {
	if (a == NULL && b == NULL) return true;
	// �ֱ�Ƚ� a, b �� data �͸��������Ƿ����
	if (a != NULL && b != NULL && a->data == b->data && equal(a->leftchild, b->leftchild) && equal(a->rightchild, b->rightchild)) return true;
	else return false;
}

// ���ʽ��
class Expression {
private :
	BinaryTree<string>* Tree; // ��ű��ʽ�Ķ�����
	string getItems(string& str); // ����������ʽÿ��ȡ��һ��
public :
	Expression(); // ���캯��
	~Expression() { delete Tree; } // ��������
	int CheckExp(string exp); // �����Ϊ���ֻ��Ƿ��ţ������ǷǷ��ַ���
	int isp(string exp); // ���ط��Ŷ�Ӧ��ջ��������
	int icp(string exp); // ���ط��Ŷ�Ӧ��ջ��������
	bool BuildTree(); // �������뽨��������
	void Polish(); // ͨ��ǰ���������������������ʽ
	void Infix(); // ͨ������������������������ʽ
	void ReversePolish(); // ͨ�������������������沨��ʽ
	void Loop(); // ��ѭ������
};

// ���캯��
Expression::Expression() {
	Tree = new BinaryTree<string>;
}

// ����õ����ʽ
string Expression::getItems(string& str) {
	// ����Ƿ�Ϊ�����
	if (CheckExp(str.substr(0, 1)) == 0) {
		// �޸� str �󷵻������
		string temStr = str.substr(0, 1);
		str = str.substr(1);
		return temStr;
	}
	else {
		// ���Է���һ������
		for (int i = 0; i < str.length(); i++) {
			if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
				if (i == 0) return "?"; // ���ش�����

				// �޸� str �󷵻������
				string temStr = str.substr(0, i);
				str = str.substr(i);
				return temStr;
			}
		}
	}

	return "?"; // ���ش�����
}

// �����ʽ����һ����ʽ��
int Expression::CheckExp(string exp) {
	// ��һ�֣����������ֹ����
	if (exp == "+" || exp == "-" || exp == "*" || exp == "/" || exp == "(" || exp == ")" || exp == "#") {
		return 0;
	}
	// ���򣬼���Ƿ�Ϊ�����֣����Ϸ������֣�
	else {
		// dot ���С�����Ƿ���ڣ� �Ϸ����������ֻ����һ��С����
		bool dot = false;
		for (int i = 0; i < exp.length(); i++) {
			if ((exp[i] < '0' || exp[i] > '9') && (i == 0 || exp[i] != '.')) return 2;
			else if (exp[i] == '.') {
				if (!dot) dot = true;
				else return false;
			}
		}
		return 1;
	}
}

// �������ջ��������
int Expression::isp(string exp) {
	if (exp == "#") return 0;
	else if (exp == "(") return 1;
	else if (exp == "*" || exp == "/") return 5;
	else if (exp == "+" || exp == "-") return 3;
	else return 6;
 }

// �������ջ��������
int Expression::icp(string exp) {
	if (exp == "#") return 0;
	else if (exp == "(") return 6;
	else if (exp == "*" || exp == "/") return 4;
	else if (exp == "+" || exp == "-") return 2;
	else return 1;
}

// �������뽨��������
bool Expression::BuildTree() {
	cout << "��������׺���ʽ��ֻ�����ֺ� '+'��'-'��'*'��'/'��'('��')' ������������������ţ���" << endl;
	string str, exp;
	cin >> str;
	str.append("#"); // ĩβ���һ��������־��
	exp = getItems(str);

	// �ڵ�ջ�� ���γɵĽڵ����ջ�У� �ȴ���ʱ��ʱ�������ǵ���ջ����������
	LinkedStack<BinTreeNode<string>*>* nodeST = new LinkedStack<BinTreeNode<string>*>;

	// ����ջ�� ��ŷ��ţ� �������ȼ�ȷ���Ƿ���ջ�����ǵ����ڵ�ջ��Ԫ�ز���������������
	LinkedStack<string>* opST = new LinkedStack<string>;
	opST->Push("#"); // �ȷ���һ�� # ��Ϊ��ʼ����

	 // ����ִ�У� ֱ�ӷ���ջ�ջ��߼������Ϸ���״̬
	while (!opST->IsEmpty()) {
		// ������������һ����ʱ�ڵ�
		BinTreeNode<string>* temNode = new BinTreeNode<string>(exp);
		string lastOp, op;

		// next ��������ڽ��ܵ� ) ʱ�����ŵ���һλ�Ƿ��� ( 
		bool next = false;

		// ������Ĳ�ͬ������в�ͬ�Ĵ���
		switch (CheckExp(exp)) {
		// ����������������ֹ����
		case 0:
			// ��������ջ����Ԫ�أ� ���Ƚ�����ջ�����ȼ����·��ŵ�ջ�����ȼ��� ���ݱȽϽ�����в�ͬ�Ĳ���
			opST->getTop(lastOp);

			// ջ�����ȼ�С��ջ�����ȼ�
			if (isp(lastOp) < icp(exp)) {
				// �·��������ջ�� �Ӽ��̽�����һ��� ������һ�ּ��
				opST->Push(exp);
				exp = getItems(str);
				continue;
			}
			// ջ�����ȼ�����ջ�����ȼ�
			else if (isp(lastOp) > icp(exp)) {
				// ����ջ��Ԫ�أ� �����������Ӧ����
				opST->Pop(op);
			}
			// ջ�����ȼ�����ջ�����ȼ���ֻ�����������ź�������������������ֹ���뿪ʼ��������
			else {
				// ����ջ��Ԫ��
				opST->Pop(op);
				// �������ֹ���� ˵���������
				if (op == "#") {
					// ��ʱ�ڵ�ջ����ջӦ��ȫ������������ ��ջ��ֻ����һ��Ԫ���ˣ����ڵ㣩�� �����������˵�����ʽ���Ϸ��� ���� false
					if (nodeST->getSize() == 1) break;
					else return false;
				}
				// ����������ţ� ����������������� Ȼ������Ӽ��̶�ȡ��һ����
				exp = getItems(str);
				continue;
			}

			// ���·�������������δ���������ŵ�ʱ�� ����ջԪ�ص���һ���Ƿ�Ϊ������
			if (exp == ")") {
				string check;
				opST->getTop(check);

				// ��һ���������ţ� next ��Ǽ�Ϊtrue
				if (check == "(") next = true;
			}

			// ���ݳ�ջ�ķ��Ž����ڵ�
			temNode = new BinTreeNode<string>(op);

			// �����Žڵ�ͽڵ�ջ�е�ǰ�����ڵ���������
			BinTreeNode<string> * left, * right;
			if (nodeST->IsEmpty()) return false;
			else nodeST->Pop(right);
			if (nodeST->IsEmpty()) return false;
			else nodeST->Pop(left);
			temNode->leftchild = left;
			temNode->rightchild = right;

			// ���� next ����Ƿ�Ϊ true ������������ŵı���Ƿ�Ϊ true
			if (next) temNode->tag = true;

			// ������ɺ�������ջ
			nodeST->Push(temNode);
			break;
		// ���������
		case 1:
			// ֱ����ڵ�ջ���Ӽ��̽�����һ����
			nodeST->Push(temNode);
			exp = getItems(str);
			break;
		// ����ǲ��Ϸ�ʽ�ӣ� ���� false�� ˵�����ʽ���Ϸ�
		case 2:
			return false;
			break;
		}
	}

	// ������ɺ� ���нڵ��Ѿ���ջ�������Ӻ��ˣ� ��ʱջ��Ԫ��һ���Ǹ��ڵ㣬 ���������ĸ��ڵ�����Ϊ������
	BinTreeNode<string>* TN;
	nodeST->getTop(TN);
	this->Tree->setRoot(TN);
	delete opST;
	delete nodeST;
	return true;
}

// ��������������������õ�� data��
void visit(BinTreeNode<string>* p) {
	cout << p->data << "  ";
}

// �������ʽ
void Expression::Polish() {
	// ֱ���� visit ����ʽǰ���������
	this->Tree->preOrder(visit);
}

// �����׺���ʽ
void Expression::Infix() {
	// ֱ���� visit ����ʽ�����������
	this->Tree->inOrder(visit);
}

// ����沨��ʽ
void Expression::ReversePolish() {
	// ֱ���� visit ����ʽ�����������
	this->Tree->postOrder(visit);
}

// ��ѭ��
void Expression::Loop() {
	// �ȸ������뽨���������������ʽ���Ϸ�����ʾ�û���������
	while (!BuildTree()) {
		cout << "��׺���ʽ���Ϸ���������������룺" << endl;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << endl << "�ɹ��������ʽ�Ķ��������������������ַ�ʽ��ӡ��" << endl << endl;

	// ������ʽ�Ϸ��� �������������������ʽ�� ��׺���ʽ�ͺ�׺���ʽ����
	cout << "�������ʽ��";
	Polish();
	cout << endl << "��׺���ʽ��";
	Infix();
	cout << endl << "�沨�����ʽ��";
	ReversePolish();

	cout << endl << "��ӡ��ɣ���ӭ�´ι��٣�" << endl << endl;
}

int main() {
	// ʵ����һ�����ʽ��
	Expression exp;

	// ������ѭ��ִ�в���
	exp.Loop();

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}