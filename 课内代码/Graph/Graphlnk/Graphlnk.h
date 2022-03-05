# ifndef _GRAPHLNK_H_
# define _GRAPHLNK_H_
# include "../Graph/Graph.h"
using namespace std;

template <class T, class E>
struct Edge {
	int dest;
	E cost;
	Edge<T, E>* link;
	Edge() {}
	Edge(int num, E weight) : dest(num), cost, link(NULL){}
	bool operator != (Edge<T, E>& R) const { return dest != R.dest; }
};

template <class T, class E>
struct Vertex {
	T data;
	Edge<T, E>* adj;
};

template <class T, class E>
class Graphlnk : public Graph<T, E> {
private :
	Vertex<T, E>* NodeTable;
	int getVertexPos(const T vertex) {
		for (int i = 0; i < Graphlnk<T, E>::numVertices; i++)
			if (NodeTable[i].data == vertex) return i;
		return -1;
	}
	friend istream& operator >> (istream& in, Graphlnk<T, E>& G) {}
	friend ostream& operator << (ostream& out, Graphlnk<T, E>& G) {}
public :
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
	T getValue(int i) { return (i >= 0 && i < Graphlnk<T, E>::numVertices) ? NodeTable[i].data : 0; }
	E getWeight(int v1, int v2);
	bool insertVertex(const T& vertex);
	bool removeVertex(int v);
	bool insertEdge(int v1, int v2, E cost);
	bool removeEdge(int v1, int v2);
	int getFirstNeibor(int v);
	int getNextNeibor(int v, int w);
};

# endif