# include <iostream>
# include <limits>
using namespace std;


# define DefaultSize 50
# define maxWeight 1e4 + 10 //  用于表示不连通的两点的距离

// 最小堆
template <class T, class E>
class MinHeap {
public:
	MinHeap(int sz = DefaultSize); // 构造函数
	~MinHeap() { delete[]heap; } // 析构函数
	bool Insert(const E x); // 插入
	bool RemoveMin(E& x); // 弹出最小元素
	bool IsEmpty() const { return currentSize == 0; } // 是否为空
	bool IsFull() const { return currentSize == maxHeapSize; } // 是否满
	void MakeEmpty() { currentSize = 0; } // 置空
private:
	E* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m); // 向下调整
	void siftUp(int satrt); // 向上调整
};

// 构造函数
template <class T, class E>
MinHeap<T, E>::MinHeap(int sz) {
	// 为 heap 分配空间
	maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new E[maxHeapSize];
	if (heap == NULL) {
		cerr << "堆存储分配失败 ！" << endl;
		exit(1);
	}
	currentSize = 0;
}

// 向下调整
template <class T, class E>
void MinHeap<T, E>::siftDown(int start, int m) {
	// i 为初始位置， j 为其一个子节点
	int i = start, j = 2 * i + 1;
	E tem = heap[i];

	// 一直调整至 m
	while (j <= m) {
		if (j < m && heap[j + 1] <= heap[j]) j++;  // j 指向其较小的子女
		if (tem <= heap[j]) break; // 已经符合条件， 直接退出
		 // 将小的往上移
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = tem; // 回放
}

// 向上调整
template <class T, class E>
void MinHeap<T, E>::siftUp(int start) {
	// j 为父节点
	int j = start, i = (j - 1) / 2;
	E tem = heap[j];

	// 一直调整至最上面
	while (j > 0) {
		if (heap[i] <= tem) break; // 已经满足条件
		 // 否则，则调整
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
		heap[j] = tem; // 回放
	}
}

// 插入
template <class T, class E>
bool MinHeap<T, E>::Insert(const E x) {
	// 如果堆已满
	if (currentSize == maxHeapSize) {
		cerr << "Heap FUll" << endl;
		return false;
	}

	// 向末尾插入
	heap[currentSize] = x;

	// 向上调整， 并使当前空间 + 1
	siftUp(currentSize);
	currentSize++;
	return true;
}

// 删除
template <class T, class E>
bool MinHeap<T, E>::RemoveMin(E& x) {
	// 堆空
	if (!currentSize) {
		cout << "Heap Empty" << endl;
		return false;
	}

	// 返回最上面的
	x = heap[0];

	// 用最下面的代替最上面的后向下调整
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}

// 前置声明
template <class T, class E>
class MinSpanTree;

// 图
template <class T, class E>
class Graphmtx {
private:
	// 重载输入
	friend istream& operator >> (istream& in, Graphmtx<T, E>& G) {
		int n, m, k, j;
		T e1, e2;
		E weight;
		in >> n >> m;

		// 接受顶点
		for (int i = 0; i < n; i++) {
			in >> e1;
			G.insertVertex(e1);
		}
		int i = 0;

		// 接受边
		while (i < m) {
			in >> e1 >> e2 >> weight;
			j = G.getVertexPos(e1);
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1) cout << "信息有误，请重新输入！" << endl; // 输入不合法
			else {
				G.insertEdge(j, k, weight);
				i++;
			}
		}
		return in;
	}

	// 重载输出
	friend ostream& operator << (ostream& out, Graphmtx<T, E>& G) {
		// 得到边和点的数目
		int n = G.NumberOfVertices();
		int m = G.NumberOfEdges();
		cout << n << "," << m << endl;

		// 遍历并打印
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

	// 邻接表的表示方法
	int maxVertices;
	int numEdges;
	int numVertices;
	T* VerticesList;
	E** Edge;

	// 返回顶点元素的位置
	int getVertexPos(T vertex) {
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex) return i;
		return -1;
	}
public:
	Graphmtx(int sz = DefaultSize); // 构造函数

	 // 析构函数
	~Graphmtx() {
		delete[] VerticesList;
		delete[] Edge;
	}
	bool GraphEmpty() const { return numEdges == 0; } // 判空
	bool GraphFull() const { return numEdges == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2; } // 判满
	int NumberOfVertices() { return numVertices; } // 返回顶点个数
	int NumberOfEdges() { return numEdges; } // 返回边的个数
	T getValue(int i) { return i >= 0 && i <= numVertices ? VerticesList[i] : NULL; } // 得到顶点的值
	E getWeight(int v1, int v2) { return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0; } // 得到边的权值
	int getFirstNeighbor(int v); // 得到顶点的第一个邻点
	int getNextNeighbor(int v, int w); // 得到下一个邻点
	bool insertVertex(const T& vertex); // 插入顶点
	bool insertEdge(T& V1, T& V2, E cost); // 插入边
	bool removeVertex(T& V); // 删除顶点
	bool removeEdge(T& V1, T& V2); // 删除边
	bool Prim(Graphmtx<T, E>*& G, const T start, MinSpanTree<T, E>*& MST); // 建立最小生成树
};

// 构造函数
template <class T, class E>
Graphmtx<T, E>::Graphmtx(int sz) {
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	VerticesList = new T[maxVertices];
	Edge = (int**) new int* [maxVertices];

	// 一些初始化
	for (int i = 0; i < maxVertices; i++) Edge[i] = new int[maxVertices];
	for (int i = 0; i < maxVertices; i++)
		for (int j = 0; j < maxVertices; j++) Edge[i][j] = (i == j) ? 0 : int(maxWeight);
}


// 得到第一个邻点
template <class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		for (int col = 0; col < Graphmtx<T, E>::numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
	}
	return -1;
}

// 得到下一个邻点
template <class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1 && w != -1) {
		for (int col = w + 1; col <= Graphmtx<T, E>::numVertices; col++) if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
	}
	return -1;
}

// 插入顶点
template <class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex) {
	// 已满
	if (Graphmtx<T, E>::numVertices == maxVertices) return false;

	// 在最后一个位置插入
	for (int i = 0; i < Graphmtx<T, E>::numVertices; i++) {
		if (VerticesList[i] == vertex) return false;
	}
	VerticesList[Graphmtx<T, E>::numVertices++] = vertex;
	return true;
}

// 删除顶点
template <class T, class E>
bool Graphmtx<T, E>::removeVertex(T& V) {
	int v = getVertexPos(V);

	// 删除的点位置不合法
	if (v < 0 && v >= Graphmtx<T, E>::numVertices) return false;
	if (Graphmtx<T, E>::numVertices == 1) return false;

	// 删除顶点和其所有相关的边
	VerticesList[v] = VerticesList[Graphmtx<T, E>::numVertices - 1];
	for (int i = 0; i < Graphmtx<T, E>::numVertices; i++) if (Edge[i][v] > 0 && Edge[i][v] < maxWeight) Graphmtx<T, E>::numEdges--;
	for (int i = 0; i < Graphmtx<T, E>::numVertices; i++) Edge[i][v] = Edge[i][Graphmtx<T, E>::numVertices - 1];
	Graphmtx<T, E>::numVertices--;
	for (int j = 0; j < Graphmtx<T, E>::numVertices; j++) Edge[v][j] = Edge[Graphmtx<T, E>::numVertices][j];
	return true;
}

// 插入边
template <class T, class E>
bool Graphmtx<T, E>::insertEdge(T& V1, T& V2, E cost) {
	// 获取两个顶点的位置
	int v1 = getVertexPos(V1);
	int v2 = getVertexPos(V2);

	// 如果原来不存在这个边并且点存在， 执行插入
	if (v1 > -1 && v1 < Graphmtx<T, E>::numVertices && v2 > -1 && v2 < Graphmtx<T, E>::numVertices && Edge[v1][v2] == maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = cost;
		Graphmtx<T, E>::numEdges++;
		return true;
	}
	else return false;
}

// 删除边 
template <class T, class E>
bool Graphmtx<T, E>::removeEdge(T& V1, T& V2) {
	// 获取顶点位置
	int v1 = getVertexPos(V1);
	int v2 = getVertexPos(V2);

	// 如果边和顶点都存在， 执行删除操作
	if (v1 > -1 && v1 < Graphmtx<T, E>::numVertices && v2 > -1 && v2 < Graphmtx<T, E>::numVertices && Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		Graphmtx<T, E>::numEdges--;
		return true;
	}
	else return false;
}

// 连通树节点类
template <class T, class E>
struct MSTEdgeNode {
	T tail, head;
	E key;
	MSTEdgeNode() : tail(-1), head(-1), key(0) {} // 构造函数
	MSTEdgeNode(const MSTEdgeNode& MN) : head(MN.head), tail(MN.tail), key(MN.key) {} // 构造函数

	 // 重载运算符
	bool operator == (const MSTEdgeNode& MN);
	bool operator <= (const MSTEdgeNode& MN);
	bool operator > (const MSTEdgeNode& MN);
	void operator = (const MSTEdgeNode& MN);

	// 重载输出
	friend ostream& operator << (ostream& out, const MSTEdgeNode& MN) {
		out << MN.tail << " - ( " << MN.key << " ) - > " << MN.head;
		return out;
	}
};

// 重载 <= 运算符
template <class T, class E>
bool MSTEdgeNode<T, E>::operator <= (const MSTEdgeNode& MN) {
	return this->key <= MN.key;
}

// 重载 > 运算符
template <class T, class E>
bool MSTEdgeNode<T, E>::operator > (const MSTEdgeNode& MN) {
	return this->key > MN.key;
}

// 重载 == 运算符
 template <class T, class E>
 bool MSTEdgeNode<T, E>::operator == (const MSTEdgeNode& MN) {
	 if (this->head == MN.head && this->tail == MN.tail && this->key == MN.key) return true;
	 else return false;
}

 // 重载 = 运算符
 template <class T, class E>
 void MSTEdgeNode<T, E>::operator = (const MSTEdgeNode& MN) {
	 this->head = MN.head;
	 this->tail = MN.tail;
	 this->key = MN.key;
 }

 // 连通树类
template <class T, class E>
class MinSpanTree {
protected:
	MSTEdgeNode<T, E>* edgevalue;
	int maxsize, n;
public:
	MinSpanTree(int sz = DefaultSize - 1) : maxsize(sz), n(0) { edgevalue = new MSTEdgeNode<T, E>[sz]; } // 构造函数
	void Insert(MSTEdgeNode<T, E>*& item); // 插入节点
	void Show(); // 打印
};

// 插入节点
template <class T, class E>
void MinSpanTree<T, E>::Insert(MSTEdgeNode<T, E>*& item) {
	// 插入节点后， 计数 + 1
	edgevalue[n] = *item;
	n++;
}

// 打印
template <class T, class E>
void MinSpanTree<T, E>::Show() {
	// 还未建立最小生成树
	if (n == 0) {
		cout << "请先建立最小生成树！" << endl;
		return;
	}

	// 如果最小生成树没满（即未全部连通）
	MSTEdgeNode<T, E> nothing;
	if (edgevalue[maxsize - 1] == nothing) return;

	// 依次打印
	for (int i = 0; i < n; i++) {
		cout << edgevalue[i] << "    ";
	}
	cout << endl;
}

// 构建最小生成树
template <class T, class E>
bool Graphmtx<T, E>::Prim(Graphmtx<T, E>*& G, const T start, MinSpanTree<T, E>*& MST) {
	// 获取顶点和边的数量， 若顶点数量为 0 ，返回 false
	int vertices = G->NumberOfVertices();
	if (vertices == 0) return false;
	int edges = G->NumberOfEdges();

	// 记录上次的顶点
	int last = G->getVertexPos(start);
	MinHeap<E, MSTEdgeNode<T, E>>H(edges);

	// 记录顶点是否已经放入
	bool* MSTvertex = new bool[vertices];
	for (int i = 0; i < vertices; i++) MSTvertex[i] = false;

	// 一些初始化
	MSTvertex[last] = true;
	int count = 1;
	MSTEdgeNode<T, E> MN;

	// 不断扩充最小生成树直到符号条件
	do {
		int next = G->getFirstNeighbor(last);

		// 往堆里面插入邻点的所有边
		while (next != -1) {
			if (MSTvertex[next] == false) {
				MN.tail = G->VerticesList[last];
				MN.head = G->VerticesList[next];
				MN.key = G->getWeight(last, next);
				H.Insert(MN);
			}
			// 下一个邻点
			next = G->getNextNeighbor(last, next);
		}

		while (count < vertices) {
			// 堆空， 返回 false
			if (H.IsEmpty()) return false;

			// 弹出权值最小的边
			H.RemoveMin(MN);

			// 若另一个顶点未被使用， 插入最小生成树中 
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

// 电网类
class ElectricNetwork {
private:
	Graphmtx<char, int>* graph;
	MinSpanTree<char, int>* tree;
public :
	ElectricNetwork(); // 构造函数
	~ElectricNetwork(); // 析构函数
	void CreateVertex(); // 创建顶点
	void AddEdge(); // 增加边
	void CreateMinSpanTree(); // 创建最小生成树
	void ShowTree(); // 展示
	void Loop(); // 主循环
};

// 构造函数
ElectricNetwork::ElectricNetwork() {
	graph = new Graphmtx<char, int>;
	tree = new MinSpanTree<char, int>(0);
}

// 析构函数
ElectricNetwork::~ElectricNetwork() {
	delete graph;
	delete tree;
}

// 建立顶点
void ElectricNetwork::CreateVertex() {
	cout << "请输入顶点的个数： " << endl;
	int nums;
	cin >> nums;
	while (nums < 1) {
		cout << "个数必须大于 0 ！" << endl;
		cin >> nums;
	}

	// 不断新建顶点
	cout << "请依次输入各顶点的名称： " << endl;
	for (int i = 1; i <= nums; i++) {
		char vertex;
		cin >> vertex;

		// 尝试插入
		if (!graph->insertVertex(vertex)) {
			cout << "第 " << i << " 个顶点插入失败，请重新输入该点及之后的顶点！" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			i--;
		}
		else {
			cout << "第 " << i << " 个顶点插入成功！" << endl;
		}
	}

	// 重新确定最小生成树的大小
	delete tree;
	tree = new MinSpanTree<char, int>(nums - 1);
	cout << endl;
}

// 增加边
void ElectricNetwork::AddEdge() {
	while (true) {
		cout << "请输入两个顶点及边（输入 ? ? 0 以结束输入）：";
		char left, right;
		int value;
		cin >> left >> right >> value;

		// 直到遇到终结标志才停止输入
		if (left == '?' && right == '?' && value == 0) {
			cout << "插入结束！" << endl << endl;
			break;
		}
		// 尝试插入
		else {
			if (graph->insertEdge(left, right, value)) {
				cout << "该边插入成功！" << endl;
			}
			else {
				cout << "该边插入失败！" << endl;
			}
		}
	}
}

// 创建最小生成树
void ElectricNetwork::CreateMinSpanTree() {
	cout << "请输入起始顶点：";
	char start;
	cin >> start;

	// 尝试创建， 并判断是否建立成功
	if (graph->Prim(graph, start, tree)) {
		cout << "成功生成 Prim 最小生成树！" << endl << endl;
	}
	else {
		cout << "生成 Prim 最小生成树失败， 请先检查是否为连通图！" << endl << endl;
	}
}

// 展示最小生成树
void ElectricNetwork::ShowTree() {
	cout << "最小生成树的顶点及边为： " << endl << endl;
	tree->Show();
}

// 主循环
void ElectricNetwork::Loop() {
	cout << "**                 电网造价模拟系统                 **" << endl;
	cout << "======================================================" << endl;
	cout << "**               请选择要执行的操作：               **" << endl;
	cout << "**               A --- 创建电网顶点                 **" << endl;
	cout << "**               B --- 添加电网的边                 **" << endl;
	cout << "**               C --- 构造最小生成树               **" << endl;
	cout << "**               D --- 显示最小生成树               **" << endl;
	cout << "**               E --- 退出程序                     **" << endl;
	cout << "======================================================" << endl << endl;

	// 不断接受指令
	while (true) {
		cout << "请选择操作： ";
		char op;
		cin >> op;

		switch (op) {
		case 'A' :
			// 建立顶点
			CreateVertex();
			break;
		case 'B' :
			// 添加边
			AddEdge();
			break;
		case 'C' :
			// 创建最小生成树
			CreateMinSpanTree();
			break;
		case 'D' :
			// 展示
			ShowTree();
			break;
		case 'E' :
			// 退出程序
			cout << "程序退出， 欢迎下次光临！" << endl << endl;
			return;
			break;
		default:
			// 非法指令
			cout << "无效的指令， 请重新输入： ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}
}

int main() {
	// 实例化一个电网类
	ElectricNetwork Net;

	// 进入主循环
	Net.Loop();

# ifdef _WIN32
	system("pause");
# endif

	return 0;
}