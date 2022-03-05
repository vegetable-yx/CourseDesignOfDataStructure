# include <iostream>
# include <limits>
using namespace std;

struct ListNode {
	int data; // 节点数据
	ListNode * link; // 后驱指针
	ListNode() : data(0), link(NULL) {} // 默认构造函数
	ListNode(int newData, ListNode* newLink = NULL) : data(newData), link(newLink) {}  // 带参数的构造函数
	ListNode(const ListNode& N) : data(N.data), link(N.link) {} // 拷贝构造函数
	~ListNode() {} // 析构函数
};

class CircleList {
private :
	ListNode* head, * current; // 头指针和当前位置指针 
	int deadnum; // 死亡数字
public :
	CircleList() : head(NULL), current(NULL), deadnum(0) {} // 默认构造函数
	CircleList(int num); // 构造函数
	~CircleList(); // 析构函数
	void SetStart(int start); // 设置起始位置
	void SetDead(int dead) { deadnum = dead; } // 设置死亡数字
	int Dead(); // 执行一次死亡操作
	void Print(); // 打印
};

// 构造函数
CircleList::CircleList(int num) :deadnum(0) {
	// 初始化头结点
	head = current = new ListNode(1);

	// 给接下来的节点分别赋值2,3,4......
	for (int i = 2; i <= num; i++) {
		current->link = new ListNode(i);
		current = current->link;
	}
	current->link = head;
}

// 析构函数
CircleList::~CircleList() {
	// 链表为空
	if (head == NULL) return;

	// 不为空，逐节点释放
	current = head->link;
	ListNode* t = current;
	while (current != head) {
		current = current->link;
		delete t;
		t = current;
	}
	delete head;
}

// 设置起始位置
void CircleList::SetStart(int start) {
	current = head;
	// 即将头结点向后移动 start - 1 位
	for (int i = 1; i < start; i++) head = head->link;
	current = head;
}

// 执行一次死亡操作
int CircleList::Dead() {
	ListNode* t = current;

	// 第 n 个节点将被删除， 先找到该节点
	for (int i = 1; i < deadnum; i++) {
		t = current;
		current = current->link;
	}

	// 删除该节点
	t->link = current->link;
	int tem = current->data;
	if (head->data == tem) head = t->link;
	delete current;
	current = t->link;
	return tem;
}

// 打印
void CircleList::Print() {
	current = head;

	// 逐节点打印信息
	do {
		cout << current->data << "    ";
		current = current->link;
	} while (current != head);
}

// 系统类
class System {
private :
	int livenums; // 幸存者数量
	CircleList* circle; // 循环链表，存放信息
public :
	System() : livenums(0) { circle = new CircleList; } // 构造函数
	~System() { delete circle; } // 析构函数
	void loop(); // 主循环
	void PrintLives(); // 打印幸存者
};

// 主循环
void System::loop() {
	string tag;
	cout << "输入 S 以开始约瑟夫生死环游戏，输入 E 或其他以退出游戏......" << endl;
	cin >> tag;

	// 输入 S 后开始游戏， 否则退出
	while (tag == "S") {
		int totNums, startNum, deadNum, liveNums;
		cout << "游戏规则：现有N人围成一圈，从第S个人开始一次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K个人为止。" << endl << endl;

		cout << "请输入生死游戏的总人数N：";
		cin >> totNums;

		// 总人数必须大于等于 2
		while (totNums < 2) {
			// 清空缓冲区
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "总人数必须为大于 1 的正整数！" << endl;
			cout << "请重新输入： ";
			cin >> totNums;
		}
		circle = new CircleList(totNums);

		cout << endl << "请输入游戏开始的位置S：";
		cin >> startNum;

		// 检验起始位置是否合法
		while (startNum < 1 || startNum > totNums) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "开始位置必须大于等于 1 且小于总人数！" << endl;
			cout << "请重新输入： ";
			cin >> startNum;
		}
		// 设置起始位置
		circle->SetStart(startNum);

		cout << endl << "请输入死亡数字M：";
		cin >> deadNum;

		// 检验死亡数字是否合法
		while (deadNum <= 1) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "死亡数字必须为大于 1 的正整数！" << endl;
			cout << "请重新输入： ";
			cin >> deadNum;
		}
		// 设置死亡数字
		circle->SetDead(deadNum);

		cout << endl << "请输入剩余的生者人数K：";
		cin >> liveNums;
		// 检验幸存者数量是否合法
		while (liveNums < 1 || liveNums >= totNums) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "剩余人数必须大于等于 1 且小于总人数！" << endl;
			cout << "请重新输入： ";
			cin >> liveNums;
		}
		livenums = liveNums;
		cout << endl << endl;

		// 执行 totNums - liveNums 次死亡操作
		for (int i = 1; i <= totNums - liveNums; i++) {
			int die = circle->Dead();
			cout << "第" << i << "个死者的位置是： " << die << endl;
		}
		cout << endl;

		// 打印幸存者信息
		PrintLives();
		cout << endl << endl;

		cout << "本次游戏已结束，可以选择继续或者退出游戏！" << endl;
		cout << "输入 S 以开始约瑟夫生死环游戏，输入 E 以退出游戏......" << endl;
		cin >> tag;
	}
}

// 打印幸存者信息
void System::PrintLives() {
	cout << "最后剩下：    " << livenums << "人" << endl;
	cout << "剩余生者的位置为：    ";
	circle->Print(); // 调用循环链表的打印函数即可
}

int main() {
	// 实例化一个约瑟夫游戏系统类并进入主循环
	System JosephGame;
	JosephGame.loop();

	// WINDOWS 平台暂停一下，防止闪退；同时在 LINUX 环境下不执行该命令，防止报错
# ifdef _WIN32
	system("pause");
# endif

	return 0;
}