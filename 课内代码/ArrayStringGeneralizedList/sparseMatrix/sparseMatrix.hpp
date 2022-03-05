# ifndef _SPARSE_MATRXI_H_
# define _SPARSE_MATRIX_H
# include <iostream>
using namespace std;

const int defaultSize = 100;

template <class T>
struct Trituple {
	int row, col;
	T value;
	void operator = (const Trituple<T>& x) {
		row = x.row;
		col = x.col;
		value = x.value;
	}
};

template <class T>
class SparseMatrix {
private :
	int Rows, Cols, Terms;
	Trituple<T>* smArray;
	int maxTerms;
	friend ostream& operator << (ostream& os, SparseMatrix<T>& M) {
		os << "rows = " << M.Rows << endl;
		os << "cols = " << M.Cols << endl;
		os << "Nonzero terms = " << M.Terms << endl;
		for (int i = 0; i < M.Terms; i++) os << M.smArray[i].row << ", " << M.smArray[i].col << " : " << M.smArray[i].value << endl;
		return os;
	}
	friend istream& operator >> (istream& is, SparseMatrix<T>& M) {
		cout << "Please input the rows, cols, terms : " << endl;
		is >> M.Rows >> M.Cols >> M.Terms;
		if (M.Terms > M.maxTerms) {
			cerr << "Too many terms ! " << endl;
			exit(1);
		}
		for (int i = 0; i < M.Terms; i++) {
			cout << "Please input row, col, value of " << "#" << i + 1 << endl;
			is >> M.smArray[i].row >> M.smArray[i].col >> M.smArray[i].value;
		}
		return is;
	}
public :
	SparseMatrix(int sz = defaultSize);
	SparseMatrix(const SparseMatrix<T>& x);
	~SparseMatrix() { delete[] smArray; }
	void operator = (const SparseMatrix<T>& x) { this->SparseMatrix<int>::SparseMatrix(x); }
	SparseMatrix<T> Transpose(); // 转置
	SparseMatrix<T> FastTranspose(); // 快速转置
	SparseMatrix<T> Add(SparseMatrix<T>& b); // 矩阵相加
	SparseMatrix<T> Multiply(SparseMatrix<T>& b); // 矩阵相乘
};

template <class T>
SparseMatrix<T>::SparseMatrix(int sz) : maxTerms(sz) {
	if (sz < 1) {
		cerr << "Initialing Wrong ! " << endl;
		exit(1);
	}
	smArray = new Trituple<T>[sz];
	if (smArray == NULL) {
		cerr << "Memory Allocating Wrong ! " << endl;
		exit(1);
	}
	Rows = Cols = Terms = 0;
}

template <class T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& x) {
	Rows = x.Rows;
	Cols = x.Cols;
	Terms = x.Terms;
	maxTerms = x.maxTerms;
	smArray = new Trituple<T>[maxTerms];
	if (smArray == NULL) {
		cerr << "Memory Allocating Wrong ! " << endl;
	}
	for (int i = 0; i < Terms; i++) smArray[i] = x.smArray[i];
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::Transpose() {
	SparseMatrix<T> b(this->maxTerms);
	b.Rows = Cols;
	b.Cols = Rows;
	b.Terms = Terms;
	if (Terms > 0) {
		int currentB = 0;
		for (int i = 0; i < Cols; i++) {
			for (int j = 0; j < Terms; j++) {
				if (smArray[j].col == i) {
					b.smArray[currentB].row = i;
					b.smArray[currentB].col = smArray[j].row;
					b.smArray[currentB].value = smArray[j].value;
					currentB++;
				}
			}
		}
	}
	return b;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::FastTranspose() {
	SparseMatrix<T> b(this->maxTerms);
	b.Rows = Rows;
	b.Cols = Cols;
	b.Terms = Terms;
	if (Terms == 0) return b;

	// 建立两个辅助数组用于存储转置每一行的数量和起始位置
	int* rowSize = new int[Cols];
	int* rowStart = new int[Cols];
	for (int i = 0; i < Cols; i++) rowSize[i] = 0;
	for (int i = 0; i < Terms; i++) rowSize[smArray[i].col]++;
	rowStart[0] = 0;
	for (int i = 1; i < Cols; i++) rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

	for (int i = 0; i < Terms; i++) {
		int j = rowStart[smArray[i].col];
		b.smArray[j].row = smArray[i].col;
		b.smArray[j].col = smArray[i].row;
		b.smArray[j].value = smArray[i].value;
		rowStart[smArray[i].col]++;
	}
	delete[] rowSize, delete[] rowStart;
	return b;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::Add(SparseMatrix<T>& b) {
	SparseMatrix<T> re;
	if (Rows != b.Rows && Cols != b.Cols) {
		cout << "Illegal add operation ! " << endl;
		return re;
	}
	re.Rows = Rows, re.Cols = Cols;

	int i = 0, j = 0;
	while (i < Terms && j < b.Terms) {
		int index_a = Cols * smArray[i].row + smArray[i].col;
		int index_b = Cols * b.smArray[j].row + b.smArray[j].col;
		if (index_a < index_b) re.smArray[re.Terms++] = smArray[i++];
		else if (index_a > index_b) re.smArray[re.Terms++] = b.smArray[j++];
		else {
			int tem = smArray[i].value + b.smArray[j].value;
			if (tem == 0) i++, j++;
			else {
				re.smArray[re.Terms] = smArray[i];
				re.smArray[re.Terms++].value = tem;
				i++, j++;
			}
		}
	}
	for (; i < Terms; i++) re.smArray[re.Terms++] = smArray[i];
	for (; j < Terms; j++) re.smArray[re.Terms++] = b.smArray[j];
	return re;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::Multiply(SparseMatrix<T>& b) {
	SparseMatrix<T> re;
	if (Cols != b.Rows) {
		cout << "Illegal multiply operation ! " << endl;
		return re;
	}
	re.Rows = Rows;
	re.Cols = b.Cols;
	re.Terms = 0;
	int* rowSize = new int[b.Rows];
	int* rowStart = new int[b.Rows + 1];
	T* tem = new T[b.Cols];
	for (int i = 0; i < b.Rows; i++) rowSize[i] = 0;
	for (int i = 0; i < b.Terms; i++) rowSize[b.smArray[i].row]++;
	rowStart[0] = 0;
	for (int i = 1; i < b.Rows + 1; i++) rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
	int current = 0;
	while (current < Terms) {
		int rowA = smArray[current].row;
		for (int i = 0; i < b.Cols; i++) tem[i] = 0;
		while (current < Terms && smArray[current].row == rowA) {
			int colA = smArray[current].col;
			for (int i = rowStart[colA]; i < rowStart[colA + 1]; i++) {
				int colB = b.smArray[i].col;
				tem[colB] += smArray[current].value * b.smArray[i].value;
			}
			current++;
		}
		for (int i = 0; i < b.Cols; i++) {
			if (tem[i] != 0) {
				re.smArray[re.Terms].row = rowA;
				re.smArray[re.Terms].col = i;
				re.smArray[re.Terms].value = tem[i];
				re.Terms++;
			}
		}
	}
	delete[] rowSize, delete[] rowStart;
	return re;
}


# endif