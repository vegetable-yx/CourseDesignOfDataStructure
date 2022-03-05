# include <iostream>
# include <string>
# include "..\LinkedStack\LinkedStack.hpp"

void checkMatchedPairs(string expression) {
	LinkedStack<char> stack;
	for (auto s : expression) {
		if (s == '(') stack.Push(s);
		else if (s == ')') {
			char tem;
			if (stack.Pop(tem)) continue;
			else {
				cout << "Illegal expression ! " << endl;
				return;
			}
		}
	}
	if (stack.IsEmpty()) cout << "Legal expression ! " << endl;
	else cout << "Illegal expression ! " << endl;
}

int main() {
	string str;
	cin >> str;
	checkMatchedPairs(str);
	return 0;
}