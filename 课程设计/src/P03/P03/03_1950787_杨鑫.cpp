# include <iostream>
# include <iomanip>
using namespace std;

// λ���࣬ �����Թ��ϵ�����
struct Position {
	int x;
	int y;
	Position(int xNew, int yNew) :x(xNew), y(yNew) {} // �������Ĺ��캯��
	Position() :x(0), y(0) {} // Ĭ�Ϲ��캯��
	Position(const Position& P) :x(P.x), y(P.y) {} // ���ƹ��캯��

	// ���� + ����
	Position& operator + (const Position& P) {
		this->x = this->x + P.x;
		this->y = this->y + P.y;
		return *this;
	}
	// ���� - ����
	Position& operator - (const Position& P) {
		this->x = this->x - P.x;
		this->y = this->y - P.y;
		return *this;
	}
	// ���� == ����
	bool operator == (const Position& P) { return x == P.x && y == P.y; }
	// ���� << �������ʵ���������
	friend ostream& operator << (ostream& out, const Position& P) {
		out << "(" << P.x << ", " << P.y << ")";
		return out;
	}
};

// ���ǰ������
template <class T>
class Stack;

// �ڵ��࣬ �ڱ�����Է�װλ����Ϣ�Լ�ǰ��ָ��
template <class T>
class Node {
	T data;
	Node<T>* link;
	Node<T>* pre;
	Node() :link(NULL), pre(NULL) {} // Ĭ�Ϲ��캯��
	Node(T& x, Node<T>* l = NULL, Node<T>* p = NULL) :data(x), link(l), pre(p) {} // �������Ĺ��캯��
	friend Stack<T>; // ���� Stack Ϊ����
};

// ջ�� ���ڴ���·������ջ����һ�� bottom �� pre ָ�룬 �������˳���������
template <class T>
class Stack {
public:
	Stack() : top(NULL), bottom(NULL) {} // Ĭ�Ϲ��캯��
	~Stack() { makeEmpty(); } // ��������
	void Push(const T& x); // ��ջ
	bool Pop(T& x); // ��ջ
	void getTop(T& x); // ��ȡջ��Ԫ��
	bool IsEmpty() const { return top == NULL; } // �ж�ջ�Ƿ��
	int getSize() const; // ��ȡջ�Ĵ�С
	void Print() const; // ˳���ӡ·��
private:
	Node<T>* top;
	Node<T>* bottom;
	void makeEmpty(); // ˽�к����� ���ջ
};

// ���ջ
template <class T>
void Stack<T>::makeEmpty() {
	Node<T>* p;
	while (top != NULL) { // �����ͷ�ջ�ĸ�Ԫ��
		p = top;
		top = top->link;
		delete p;
	}
}

// ��ջ
template <class T>
void Stack<T>::Push(const T& x) {
	T tem = x;
	top = new Node<T>(tem, top); // �ڶ��������½ڵ�
	top->pre = NULL;
	if (top->link != NULL) top->link->pre = top; 
	else bottom = top; // �����ջ�����һ��Ԫ�أ����Ԫ�ؼ��� top Ҳ�� bottom
}

// ��ջ
template <class T>
bool Stack<T>::Pop(T& x) {
	if (IsEmpty()) return false; // ջ�գ� ֱ���˳�
	Node<T>* p = top;
	top = top->link; // ջ��Ԫ�ر�Ϊ��һ��
	if (top != NULL) top->pre = NULL;
	x = p->data; // �Ƴ�Ԫ�ص�ֵ��������
	delete p;
	if (top == NULL) bottom = NULL; // ������һ��Ԫ�ر��ͷţ��� bottom �಻����
	return true;
}

// ��ȡջ��Ԫ�ص�ֵ
template <class T>
void Stack<T>::getTop(T& x) {
	if (IsEmpty()) return; // ջ�գ� ֱ���˳�
	x = top->data;
}

// ��ȡջ�Ĵ�С
template <class T>
int Stack<T>::getSize() const {
	Node<T>* p = top;
	int k = 0;
	while (p != NULL) { // �����ۼ�Ԫ�ظ���
		p = p->link;
		++k;
	}
	return k;
}

// ˳�����·��
template <class T>
void Stack<T>::Print() const {
	Node<T>* p = bottom;
	bool tag = 1; // �Ƿ��ǵ�һ���ı�ǣ� ���ǵ�һ����ǰ�治��� ��--->��
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

// �Թ��࣬ ����Թ�ͼ��·��ջ
class Maze {
public :
	Maze() {} // Ĭ�Ϲ��캯��
	void PrintMap(); // ��ӡ����ȷ·�����Թ�ͼ
	void PrintPath(); // ��ӡ��ϸ·��
	void GeneratePath(); // ����·��
private:
	// ��ʼ�Թ�ͼ
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
	Stack<Position> mazeStack; // ·��ջ
};

// ��ӡ��·�����Թ�ͼ
void Maze::PrintMap() {
	cout << "\t";
	for (int i = 0; i < 20; i++) cout << "��" << i << "��" << '\t';
	// �����Թ�ͼ���鲢����ʽ��ӡ
	for (int i = 0; i < 20; i++) {
		cout << endl;
		cout << "��" << i << "��" << '\t';
		for (int j = 0; j < 20; j++) {
			cout << setw(4) << map[i][j] << "    ";
		}
	}
	cout << endl << endl;
}

// ��ӡ·��
void Maze::PrintPath() {
	cout << "·������Ϊ �� " << mazeStack.getSize() << endl; // ���·������
	cout << "�Թ�·����" << endl;
	mazeStack.Print();
}

// ����·�����ǵݹ鷽����
void Maze::GeneratePath() {
	// ����һ����λ���飬����ǰ�����ĸ�����
	Position up(-1, 0), down(1, 0), left(0, -1), right(0, 1);
	Position direction[4] = { up, down, left, right };

	bool temMap[25][25]; // ������飬���ڼ�¼ĳλ���Ƿ񱻱�����
	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 25; j++) temMap[i][j] = 1; // ��ʼ���������
	Position cur(1, 1), end(18,18); // ��¼��ǰλ�ú��յ�λ��
	mazeStack.Push(cur); // �Ƚ������ջ

	// ��ǰλ�ò������յ㣨�ҵ����ڣ���·��ջ��Ϊ�գ���·���յ㣩ʱ����������Ѱ
	while (!mazeStack.IsEmpty() && !(cur == end)) {
		bool tag = 0; // �Ƿ��ܴӵ�ǰλ�������ߵı��
		int i;

		// �ĸ�����������Ѱ
		for (i = 0; i < 4; i++) {
			cur = cur + direction[i];
			if (map[cur.x][cur.y] == '0' && temMap[cur.x][cur.y]) { // ������ƶ�����λ���Ƿ�Ϊ�ϰ�����Ѿ����߹�
				mazeStack.Push(cur);
				map[cur.x][cur.y] = 'X'; // ���Թ�ͼ�б��Ϊ�߹��ĵ㣨��֮����ˣ���ȡ����ǣ�
				temMap[cur.x][cur.y] = 0; // ������߹�������ȡ����ǣ�
				tag = 1; // ���Ϊ 1
				break;
			}
			cur = cur - direction[i]; // ��·����������
		}
		if (!tag) { 
			if (i >= 4) { // ���з��������������ͨ�����˸õ㲢��·��ջ�е����õ�
				map[cur.x][cur.y] = '0';
				mazeStack.Pop(cur);
			}
			mazeStack.getTop(cur); // ����ջ�������������֮ǰ�Թ���·�ѱ���Ƕ��޷����ߣ�
		}
	}
}

int main() {
	string order;
	Maze maze; // ��ʼ��һ���Թ���
	maze.GeneratePath(); // ����·��

	// �����û�ָ������Ӧ����
	cout << "���� S ����ʾ�Թ���ͼ�� ����������˳�......" << endl;
	cin >> order;
	if (order == "S") {
	maze.PrintMap(); // ��ӡ��ͼ
	cout << "���� S ����ʾ�Թ�·���� ����������˳�......" << endl;
	cin >> order;
	if (order == "S") maze.PrintPath(); // ��ӡ·��
	}

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}