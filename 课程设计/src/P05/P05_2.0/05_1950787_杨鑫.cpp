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
	char* file; // 文件名， 代表着一个文本文件
public :
	System() : stringTree(NULL), file(NULL) {}
	~System() { delete stringTree; }
	bool CreateFile(char* fileName); // 创建一个文本文件
	bool InputFile(); // 向文件输入文本
	void OutputFile(char* fileName); // 输出文件内容
};

// 创建文本文件
bool System::CreateFile(char* fileName) {
	// 检测 fileName 是否以 ".txt" 为后缀结尾且名字部分不为空
	if (strlen(fileName) < 5 || strcmp(fileName + strlen(fileName) - 4, ".txt")) {
		return false;
	}
	else {
		// 保存文件名
		file = fileName;
		return true;
	}
}

// 向文件输入内容
bool System::InputFile() {
	ofstream out(file, ios::in); // 建立输入流

	// 文件打开失败的检测
	if (!out) {
		return false;
	}

	char buffer[500]; // 缓存数组， 用于临时接受键盘输入
	cout << endl << "请输入一段英文：（在文本最后输入 ^  或换行后输入 Ctrl + Z 以作为为结束标志）" << endl;

	// 不断从键盘接受输入到缓存数组中， 直到遇到结束标志
	while (cin.getline(buffer, sizeof(buffer))) {
		out << buffer << endl; // 将缓存数组中的内容输入到文件

		// 检测末尾是否有结束标志
		if (buffer[strlen(buffer) - 1] == '^') break;
	}

	out.close(); // 关闭文件

	//清空缓冲区
	cin.clear();

	return true;
}

// 输出文件， 同时每输出一行进行关键字检测
void System::OutputFile(char* fileName) {
	ifstream in(file, ios::out); // 建立输出流
	char buffer[500]; // 缓存数组

	// 不断读取文件内容， 直到文件末尾
	while (!in.eof())
	{
		in.getline(buffer, sizeof(buffer)); // 先将一行内容读取到 buffer
		cout << buffer << endl; // 打印该行
	}

	in.close();
}


int main() {
	System sys;
	cout << "欢迎来到关键字检索系统！" << endl << endl;

	// 输入文件名并检测是否为合法的文本文件
	char fileName[100];
	cout << "请输入文件名：";
	cin >> fileName;

	// 清空剩下的输入
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// 检测
	while (!sys.CreateFile(fileName)) {
		cout << "应当为合法的 .txt 文件名格式！请重新输入名字！" << endl;
		cin >> fileName;
	}

	while (!sys.InputFile()) {
		cout << "文件打开失败， 请检查文件名是否合法并重新输入！" << endl;

		// 重新输入文件名
		cin >> fileName;
		while (!sys.CreateFile(fileName)) {
			cout << "应当为合法的文本文件名格式！请重新输入名字！" << endl;
			cin >> fileName;
		}
	}
	cout << "本段文本已保存到" << fileName << "中！" << endl << endl;

	// 输入关键字并搜索
	string target;
	cout << "请输入要检索的文字：";
	cin >> target;
	cout << endl << "显示源文件：" << fileName << endl;

	sys.OutputFile(fileName);

	//cout << "在源文件中共检索到：" << numOfTarget << "个关键字\"" << target << "\"" << endl;

	system("pause");

	return 0;
}