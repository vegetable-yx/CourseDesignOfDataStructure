# include <iostream>
# include <string>
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

// AVL树的节点类
template <class K>
struct AVLNode {
	K key;
	int bf;
	AVLNode<K>* left, * right;
	AVLNode() : bf(0), left(NULL), right(NULL) {} // 构造函数
	AVLNode(K newKey, AVLNode<K>* newLeft = NULL, AVLNode<K>* newRight = NULL) : key(newKey), bf(0), left(newLeft), right(newRight) {} // 构造函数
	~AVLNode() {} // 析构函数

	// 三个重载比较运算符的函数
	bool operator < (const AVLNode<K>& AN) { return this->key < AN.key; }
	bool operator > (const AVLNode<K>& AN) { return this->key > AN.key; }
	bool operator == (const AVLNode<K>& AN) { return this->key == AN.key; }
};

// AVL树类
template <class K>
class AVLTree {
private:
	AVLNode<K>* root;
	bool Insert(AVLNode<K>*& ptr, K& d); // 插入
	bool Remove(AVLNode<K>*& ptr, K& d); // 删除
	void RotateL(AVLNode<K>*& ptr); // 左单旋转
	void RotateR(AVLNode<K>*& ptr); // 右单旋转
	void RotateLR(AVLNode<K>*& ptr); // 先左后右旋转
	void RotateRL(AVLNode<K>*& ptr); // 先右后左旋转
	AVLNode<K>* Search(K& d, AVLNode<K>*& ptr); // 查找函数
	void makeEmpty(AVLNode<K>*& ptr); // 置空
	void Show(AVLNode<K>*& ptr); // 输出
public:
	AVLTree() : root(NULL) {} // 构造函数
	~AVLTree() { makeEmpty(root); } // 析构函数
	AVLNode<K>* Search(K& d) { return Search(d, root); } // 查找
	bool Insert(K& d) { return Insert(root, d); } // 插入
	bool Remove(K& d) { return Remove(root, d); }; // 删除
	void SetRoot(K& d); // 设置根节点
	void Show() { Show(root); } // 输出
};

// 左单旋转
template <class K>
void AVLTree<K>::RotateL(AVLNode<K>*& ptr) {
	AVLNode<K>* subL = ptr; // 要左旋转的节点
	ptr = subL->right; // 原节点的右子女
	subL->right = ptr->left; // 移去左边子女
	ptr->left = subL; // 旋转
	ptr->bf = subL->bf = 0; // 更新 bf
}

// 右单旋转
template <class K>
void AVLTree<K>::RotateR(AVLNode<K>*& ptr) {
	AVLNode<K>* subR = ptr; // 要旋转的右节点
	ptr = subR->left; // 原节点的左子女
	subR->left = ptr->right; // 移去右边子女
	ptr->right = subR; // 旋转
	ptr->bf = subR->bf = 0; // 更新 bf
}

// 先左后右旋转
template <class K>
void AVLTree<K>::RotateLR(AVLNode<K>*& ptr) {
	AVLNode<K>* subR = ptr, * subL = subR->left;
	ptr = subL->right;
	subL->right = ptr->left;  // 移去左边子女
	ptr->left = subL; // 左单旋转
	if (ptr->bf <= 0) subL->bf = 0; // 插入新节点后左子树高
	else subL->bf = -1; // 否则
	subR->left = ptr->right; // 移去右边子女
	ptr->right = subR; // 右单旋转

	 // 更新 bf
	if (ptr->bf == -1) subR->bf = 1;
	else subR->bf = 0;
	ptr->bf = 0;
}

// 先右后左旋转
template <class K>
void AVLTree<K>::RotateRL(AVLNode<K>*& ptr) {
	AVLNode<K>* subL = ptr, * subR = ptr->right;
	ptr = subR->left;
	subR->left = ptr->right; // 移去右边子女
	ptr->right = subR; // 右单旋转
	if (ptr->bf >= 0) subR->bf = 0; // 插入新节点后右子树高
	else subR->bf = 1; // 否则
	subL->right = ptr->left; // 移去左边子女
	ptr->left = subL; // 左单旋转

	 // 更新 bf
	if (ptr->bf == 1) subL->bf = -1;
	else subL->bf = 0;
	ptr->bf = 0;
}

// 设置根节点
template <class K>
void AVLTree<K>::SetRoot(K& d) {
	this->root = new AVLNode<K>;
	this->root->key = d;
}

// 置空
template <class K>
void AVLTree<K>::makeEmpty(AVLNode<K>*& ptr) {
	if (ptr == NULL) return;

	// 递归置空左子树
	if (ptr->left != NULL) {
		makeEmpty(ptr->left);
	}

	// 递归置空右子树 
	if (ptr->right != NULL) {
		makeEmpty(ptr->right);
	}
	delete ptr; // 删除该节点
}

template <class K>
bool AVLTree<K>::Insert(AVLNode<K>*& ptr, K& d) {
	AVLNode<K>* pr = NULL, * p = ptr, * q;
	int n;
	LinkedStack<AVLNode<K>*> st;

	// 寻找插入位置
	while (p != NULL) {
		if (d == p->key) return false; // 若已存在关键字相等的节点， 插入失败
		pr = p;
		st.Push(pr); // 用栈存储查找的路径
		if (d < p->key) p = p->left;
		else p = p->right;
	}

	// 创建新节点
	p = new AVLNode<K>;
	p->key = d;

	// 若之前为空树
	if (pr == NULL) {
		ptr = p;
		return true;
	}

	// 新节点插入
	if (d < pr->key) pr->left = p;
	else pr->right = p;

	// 重新平衡 AVL 树
	while (!st.IsEmpty()) {
		st.Pop(pr);  // 从栈中弹出父节点
		if (p == pr->left) pr->bf--;  // 调整平衡因子
		else pr->bf++;
		if (pr->bf == 0) break; // 不需要调整， 已经平衡
		if (pr->bf == 1 || pr->bf == -1) p = pr;  // 该子树平衡， 但还需检测上面的节点是否平衡
		else {  // 该子树已经失衡
			n = (pr->bf < 0) ? -1 : 1; // 区别单双旋转的标志

			 // 单旋转情况
			if (p->bf == n) {
				if (n == -1) RotateR(pr);
				else RotateL(pr);
			}
			// 双旋转情况
			else {
				if (n == -1) RotateLR(pr);
				else RotateRL(pr);
			}
			break;
		}
	}

	// 已经调整至根节点
	if (st.IsEmpty()) ptr = pr;
	// 中间重新链接
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

	// 寻找删除位置
	while (p != NULL) {
		if (d == p->key) break; // 成功找到， 停止搜索
		pr = p;
		st.Push(pr); // 用栈保存路径
		if (d < p->key) p = p->left;
		else p = p->right;
	}

	if (p == NULL) return false; // 未找到， 取消删除操作

	 // 若被删节点有两个子女， 向下搜索
	if (p->left != NULL && p->right != NULL) {
		pr = p;
		st.Push(pr);
		q = p->left;
		while (q->right != NULL) {
			pr = q;
			st.Push(pr);
			q = q->right;
		}
		p->key = q->key; // 用 q 的值填补 p
		p = q; // 被删节点转换 
	}

	// 被删节点只有一个子女
	bool leftTag = false;
	if (p->left != NULL) q = p->left;
	else q = p->right;
	if (pr == NULL) ptr = q; // 若被删节点为根节点
	else {
		if (pr->left == p) pr->left = q, leftTag = true; // 链接
		else pr->right = q;

		// 重新平衡 AVL 树
		while (!st.IsEmpty()) {
			st.Pop(pr);  // 从栈中退出父节点
			if (leftTag || pr->left == q) pr->bf++, leftTag = false; // 调整平衡因子
			else pr->bf--;
			if (!st.IsEmpty()) {
				st.getTop(ppr);
				nn = (ppr->left == pr) ? -1 : 1;
			}
			else nn = 0; // 栈空， 不必链接
			if (pr->bf == 1 || pr->bf == -1) break; // 不必调整的情况

			 // 需要调整的情况
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

				// 单旋转情况
				if (q->bf == n) {
					if (n == -1) RotateR(pr);
					else RotateL(pr);
				}
				// 双旋转情况
				else {
					if (n == -1) RotateLR(pr);
					else RotateRL(pr);
				}
				if (nn == -1) ppr->left = pr;
				else if (nn == 1) ppr->right = pr; // 链接
			}

			// 子树未失衡， 但需要向上检测
			q = pr;
		}
		if (st.IsEmpty()) ptr = pr; // 调整到根节点
	}
	delete p;
	return true;
}

// 查找
template <class K>
AVLNode<K>* AVLTree<K>::Search(K& d, AVLNode<K>*& ptr) {
	if (ptr == NULL) return NULL;
	if (d < ptr->key) return Search(d, ptr->left); // 关键码小于此节点， 在其左子树中查找
	else if (d > ptr->key) return Search(d, ptr->right); // 关键码大于此节点， 在其右子树中查找
	else return ptr; // 关键码相等， 成功找到， 返回该节点
}

// 输出
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

// 系统类
class System{
private :
	AVLTree<int>* Tree;
public :
	System(); // 构造函数
	~System(); // 析构函数
	bool BuildTree(); // 建立树
	void Show(); // 展示
	bool Insert(); // 插入
	bool Remove(); // 删除
	bool Search(); // 寻找
	void Loop(); // 主循环
};

// 构造函数
System::System() {
	Tree = new AVLTree<int>;
}

// 析构函数
System::~System() {
	delete Tree;
}

// 建立树
bool System::BuildTree() {
	// 先删除原来的树， 重新建立一颗新树
	delete Tree;
	Tree = new AVLTree<int>;

	cout << "Please input keys to create tree ( input '#' to stop ) : ";
	string temNum;
	cin >> temNum;

	// 不断读入， 直到输入为 #
	while (temNum != "#") {
		// 如果不是 # ， 将其转换为数字
		int num = stoi(temNum);

		// 尝试插入， 若失败说明已有该元素
		if (!Tree->Insert(num)) {
			cout << "The key ( " << num << " ) is repeated ! " << endl;
		}
		cin >> temNum;
	}

	return true;
}

// 展示
void System::Show() {
	cout << "The Tree is : " << endl;

	// 调用 AVL 树的中序遍历函数打印信息
	Tree->Show();
	cout << endl << endl;
}

// 插入
bool System::Insert() {
	cout << "Please input key which inserted : ";
	int num;
	cin >> num;

	// 尝试插入， 若失败， 说明已经存在该元素
	if (Tree->Insert(num)) {
		cout << "Successfully inserted ! " << endl;
		return true;
	}
	else {
		cout << num << " is repeated !  " << endl;
		return false;
	}
}

// 删除
bool System::Remove() {
	cout << "Please input key which removed : ";
	int num;
	cin >> num;

	// 尝试删除， 若失败说明该元素不存在
	if (Tree->Remove(num)) {
		cout << "Successfully removed ! " << endl;
		return true;
	}
	else {
		cout << num << " is not in !  " << endl;
		return false;
	}
}

// 查询
bool System::Search() {
	cout << "Please input key which searched : ";
	int num;
	cin >> num;

	// 根据 AVL树 的查询函数进行搜索
	if (Tree->Search(num)) {
		cout << "Successfully searched ! " << endl;
		return true;
	}
	else {
		cout << "No this key ! " << endl;
		return false;
	}
}

// 主循环
void System::Loop() {
	cout << "**                    二叉排序树                    **" << endl;
	cout << "======================================================" << endl;
	cout << "**               请选择要执行的操作：               **" << endl;
	cout << "**               1 --- 建立二叉排序树               **" << endl;
	cout << "**               2 --- 插入元素                     **" << endl;
	cout << "**               3 --- 删除元素                     **" << endl;
	cout << "**               4 --- 查找元素                     **" << endl;
	cout << "**               5 --- 查看二叉树                   **" << endl;
	cout << "**               6 --- 退出程序                     **" << endl;
	cout << "======================================================" << endl << endl;

	// 不断接受用户命令
	while (true) {
		int choice;
		cout << "Please select : ";
		cin >> choice;

		switch (choice) {
		case 1 :
			// 建立树
			BuildTree();
			Show();
			break;
		case 2:
			// 插入
			Insert();
			Show();
			break;
		case 3:
			// 删除
			Remove();
			Show();
			break;
		case 4 :
			// 检索
			Search();
			Show();
			break;
		case 5:
			// 显示
			Show();
			break;
		case 6 :
			// 退出程序
			cout << "Welcome back soon ! " << endl << endl;
			return;
			break;
		default:
			// 不合法命令
			cout << "Illigal input ! " << endl;

			// 清空缓存区
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
}

int main() {
	// 实例化一个系统
	System sys;

	// 调用主循环函数
	sys.Loop();

# ifdef _WIN32
	system("pause");
#endif

	return 0;
}