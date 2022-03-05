# ifndef _GRAPHMTX_H_
# define _GRAPHMTX_H_
# include "../Graph/Graph.h"
using namespace std;

template <class T, class E>
class Graphmtx : public Graph<T, E> {
private :
	friend istream& operator >> (istream& in, Graphmtx<T, E>& G) {
		int n, m, k, j;
		T e1, e2;
		E weight;
		in >> n >> m;
		for (int i = 0; i < n; i++) {
			in >> e1;
			G.insertVertex(e1);
		}
		int i = 0;
		while (i < m) {
			in >> e1 >> e2 >> weight;
			j = G.getVertexPos(e1);
			k = G.getVertexPos(e2);
			if (j == -1 || k == -1) cout << "信息有误，请重新输入！" << endl;
			else {
				G.insertEdge(j, k, weight);
				i++;
			}
		}
		return in;
	}
	friend ostream& operator << (ostream& out, Graphmtx<T, E>& G) {
		int n = G.NumberOfVertices();
		int m = G.NumberOfEdges();
		cout << n << "," << m << endl;
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

	T* VerticesList;
	E** Edge;
	int getVertexPos(T vertex) {
		for (int i = 0; i < Graphmtx<T, E>::numVertices; i++)
			if (VerticesList[i] == vertex) return i;
		return -1;
	}
public :
	Graphmtx(int sz = DefaultVertices);
	~Graphmtx() {
		delete[] VerticesList;
		delete[] Edge;
	}
	T getValue(int i) { return i >= 0 && i <= Graphmtx<T, E>::numVertices ? VerticesList[i] : NULL; }
	E getWeight(int v1, int v2) { return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0; }
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
};

template <class T, class E>
Graphmtx<T, E>::Graphmtx(int sz) {
	Graphmtx<T, E>::numVertices = sz;
	Graphmtx<T, E>::numVertices = 0;
	Graphmtx<T, E>::numEdges = 0;
	VerticesList = new T[maxVertices];
	Edge = (int**) new int* [maxVertices];
	for (int i = 0; i < maxVertices; i++) Edge[i] = new int[maxVertices];
	for (int i = 0; i < maxVertices; i++)
		for (int j = 0; j < maxVertices; j++) Edge[i][j] = (i == j) ? 0 : maxWeight;
}

template <class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v) {
	if (v != -1) {
		for (int col = 0; col < Graphmtx<T,E>::numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
	}
	return -1;
}

template <class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
	if (v != -1 && w != -1) {
		for (int col = w + 1; col <= Graphmtx<T, E>::numVertices; col++) if (Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
	}
	return -1;
}

template <class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex) {
	if (Graphmtx<T,E>::numVertices == maxVertices) return false;
	VerticesList[Graphmtx<T,E>::numVertices++] = vertex;
	return true;
}

template <class T, class E>
bool Graphmtx<T, E>::removeVertex(int v) {
	if (v < 0 && v >= Graphmtx<T,E>::numVertices) return false;
	if (Graphmtx<T, E>::numVertices == 1) return false;
	VerticesList[v] = VerticesList[Graphmtx<T,E>::numVertices - 1];
	for (int i = 0; i < Graphmtx<T, E>::numVertices; i++) if (Edge[i][v] > 0 && Edge[i][v] < maxWeight) Graphmtx<T, E>::numEdges--;
	for (int i = 0; i < Graphmtx<T, E>::numVertices; i++) Edge[i][v] = Edge[i][Graphmtx<T,E>::numVertices - 1];
	Graphmtx<T, E>::numVertices--;
	for (int j = 0; j < Graphmtx<T, E>::numVertices; j++) Edge[v][j] = Edge[Graphmtx<T, E>::numVertices][j];
	return true;
}

template <class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost) {
	if (v1 > -1 && v1 < Graphmtx<T,E>::numVertices && v2 > -1 && v2 < Graphmtx<T, E>::numVertices && Edge[v1][v2] == maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = cost;
		Graphmtx<T, E>::numEdges++;
		return true;
	}
	else return false;
}

template <class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2) {
	if (v1 > -1 && v1 < Graphmtx<T, E>::numVertices && v2 > -1 && v2 < Graphmtx<T,E>::numVertices && Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight) {
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		Graphmtx<T, E>::numEdges--;
		return true;
	}
	else return false;
}



# endif