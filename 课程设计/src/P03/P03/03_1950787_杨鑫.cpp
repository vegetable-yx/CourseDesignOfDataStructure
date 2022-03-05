# include <iostream>
# include <iomanip>
using namespace std;

// 位置类， 代表迷宫上的坐标
struct Position {
	int x;
	int y;
	Position(int xNew, int yNew) :x(xNew), y(yNew) {} // 带参数的构造函数
	Position() :x(0), y(0) {} // 默认构造函数
	Position(const Position& P) :x(P.x), y(P.y) {} // 复制构造函数

	// 重载 + 运算
	Position& operator + (const Position& P) {
		this->x = this->x + P.x;
		this->y = this->y + P.y;
		return *this;
	}
	// 重载 - 运算
	Position& operator - (const Position& P) {
		this->x = this->x - P.x;
		this->y = this->y - P.y;
		return *this;
	}
	// 重载 == 运算
	bool operator == (const Position& P) { return x == P.x && y == P.y; }
	// 重载 << 运算符，实现坐标输出
	friend ostream& operator << (ostream& out, const Position& P) {
		out << "(" << P.x << ", " << P.y << ")";
		return out;
	}
};

// 类的前置声明
template <class T>
class Stack;

// 节点类， 在本题可以封装位置信息以及前后指针
template <class T>
class Node {
	T data;
	Node<T>* link;
	Node<T>* pre;
	Node() :link(NULL), pre(NULL) {} // 默认构造函数
	Node(T& x, Node<T>* l = NULL, Node<T>* p = NULL) :data(x), link(l), pre(p) {} // 带参数的构造函数
	friend Stack<T>; // 声明 Stack 为友类
};

// 栈， 用于储存路径（此栈还带一个 bottom 和 pre 指针， 方便进行顺序输出操作
template <class T>
class Stack {
public:
	Stack() : top(NULL), bottom(NULL) {} // 默认构造函数
	~Stack() { makeEmpty(); } // 析构函数
	void Push(const T& x); // 入栈
	bool Pop(T& x); // 出栈
	void getTop(T& x); // 获取栈顶元素
	bool IsEmpty() const { return top == NULL; } // 判断栈是否空
	int getSize() const; // 获取栈的大小
	void Print() const; // 顺序打印路径
private:
	Node<T>* top;
	Node<T>* bottom;
	void makeEmpty(); // 私有函数， 清空栈
};

// 清空栈
template <class T>
void Stack<T>::makeEmpty() {
	Node<T>* p;
	while (top != NULL) { // 依次释放栈的各元素
		p = top;
		top = top->link;
		delete p;
	}
}

// 入栈
template <class T>
void Stack<T>::Push(const T& x) {
	T tem = x;
	top = new Node<T>(tem, top); // 在顶部插入新节点
	top->pre = NULL;
	if (top->link != NULL) top->link->pre = top; 
	else bottom = top; // 如果入栈后仅有一个元素，则该元素既是 top 也是 bottom
}

// 出栈
template <class T>
bool Stack<T>::Pop(T& x) {
	if (IsEmpty()) return false; // 栈空， 直接退出
	Node<T>* p = top;
	top = top->link; // 栈顶元素变为下一个
	if (top != NULL) top->pre = NULL;
	x = p->data; // 移除元素的值传给引用
	delete p;
	if (top == NULL) bottom = NULL; // 如果最后一个元素被释放，则 bottom 亦不存在
	return true;
}

// 获取栈顶元素的值
template <class T>
void Stack<T>::getTop(T& x) {
	if (IsEmpty()) return; // 栈空， 直接退出
	x = top->data;
}

// 获取栈的大小
template <class T>
int Stack<T>::getSize() const {
	Node<T>* p = top;
	int k = 0;
	while (p != NULL) { // 不断累加元素个数
		p = p->link;
		++k;
	}
	return k;
}

// 顺序输出路径
template <class T>
void Stack<T>::Print() const {
	Node<T>* p = bottom;
	bool tag = 1; // 是否是第一个的标记， 若是第一个，前面不输出 “--->”
	while (p != NULL) {
		if (tag) {
			cout << p->data;
			tag = 0;
		}
		else cout << " ---> " << p->data;
		p = p->pre;
	}
	cout << endl;
}

// 迷宫类， 存放迷宫图和路径栈
class Maze {
public :
	Maze() {} // 默认构造函数
	void PrintMap(); // 打印带正确路径的迷宫图
	void PrintPath(); // 打印详细路径
	void GeneratePath(); // 生成路径
private:
	// 初始迷宫图
	char map[25][25] = {
		"####################",
		"#S00########0#######",
		"##0####0###000######",
		"##00################",
		"#00##0000#000000####",
		"#0#000##0#0####0####",
		"#000####000####0####",
		"##0#########000000##",
		"##0#########0##0####",
		"##0#00###0000###00##",
		"#00#0####0##########",
		"#0000####0##00000###",
		"#########0000###0###",
		"##0#######0####0000#",
		"##00####000#######0#",
		"###0####0#########0#",
		"###0##000#####00000#",
		"##############0#####",
		"##############00000#",
		"####################"
	}; 
	Stack<Position> mazeStack; // 路径栈
};

// 打印带路径的迷宫图
void Maze::PrintMap() {
	cout << "\t";
	for (int i = 0; i < 20; i++) cout << "第" << i << "列" << '\t';
	// 遍历迷宫图数组并按格式打印
	for (int i = 0; i < 20; i++) {
		cout << endl;
		cout << "第" << i << "行" << '\t';
		for (int j = 0; j < 20; j++) {
			cout << setw(4) << map[i][j] << "    ";
		}
	}
	cout << endl << endl;
}

// 打印路径
void Maze::PrintPath() {
	cout << "路径长度为 ： " << mazeStack.getSize() << endl; // 输出路径长度
	cout << "迷宫路径：" << endl;
	mazeStack.Print();
}

// 生成路径（非递归方法）
void Maze::GeneratePath() {
	// 建立一个方位数组，代表前进的四个方向
	Position up(-1, 0), down(1, 0), left(0, -1), right(0, 1);
	Position direction[4] = { up, down, left, right };

	bool temMap[25][25]; // 标记数组，用于记录某位置是否被遍历过
	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 25; j++) temMap[i][j] = 1; // 初始化标记数组
	Position cur(1, 1), end(18,18); // 记录当前位置和终点位置
	mazeStack.Push(cur); // 先将起点入栈

	// 当前位置不等于终点（找到出口）且路径栈不为空（无路至终点）时继续往下搜寻
	while (!mazeStack.IsEmpty() && !(cur == end)) {
		bool tag = 0; // 是否能从当前位置往下走的标记
		int i;

		// 四个方向依次搜寻
		for (i = 0; i < 4; i++) {
			cur = cur + direction[i];
			if (map[cur.x][cur.y] == '0' && temMap[cur.x][cur.y]) { // 检测欲移动到的位置是否为障碍物或已经被走过
				mazeStack.Push(cur);
				map[cur.x][cur.y] = 'X'; // 在迷宫图中标记为走过的点（若之后回退，可取消标记）
				temMap[cur.x][cur.y] = 0; // 标记已走过（不会取消标记）
				tag = 1; // 标记为 1
				break;
			}
			cur = cur - direction[i]; // 无路继续往下走
		}
		if (!tag) { 
			if (i >= 4) { // 所有方向尝试完均不能走通，回退该点并从路径栈中弹出该点
				map[cur.x][cur.y] = '0';
				mazeStack.Pop(cur);
			}
			mazeStack.getTop(cur); // 尝试栈顶点的其他方向（之前试过的路已被标记而无法再走）
		}
	}
}

int main() {
	string order;
	Maze maze; // 初始化一个迷宫类
	maze.GeneratePath(); // 生成路径

	// 接受用户指令并完成相应操作
	cout << "输入 S 以显示迷宫地图， 输出其他以退出......" << endl;
	cin >> order;
	if (order == "S") {
	maze.PrintMap(); // 打印地图
	cout << "输入 S 以显示迷宫路径， 输出其他以退出......" << endl;
	cin >> order;
	if (order == "S") maze.PrintPath(); // 打印路径
	}

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}