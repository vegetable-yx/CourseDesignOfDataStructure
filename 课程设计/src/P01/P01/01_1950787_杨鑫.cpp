# include <iostream>
# include <string>
# include <limits>
using namespace std;

// 学生信息类，包含考生的基本信息和一些基本函数
class StudentInfo {
private :
	string ID;
	string name;
	string gender;
	int age;
	string categoryOfExamination;
public :
	StudentInfo() = default; // 默认构造函数
	StudentInfo(string newID, string newName, string newGender, int newAge, string newCategoryOfExamination) : ID(newID), name(newName), gender(newGender), age(newAge), categoryOfExamination(newCategoryOfExamination) {} // 带参数的构造函数
	~StudentInfo() {} // 析构函数，类里面不含指针，无需释放
	StudentInfo(const StudentInfo& StuInfo); // 拷贝构造函数
	StudentInfo& operator = (const StudentInfo& StuInfo); //重载 = 运算符
	friend ostream& operator << (ostream& out, const StudentInfo& StuInfo); //友元函数，实现输出
	friend istream& operator >> (istream& in, StudentInfo& StuInfo); // 友元函数，实现输入

	// 一些接口函数
	string getID() { return ID; }
	string getName() { return name; }
	string getGender() { return gender; }
	int getAge() { return age; }
	string getCategoryOfExamination() { return categoryOfExamination; }
};

// 拷贝构造函数
StudentInfo::StudentInfo(const StudentInfo& StuInfo) {
	ID = StuInfo.ID;
	name = StuInfo.name;
	gender = StuInfo.gender;
	age = StuInfo.age;
	categoryOfExamination = StuInfo.categoryOfExamination;
}

// 重载 = 运算符
StudentInfo& StudentInfo::operator = (const StudentInfo& StuInfo) {
	ID = StuInfo.ID;
	name = StuInfo.name;
	gender = StuInfo.gender;
	age = StuInfo.age;
	categoryOfExamination = StuInfo.categoryOfExamination;
	return *this;
}

//友元函数，实现输出
ostream& operator << (ostream& out, const StudentInfo& StuInfo) {
	out << StuInfo.ID << '\t' << StuInfo.name << '\t' << StuInfo.gender << '\t' << StuInfo.age << '\t' << StuInfo.categoryOfExamination;
	return out;
}

//友元函数，实现输入
istream& operator >> (istream& in, StudentInfo& StuInfo) {
	string id, name, gender, category;
	int age;
	in >> id >> name >> gender;

	// 规范输入：年龄必须为数字，否则需要重新输入
	while (!(cin >> age)) {
		cout << "年龄必须为数字！ 请重新输入！（从年龄开始）" << endl;
		// 将缓存区清空
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	}
	cin >> category;
	StuInfo.ID = id, StuInfo.name = name, StuInfo.gender = gender, StuInfo.age = age, StuInfo.categoryOfExamination = category;
	return in;
}

template <class T>
class InfoList;

template <class T>
class System;

template <class T>
class InfoNode { // 节点类，用于链式存储学生信息
private :
	T data;
	InfoNode* pre;
	InfoNode* link; // 设计为双链
public :
	InfoNode() :pre(NULL), link(NULL) {} // 默认构造函数
	InfoNode(T newData, InfoNode* newPre = NULL, InfoNode* newLink = NULL) : data(newData), pre(newPre), link(newLink) {} // 带参数的构造函数
	InfoNode(const InfoNode& IN) : data(IN.data), pre(IN.pre), link(IN.link) {} // 拷贝构造函数
	~InfoNode() {} // 析构函数
	friend class InfoList<T>; // 声明 InfoList 为友类
	friend class System<T>; // 声明 Sysytem 为友类
};

template <class T>
class InfoList { // 链表类（有附加头结点）
private :
	InfoNode<T>* head;
public :
	InfoList() { head = new InfoNode<T>; } // 默认构造函数
	~InfoList(); // 析构函数
	int Size(); // 返回长度
	bool Insert(int location, InfoNode<T>* IN); // 插入
	bool Remove(string rmID); // 删除
	bool Search(string checkID, InfoNode<T>*& result); // 搜索
	bool Update(string curID, T nowInfo); // 修改
	void Print(); // 统计
};

// 依次释放所有节点
template <class T>
InfoList<T>::~InfoList() {
	InfoNode<T>* p = head->link;
	while (p != NULL) {
		head->link = p->link;
		delete p;
		p = head->link;
	}
	delete head;
}

// 返回链表长度
template <class T>
int InfoList<T>::Size() {
	int num = 0;
	InfoNode<T>* cur = head->link;
	while (cur != NULL) {
		cur = cur->link;
		num++;
	}
	return num;
}

// 插入节点
template <class T>
bool InfoList<T>::Insert(int location, InfoNode<T>* IN) {
	InfoNode<T>* cur = head;
	int i;

	// 尝试移动到指定位置
	for (i = 0; i < location && cur != NULL; i++) cur = cur->link;
	// 移动不到指定位置（即位置不合法）
	if (i < location) {
		cout << "插入位置有误！" << endl;
		return false;
	}
	// 查询是否已存在该学号，若存在则提示错误并返回
	InfoNode<T>* t;
	if (Search(IN->data.getID(), t)) {
		cout << "学号已存在，请重新输入！" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	// 不存在则正常插入
	IN->link = cur->link;
	if (cur->link != NULL) cur->link->pre = IN;
	IN->pre = cur;
	cur->link = IN;
	return true;
}

// 删除指定的节点
template <class T>
bool InfoList<T>::Remove(string rmID) {
	InfoNode<T>* cur = head->link;

	// 检索该节点
	while (cur != NULL) {
		if (cur->data.getID() == rmID) break;
		else cur = cur->link;
	}
	// 不存在则直接返回并报错
	if (cur == NULL) {
		cout << "删除元素不存在！" << endl;
		return false;
	}

	// 若存在则执行删除
	cur->pre->link = cur->link;
	if (cur->link != NULL) cur->link->pre = cur->pre;
	delete cur;
	return true;
}

// 检索学号是否存在
template <class T>
bool InfoList<T>::Search(string checkID, InfoNode<T>*& result) {
	InfoNode<T>* cur = head->link;
	// 顺序检索
	while (cur != NULL) {
		if (cur->data.getID() == checkID) {
			result = cur;
			return true;
		}
		else cur = cur->link; // 搜索成功后把该节点通过引用返回
	}
	return false;
}

// 用新数据修改指定的节点
template <class T>
bool InfoList<T>::Update(string curID, T nowInfo) {
	// 检索新的学号是否已经存在
	InfoNode<T>* t;
	if (nowInfo.getID() != curID && Search(nowInfo.getID(), t)) {
		cout << "修改后的学号已存在！" << endl;
		return false;
	}

	// 存在则修改
	InfoNode<T>* cur = head->link;
	// 顺序检索
	while (cur != NULL) {
		if (cur->data.getID() == curID) break;
		else cur = cur->link;
	}
	if (cur == NULL) {
		cout << "被修改的学号不存在！" << endl;
		return false;
	}
	cur->data = nowInfo;
	return true;
}

// 统计（打印）
template <class T>
void InfoList<T>::Print() {
	cout << "考号" << '\t' << "姓名" << '\t' << "性别" << '\t' << "年龄" << '\t' << "报考类别" << endl;
	InfoNode<T>* cur = head->link;

	// 依次打印所有节点信息
	while (cur != NULL) {
		cout << cur->data << endl; // 利用重载的 << 运算符打印信息
		cur = cur->link;
	}
	cout << endl;
}

template <class T>
class System { // 系统类，用于交互和管理执行各种操作
private :
	InfoList<T>* Info;
public :
	~System() { delete Info; } // 程序退出时释放空间
	void init(); // 初始化系统
	void loop(); // 主循环（即反复询问用户的操作并执行）
	void insert(); // 执行插入指令
	void remove(); // 执行删除指令
	void update(); // 执行修改指令
	void search(); // 执行查找指令
	void show(); // 执行统计指令
};

// 初始化
template <class T>
void System<T>::init() {
	Info = new InfoList<T>;
	int studentNums;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	cin >> studentNums;
	// 规范输入并抛出异常输入
	while (studentNums <= 0 || cin.fail())
	{
		cout << "考生人数只能是正整数！" << endl;
		cout << "请重新输入考生人数：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> studentNums;
	}

	// 依次输入信息并插入表中
	for (int i = 0; i < studentNums; i++) {
		cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
		T tem;
		cin >> tem;
		InfoNode<T>* temNode = new InfoNode<T>(tem, NULL, NULL);
		while (!Info->Insert(i, temNode)) { // 若插图失败则重新输入
			cout << "输入信息不合法，请重新输入！" << endl;
			cin >> tem;
			temNode = new InfoNode<T>(tem, NULL, NULL);
		}
	}
}

// 主循环函数
template <class T>
void System<T>::loop() {
	init();
	cout << "建立成功！" << endl << endl;
	while (true) {
		int operation;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "请选择您要进行的操作 （1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
		cin >> operation;
		switch (operation) {
		case 1:
			insert();
			break;
		case 2:
			remove();
			break;
		case 3:
			search();
			break;
		case 4:
			update();
			break;
		case 5:
			show();
			break;
		case 0:
			cout << "退出成功，欢迎下次光临！" << endl;
			return;
			break;
		default :
			cout << "输入操作数有误，请尝试重新输入！" << endl;
			break;
		}
	}
}

// 执行插入指令
template <class T>
void System<T>::insert() {
	int location;
	cout << "请输入您要插入的考生的位置！" << endl;
	cin >> location;

	// 检测 location 是否合法，不合法则重新输入，直到用户退出或者合法
	while (location < 0 || location > Info->Size()) {
		cout << "位置不合法，请重新输入：（输入 -1 以退出本次操作）" << endl;
		cin >> location;
		if (location == -1) {
			cout << "退出成功，此次操作被忽略！" << endl;
			return;
		}
	}

	// 检测插入是否合法，不合法则重新输入，直到用户退出或者合法
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
	T tem;
	cin >> tem;
	InfoNode<T>* temNode = new InfoNode<T>(tem, NULL, NULL);
	while (!Info->Insert(location, temNode)) {
		cout << "插入失败，输入 0 以退出本次操作，输入 1 以继续：" << endl;
		bool tag; // 退出或者继续的标识
		cin >> tag;
		if (!tag) {
			cout << "退出成功，此次操作被忽略！" << endl;
			return;
		}
		cout << "请再次输入：" << endl;
		cin >> tem;
		temNode = new InfoNode<T>(tem, NULL, NULL);
	}
	cout << "插入成功！" << endl;
	show();
}

//执行删除指令
template <class T>
void System<T>::remove() {
	string rmID;
	cout << "请输入要删除的记录的学生学号：" << endl;
	cin >> rmID;

	// 检测是否成功删除，不成功则重新输入学号，直到用户退出或者成功删除
	while (!Info->Remove(rmID)) {
		cout << "删除失败，输入 0 以退出本次操作，输入 1 以继续：" << endl;
		bool tag;
		cin >> tag;
		if (!tag) {
			cout << "退出成功，此次操作被忽略！" << endl;
			return;
		}
		cout << "请再次输入：" << endl;
		cin >> rmID;
	}
	cout << "删除成功！" << endl;
	show();
}

//执行修改指令
template <class T>
void System<T>::update() {
	string rmID;
	InfoNode<T>* t;
	cout << "请输入要修改的记录的学生学号：" << endl;
	cin >> rmID;

	// 检测 学号是否存在，不存在则重新输入，直到用户退出或者存在
	while (!Info->Search(rmID, t)) {
		cout << "被修改学生不存在，请重新输入：（输入 Q 以退出本次操作，输入其他任意字符以继续...）";
		cin >> rmID;
		if (rmID == "Q") {
			cout << "退出成功，此次操作被忽略！" << endl;
			return;
		}
		cout <<"请再次输入：" << endl;
		cin >> rmID;
	}

	// 检测修改是否合法，不合法则重新输入，直到用户退出或者合法
	cout << "请依次输入修改后的考号，姓名，性别，年龄及报考类别！" << endl;
	T tem;
	cin >> tem;
	while (!Info->Update(rmID, tem)) {
		cout << "修改失败，输入 0 以退出本次操作，输入 1 以继续：" << endl;
		bool tag;
		cin >> tag;
		if (!tag) {
			cout << "退出成功，此次操作被忽略！" << endl;
			return;
		}
		cout << "请再次输入：" << endl;
		cin >> tem;
	}
	cout << "修改成功！" << endl;
	show();
}

// 执行检索指令
template <class T>
void System<T>::search() {
	string checkID;

	// 规定输入 Q 为取消指令
	cout << "请输入待查询学生的学号！（输入 Q 以退出本次操作）" << endl;
	cin >> checkID;
	if (checkID == "Q") {
		cout << "退出成功，此次操作被忽略！" << endl;
		return;
	}
	InfoNode<T>* result;
	if (!Info->Search(checkID, result)) {
		cout << "未查询到该考生！" << endl;
	}
	else {
		// 打印信息
		cout << "查询成功！信息如下：" << endl << endl;
		cout << "考号" << '\t' << "姓名" << '\t' << "性别" << '\t' << "年龄" << '\t' << "报考类别" << endl;
		cout << result->data.getID() << '\t' << result->data.getName() << '\t' << result->data.getGender() << '\t' << result->data.getAge() << '\t' << result->data.getCategoryOfExamination() << '\t' << endl;
	}
}

// 执行统计指令
template <class T>
void System<T>::show() {
	Info->Print(); // 直接调用 Print() 即可
}

// 程序入口
int main() {
	System<StudentInfo> sys; // 建立一个系统
	sys.loop(); // 进入主循环


# ifdef _WIN32
	system("pause");
# endif

	return 0;
}