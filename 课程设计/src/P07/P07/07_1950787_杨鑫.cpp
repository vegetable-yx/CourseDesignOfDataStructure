# include <iostream>
# include <limits>
using namespace std;

// 节点类
template<class T>
struct LinkNode {
	T data;
	LinkNode <T>* link;
	LinkNode(LinkNode<T>* ptr = NULL) : link(ptr) {}; // 构造函数
	LinkNode(const T& tem, LinkNode<T>* ptr = NULL) : data(tem), link(ptr) {}; // 构造函数
};

// 栈
template <class T>
class LinkedStack {
public:
	LinkedStack() : top(NULL) {} // 构造函数
	~LinkedStack() { makeEmpty(); } // 析构函数
	void Push(const T& x); // 入栈
	bool Pop(T& x); // 出栈
	bool getTop(T& x) const; // 得到栈顶元素
	bool IsEmpty() const { return top == NULL; } // 判断是否栈空
	int getSize() const; // 返回栈中元素个数
	void makeEmpty(); // 栈置空
private:
	LinkNode<T>* top;  // 栈顶元素
};

// 栈置空
template <class T>
void LinkedStack<T>::makeEmpty() {
	LinkNode<T>* p;

	// 逐节点释放
	while (top != NULL) {
		p = top;
		top = top->link;
		delete p;
	}
}

// 入栈
template <class T>
void LinkedStack<T>::Push(const T& x) {
	top = new LinkNode<T>(x, top); // 新元素成为栈顶并与之前元素链接
}

// 出栈
template <class T>
bool LinkedStack<T>::Pop(T& x) {
	if (IsEmpty()) return false; // 栈空， 直接返回false
	LinkNode<T>* p = top;
	top = top->link; // 重置栈顶元素
	x = p->data;
	delete p;
	return true;
}

// 得到栈顶元素
template <class T>
bool LinkedStack<T>::getTop(T& x) const {
	if (IsEmpty()) return false;  // 栈空， 直接返回false
	x = top->data; // 降栈顶元素赋值给 x
	return true;
}

// 返回栈中元素个数
template <class T>
int LinkedStack<T>::getSize() const {
	LinkNode<T>* p = top;
	int k = 0;

	// 遍历元素并计数
	while (p != NULL) {
		p = p->link;
		++k;
	}
	return k;
}

// 二叉树节点类
template <class T>
struct BinTreeNode {
	T data;
	bool tag; // 增设一个标记， 用于标记是否需要进行括号打印
	BinTreeNode<T>* leftchild, * rightchild;
	BinTreeNode() : tag(0), leftchild(NULL), rightchild(NULL) {} // 构造函数
	BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL) : tag(0), data(x), leftchild(l), rightchild(r) {} // 构造函数
};

// 二叉树类
template <class T>
class BinaryTree {
public:
	BinaryTree() : root(NULL) {} // 构造函数
	~BinaryTree() { destroy(root); } // 析构函数
	bool IsEmpty() { return root == NULL; } // 是否为空
	BinTreeNode<T>* Parent(BinTreeNode<T>* current) { return (root == NULL || root == current ? NULL : Parent(root, current)); } // 得到父节点
	BinTreeNode<T>* LeftChild(BinTreeNode<T>* current) { return current == NULL ? NULL : current->leftchild; } // 得到左子节点
	BinTreeNode<T>* RightChild(BinTreeNode<T>* current) { return current == NULL ? NULL : current->rightchild; } // 得到右子节点
	int Height() { return Height(root); } // 得到二叉树高度
	int Size() { return Size(root); } // 得到二叉树节点个数
	BinTreeNode<T>* getRoot() const { return root; } // 返回根节点
	void setRoot(BinTreeNode<T>* newRoot) { root = newRoot; } // 设置根节点
	void preOrder(void (*visit) (BinTreeNode<T>* p)) { preOrder(root, visit); } // 前序遍历
	void inOrder(void (*visit) (BinTreeNode<T>* p)) { inOrder(root, visit); } // 中序遍历
	void postOrder(void (*visit) (BinTreeNode<T>* p)) { postOrder(root, visit); } // 后序遍历
private:
	BinTreeNode<T>* root;
	void destroy(BinTreeNode<T>*& subTree); // 释放一个子树
	int Height(BinTreeNode<T>* subTree) const; // 返回子树高度
	int Size(BinTreeNode<T>*) const; // 返回子树节点个数
	BinTreeNode<T>* Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current); // 返回父节点
	void preOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p)); // 前序遍历
	void inOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p)); // 中序遍历
	void postOrder(BinTreeNode<T>*& subTree, void (*visit)(BinTreeNode<T>* p)); // 后序遍历
};

// 释放子树
template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T>*& subTree) {
	// 递归释放左子树和右子树后再释放根节点
	if (subTree != NULL) {
		destroy(subTree->leftchild);
		destroy(subTree->rightchild);
		delete subTree;
	}
}

// 返回父节点
template <class T>
BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) {
	if (subTree == NULL) return NULL; // 当前子树为空

	 // 子树左子节点或者右子节点为待查节点
	if (subTree->leftChild == current || subTree->rightchild == current) return subTree;
	BinTreeNode<T>* p;

	// 分别在左右子树中查找该点的父节点
	if ((p = Parent(subTree->rightchild, current)) != NULL) return p;
	else return Parent(subTree->leftchild, current);
}

// 中序遍历
template <class T>
void BinaryTree<T>::inOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		// 若打印括号标记为 true， 则先打印左括号
		if (subTree->tag) cout << "( ";

		// 先遍历左子树， 然后遍历该节点， 然后遍历右子树
		inOrder(subTree->leftchild, visit);
		visit(subTree);
		inOrder(subTree->rightchild, visit);

		// 若打印括号标记为 true， 则在最后打印右括号
		if (subTree->tag) cout << ") ";
	}
}

// 前序遍历
template <class T>
void BinaryTree<T>::preOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		// 若打印括号标记为 true， 则先打印左括号
		if (subTree->tag) cout << "( ";

		// 先遍历该节点， 然后遍历左子树， 然后遍历右子树
		visit(subTree);
		preOrder(subTree->leftchild, visit);
		preOrder(subTree->rightchild, visit);

		// 若打印括号标记为 true， 则在最后打印右括号
		if (subTree->tag) cout << ") ";
	}
}

// 后序遍历
template <class T>
void BinaryTree<T>::postOrder(BinTreeNode<T>*& subTree, void (*visit) (BinTreeNode<T>* p)) {
	if (subTree != NULL) {
		// 若打印括号标记为 true， 则先打印左括号
		if (subTree->tag) cout << "( ";

		// 先遍历左子树， 然后遍历右子树， 然后遍历该节点
		postOrder(subTree->leftchild, visit);
		postOrder(subTree->rightchild, visit);
		visit(subTree);

		// 若打印括号标记为 true， 则在最后打印右括号
		if (subTree->tag) cout << ") ";
	}
}

// 返回子树节点个数
template <class T>
int BinaryTree<T>::Size(BinTreeNode<T>* subTree) const {
	if (subTree == NULL) return 0;
	// 递归， 节点个数等于左子树节点个数 + 右子树节点个数 + 1
	else return 1 + Size(subTree->leftchild) + Size(subTree->rightchild);
}

// 返回子树高度
template <class T>
int BinaryTree<T>::Height(BinTreeNode<T>* subTree) const {
	if (subTree == NULL) return 0;
	// 子树高度为左子树和右子树中的最大高度 + 1
	else {
		int LHeight = Height(subTree->leftchild);
		int RHeight = Height(subTree->rightchild);
		return LHeight < RHeight ? RHeight + 1 : LHeight + 1;
	}
}

// 重载 == 运算符
template <class T>
int operator == (const BinaryTree<T>& s, const BinaryTree<T>& t) {
	// 调用 equal 函数进行逐节点比较
	return equal(s.root, t.root);
}

// 比较
template <class T>
bool equal(BinTreeNode<T>* a, BinTreeNode<T>* b) {
	if (a == NULL && b == NULL) return true;
	// 分别比较 a, b 的 data 和各自子树是否相等
	if (a != NULL && b != NULL && a->data == b->data && equal(a->leftchild, b->leftchild) && equal(a->rightchild, b->rightchild)) return true;
	else return false;
}

// 表达式类
class Expression {
private :
	BinaryTree<string>* Tree; // 存放表达式的二叉树
	string getItems(string& str); // 根据输入表达式每次取出一项
public :
	Expression(); // 构造函数
	~Expression() { delete Tree; } // 析构函数
	int CheckExp(string exp); // 检查项为数字还是符号，或者是非法字符串
	int isp(string exp); // 返回符号对应的栈内优先数
	int icp(string exp); // 返回符号对应的栈外优先数
	bool BuildTree(); // 根据输入建立二叉树
	void Polish(); // 通过前序遍历二叉树输出波兰表达式
	void Infix(); // 通过中序遍历二叉树输出中序表达式
	void ReversePolish(); // 通过后序遍历二叉树输出逆波兰式
	void Loop(); // 主循环函数
};

// 构造函数
Expression::Expression() {
	Tree = new BinaryTree<string>;
}

// 逐个得到表达式
string Expression::getItems(string& str) {
	// 检查是否为运算符
	if (CheckExp(str.substr(0, 1)) == 0) {
		// 修改 str 后返回运算符
		string temStr = str.substr(0, 1);
		str = str.substr(1);
		return temStr;
	}
	else {
		// 尝试返回一个数字
		for (int i = 0; i < str.length(); i++) {
			if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
				if (i == 0) return "?"; // 返回错误码

				// 修改 str 后返回运算符
				string temStr = str.substr(0, i);
				str = str.substr(i);
				return temStr;
			}
		}
	}

	return "?"; // 返回错误码
}

// 检查表达式是哪一种形式的
int Expression::CheckExp(string exp) {
	// 第一种：运算符及终止符号
	if (exp == "+" || exp == "-" || exp == "*" || exp == "/" || exp == "(" || exp == ")" || exp == "#") {
		return 0;
	}
	// 否则，检测是否为纯数字（即合法的数字）
	else {
		// dot 标记小数点是否存在， 合法的数字最多只能有一个小数点
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

// 返回项的栈内优先数
int Expression::isp(string exp) {
	if (exp == "#") return 0;
	else if (exp == "(") return 1;
	else if (exp == "*" || exp == "/") return 5;
	else if (exp == "+" || exp == "-") return 3;
	else return 6;
 }

// 返回项的栈外优先数
int Expression::icp(string exp) {
	if (exp == "#") return 0;
	else if (exp == "(") return 6;
	else if (exp == "*" || exp == "/") return 4;
	else if (exp == "+" || exp == "-") return 2;
	else return 1;
}

// 根据输入建立二叉树
bool Expression::BuildTree() {
	cout << "请输入中缀表达式（只含数字和 '+'，'-'，'*'，'/'，'('，')' 四种运算符和左右括号）：" << endl;
	string str, exp;
	cin >> str;
	str.append("#"); // 末尾添加一个结束标志符
	exp = getItems(str);

	// 节点栈， 将形成的节点存在栈中， 等待何时的时机将他们弹出栈并链接起来
	LinkedStack<BinTreeNode<string>*>* nodeST = new LinkedStack<BinTreeNode<string>*>;

	// 符号栈， 存放符号， 根据优先级确定是否入栈或者是弹出节点栈的元素并把他们链接起来
	LinkedStack<string>* opST = new LinkedStack<string>;
	opST->Push("#"); // 先放入一个 # 作为起始符号

	 // 反复执行， 直接符号栈空或者检测出不合法的状态
	while (!opST->IsEmpty()) {
		// 根据输入的项建立一个临时节点
		BinTreeNode<string>* temNode = new BinTreeNode<string>(exp);
		string lastOp, op;

		// next 标记用于在接受到 ) 时检测符号的下一位是否是 ( 
		bool next = false;

		// 根据项的不同种类进行不同的处理
		switch (CheckExp(exp)) {
		// 如果是运算符或者终止符号
		case 0:
			// 弹出符号栈顶的元素， 并比较它的栈内优先级和新符号的栈外优先级， 根据比较结果进行不同的操作
			opST->getTop(lastOp);

			// 栈内优先级小于栈外优先级
			if (isp(lastOp) < icp(exp)) {
				// 新符号入符号栈， 从键盘接收下一个项， 进行下一轮检测
				opST->Push(exp);
				exp = getItems(str);
				continue;
			}
			// 栈内优先级大于栈外优先级
			else if (isp(lastOp) > icp(exp)) {
				// 弹出栈顶元素， 在下面进行相应操作
				opST->Pop(op);
			}
			// 栈内优先级等于栈外优先级（只可能是右括号和左括号相遇或者是终止符与开始符相遇）
			else {
				// 弹出栈顶元素
				opST->Pop(op);
				// 如果是终止符， 说明输入结束
				if (op == "#") {
					// 此时节点栈所有栈应该全部链接起来， 即栈中只存在一个元素了（根节点）， 如果不是这样说明表达式不合法， 返回 false
					if (nodeST->getSize() == 1) break;
					else return false;
				}
				// 如果是右括号， 即与左括号相抵消， 然后继续从键盘读取下一个项
				exp = getItems(str);
				continue;
			}

			// 当新符号是右括号且未遇到左括号的时候， 检测出栈元素的下一个是否为左括号
			if (exp == ")") {
				string check;
				opST->getTop(check);

				// 下一个是左括号， next 标记记为true
				if (check == "(") next = true;
			}

			// 根据出栈的符号建立节点
			temNode = new BinTreeNode<string>(op);

			// 将符号节点和节点栈中的前两个节点链接起来
			BinTreeNode<string> * left, * right;
			if (nodeST->IsEmpty()) return false;
			else nodeST->Pop(right);
			if (nodeST->IsEmpty()) return false;
			else nodeST->Pop(left);
			temNode->leftchild = left;
			temNode->rightchild = right;

			// 根据 next 标记是否为 true 决定其输出括号的标记是否为 true
			if (next) temNode->tag = true;

			// 链接完成后重新入栈
			nodeST->Push(temNode);
			break;
		// 如果是数字
		case 1:
			// 直接入节点栈并从键盘接收下一个项
			nodeST->Push(temNode);
			exp = getItems(str);
			break;
		// 如果是不合法式子， 返回 false， 说明表达式不合法
		case 2:
			return false;
			break;
		}
	}

	// 建立完成后， 所有节点已经入栈并且链接好了， 这时栈顶元素一定是根节点， 将二叉树的根节点设置为它即可
	BinTreeNode<string>* TN;
	nodeST->getTop(TN);
	this->Tree->setRoot(TN);
	delete opST;
	delete nodeST;
	return true;
}

// 遍历函数（这里是输出该点的 data）
void visit(BinTreeNode<string>* p) {
	cout << p->data << "  ";
}

// 输出波兰式
void Expression::Polish() {
	// 直接以 visit 的形式前序遍历即可
	this->Tree->preOrder(visit);
}

// 输出中缀表达式
void Expression::Infix() {
	// 直接以 visit 的形式中序遍历即可
	this->Tree->inOrder(visit);
}

// 输出逆波兰式
void Expression::ReversePolish() {
	// 直接以 visit 的形式后序遍历即可
	this->Tree->postOrder(visit);
}

// 主循环
void Expression::Loop() {
	// 先根据输入建立二叉树，若表达式不合法则提示用户重新输入
	while (!BuildTree()) {
		cout << "中缀表达式不合法，请检查后重新输入：" << endl;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cout << endl << "成功建立表达式的二叉树，接下来将以三种方式打印！" << endl << endl;

	// 输入表达式合法， 建立二叉树后输出波兰式， 中缀表达式和后缀表达式即可
	cout << "波兰表达式：";
	Polish();
	cout << endl << "中缀表达式：";
	Infix();
	cout << endl << "逆波兰表达式：";
	ReversePolish();

	cout << endl << "打印完成，欢迎下次光临！" << endl << endl;
}

int main() {
	// 实例化一个表达式类
	Expression exp;

	// 调用主循环执行操作
	exp.Loop();

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}