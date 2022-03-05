# include <iostream>
# include <limits>
using namespace std;

struct ListNode {
	int data; // �ڵ�����
	ListNode * link; // ����ָ��
	ListNode() : data(0), link(NULL) {} // Ĭ�Ϲ��캯��
	ListNode(int newData, ListNode* newLink = NULL) : data(newData), link(newLink) {}  // �������Ĺ��캯��
	ListNode(const ListNode& N) : data(N.data), link(N.link) {} // �������캯��
	~ListNode() {} // ��������
};

class CircleList {
private :
	ListNode* head, * current; // ͷָ��͵�ǰλ��ָ�� 
	int deadnum; // ��������
public :
	CircleList() : head(NULL), current(NULL), deadnum(0) {} // Ĭ�Ϲ��캯��
	CircleList(int num); // ���캯��
	~CircleList(); // ��������
	void SetStart(int start); // ������ʼλ��
	void SetDead(int dead) { deadnum = dead; } // ������������
	int Dead(); // ִ��һ����������
	void Print(); // ��ӡ
};

// ���캯��
CircleList::CircleList(int num) :deadnum(0) {
	// ��ʼ��ͷ���
	head = current = new ListNode(1);

	// ���������Ľڵ�ֱ�ֵ2,3,4......
	for (int i = 2; i <= num; i++) {
		current->link = new ListNode(i);
		current = current->link;
	}
	current->link = head;
}

// ��������
CircleList::~CircleList() {
	// ����Ϊ��
	if (head == NULL) return;

	// ��Ϊ�գ���ڵ��ͷ�
	current = head->link;
	ListNode* t = current;
	while (current != head) {
		current = current->link;
		delete t;
		t = current;
	}
	delete head;
}

// ������ʼλ��
void CircleList::SetStart(int start) {
	current = head;
	// ����ͷ�������ƶ� start - 1 λ
	for (int i = 1; i < start; i++) head = head->link;
	current = head;
}

// ִ��һ����������
int CircleList::Dead() {
	ListNode* t = current;

	// �� n ���ڵ㽫��ɾ���� ���ҵ��ýڵ�
	for (int i = 1; i < deadnum; i++) {
		t = current;
		current = current->link;
	}

	// ɾ���ýڵ�
	t->link = current->link;
	int tem = current->data;
	if (head->data == tem) head = t->link;
	delete current;
	current = t->link;
	return tem;
}

// ��ӡ
void CircleList::Print() {
	current = head;

	// ��ڵ��ӡ��Ϣ
	do {
		cout << current->data << "    ";
		current = current->link;
	} while (current != head);
}

// ϵͳ��
class System {
private :
	int livenums; // �Ҵ�������
	CircleList* circle; // ѭ�����������Ϣ
public :
	System() : livenums(0) { circle = new CircleList; } // ���캯��
	~System() { delete circle; } // ��������
	void loop(); // ��ѭ��
	void PrintLives(); // ��ӡ�Ҵ���
};

// ��ѭ��
void System::loop() {
	string tag;
	cout << "���� S �Կ�ʼԼɪ����������Ϸ������ E ���������˳���Ϸ......" << endl;
	cin >> tag;

	// ���� S ��ʼ��Ϸ�� �����˳�
	while (tag == "S") {
		int totNums, startNum, deadNum, liveNums;
		cout << "��Ϸ��������N��Χ��һȦ���ӵ�S���˿�ʼһ�α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ��" << endl << endl;

		cout << "������������Ϸ��������N��";
		cin >> totNums;

		// ������������ڵ��� 2
		while (totNums < 2) {
			// ��ջ�����
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "����������Ϊ���� 1 ����������" << endl;
			cout << "���������룺 ";
			cin >> totNums;
		}
		circle = new CircleList(totNums);

		cout << endl << "��������Ϸ��ʼ��λ��S��";
		cin >> startNum;

		// ������ʼλ���Ƿ�Ϸ�
		while (startNum < 1 || startNum > totNums) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "��ʼλ�ñ�����ڵ��� 1 ��С����������" << endl;
			cout << "���������룺 ";
			cin >> startNum;
		}
		// ������ʼλ��
		circle->SetStart(startNum);

		cout << endl << "��������������M��";
		cin >> deadNum;

		// �������������Ƿ�Ϸ�
		while (deadNum <= 1) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�������ֱ���Ϊ���� 1 ����������" << endl;
			cout << "���������룺 ";
			cin >> deadNum;
		}
		// ������������
		circle->SetDead(deadNum);

		cout << endl << "������ʣ�����������K��";
		cin >> liveNums;
		// �����Ҵ��������Ƿ�Ϸ�
		while (liveNums < 1 || liveNums >= totNums) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "ʣ������������ڵ��� 1 ��С����������" << endl;
			cout << "���������룺 ";
			cin >> liveNums;
		}
		livenums = liveNums;
		cout << endl << endl;

		// ִ�� totNums - liveNums ����������
		for (int i = 1; i <= totNums - liveNums; i++) {
			int die = circle->Dead();
			cout << "��" << i << "�����ߵ�λ���ǣ� " << die << endl;
		}
		cout << endl;

		// ��ӡ�Ҵ�����Ϣ
		PrintLives();
		cout << endl << endl;

		cout << "������Ϸ�ѽ���������ѡ����������˳���Ϸ��" << endl;
		cout << "���� S �Կ�ʼԼɪ����������Ϸ������ E ���˳���Ϸ......" << endl;
		cin >> tag;
	}
}

// ��ӡ�Ҵ�����Ϣ
void System::PrintLives() {
	cout << "���ʣ�£�    " << livenums << "��" << endl;
	cout << "ʣ�����ߵ�λ��Ϊ��    ";
	circle->Print(); // ����ѭ������Ĵ�ӡ��������
}

int main() {
	// ʵ����һ��Լɪ����Ϸϵͳ�ಢ������ѭ��
	System JosephGame;
	JosephGame.loop();

	// WINDOWS ƽ̨��ͣһ�£���ֹ���ˣ�ͬʱ�� LINUX �����²�ִ�и������ֹ����
# ifdef _WIN32
	system("pause");
# endif

	return 0;
}