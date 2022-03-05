# include "BinaryTree.hpp"
using namespace std;

int main() {
	BinaryTree<char> tree('#');
	cin >> tree;
	cout << tree << endl;
	tree.PrintBTree(tree.getRoot());


	return 0;
}