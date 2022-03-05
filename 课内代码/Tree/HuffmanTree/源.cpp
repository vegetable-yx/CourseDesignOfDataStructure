# include "HuffmanTree.h"
using namespace std;

struct word {
	char ch;
	int key;
	word() : ch('!'), key(1) {}
	word(char c, int k) : ch(c), key(k) {}
	//void operator = (const word& W) {
	//	ch = W.ch;
	//	key = W.key;
	//}
	bool operator <= (const word& wd) {
		if (key <= wd.key) return true;
		return false;
	}
	friend ostream& operator << (ostream& out, word& W) {
		out << W.ch;
		return out;
	}
};

int main() {
	word w[10] = { {'A', 1}, {'B', 2}, {'Z', 26}, {'P', 16}, {'Q', 17}, {'D', 4}, {'I', 9}, {'S', 19}, {'Y', 25}, {'X', 24} };
	HuffmanTree<int, word>HT(w, 10);
	cout << HT;


	return 0;
}