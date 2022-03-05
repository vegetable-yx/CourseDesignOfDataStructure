# ifndef _GRAPH_H_
# define _GRAPH_H_
# include <iostream>

const int maxWeight = 1e5 + 10;
const int DefaultVertices = 30;
const int maxVertices = 1000;

template <class T, class E>
class Graph {
public :
	Graph(int sz = DefaultVertices) {}
	~Graph() {}
	virtual bool insertVertex(const T& vertex) = 0;
	virtual bool insertEdge(int v1, int v2, int weight) = 0;
	virtual bool removeVertex(int v) = 0;
	virtual bool removeEdge(int v1, int v2) = 0;
	bool GraphEmpty() const { return numEdges == 0; }
	bool GraphFull() const { return numEdges == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2; }
	int NumberOfVertices() { return numVertices; }
	int NumberOfEdges() { return numEdges; }
	virtual T getValue(int i) = 0;
	virtual E getWeight(int v1, int v2) = 0;
	virtual int getFirstNeighbor(int v) = 0;
	virtual int getNextNeighbor(int v1, int v2) = 0;
protected :
	int maxVertices;
	int numEdges;
	int numVertices;
	virtual int getVertexPos(T vertex) = 0;
};

# endif