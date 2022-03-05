# include <iostream>
using namespace std;

// Stack 的前置声明
class Stack;

// 节点类， 用于存储点的坐标信息
struct Node{
	int x;
	int y;
	Node* link;
	Node(int newX = 0, int newY = 0, Node* newLink = NULL) : x(newX), y(newY), link(newLink) {} // 参数有默认值的构造函数
	~Node() {}
	Node(const Node& n) :x(n.x), y(n.y), link(n.link) {} // 拷贝构造函数
	friend class Stack; // 声明 Stack 为友类
};

// 栈
class Stack{
private :
	Node* top; // 栈顶
public :
	Stack() :top(NULL) {} // 默认构造函数
	~Stack(); // 析构函数
	void Push(int x, int y); // 入栈
	bool Pop(int &x, int &y); // 出栈
};

Stack::~Stack() {
	Node* p;
	while (top != NULL) { // 逐节点释放
		p = top;
		top = top->link;
		delete p;
	}
}

void Stack::Push(int x, int y) {
	Node* newNode = new Node(x, y, top); // 新节点的建立与链接
	top = newNode; // 更新栈顶
}

bool Stack::Pop(int &x, int &y) {
	if (top == NULL) return false; // 栈空，返回false
	x = top->x, y = top->y;
	Node* temNode = top;
	top = top->link; // 栈顶元素更新
	delete temNode;
	return true;
}

// 八皇后类， 实现八皇后游戏功能的封装
class NQueen{
public :
	NQueen(int sz = 0); // 构造函数
	~NQueen() { delete board, delete stack; } // 析构函数
	void Solution(); // 求解
	bool Illigal(int rows, int cols); // 判断位置是否合法
	void Print(); // 打印解法
private :
	int size; // 棋盘大小（皇后个数）
	int numOfSolutions; // 解的个数
	char** board; // 棋盘
	Stack* stack; // 临时存储可能的解法节点的栈
};

NQueen::NQueen(int sz) { // 构造函数
	size = sz;
	numOfSolutions = 0;
	stack = new Stack;

	// 初始化棋盘
	board = new char* [size];
	for (int i = 0; i < size; i++) board[i] = new char[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) board[i][j] = '0';
}

// 求解八皇后问题的非递归算法
void NQueen::Solution() {
	int lastX = -1, lastY = -1; // 标记上次出栈的坐标位置，若无，则用 (-1, -1) 来表示

	// 不断寻找解
	int rows = 0;
	while (true) {
		bool tag = false; // 标记，当前行是否有合法的位置并放置皇后于该位置上
		for (int cols = lastY + 1; cols < size; cols++) { // 寻找当前行是否有合法的位置
			if (Illigal(rows, cols)) {
				stack->Push(rows, cols);
				board[rows][cols] = 'X';
				tag = true; // 更新标记
				break;
			}
		}
		if (!tag) { // 未找到位置
			rows--;
			if (!(stack->Pop(lastX, lastY))) { // 栈空，说明已经完成寻找
				cout << "共有" << numOfSolutions << "种解法！" << endl;
				return;
			}
			board[lastX][lastY] = '0'; // 棋盘该位置还原为无皇后状态
		}
		else { // 找到位置并放置
			if (rows == size - 1) { // 已经是最后一行，说明成功找到一组解
				Print(); // 打印
				numOfSolutions++; // 解数量++
				stack->Pop(lastX, lastY); // 弹出，从而进行下一轮解的寻找
				board[lastX][lastY] = '0';
			}
			else rows++, lastX = -1, lastY = -1; // 不是最后一行，继续往下一行寻找
		}
	}
}

bool NQueen::Illigal(int rows, int cols) { // 判断位置是否合法
	// 条件一：同一列不能有两个及以上的皇后
	for (int i = 0; i < rows; i++) {
		if (board[i][cols] == 'X') return false;
	}
	// 条件二：左斜线方向不能有两个及以上的皇后
	for (int i = rows, j = cols; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == 'X') return false;
	}
	// 条件三：右斜线方向不能有两个及以上的皇后
	for (int i = rows, j = cols; i >= 0 && j < size; i--, j++) {
		if (board[i][j] == 'X') return false;
	}
	return true;
}

void NQueen::Print() { // 打印解法之一
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j] << "    ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

// 系统类
class System {
private :
	NQueen* NQ;
public :
	System() : NQ(NULL) {} // 构造函数
	~System() { delete NQ; } // 析构函数
	void Start(); // 初始化游戏
	void MakeBoard(int sz); // 建立初始棋盘
	void FindMethod(); // 求解
};

void System::Start() { // 初始化游戏
	cout << "现有 N * N 的棋盘， 放入 N 个皇后， 要求所有皇后不在同一行、 列和同一斜线上！" << endl << endl;
	cout << "请输入皇后的个数 ： ";
	int temSize;

	// 检测输入的皇后个数是否是大于等于2的，若不是则重新输入
	cin >> temSize;
	while (temSize < 2) {
		cout << "皇后个数应该大于 1 ！请重新输入 ： " << endl;
		cin >> temSize;
	}

	// 建立棋盘
	MakeBoard(temSize);
}

void System::MakeBoard(int sz) { // 建立初始棋盘
	NQ = new NQueen(sz);
}

void System::FindMethod() { // 求解
	cout << "皇后摆法：" << endl << endl;
	NQ->Solution(); // 调用 NQueen 的求解函数
}

bool tryy(int i) {
	if (i == 2) return false;
}

int main() {
	System sys; // 实例化一个系统 
	sys.Start(); // 初始化游戏
	sys.FindMethod(); // 开始求解

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}