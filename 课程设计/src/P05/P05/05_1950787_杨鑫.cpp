# include <iostream>
# include <fstream>
# include <cctype>
# include <limits>
# include <string.h>
using namespace std;

// �ļ�ϵͳ�࣬ ��װ���ļ�������Ӧ��һЩ����
class FileSystem {
private :
	char* file; // �ļ����� ������һ���ı��ļ�
	int* next; // next ���飬 �Ǹ��ݴ����ҵĹؼ��ֲ����ģ� ���� KMP �㷨���йؼ��ֵĲ���
	void getNext(string pat, int* next); // ���� next ����
	int Search(int start, string target, string pat, bool tag); // ���ҹؼ���
public :
	FileSystem() : file(NULL), next(NULL) {} // ���캯��
	~FileSystem(); // ��������
	bool CreateFile(char* fileName); // ����һ���ı��ļ�
	bool InputFile(); // ���ļ������ı�
	int OutputFile(char* fileName, string pat, bool tag); // ����ļ����ݲ��� KMP �㷨ͳ����ؼ���ƥ�������
};

// ��������
FileSystem::~FileSystem() {
	delete next;
}

// �����ı��ļ�
bool FileSystem::CreateFile(char* fileName) {
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
bool FileSystem::InputFile() {
	ofstream out(file, ios::out); // ����������

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
int FileSystem::OutputFile(char* fileName, string pat, bool tag) {
	int count = 0; // �ؼ��ָ�������
	ifstream in(file, ios::in); // ���������
	char buffer[500]; // ��������

	// ���ݹؼ��� pat ���� next ����
	next = new int[pat.length()];
	getNext(pat, next);

	// ���϶�ȡ�ļ����ݣ� ֱ���ļ�ĩβ
	while (!in.eof())
	{
		in.getline(buffer, sizeof(buffer)); // �Ƚ�һ�����ݶ�ȡ�� buffer
		count += Search(0, buffer, pat, tag); // �Ը���ִ��һ�ιؼ��ֵ������� ���������ӵ� count ��
		cout << buffer << endl; // ��ӡ����
	}

	in.close();
	return count;
}

// ���������� ��Ҫ�ĸ������� target �ļ�����ʼλ�ã� target �ַ����� pat �ַ����� tag ��ǣ��Ƿ�Ϊȫƥ�䣩
int FileSystem::Search(int start, string target, string pat, bool tag) {
	int posP = 0, posT = start; // ��ʼ�� pat �� target ����ʼλ��
	int lP = pat.length(), lT = target.length(); // ��ȡ����
	if (start >= lT) return 0; // ��ʼλ�ó�������λ�ã� ֱ�ӷ��� 0
	
	// ���� KMP �㷨�� �õ� next ����� �������ַ������������� ʱ�临�Ӷ�Ϊ O(m + n)
	while (posP < lP && posT < lT) {
		if (posP == -1 || pat[posP] == target[posT]) posP++, posT++;
		else posP = next[posP];
	}

	// ��⵽ĩβ�� ��ƥ����ֶΣ� ��ؼ���Ϊ 0 ��
	if (posP < lP) return 0;
	else if (!tag) { // ��ƥ��ģʽΪ����ƥ�䣬 ������ǰ����ʲô�ַ�
		return 1 + Search(posT, target, pat, tag); // �ҵ�1���ؼ��ֺ� �����Ӻ��濪ʼ������һ�ֲ���
	}
	else { // ��ƥ��ģʽΪȫƥ�䣬 ������ǰ��ͺ�����ַ�
		if ((posT - lP == 0 || !isalnum(target[posT - lP - 1])) && (posT >= lT || !isalnum(target[posT]))) { // ��ǰ�滹���ַ�������Ϊ��ĸ�������֣� �����滹���ַ���Ҳ����Ϊ��ĸ�������֡������������ʱ˵���ɹ��ҵ�һ��ȫƥ���Ŀ�꣬ ���� + 1
			return 1 + Search(posT, target, pat, tag); // �ҵ�1���ؼ��ֺ� �����Ӻ��濪ʼ������һ�ֲ���
		}
		else { // ������ʱ�� ���������ӣ� �����Ӻ��濪ʼ���
			return Search(posT, target, pat, tag);
		}
	}
	
}

// ���� next ����
void FileSystem::getNext(string pat, int* next) {
	// ��ʼ��
	int j = 0, k = -1, len = pat.length();
	next[0] = -1;

	// ������ĵ� 1 ~ len - 1 ��Ԫ�ظ�ֵ
	while (j < len - 1) {
		if (k == -1 || pat[j] == pat[k]) { // �� k == -1 �� �� j �͵� k λ��ͬ
			++j, ++k;
			next[j] = k;
		}
		else k = next[k];
	}
}


int main() {
	FileSystem MyFile; // ʵ����һ���ļ�ϵͳ��
	cout << "��ӭ�����ؼ��ּ���ϵͳ��" << endl << endl;

	// �����ļ���������Ƿ�Ϊ�Ϸ����ı��ļ�
	char fileName[100];
	cout << "�������ļ�����";
	cin >> fileName;

	// ���ʣ�µ�����
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// ���
	while (!MyFile.CreateFile(fileName)) {
		cout << "Ӧ��Ϊ�Ϸ��� .txt �ļ�����ʽ���������������֣�" << endl;
		cin >> fileName;
	}

	while (!MyFile.InputFile()) {
		cout << "�ļ���ʧ�ܣ� �����ļ����Ƿ�Ϸ����������룡" << endl;

		// ���������ļ���
		cin >> fileName;
		while (!MyFile.CreateFile(fileName)) {
			cout << "Ӧ��Ϊ�Ϸ����ı��ļ�����ʽ���������������֣�" << endl;
			cin >> fileName;
		}
	}
	cout << "�����ı��ѱ��浽" << fileName << "�У�" << endl << endl;
	
	// ����ؼ��ֲ�����
	string target;
	cout << "������Ҫ���������֣������ո񣩣�";
	cin >> target;

	// �������ģʽ
	string check;
	bool tag;
	cout << "�����������ʽ�� 0 Ϊ����ƥ����ң� 1 Ϊȫƥ����ң���" << endl;
	cin >> check;

	// ���벻�Ϸ�����������
	while (check != "0" && check != "1") {
		cout << "���벻�Ϸ��� ���������룺" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> check;
	}

	// ��������ȷ�� tag ��ֵ�� ����֮����õ�
	if (check == "0") tag = false;
	else tag = true;

	cout << endl << "��ʾԴ�ļ���" << fileName << endl << endl;

	// ������ļ����ݱ߰�����ģʽ�����ؼ���
	int numOfTarget = MyFile.OutputFile(fileName, target, tag);

	cout << "��Դ�ļ��й���������" << numOfTarget << "���ؼ���\"" << target << "\"��" << endl << endl;

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}