# ifndef _CALCULATOR_H_
# define _CALCULATOR_H_
# include <map>
# include "..\LinkedStack\LinkedStack.hpp"
using namespace std;

map<char, int> isp = { {'#',0}, {'(',1}, {'*',5}, {'/',5}, {'+',3}, {'-',3}, {')',6} };
map<char, int> icp = { {'#',0}, {'(',6}, {'*',4}, {'/',4}, {'+',2}, {'-',2}, {')',1} };

class Calculator : public LinkedStack<double> {
public :
	Calculator() { stack = LinkedStack<double>(); }
	void Run();
	void Clear();
private:
	LinkedStack<double> stack;
	void addStack(double);
	bool get2NumsFromStack(double&, double&);
	void calculate(char);
	void postfix();
};

void Calculator::addStack(double num) {
	stack.Push(num);
}

bool Calculator::get2NumsFromStack(double& left, double& right) {
	if (stack.Pop(right) && stack.Pop(left)) return true;
	cerr << "Illegal eqotion ! " << endl;
	return false;
}

void Calculator::calculate(char op) {
	double l, r;
	if (!get2NumsFromStack(l, r)) {
		Clear();
		return;
	}
	switch (op) {
	case '+':
		addStack(l + r);
		break;
	case '-':
		addStack(l - r);
		break;
	case '*':
		addStack(l * r);
		break;
	case '/':
		if (r == 0) {
			cerr << "Divided by zero ! " << endl;
			Clear();
			return;
		}
		addStack(l / r);
		break;
	default:
		Clear();
		return;
	}
}

void Calculator::postfix() {
	LinkedStack<char> s;
	char ch;
	double num;
	s.Push('#');
	cin >> ch;
	while (!s.IsEmpty()) {
		switch (ch) {
		case '+': case '-': case '*': case '/':case '#':case '(':case ')':
			char tem;
			s.getTop(tem);
			if (isp[tem] < icp[ch]) {
				s.Push(ch);
				cin >> ch;
				break;
			}
			else if (isp[tem] > icp[ch]) {
				char op;
				s.Pop(op);
				calculate(op);
			}
			else {
				char op;
				s.Pop(op);
				if (op == '(') cin >> ch;
			}
			break;
		default:
			cin.putback(ch);
			cin >> num;
			addStack(num);
			cin >> ch;
			break;
		}
	}
}

void Calculator::Clear() {
	stack.makeEmpty();
}

void Calculator::Run() {
	postfix();

	double re;
	if (stack.Pop(re) && !stack.Pop(re)) cout << "Result : " << re << endl;
	else cerr << "Illegal eqution ! " << endl;
}


#endif