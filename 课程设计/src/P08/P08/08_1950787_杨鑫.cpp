# include <iostream>
# include <limits>
using namespace std;


# define DefaultSize 50
# define maxWeight 1e4 + 10 //  ���ڱ�ʾ����ͨ������ľ���

// ��С��
template <class T, class E>
class MinHeap {
public:
	MinHeap(int sz = DefaultSize); // ���캯��
	~MinHeap() { delete[]heap; } // ��������
	bool Insert(const E x); // ����
	bool RemoveMin(E& x); // ������СԪ��
	bool IsEmpty() const { return currentSize == 0; } // �Ƿ�Ϊ��
	bool IsFull() const { return currentSize == maxHeapSize; } // �Ƿ���
	void MakeEmpty() { currentSize = 0; } // �ÿ�
private:
	E* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m); // ���µ���
	void siftUp(int satrt); // ���ϵ���
};

// ���캯��
template <class T, class E>
MinHeap<T, E>::MinHeap(int sz) {
	// Ϊ heap ����ռ�
	maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new E[maxHeapSize];
	if (heap == NULL) {
		cerr << "�Ѵ洢����ʧ�� ��" << endl;
		exit(1);
	}
	currentSize = 0;
}

// ���µ���
template <class T, class E>
void MinHeap<T, E>::siftDown(int start, int m) {
	// i Ϊ��ʼλ�ã� j Ϊ��һ���ӽڵ�
	int i = start, j = 2 * i + 1;
	E tem = heap[i];

	// һֱ������ m
	while (j <= m) {
		if (j < m && heap[j + 1] <= heap[j]) j++;  // j ָ�����С����Ů
		if (tem <= heap[j]) break; // �Ѿ����������� ֱ���˳�
		 // ��С��������
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = tem; // �ط�
}

// ���ϵ���
template <class T, class E>
void MinHeap<T, E>::siftUp(int start) {
	// j Ϊ���ڵ�
	int j = start, i = (j - 1) / 2;
	E tem = heap[j];

	// һֱ������������
	while (j > 0) {
		if (heap[i] <= tem) break; // �Ѿ���������
		 // ���������
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
		heap[j] = tem; // �ط�
	}
}

// ����
template <class T, class E>
bool MinHeap<T, E>::Insert(const E x) {
	// ���������
	if (currentSize == maxHeapSize) {
		cerr << "Heap FUll" << endl;
		return false;
	}

	// ��ĩβ����
	heap[currentSize] = x;

	// ���ϵ����� ��ʹ��ǰ�ռ� + 1
	siftUp(currentSize);
	currentSize++;
	return true;
}

// ɾ��
template <class T, class E>
bool MinHeap<T, E>::RemoveMin(E& x) {
	// �ѿ�
	if (!currentSize) {
		cout << "Heap Empty" << endl;
		return false;
	}

	// �����������
	x = heap[0];

	// ��������Ĵ���������ĺ����µ���
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}

// ǰ������
template <class T, class E>
class MinSpanTree;

// ͼ
template <class T, class E>
class Graphmtx {
private:
	// ��������
	friend istream& operator >> (istream& in, Graphmtx<T, E>& G) {
		int n, m, k, j;
		T e1, e2;
		E weight;
		in >> n >> m;

		// ���ܶ���
		for (int i = 0; i < n; i++) {
			in >> e1;
			G.insertVertex(e1);
		}
		int i = 0;

		// ���ܱ�
		while (i < m) {
			in >> e1 >> e2 >> weight;
			j = G.getVertexPos(e1);
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1) cout << "��Ϣ�������������룡" << endl; // ���벻�Ϸ�
			else {
				G.insertEdge(j, k, weight);
				i++;
			}
		}
		return in;
	}

	// �������
	friend ostream& operator << (ostream& out, Graphmtx<T, E>& G) {
		// �õ��ߺ͵����Ŀ
		int n = G.NumberOfVertices();
		int m = G.NumberOfEdges();
		cout << n << "," << m << endl;

		// ��������ӡ
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				E w = G.getWeight(i, j);
				if (w > 0 && w < maxWeight) {
					T e1 = G.getValue(i);
					T e2 = G.getValue(j);
					cout << "(" << e1 << "," << e2 << "," << w << ")" << endl;
				}
			}
		}
		return out;
	}

	// �ڽӱ�ı�ʾ����
	int maxVertices;
	int numEdges;
	int numVertices;
	T* VerticesList;
	E** Edge;

	// ���ض���Ԫ�ص�λ��
	int getVertexPos(T vertex) {
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex) return i;
		return -1;
	}
public:
	Graphmtx(int sz = DefaultSize); // ���캯��

	 // ��������
	~Graphmtx() {
		delete[] VerticesList;
		delete[] Edge;
	}
	bool GraphEmpty() const { return numEdges == 0; } // �п�
	bool GraphFull() const { return numEdges == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2; } // ����
	int NumberOfVertices() { return numVertices; } // ���ض������
	int NumberOfEdges() { return numEdges; } // ���رߵĸ���
	T getValue(int i) { return i >= 0 && i <= numVertices ? VerticesList[i] : NULL; } // �õ������ֵ
	E getWeight(int v1, int v2) { return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0; } // �õ��ߵ�Ȩֵ
	int getFirstNeighbor(int v); // �õ�����ĵ�һ���ڵ�
	int getNextNeighbor(int v, int w); // �õ���һ���ڵ�
	bool insertVertex(const T& vertex); // ���붥��
	bool insertEdge(T& V1, T& V2, E cost); // �����
	bool removeVertex(T& V); // ɾ������
	bool removeEdge(T& V1, T& V2); // ɾ����
	bool Prim(Graphmtx<T, E>*& G, const T start, MinSpanTree<T, E>*& MST); // ������С������
};

// ���캯��
template <class T, class E>
Graphmtx<T, E>::Graphmtx(int sz) {
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	VerticesList = new T[maxVertices];
	Edge = (int**) new int* [maxVertices];

	// һЩ��ʼ��
	for (int i = 0; i < maxVertices; i++) Edge[i] = new int[maxVertices];
	for (int i = 0; i < maxVertices; i++)
		for (int j = 0; j < maxVertices; j++) Edge[i][j] = (i == j) ? 0 : int(maxWeight);
}


// �õ���һ���ڵ�
template <class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		for (int col = 0; col < Graphmtx<T, E>::numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
	}
	return -1;
}

// �õ���һ���ڵ�
template <class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1 && w != -1) {
		for (int col = w + 1; col <= Graphmtx<T, E>::numVertices; col++) if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
	}
	return -1;
}

// ���붥��
template <class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex) {
	// ����
	if (Graphmtx<T, E>::numVertices == maxVertices) return false;

	// �����һ��λ�ò���
	for (int i = 0; i < Graphmtx<T, E>::numVertices; i++) {
		if (VerticesList[i] == vertex) return false;
	}
	VerticesList[Graphmtx<T, E>::numVertices++] = vertex;
	return true;
}

// ɾ������
template <class T, class E>
bool Graphmtx<T, E>::removeVertex(T& V) {
	int v = getVertexPos(V);

	// ɾ���ĵ�λ�ò��Ϸ�
	if (v < 0 && v >= Graphmtx<T, E>::numVertices) return false;
	if (Graphmtx<T, E>::numVertices == 1) return false;

	// ɾ���������������صı�
	VerticesList[v] = VerticesList[Graphmtx<T, E>::numVertices - 1];
	for (int i = 0; i < Graphmtx<T, E>::numVertices; i++) if (Edge[i][v] > 0 && Edge[i][v] < maxWeight) Graphmtx<T, E>::numEdges--;
	for (int i = 0; i < Graphmtx<T, E>::numVertices; i++) Edge[i][v] = Edge[i][Graphmtx<T, E>::numVertices - 1];
	Graphmtx<T, E>::numVertices--;
	for (int j = 0; j < Graphmtx<T, E>::numVertices; j++) Edge[v][j] = Edge[Graphmtx<T, E>::numVertices][j];
	return true;
}

// �����
template <class T, class E>
bool Graphmtx<T, E>::insertEdge(T& V1, T& V2, E cost) {
	// ��ȡ���������λ��
	int v1 = getVertexPos(V1);
	int v2 = getVertexPos(V2);

	// ���ԭ������������߲��ҵ���ڣ� ִ�в���
	if (v1 > -1 && v1 < Graphmtx<T, E>::numVertices && v2 > -1 && v2 < Graphmtx<T, E>::numVertices && Edge[v1][v2] == maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = cost;
		Graphmtx<T, E>::numEdges++;
		return true;
	}
	else return false;
}

// ɾ���� 
template <class T, class E>
bool Graphmtx<T, E>::removeEdge(T& V1, T& V2) {
	// ��ȡ����λ��
	int v1 = getVertexPos(V1);
	int v2 = getVertexPos(V2);

	// ����ߺͶ��㶼���ڣ� ִ��ɾ������
	if (v1 > -1 && v1 < Graphmtx<T, E>::numVertices && v2 > -1 && v2 < Graphmtx<T, E>::numVertices && Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		Graphmtx<T, E>::numEdges--;
		return true;
	}
	else return false;
}

// ��ͨ���ڵ���
template <class T, class E>
struct MSTEdgeNode {
	T tail, head;
	E key;
	MSTEdgeNode() : tail(-1), head(-1), key(0) {} // ���캯��
	MSTEdgeNode(const MSTEdgeNode& MN) : head(MN.head), tail(MN.tail), key(MN.key) {} // ���캯��

	 // ���������
	bool operator == (const MSTEdgeNode& MN);
	bool operator <= (const MSTEdgeNode& MN);
	bool operator > (const MSTEdgeNode& MN);
	void operator = (const MSTEdgeNode& MN);

	// �������
	friend ostream& operator << (ostream& out, const MSTEdgeNode& MN) {
		out << MN.tail << " - ( " << MN.key << " ) - > " << MN.head;
		return out;
	}
};

// ���� <= �����
template <class T, class E>
bool MSTEdgeNode<T, E>::operator <= (const MSTEdgeNode& MN) {
	return this->key <= MN.key;
}

// ���� > �����
template <class T, class E>
bool MSTEdgeNode<T, E>::operator > (const MSTEdgeNode& MN) {
	return this->key > MN.key;
}

// ���� == �����
 template <class T, class E>
 bool MSTEdgeNode<T, E>::operator == (const MSTEdgeNode& MN) {
	 if (this->head == MN.head && this->tail == MN.tail && this->key == MN.key) return true;
	 else return false;
}

 // ���� = �����
 template <class T, class E>
 void MSTEdgeNode<T, E>::operator = (const MSTEdgeNode& MN) {
	 this->head = MN.head;
	 this->tail = MN.tail;
	 this->key = MN.key;
 }

 // ��ͨ����
template <class T, class E>
class MinSpanTree {
protected:
	MSTEdgeNode<T, E>* edgevalue;
	int maxsize, n;
public:
	MinSpanTree(int sz = DefaultSize - 1) : maxsize(sz), n(0) { edgevalue = new MSTEdgeNode<T, E>[sz]; } // ���캯��
	void Insert(MSTEdgeNode<T, E>*& item); // ����ڵ�
	void Show(); // ��ӡ
};

// ����ڵ�
template <class T, class E>
void MinSpanTree<T, E>::Insert(MSTEdgeNode<T, E>*& item) {
	// ����ڵ�� ���� + 1
	edgevalue[n] = *item;
	n++;
}

// ��ӡ
template <class T, class E>
void MinSpanTree<T, E>::Show() {
	// ��δ������С������
	if (n == 0) {
		cout << "���Ƚ�����С��������" << endl;
		return;
	}

	// �����С������û������δȫ����ͨ��
	MSTEdgeNode<T, E> nothing;
	if (edgevalue[maxsize - 1] == nothing) return;

	// ���δ�ӡ
	for (int i = 0; i < n; i++) {
		cout << edgevalue[i] << "    ";
	}
	cout << endl;
}

// ������С������
template <class T, class E>
bool Graphmtx<T, E>::Prim(Graphmtx<T, E>*& G, const T start, MinSpanTree<T, E>*& MST) {
	// ��ȡ����ͱߵ������� ����������Ϊ 0 ������ false
	int vertices = G->NumberOfVertices();
	if (vertices == 0) return false;
	int edges = G->NumberOfEdges();

	// ��¼�ϴεĶ���
	int last = G->getVertexPos(start);
	MinHeap<E, MSTEdgeNode<T, E>>H(edges);

	// ��¼�����Ƿ��Ѿ�����
	bool* MSTvertex = new bool[vertices];
	for (int i = 0; i < vertices; i++) MSTvertex[i] = false;

	// һЩ��ʼ��
	MSTvertex[last] = true;
	int count = 1;
	MSTEdgeNode<T, E> MN;

	// ����������С������ֱ����������
	do {
		int next = G->getFirstNeighbor(last);

		// ������������ڵ�����б�
		while (next != -1) {
			if (MSTvertex[next] == false) {
				MN.tail = G->VerticesList[last];
				MN.head = G->VerticesList[next];
				MN.key = G->getWeight(last, next);
				H.Insert(MN);
			}
			// ��һ���ڵ�
			next = G->getNextNeighbor(last, next);
		}

		while (count < vertices) {
			// �ѿգ� ���� false
			if (H.IsEmpty()) return false;

			// ����Ȩֵ��С�ı�
			H.RemoveMin(MN);

			// ����һ������δ��ʹ�ã� ������С�������� 
			if (!MSTvertex[G->getVertexPos(MN.head)]) {
				MSTEdgeNode<T, E>* ptr = &MN;
				MST->Insert(ptr);
				last = G->getVertexPos(MN.head);
				MSTvertex[last] = true;
				count++;
				break;
			}
		}
	} while (count < vertices);

	return true;
}

// ������
class ElectricNetwork {
private:
	Graphmtx<char, int>* graph;
	MinSpanTree<char, int>* tree;
public :
	ElectricNetwork(); // ���캯��
	~ElectricNetwork(); // ��������
	void CreateVertex(); // ��������
	void AddEdge(); // ���ӱ�
	void CreateMinSpanTree(); // ������С������
	void ShowTree(); // չʾ
	void Loop(); // ��ѭ��
};

// ���캯��
ElectricNetwork::ElectricNetwork() {
	graph = new Graphmtx<char, int>;
	tree = new MinSpanTree<char, int>(0);
}

// ��������
ElectricNetwork::~ElectricNetwork() {
	delete graph;
	delete tree;
}

// ��������
void ElectricNetwork::CreateVertex() {
	cout << "�����붥��ĸ����� " << endl;
	int nums;
	cin >> nums;
	while (nums < 1) {
		cout << "����������� 0 ��" << endl;
		cin >> nums;
	}

	// �����½�����
	cout << "�������������������ƣ� " << endl;
	for (int i = 1; i <= nums; i++) {
		char vertex;
		cin >> vertex;

		// ���Բ���
		if (!graph->insertVertex(vertex)) {
			cout << "�� " << i << " ���������ʧ�ܣ�����������õ㼰֮��Ķ��㣡" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			i--;
		}
		else {
			cout << "�� " << i << " ���������ɹ���" << endl;
		}
	}

	// ����ȷ����С�������Ĵ�С
	delete tree;
	tree = new MinSpanTree<char, int>(nums - 1);
	cout << endl;
}

// ���ӱ�
void ElectricNetwork::AddEdge() {
	while (true) {
		cout << "�������������㼰�ߣ����� ? ? 0 �Խ������룩��";
		char left, right;
		int value;
		cin >> left >> right >> value;

		// ֱ�������ս��־��ֹͣ����
		if (left == '?' && right == '?' && value == 0) {
			cout << "���������" << endl << endl;
			break;
		}
		// ���Բ���
		else {
			if (graph->insertEdge(left, right, value)) {
				cout << "�ñ߲���ɹ���" << endl;
			}
			else {
				cout << "�ñ߲���ʧ�ܣ�" << endl;
			}
		}
	}
}

// ������С������
void ElectricNetwork::CreateMinSpanTree() {
	cout << "��������ʼ���㣺";
	char start;
	cin >> start;

	// ���Դ����� ���ж��Ƿ����ɹ�
	if (graph->Prim(graph, start, tree)) {
		cout << "�ɹ����� Prim ��С��������" << endl << endl;
	}
	else {
		cout << "���� Prim ��С������ʧ�ܣ� ���ȼ���Ƿ�Ϊ��ͨͼ��" << endl << endl;
	}
}

// չʾ��С������
void ElectricNetwork::ShowTree() {
	cout << "��С�������Ķ��㼰��Ϊ�� " << endl << endl;
	tree->Show();
}

// ��ѭ��
void ElectricNetwork::Loop() {
	cout << "**                 �������ģ��ϵͳ                 **" << endl;
	cout << "======================================================" << endl;
	cout << "**               ��ѡ��Ҫִ�еĲ�����               **" << endl;
	cout << "**               A --- ������������                 **" << endl;
	cout << "**               B --- ��ӵ����ı�                 **" << endl;
	cout << "**               C --- ������С������               **" << endl;
	cout << "**               D --- ��ʾ��С������               **" << endl;
	cout << "**               E --- �˳�����                     **" << endl;
	cout << "======================================================" << endl << endl;

	// ���Ͻ���ָ��
	while (true) {
		cout << "��ѡ������� ";
		char op;
		cin >> op;

		switch (op) {
		case 'A' :
			// ��������
			CreateVertex();
			break;
		case 'B' :
			// ��ӱ�
			AddEdge();
			break;
		case 'C' :
			// ������С������
			CreateMinSpanTree();
			break;
		case 'D' :
			// չʾ
			ShowTree();
			break;
		case 'E' :
			// �˳�����
			cout << "�����˳��� ��ӭ�´ι��٣�" << endl << endl;
			return;
			break;
		default:
			// �Ƿ�ָ��
			cout << "��Ч��ָ� ���������룺 ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
}

int main() {
	// ʵ����һ��������
	ElectricNetwork Net;

	// ������ѭ��
	Net.Loop();

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}