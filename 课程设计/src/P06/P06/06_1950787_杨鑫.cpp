# include <iostream>
# include <limits>
using namespace std;

// 前置声明
class Genealogy;

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

// 队列
template <class T>
class LinkedQueue {
private:
	LinkNode<T>* front, * rear;
public:
	LinkedQueue() : front(NULL), rear(NULL) {} // 构造函数
	~LinkedQueue() { makeEmpty(); } // 析构函数
	bool EnQueue(const T& x); // 进入队列
	bool DeQueue(T& x); // 出队列
	bool getFront(T& x) const; // 返回 front
	void makeEmpty(); // 置空
	bool IsEmpty() const { return front == NULL; } // 判断队列是否为空
	int getSize() const; // 返回队列元素个数

	 // 友元函数， 实现队列输出
	friend ostream& operator << (ostream& os, const LinkedQueue<T>& Q) {
		LinkNode<T>* p = Q.front;
		while (p != NULL) {
			os << p->data << "    ";
			p = p->link;
		}
		return os;
	}
};

// 置空
template <class T>
void LinkedQueue<T>::makeEmpty() {
	LinkNode<T>* p;

	// 逐元素释放
	while (front != NULL) {
		p = front;
		front = front->link;
		delete p;
	}
}

// 进入队列
template <class T>
bool LinkedQueue<T>::EnQueue(const T& x) {
	// 若队列为空
	if (IsEmpty()) {
		front = rear = new LinkNode<T>(x);
		if (front == NULL) return false;
	}
	else {  // 若队列不为空
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL) return false;
		rear = rear->link;
	}
	return true;
}

// 出队列
template <class T>
bool LinkedQueue<T>::DeQueue(T& x) {
	if (IsEmpty()) return false; // 队列为空， 返回 false
	LinkNode<T>* p = front;
	x = front->data;
	front = front->link; // 重置 front
	delete p;
	return true;
}

// 得到 front 的值
template <class T>
bool LinkedQueue<T>::getFront(T& x) const {
	if (IsEmpty()) return false; // 队列为空， 返回 false
	x = front->data;
	return true;
}

// 返回队列元素个数
template <class T>
int LinkedQueue<T>::getSize() const {
	LinkNode<T>* p = front;
	int k = 0;

	// 遍历并计数
	while (p != 0) {
		p = p->link;
		k++;
	}
	return k;
}

// 家谱树节点类
template <class T>
struct GenealogyTreeNode{
	T data;
	GenealogyTreeNode<T>* pre, *son, *brother; // 分别指向上一节点（父亲或者哥哥），儿子，弟弟
	GenealogyTreeNode() : pre(NULL), son(NULL), brother(NULL) {} // 构造函数
	GenealogyTreeNode(T& newData, GenealogyTreeNode<T>* p = NULL, GenealogyTreeNode<T>* s = NULL, GenealogyTreeNode<T>* b = NULL) : data(newData), pre(p), son(s), brother(b) {} // 构造函数
	~GenealogyTreeNode() {} // 析构函数
	bool operator < (const GenealogyTreeNode<T>& GTN) { return this->data < GTN.data; } // 重载小于符号
	bool operator > (const GenealogyTreeNode<T>& GTN) { return this->data > GTN.data; } // 重载大于符号
	bool operator == (const GenealogyTreeNode<T>& GTN) { return this->data == GTN.data; } // 重载 == 符号
};

// 家谱树类
template <class T>
class GenealogyTree{
private :
	GenealogyTreeNode<T>* root;
	void makeEmpty(GenealogyTreeNode<T>*& ptr); // 置空
public :
	GenealogyTree() : root(NULL) {}  // 构造函数
	~GenealogyTree() { makeEmpty(root); } // 析构函数
	bool IsEmpty() { return root == NULL; } // 检测是否为空
	void SetRoot(GenealogyTreeNode<T>*& R); // 设置根节点
	bool Insert(GenealogyTreeNode<T>*& d, GenealogyTreeNode<T>*& fa); // 插入节点
	bool Remove(GenealogyTreeNode<T>*& d); // 删除节点
	void Show(); //打印家谱树
};

// 置空
template <class T>
void GenealogyTree<T>::makeEmpty(GenealogyTreeNode<T>*& ptr) {
	if (ptr == NULL) return;

	// 递归释放子节点
	if (ptr->son != NULL) {
		makeEmpty(ptr->son);
	}

	// 递归释放兄弟节点
	if (ptr->brother != NULL) {
		makeEmpty(ptr->brother);
	}
	delete ptr; // 释放该节点
}

// 设置根节点
template <class T>
void GenealogyTree<T>::SetRoot(GenealogyTreeNode<T>*& R) {
	root = R;
}

// 插入
template <class T>
bool GenealogyTree<T>::Insert(GenealogyTreeNode<T>*& d, GenealogyTreeNode<T>*& fa) {
	// 若其父节点原本无儿子， 该节点成为其父节点长子
	if (fa->son == NULL) {
		fa->son = d;
		d->pre = fa;
	}
	else { 
		// 否则， 找到其最后一个兄弟节点， 然后链接在后面
		GenealogyTreeNode<T>* pr = fa->son;
		while (pr->brother != NULL) {
			pr = pr->brother;
		}
		pr->brother = d;
		d->pre = pr;
	}
	return true;
}

// 删除
template <class T>
bool GenealogyTree<T>::Remove(GenealogyTreeNode<T>*& d) {
	// 前面无节点（即为根节点）
	if (d->pre == NULL) {
		makeEmpty(d->son);
		delete d;
		root = NULL;
		return true;
	}
	// 若为其父节点的长子节点， 需要将其第一个兄弟变成长子
	if (d->pre->son == d) {
		d->pre->son = d->brother;
		if (d->brother != NULL) d->brother->pre = d->pre;
		makeEmpty(d->son);
		delete d;
		return true;
	}
	else {
		// 否则， 则直接把该节点前后兄弟节点相连即可
		d->pre->brother = d->brother;
		if (d->brother != NULL) d->brother->pre = d ->pre;
		makeEmpty(d->son);
		delete d;
		return true;
	}
}

// 打印
template <class T>
void GenealogyTree<T>::Show() {
	if (root == NULL) {
		cout << "家谱树已被清空， 暂无相关信息！" << endl << endl;
		return;
	}

	GenealogyTreeNode<T>* cur = NULL;
	LinkedQueue<GenealogyTreeNode<T>*> LQ;
	LQ.EnQueue(root); // 用队列便于分代打印

	cout << "======================================================" << endl;
	int count = 1;

	// 反复打印， 直到队列为空
	while (!LQ.IsEmpty()) {
		cout << "第 " << count << " 代：";
		
		int nums = LQ.getSize(); // 获取当前队列长度

		// 打印出一代子女的信息， 并把他们的子节点入队列
		for (int i = 0; i < nums; i++) {
			LQ.DeQueue(cur);
			cout << cur->data << "    ";

			// 将该节点的所有子节点入队列
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

// AVL树的节点类
template <class K>
struct AVLNode{
	K key;
	int bf;
	AVLNode<K>* left, *right;
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
private :
	AVLNode<K>* root;
	bool Insert(AVLNode<K>*& ptr, K& d); // 插入
	bool Remove(AVLNode<K>*& ptr, K& d); // 删除
	void RotateL(AVLNode<K>*& ptr); // 左单旋转
	void RotateR(AVLNode<K>*& ptr); // 右单旋转
	void RotateLR(AVLNode<K>*& ptr); // 先左后右旋转
	void RotateRL(AVLNode<K>*& ptr); // 先右后左旋转
	AVLNode<K>* Search(K& d, AVLNode<K>*& ptr); // 查找函数
	void makeEmpty(AVLNode<K>*& ptr); // 置空
public :
	AVLTree() : root(NULL) {} // 构造函数
	~AVLTree() { makeEmpty(root); } // 析构函数
	AVLNode<K>* Search(K& d) { return Search(d, root); } // 查找
	bool Insert(K& d) { return Insert(root, d); } // 插入
	bool Remove(K& d, bool tag); // 删除
	bool Update(K& curData, K& newData); // 更新
	void SetRoot(K& d); // 设置根节点
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

// 修改节点
template <class K>
bool AVLTree<K>::Update(K& curData, K& newData) {
	// 若修改后的名字已被使用
	if (Search(newData, root) != NULL) {
		return false;
	}

	// 先移除原节点， 修改值后再次插入， 确保仍然是符合二叉排序树的
	Remove(root, curData);
	curData->data = newData->data;
	Insert(curData);
	return true;
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
		if (*d == *(p->key)) return false; // 若已存在关键字相等的节点， 插入失败
		pr = p;
		st.Push(pr); // 用栈存储查找的路径
		if (*d < *(p->key)) p = p->left;
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
	if (*d < *(pr->key)) pr->left = p;
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
		if (*(q->key) > *(pr->key)) q->left = pr;
		else q->right = pr;
	}
	return true;
}

// 删除
template <class K>
bool AVLTree<K>::Remove(K& d, bool tag) {
	if (d == NULL) return false;

	// 删除子树
	if (d->son != NULL) {
		Remove(d->son, tag);
	}

	// 若 tag 为 true， 则删除后继兄弟节点
	if (tag && d->brother != NULL) {
		Remove(d->brother, tag);
	}
	Remove(root, d); // 删除该节点
}

template <class K>
bool AVLTree<K>::Remove(AVLNode<K>*& ptr, K& d) {
	AVLNode<K>* pr = NULL, * p = ptr, * q, * ppr = NULL;
	int n, nn = 0;
	LinkedStack<AVLNode<K>*> st;

	// 寻找删除位置
	while (p != NULL) {
		if (*d == *(p->key)) break; // 成功找到， 停止搜索
		pr = p;
		st.Push(pr); // 用栈保存路径
		if (*d < *(p->key)) p = p->left;
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

			 // 子树失衡的情况
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
	if (*d < *(ptr->key)) return Search(d, ptr->left); // 关键码小于此节点， 在其左子树中查找
	else if (*d > *(ptr->key)) return Search(d, ptr->right); // 关键码大于此节点， 在其右子树中查找
	else return ptr; // 关键码相等， 成功找到， 返回该节点
}

// 家谱类
class Genealogy{
private :
	GenealogyTree<string>* Tree; // 家谱树， 用于存放所有成员信息， 并体现他们的辈分关系
	AVLTree<GenealogyTreeNode<string>*>* AVLGenealogy; // AVL 家谱树， 以平衡二叉排序树的形式存放所有成员信息， 可以减少操作的时间复杂度
public :
	Genealogy(); // 构造函数
	~Genealogy(); // 析构函数
	void Complete(); // 完善家庭
	void AddMember(); // 添加成员
	void DeleteFamily(); // 解散子家庭
	void SearchMember(); // 寻找成员
	void ChangeMember(); // 修改成员
	void ShowGenealogy(); // 打印家谱
	void Loop(); // 主循环函数
};

// 构造函数
Genealogy::Genealogy() {
	Tree = new GenealogyTree<string>;
	AVLGenealogy = new AVLTree<GenealogyTreeNode<string>*>;
}

// 析构函数
Genealogy::~Genealogy() {
	delete Tree;
	delete AVLGenealogy;
}

// 完善家庭
void Genealogy::Complete() {
	cout << "请输入要建立家庭的人的姓名：";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// 检验成员是否存在
	while ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "该成员不存在，请重新输入：";
		delete temTN;
		cin >> name;
		temTN = new GenealogyTreeNode<string>(name);
	}

	// 删除临时节点， 将其变为“真实的”家谱树节点
	delete temTN;
	temTN = temAN->key;

	// 已有子女， 取消本次操作
	if (temTN->son != NULL) {
		cout << "该成员已有子女， 无法执行该操作。 若想添加子女， 请退出后执行添加命令！" << endl;
		return;
	}

	// 确定本次子女个数
	cout << "请输入 " << name << " 的儿女人数：";
	int nums;
	cin >> nums;
	while (nums < 1) {
		cout << "人数必须为正数！" << endl;
		cin >> nums;
	}

	// 用一个栈来存储本次输入的子女信息
	LinkedQueue<string>* nameQueue = new LinkedQueue<string>;
	cout << "请依次输入 " << name << " 的儿女的姓名：" << endl;

	// 依次插入
	for (int i = 0; i < nums; i++) {
		string temName;
		cin >> temName;
		GenealogyTreeNode<string>* inTN = new GenealogyTreeNode<string>(temName);

		// 尝试一次插入
		if (AVLGenealogy->Insert(inTN)) {
			// 插入成功， 将新节点与其父节点链接起来， 并入队列
			Tree->Insert(inTN, temTN);
			nameQueue->EnQueue(temName);
			cout << "第 " << i + 1 << " 个儿女插入成功！" << endl;
		}
		else {
			// 插入失败， 重新输入
			cout << "第 " << i + 1 << " 个儿女插入失败！请重新输入该子女及其以后的子女姓名：";
			i--;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	// 利用队列打印本次插入的子女信息
	cout << name << "的第一代子孙是：";
	cout << *nameQueue << endl;
	delete nameQueue;
}

// 添加成员
void Genealogy::AddMember() {
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// 检验父节点是否存在
	while ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "该成员不存在，请重新输入：";
		delete temTN;
		cin >> name;
		temTN = new GenealogyTreeNode<string>(name);
	}

	delete temTN;
	temTN = temAN->key;

	cout << "请输入 " << name << " 新添加的儿子（或女儿）的姓名：" << endl;
	string temName;
	cin >> temName;
	GenealogyTreeNode<string>* inTN = new GenealogyTreeNode<string>(temName);
	
	// 尝试插入
	while(!AVLGenealogy->Insert(inTN)) {
		cout << " 插入失败！请重新输入该子女的姓名：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> temName;
		delete inTN;
		inTN = new GenealogyTreeNode<string>(temName);
	}
	Tree->Insert(inTN, temTN);
	cout << "插入成功！" << endl;

	// 打印其第一代子女
	cout << name << "的第一代子孙是：";
	GenealogyTreeNode<string>* p = temTN->son;
	while (p != NULL) {
		cout << p->data << "    ";
		p = p->brother;
	}
	cout << endl;
}

// 删除
void Genealogy::DeleteFamily() {
	cout << "请输入要解散的家庭的人的姓名：";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// 寻找是否存在
	while ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "该成员不存在，请重新输入：";
		delete temTN;
		cin >> name;
		temTN = new GenealogyTreeNode<string>(name);
	}

	delete temTN;
	temTN = temAN->key;

	// 输出要解散的家庭的信息
	cout << "要解散的家庭的人是：" << name << endl;
	cout << name << "的第一代子孙是：";
	GenealogyTreeNode<string>* p = temTN->son;
	while (p != NULL) {
		cout << p->data << "    ";
		p = p->brother;
	}
	cout << endl;
	
	// 先删除该节点的子节点的所有子节点和兄弟节点已经该子节点本身
	AVLGenealogy->Remove(temTN->son, true);
	// 再删除该节点的所有子节点（不删除兄弟节点）
	AVLGenealogy->Remove(temTN, false);
	// 在家谱树中重新链接相关节点
	Tree->Remove(temTN);
}

// 查找
void Genealogy::SearchMember() {
	cout << "请输入要查找的人的姓名：";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// 在 AVL 树中查找
	 // 查找失败
	if ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "该成员不存在！" << endl;
		delete temTN;
		return;
	}

	delete temTN;
	temTN = temAN->key;

	// 查找成功， 打印相关信息
	cout << name << "存在！" << endl;
	cout << name << "的第一代子孙是：";
	GenealogyTreeNode<string>* p = temTN->son;
	while (p != NULL) {
		cout << p->data << "    ";
		p = p->brother;
	}
	cout << endl;
}

// 修改成员信息
void Genealogy::ChangeMember() {
	cout << "请输入要修改的人的姓名：";
	string name;
	cin >> name;
	GenealogyTreeNode<string>* temTN = new GenealogyTreeNode<string>(name);
	AVLNode< GenealogyTreeNode<string>*>* temAN = NULL;

	// 查找是否存在
	while ((temAN = AVLGenealogy->Search(temTN)) == NULL) {
		cout << "该成员不存在，请重新输入：";
		delete temTN;
		cin >> name;
		temTN = new GenealogyTreeNode<string>(name);
	}

	delete temTN;
	temTN = temAN->key;

	cout << "要修改的人是：" << name << endl;
	cout << "输入修改后的名字：" << endl;
	string newName;
	cin >> newName;
	GenealogyTreeNode<string>* newTN = new GenealogyTreeNode<string>(newName);
	AVLNode< GenealogyTreeNode<string>*>* newAN = NULL;

	// 查找新名字是否已经被使用
	while ((newAN = AVLGenealogy->Search(newTN)) != NULL) {
		cout << "该姓名已存在，请重新输入：";
		delete newTN;
		cin >> newName;
		newTN = new GenealogyTreeNode<string>(newName);
	}

	// 更新节点信息
	AVLGenealogy->Update(temTN, newTN);
	cout << "修改成功！" << endl;

	// 释放无用的临时节点
	delete newTN;
}

// 打印家谱树
void Genealogy::ShowGenealogy() {
	cout << endl << "当前家谱为：" << endl << endl;
	Tree->Show(); // 调用家谱树的打印函数
	cout << endl;
}

// 主循环函数
void Genealogy::Loop() {
	cout << "**                   家谱管理系统                   **" << endl;
	cout << "======================================================" << endl;
	cout << "**               请选择要执行的操作：               **" << endl;
	cout << "**                  A --- 完善家谱                  **" << endl;
	cout << "**                B --- 添加家庭成员                **" << endl;
	cout << "**                C --- 解散局部家庭                **" << endl;
	cout << "**                D --- 查找家庭成员                **" << endl;
	cout << "**              E --- 更改家庭成员姓名              **" << endl;
	cout << "**                S --- 查看家庭成员                **" << endl;
	cout << "**                  Z --- 退出程序                  **" << endl;
	cout << "======================================================" << endl;

	// 建立该家谱的祖先节点
	cout << "首先请建立一个家谱！" << endl << "请输入祖先姓名：" << endl;
	string ancestor;
	cin >> ancestor;
	GenealogyTreeNode<string>* t = new GenealogyTreeNode<string>(ancestor);

	// 分别为 AVL 树和家谱树设置根节点
	AVLGenealogy->SetRoot(t);
	Tree->SetRoot(t);
	cout << "此家谱的祖先是：" << ancestor << endl;

	// 不断询问用户所需操作并实现
	char op;
	while (true) {
		cout << "请输入要执行的操作：" << endl;
		cin >> op;
		switch (op) {
		case 'A': 
			// 完善家庭操作
			Complete();
			//ShowGenealogy();
			break;
		case 'B':
			// 添加成员操作
			AddMember();
			//ShowGenealogy();
			break;
		case 'C':
			// 解散子家庭操作
			DeleteFamily();
			//ShowGenealogy();
			break;
		case 'D':
			// 查找成员操作
			SearchMember();
			//ShowGenealogy();
			break;
		case 'E':
			// 修改成员信息操作
			ChangeMember();
			//ShowGenealogy();
			break;
		case 'S':
			// 打印家谱树操作
			ShowGenealogy();
			break;
		case 'Z':
			// 退出操作
			cout << "本次程序结束， 欢迎下次光临！" << endl << endl;
			//ShowGenealogy();
			return;
			break;
		default:
			// 其他无效指令
			cout << "无效指令， 请重新输入！";
			break;
		}

		// 清空缓冲区
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// 检测家谱是否被删空， 若删空则退出程序
		if (Tree->IsEmpty()) {
			cout << "家谱树已被清空， 本次操作结束， 欢迎下次光临！" << endl << endl;
			return;
		}
	}
}

int main() {
	// 实例化一个家谱类
	Genealogy MyGenealogy;

	// 调用主循环实现相应操作
	MyGenealogy.Loop();

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}