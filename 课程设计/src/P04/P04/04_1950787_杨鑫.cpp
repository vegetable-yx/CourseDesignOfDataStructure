# include <iostream>
using namespace std;

// Stack ��ǰ������
class Stack;

// �ڵ��࣬ ���ڴ洢���������Ϣ
struct Node{
	int x;
	int y;
	Node* link;
	Node(int newX = 0, int newY = 0, Node* newLink = NULL) : x(newX), y(newY), link(newLink) {} // ������Ĭ��ֵ�Ĺ��캯��
	~Node() {}
	Node(const Node& n) :x(n.x), y(n.y), link(n.link) {} // �������캯��
	friend class Stack; // ���� Stack Ϊ����
};

// ջ
class Stack{
private :
	Node* top; // ջ��
public :
	Stack() :top(NULL) {} // Ĭ�Ϲ��캯��
	~Stack(); // ��������
	void Push(int x, int y); // ��ջ
	bool Pop(int &x, int &y); // ��ջ
};

Stack::~Stack() {
	Node* p;
	while (top != NULL) { // ��ڵ��ͷ�
		p = top;
		top = top->link;
		delete p;
	}
}

void Stack::Push(int x, int y) {
	Node* newNode = new Node(x, y, top); // �½ڵ�Ľ���������
	top = newNode; // ����ջ��
}

bool Stack::Pop(int &x, int &y) {
	if (top == NULL) return false; // ջ�գ�����false
	x = top->x, y = top->y;
	Node* temNode = top;
	top = top->link; // ջ��Ԫ�ظ���
	delete temNode;
	return true;
}

// �˻ʺ��࣬ ʵ�ְ˻ʺ���Ϸ���ܵķ�װ
class NQueen{
public :
	NQueen(int sz = 0); // ���캯��
	~NQueen() { delete board, delete stack; } // ��������
	void Solution(); // ���
	bool Illigal(int rows, int cols); // �ж�λ���Ƿ�Ϸ�
	void Print(); // ��ӡ�ⷨ
private :
	int size; // ���̴�С���ʺ������
	int numOfSolutions; // ��ĸ���
	char** board; // ����
	Stack* stack; // ��ʱ�洢���ܵĽⷨ�ڵ��ջ
};

NQueen::NQueen(int sz) { // ���캯��
	size = sz;
	numOfSolutions = 0;
	stack = new Stack;

	// ��ʼ������
	board = new char* [size];
	for (int i = 0; i < size; i++) board[i] = new char[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) board[i][j] = '0';
}

// ���˻ʺ�����ķǵݹ��㷨
void NQueen::Solution() {
	int lastX = -1, lastY = -1; // ����ϴγ�ջ������λ�ã����ޣ����� (-1, -1) ����ʾ

	// ����Ѱ�ҽ�
	int rows = 0;
	while (true) {
		bool tag = false; // ��ǣ���ǰ���Ƿ��кϷ���λ�ò����ûʺ��ڸ�λ����
		for (int cols = lastY + 1; cols < size; cols++) { // Ѱ�ҵ�ǰ���Ƿ��кϷ���λ��
			if (Illigal(rows, cols)) {
				stack->Push(rows, cols);
				board[rows][cols] = 'X';
				tag = true; // ���±��
				break;
			}
		}
		if (!tag) { // δ�ҵ�λ��
			rows--;
			if (!(stack->Pop(lastX, lastY))) { // ջ�գ�˵���Ѿ����Ѱ��
				cout << "����" << numOfSolutions << "�ֽⷨ��" << endl;
				return;
			}
			board[lastX][lastY] = '0'; // ���̸�λ�û�ԭΪ�޻ʺ�״̬
		}
		else { // �ҵ�λ�ò�����
			if (rows == size - 1) { // �Ѿ������һ�У�˵���ɹ��ҵ�һ���
				Print(); // ��ӡ
				numOfSolutions++; // ������++
				stack->Pop(lastX, lastY); // �������Ӷ�������һ�ֽ��Ѱ��
				board[lastX][lastY] = '0';
			}
			else rows++, lastX = -1, lastY = -1; // �������һ�У���������һ��Ѱ��
		}
	}
}

bool NQueen::Illigal(int rows, int cols) { // �ж�λ���Ƿ�Ϸ�
	// ����һ��ͬһ�в��������������ϵĻʺ�
	for (int i = 0; i < rows; i++) {
		if (board[i][cols] == 'X') return false;
	}
	// ����������б�߷����������������ϵĻʺ�
	for (int i = rows, j = cols; i >= 0 && j >= 0; i--, j--) {
		if (board[i][j] == 'X') return false;
	}
	// ����������б�߷����������������ϵĻʺ�
	for (int i = rows, j = cols; i >= 0 && j < size; i--, j++) {
		if (board[i][j] == 'X') return false;
	}
	return true;
}

void NQueen::Print() { // ��ӡ�֮ⷨһ
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j] << "    ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

// ϵͳ��
class System {
private :
	NQueen* NQ;
public :
	System() : NQ(NULL) {} // ���캯��
	~System() { delete NQ; } // ��������
	void Start(); // ��ʼ����Ϸ
	void MakeBoard(int sz); // ������ʼ����
	void FindMethod(); // ���
};

void System::Start() { // ��ʼ����Ϸ
	cout << "���� N * N �����̣� ���� N ���ʺ� Ҫ�����лʺ���ͬһ�С� �к�ͬһб���ϣ�" << endl << endl;
	cout << "������ʺ�ĸ��� �� ";
	int temSize;

	// �������Ļʺ�����Ƿ��Ǵ��ڵ���2�ģ�����������������
	cin >> temSize;
	while (temSize < 2) {
		cout << "�ʺ����Ӧ�ô��� 1 ������������ �� " << endl;
		cin >> temSize;
	}

	// ��������
	MakeBoard(temSize);
}

void System::MakeBoard(int sz) { // ������ʼ����
	NQ = new NQueen(sz);
}

void System::FindMethod() { // ���
	cout << "�ʺ�ڷ���" << endl << endl;
	NQ->Solution(); // ���� NQueen ����⺯��
}

bool tryy(int i) {
	if (i == 2) return false;
}

int main() {
	System sys; // ʵ����һ��ϵͳ 
	sys.Start(); // ��ʼ����Ϸ
	sys.FindMethod(); // ��ʼ���

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}