# include <iostream>
# include <fstream>
# include <cctype>
# include <limits>
# include <string.h>
using namespace std;

// 文件系统类， 封装了文件名和相应的一些操作
class FileSystem {
private :
	char* file; // 文件名， 代表着一个文本文件
	int* next; // next 数组， 是根据待查找的关键字产生的， 用于 KMP 算法进行关键字的查找
	void getNext(string pat, int* next); // 产生 next 数组
	int Search(int start, string target, string pat, bool tag); // 查找关键字
public :
	FileSystem() : file(NULL), next(NULL) {} // 构造函数
	~FileSystem(); // 析构函数
	bool CreateFile(char* fileName); // 创建一个文本文件
	bool InputFile(); // 向文件输入文本
	int OutputFile(char* fileName, string pat, bool tag); // 输出文件内容并用 KMP 算法统计与关键字匹配的数量
};

// 析构函数
FileSystem::~FileSystem() {
	delete next;
}

// 创建文本文件
bool FileSystem::CreateFile(char* fileName) {
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
bool FileSystem::InputFile() {
	ofstream out(file, ios::out); // 建立输入流

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
int FileSystem::OutputFile(char* fileName, string pat, bool tag) {
	int count = 0; // 关键字个数计数
	ifstream in(file, ios::in); // 建立输出流
	char buffer[500]; // 缓存数组

	// 根据关键字 pat 建立 next 数组
	next = new int[pat.length()];
	getNext(pat, next);

	// 不断读取文件内容， 直到文件末尾
	while (!in.eof())
	{
		in.getline(buffer, sizeof(buffer)); // 先将一行内容读取到 buffer
		count += Search(0, buffer, pat, tag); // 对该行执行一次关键字的搜索， 并将个数加到 count 上
		cout << buffer << endl; // 打印该行
	}

	in.close();
	return count;
}

// 搜索函数， 需要四个参数： target 的检索起始位置， target 字符串， pat 字符串， tag 标记（是否为全匹配）
int FileSystem::Search(int start, string target, string pat, bool tag) {
	int posP = 0, posT = start; // 初始化 pat 和 target 的起始位置
	int lP = pat.length(), lT = target.length(); // 获取长度
	if (start >= lT) return 0; // 起始位置超过最后的位置， 直接返回 0
	
	// 根据 KMP 算法， 得到 next 数组后， 对两个字符串进行搜索， 时间复杂度为 O(m + n)
	while (posP < lP && posT < lT) {
		if (posP == -1 || pat[posP] == target[posT]) posP++, posT++;
		else posP = next[posP];
	}

	// 检测到末尾， 无匹配的字段， 则关键字为 0 个
	if (posP < lP) return 0;
	else if (!tag) { // 若匹配模式为部分匹配， 无需检测前后是什么字符
		return 1 + Search(posT, target, pat, tag); // 找到1个关键字后， 继续从后面开始进行下一轮查找
	}
	else { // 若匹配模式为全匹配， 则需检测前面和后面的字符
		if ((posT - lP == 0 || !isalnum(target[posT - lP - 1])) && (posT >= lT || !isalnum(target[posT]))) { // 若前面还有字符，则不能为字母或者数字； 若后面还有字符，也不能为字母或者数字。当满足该条件时说明成功找到一个全匹配的目标， 计数 + 1
			return 1 + Search(posT, target, pat, tag); // 找到1个关键字后， 继续从后面开始进行下一轮查找
		}
		else { // 不满足时， 计数不增加， 继续从后面开始检测
			return Search(posT, target, pat, tag);
		}
	}
	
}

// 产生 next 数组
void FileSystem::getNext(string pat, int* next) {
	// 初始化
	int j = 0, k = -1, len = pat.length();
	next[0] = -1;

	// 对数组的第 1 ~ len - 1 个元素赋值
	while (j < len - 1) {
		if (k == -1 || pat[j] == pat[k]) { // 若 k == -1 或 第 j 和第 k 位相同
			++j, ++k;
			next[j] = k;
		}
		else k = next[k];
	}
}


int main() {
	FileSystem MyFile; // 实例化一个文件系统类
	cout << "欢迎来到关键字检索系统！" << endl << endl;

	// 输入文件名并检测是否为合法的文本文件
	char fileName[100];
	cout << "请输入文件名：";
	cin >> fileName;

	// 清空剩下的输入
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// 检测
	while (!MyFile.CreateFile(fileName)) {
		cout << "应当为合法的 .txt 文件名格式！请重新输入名字！" << endl;
		cin >> fileName;
	}

	while (!MyFile.InputFile()) {
		cout << "文件打开失败， 请检查文件名是否合法并重新输入！" << endl;

		// 重新输入文件名
		cin >> fileName;
		while (!MyFile.CreateFile(fileName)) {
			cout << "应当为合法的文本文件名格式！请重新输入名字！" << endl;
			cin >> fileName;
		}
	}
	cout << "本段文本已保存到" << fileName << "中！" << endl << endl;
	
	// 输入关键字并搜索
	string target;
	cout << "请输入要检索的文字（不含空格）：";
	cin >> target;

	// 输入检索模式
	string check;
	bool tag;
	cout << "请输入检索方式（ 0 为部分匹配查找， 1 为全匹配查找）：" << endl;
	cin >> check;

	// 输入不合法则重新输入
	while (check != "0" && check != "1") {
		cout << "输入不合法， 请重新输入：" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> check;
	}

	// 根据输入确定 tag 的值， 并在之后会用到
	if (check == "0") tag = false;
	else tag = true;

	cout << endl << "显示源文件：" << fileName << endl << endl;

	// 边输出文件内容边按检索模式检索关键字
	int numOfTarget = MyFile.OutputFile(fileName, target, tag);

	cout << "在源文件中共检索到：" << numOfTarget << "个关键字\"" << target << "\"！" << endl << endl;

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}