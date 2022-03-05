# include <iostream>
# include <string>
# include <limits>
using namespace std;

// ѧ����Ϣ�࣬���������Ļ�����Ϣ��һЩ��������
class StudentInfo {
private :
	string ID;
	string name;
	string gender;
	int age;
	string categoryOfExamination;
public :
	StudentInfo() = default; // Ĭ�Ϲ��캯��
	StudentInfo(string newID, string newName, string newGender, int newAge, string newCategoryOfExamination) : ID(newID), name(newName), gender(newGender), age(newAge), categoryOfExamination(newCategoryOfExamination) {} // �������Ĺ��캯��
	~StudentInfo() {} // ���������������治��ָ�룬�����ͷ�
	StudentInfo(const StudentInfo& StuInfo); // �������캯��
	StudentInfo& operator = (const StudentInfo& StuInfo); //���� = �����
	friend ostream& operator << (ostream& out, const StudentInfo& StuInfo); //��Ԫ������ʵ�����
	friend istream& operator >> (istream& in, StudentInfo& StuInfo); // ��Ԫ������ʵ������

	// һЩ�ӿں���
	string getID() { return ID; }
	string getName() { return name; }
	string getGender() { return gender; }
	int getAge() { return age; }
	string getCategoryOfExamination() { return categoryOfExamination; }
};

// �������캯��
StudentInfo::StudentInfo(const StudentInfo& StuInfo) {
	ID = StuInfo.ID;
	name = StuInfo.name;
	gender = StuInfo.gender;
	age = StuInfo.age;
	categoryOfExamination = StuInfo.categoryOfExamination;
}

// ���� = �����
StudentInfo& StudentInfo::operator = (const StudentInfo& StuInfo) {
	ID = StuInfo.ID;
	name = StuInfo.name;
	gender = StuInfo.gender;
	age = StuInfo.age;
	categoryOfExamination = StuInfo.categoryOfExamination;
	return *this;
}

//��Ԫ������ʵ�����
ostream& operator << (ostream& out, const StudentInfo& StuInfo) {
	out << StuInfo.ID << '\t' << StuInfo.name << '\t' << StuInfo.gender << '\t' << StuInfo.age << '\t' << StuInfo.categoryOfExamination;
	return out;
}

//��Ԫ������ʵ������
istream& operator >> (istream& in, StudentInfo& StuInfo) {
	string id, name, gender, category;
	int age;
	in >> id >> name >> gender;

	// �淶���룺�������Ϊ���֣�������Ҫ��������
	while (!(cin >> age)) {
		cout << "�������Ϊ���֣� ���������룡�������俪ʼ��" << endl;
		// �����������
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
class InfoNode { // �ڵ��࣬������ʽ�洢ѧ����Ϣ
private :
	T data;
	InfoNode* pre;
	InfoNode* link; // ���Ϊ˫��
public :
	InfoNode() :pre(NULL), link(NULL) {} // Ĭ�Ϲ��캯��
	InfoNode(T newData, InfoNode* newPre = NULL, InfoNode* newLink = NULL) : data(newData), pre(newPre), link(newLink) {} // �������Ĺ��캯��
	InfoNode(const InfoNode& IN) : data(IN.data), pre(IN.pre), link(IN.link) {} // �������캯��
	~InfoNode() {} // ��������
	friend class InfoList<T>; // ���� InfoList Ϊ����
	friend class System<T>; // ���� Sysytem Ϊ����
};

template <class T>
class InfoList { // �����ࣨ�и���ͷ��㣩
private :
	InfoNode<T>* head;
public :
	InfoList() { head = new InfoNode<T>; } // Ĭ�Ϲ��캯��
	~InfoList(); // ��������
	int Size(); // ���س���
	bool Insert(int location, InfoNode<T>* IN); // ����
	bool Remove(string rmID); // ɾ��
	bool Search(string checkID, InfoNode<T>*& result); // ����
	bool Update(string curID, T nowInfo); // �޸�
	void Print(); // ͳ��
};

// �����ͷ����нڵ�
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

// ����������
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

// ����ڵ�
template <class T>
bool InfoList<T>::Insert(int location, InfoNode<T>* IN) {
	InfoNode<T>* cur = head;
	int i;

	// �����ƶ���ָ��λ��
	for (i = 0; i < location && cur != NULL; i++) cur = cur->link;
	// �ƶ�����ָ��λ�ã���λ�ò��Ϸ���
	if (i < location) {
		cout << "����λ������" << endl;
		return false;
	}
	// ��ѯ�Ƿ��Ѵ��ڸ�ѧ�ţ�����������ʾ���󲢷���
	InfoNode<T>* t;
	if (Search(IN->data.getID(), t)) {
		cout << "ѧ���Ѵ��ڣ����������룡" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	// ����������������
	IN->link = cur->link;
	if (cur->link != NULL) cur->link->pre = IN;
	IN->pre = cur;
	cur->link = IN;
	return true;
}

// ɾ��ָ���Ľڵ�
template <class T>
bool InfoList<T>::Remove(string rmID) {
	InfoNode<T>* cur = head->link;

	// �����ýڵ�
	while (cur != NULL) {
		if (cur->data.getID() == rmID) break;
		else cur = cur->link;
	}
	// ��������ֱ�ӷ��ز�����
	if (cur == NULL) {
		cout << "ɾ��Ԫ�ز����ڣ�" << endl;
		return false;
	}

	// ��������ִ��ɾ��
	cur->pre->link = cur->link;
	if (cur->link != NULL) cur->link->pre = cur->pre;
	delete cur;
	return true;
}

// ����ѧ���Ƿ����
template <class T>
bool InfoList<T>::Search(string checkID, InfoNode<T>*& result) {
	InfoNode<T>* cur = head->link;
	// ˳�����
	while (cur != NULL) {
		if (cur->data.getID() == checkID) {
			result = cur;
			return true;
		}
		else cur = cur->link; // �����ɹ���Ѹýڵ�ͨ�����÷���
	}
	return false;
}

// ���������޸�ָ���Ľڵ�
template <class T>
bool InfoList<T>::Update(string curID, T nowInfo) {
	// �����µ�ѧ���Ƿ��Ѿ�����
	InfoNode<T>* t;
	if (nowInfo.getID() != curID && Search(nowInfo.getID(), t)) {
		cout << "�޸ĺ��ѧ���Ѵ��ڣ�" << endl;
		return false;
	}

	// �������޸�
	InfoNode<T>* cur = head->link;
	// ˳�����
	while (cur != NULL) {
		if (cur->data.getID() == curID) break;
		else cur = cur->link;
	}
	if (cur == NULL) {
		cout << "���޸ĵ�ѧ�Ų����ڣ�" << endl;
		return false;
	}
	cur->data = nowInfo;
	return true;
}

// ͳ�ƣ���ӡ��
template <class T>
void InfoList<T>::Print() {
	cout << "����" << '\t' << "����" << '\t' << "�Ա�" << '\t' << "����" << '\t' << "�������" << endl;
	InfoNode<T>* cur = head->link;

	// ���δ�ӡ���нڵ���Ϣ
	while (cur != NULL) {
		cout << cur->data << endl; // �������ص� << �������ӡ��Ϣ
		cur = cur->link;
	}
	cout << endl;
}

template <class T>
class System { // ϵͳ�࣬���ڽ����͹���ִ�и��ֲ���
private :
	InfoList<T>* Info;
public :
	~System() { delete Info; } // �����˳�ʱ�ͷſռ�
	void init(); // ��ʼ��ϵͳ
	void loop(); // ��ѭ����������ѯ���û��Ĳ�����ִ�У�
	void insert(); // ִ�в���ָ��
	void remove(); // ִ��ɾ��ָ��
	void update(); // ִ���޸�ָ��
	void search(); // ִ�в���ָ��
	void show(); // ִ��ͳ��ָ��
};

// ��ʼ��
template <class T>
void System<T>::init() {
	Info = new InfoList<T>;
	int studentNums;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	cin >> studentNums;
	// �淶���벢�׳��쳣����
	while (studentNums <= 0 || cin.fail())
	{
		cout << "��������ֻ������������" << endl;
		cout << "���������뿼��������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> studentNums;
	}

	// ����������Ϣ���������
	for (int i = 0; i < studentNums; i++) {
		cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
		T tem;
		cin >> tem;
		InfoNode<T>* temNode = new InfoNode<T>(tem, NULL, NULL);
		while (!Info->Insert(i, temNode)) { // ����ͼʧ������������
			cout << "������Ϣ���Ϸ������������룡" << endl;
			cin >> tem;
			temNode = new InfoNode<T>(tem, NULL, NULL);
		}
	}
}

// ��ѭ������
template <class T>
void System<T>::loop() {
	init();
	cout << "�����ɹ���" << endl << endl;
	while (true) {
		int operation;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "��ѡ����Ҫ���еĲ��� ��1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
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
			cout << "�˳��ɹ�����ӭ�´ι��٣�" << endl;
			return;
			break;
		default :
			cout << "��������������볢���������룡" << endl;
			break;
		}
	}
}

// ִ�в���ָ��
template <class T>
void System<T>::insert() {
	int location;
	cout << "��������Ҫ����Ŀ�����λ�ã�" << endl;
	cin >> location;

	// ��� location �Ƿ�Ϸ������Ϸ����������룬ֱ���û��˳����ߺϷ�
	while (location < 0 || location > Info->Size()) {
		cout << "λ�ò��Ϸ������������룺������ -1 ���˳����β�����" << endl;
		cin >> location;
		if (location == -1) {
			cout << "�˳��ɹ����˴β��������ԣ�" << endl;
			return;
		}
	}

	// �������Ƿ�Ϸ������Ϸ����������룬ֱ���û��˳����ߺϷ�
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
	T tem;
	cin >> tem;
	InfoNode<T>* temNode = new InfoNode<T>(tem, NULL, NULL);
	while (!Info->Insert(location, temNode)) {
		cout << "����ʧ�ܣ����� 0 ���˳����β��������� 1 �Լ�����" << endl;
		bool tag; // �˳����߼����ı�ʶ
		cin >> tag;
		if (!tag) {
			cout << "�˳��ɹ����˴β��������ԣ�" << endl;
			return;
		}
		cout << "���ٴ����룺" << endl;
		cin >> tem;
		temNode = new InfoNode<T>(tem, NULL, NULL);
	}
	cout << "����ɹ���" << endl;
	show();
}

//ִ��ɾ��ָ��
template <class T>
void System<T>::remove() {
	string rmID;
	cout << "������Ҫɾ���ļ�¼��ѧ��ѧ�ţ�" << endl;
	cin >> rmID;

	// ����Ƿ�ɹ�ɾ�������ɹ�����������ѧ�ţ�ֱ���û��˳����߳ɹ�ɾ��
	while (!Info->Remove(rmID)) {
		cout << "ɾ��ʧ�ܣ����� 0 ���˳����β��������� 1 �Լ�����" << endl;
		bool tag;
		cin >> tag;
		if (!tag) {
			cout << "�˳��ɹ����˴β��������ԣ�" << endl;
			return;
		}
		cout << "���ٴ����룺" << endl;
		cin >> rmID;
	}
	cout << "ɾ���ɹ���" << endl;
	show();
}

//ִ���޸�ָ��
template <class T>
void System<T>::update() {
	string rmID;
	InfoNode<T>* t;
	cout << "������Ҫ�޸ĵļ�¼��ѧ��ѧ�ţ�" << endl;
	cin >> rmID;

	// ��� ѧ���Ƿ���ڣ����������������룬ֱ���û��˳����ߴ���
	while (!Info->Search(rmID, t)) {
		cout << "���޸�ѧ�������ڣ����������룺������ Q ���˳����β������������������ַ��Լ���...��";
		cin >> rmID;
		if (rmID == "Q") {
			cout << "�˳��ɹ����˴β��������ԣ�" << endl;
			return;
		}
		cout <<"���ٴ����룺" << endl;
		cin >> rmID;
	}

	// ����޸��Ƿ�Ϸ������Ϸ����������룬ֱ���û��˳����ߺϷ�
	cout << "�����������޸ĺ�Ŀ��ţ��������Ա����估�������" << endl;
	T tem;
	cin >> tem;
	while (!Info->Update(rmID, tem)) {
		cout << "�޸�ʧ�ܣ����� 0 ���˳����β��������� 1 �Լ�����" << endl;
		bool tag;
		cin >> tag;
		if (!tag) {
			cout << "�˳��ɹ����˴β��������ԣ�" << endl;
			return;
		}
		cout << "���ٴ����룺" << endl;
		cin >> tem;
	}
	cout << "�޸ĳɹ���" << endl;
	show();
}

// ִ�м���ָ��
template <class T>
void System<T>::search() {
	string checkID;

	// �涨���� Q Ϊȡ��ָ��
	cout << "���������ѯѧ����ѧ�ţ������� Q ���˳����β�����" << endl;
	cin >> checkID;
	if (checkID == "Q") {
		cout << "�˳��ɹ����˴β��������ԣ�" << endl;
		return;
	}
	InfoNode<T>* result;
	if (!Info->Search(checkID, result)) {
		cout << "δ��ѯ���ÿ�����" << endl;
	}
	else {
		// ��ӡ��Ϣ
		cout << "��ѯ�ɹ�����Ϣ���£�" << endl << endl;
		cout << "����" << '\t' << "����" << '\t' << "�Ա�" << '\t' << "����" << '\t' << "�������" << endl;
		cout << result->data.getID() << '\t' << result->data.getName() << '\t' << result->data.getGender() << '\t' << result->data.getAge() << '\t' << result->data.getCategoryOfExamination() << '\t' << endl;
	}
}

// ִ��ͳ��ָ��
template <class T>
void System<T>::show() {
	Info->Print(); // ֱ�ӵ��� Print() ����
}

// �������
int main() {
	System<StudentInfo> sys; // ����һ��ϵͳ
	sys.loop(); // ������ѭ��


# ifdef _WIN32
	system("pause");
# endif

	return 0;
}