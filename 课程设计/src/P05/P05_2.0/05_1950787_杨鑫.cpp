# include <iostream>
# include <fstream>
using namespace std;

struct TrieNode {

};

class Trie {

};

class System {
private :
	Trie* stringTree;
	char* file; // �ļ����� ������һ���ı��ļ�
public :
	System() : stringTree(NULL), file(NULL) {}
	~System() { delete stringTree; }
	bool CreateFile(char* fileName); // ����һ���ı��ļ�
	bool InputFile(); // ���ļ������ı�
	void OutputFile(char* fileName); // ����ļ�����
};

// �����ı��ļ�
bool System::CreateFile(char* fileName) {
	// ��� fileName �Ƿ��� ".txt" Ϊ��׺��β�����ֲ��ֲ�Ϊ��
	if (strlen(fileName) < 5 || strcmp(fileName + strlen(fileName) - 4, ".txt")) {
		return false;
	}
	else {
		// �����ļ���
		file = fileName;
		return true;
	}
}

// ���ļ���������
bool System::InputFile() {
	ofstream out(file, ios::in); // ����������

	// �ļ���ʧ�ܵļ��
	if (!out) {
		return false;
	}

	char buffer[500]; // �������飬 ������ʱ���ܼ�������
	cout << endl << "������һ��Ӣ�ģ������ı�������� ^  ���к����� Ctrl + Z ����ΪΪ������־��" << endl;

	// ���ϴӼ��̽������뵽���������У� ֱ������������־
	while (cin.getline(buffer, sizeof(buffer))) {
		out << buffer << endl; // �����������е��������뵽�ļ�

		// ���ĩβ�Ƿ��н�����־
		if (buffer[strlen(buffer) - 1] == '^') break;
	}

	out.close(); // �ر��ļ�

	//��ջ�����
	cin.clear();

	return true;
}

// ����ļ��� ͬʱÿ���һ�н��йؼ��ּ��
void System::OutputFile(char* fileName) {
	ifstream in(file, ios::out); // ���������
	char buffer[500]; // ��������

	// ���϶�ȡ�ļ����ݣ� ֱ���ļ�ĩβ
	while (!in.eof())
	{
		in.getline(buffer, sizeof(buffer)); // �Ƚ�һ�����ݶ�ȡ�� buffer
		cout << buffer << endl; // ��ӡ����
	}

	in.close();
}


int main() {
	System sys;
	cout << "��ӭ�����ؼ��ּ���ϵͳ��" << endl << endl;

	// �����ļ���������Ƿ�Ϊ�Ϸ����ı��ļ�
	char fileName[100];
	cout << "�������ļ�����";
	cin >> fileName;

	// ���ʣ�µ�����
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// ���
	while (!sys.CreateFile(fileName)) {
		cout << "Ӧ��Ϊ�Ϸ��� .txt �ļ�����ʽ���������������֣�" << endl;
		cin >> fileName;
	}

	while (!sys.InputFile()) {
		cout << "�ļ���ʧ�ܣ� �����ļ����Ƿ�Ϸ����������룡" << endl;

		// ���������ļ���
		cin >> fileName;
		while (!sys.CreateFile(fileName)) {
			cout << "Ӧ��Ϊ�Ϸ����ı��ļ�����ʽ���������������֣�" << endl;
			cin >> fileName;
		}
	}
	cout << "�����ı��ѱ��浽" << fileName << "�У�" << endl << endl;

	// ����ؼ��ֲ�����
	string target;
	cout << "������Ҫ���������֣�";
	cin >> target;
	cout << endl << "��ʾԴ�ļ���" << fileName << endl;

	sys.OutputFile(fileName);

	//cout << "��Դ�ļ��й���������" << numOfTarget << "���ؼ���\"" << target << "\"" << endl;

	system("pause");

	return 0;
}