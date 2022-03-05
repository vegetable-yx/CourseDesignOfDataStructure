# ifndef _MIN_SPAN_TREE_H_
# define _MIN_SPAN_TREE_H_
# include <iostream>
# include <float.h>
# include "../Graphmtx/Graphmtx.h"
# include "../../Tree/MinHeap/MinHeap.h"
# include "../../SetAndDictionary/UFSet/UFSets.h"

const float maxValue = FLT_MAX;

template <class T, class E>
struct MSTEdgeNode {
	int tail, head;
	E key;
	MSTEdgeNode() : tail(-1), head(-1), key(0) {}
};

template <class T, class E>
class MinSpanTree {
protected :
	MSTEdgeNode<T, E>* edgevalue;
	int maxsize, n;
public :
	MinSpanTree(int sz = DefaultSize - 1) : maxsize(sz), n(0) { edgevalue = new MSTEdgeNode<T, E>[sz]; }
	int Insert(MSTEdgeNode<T, E>& item);
};

template <class T, class E>
void Kruskal(Graphmtx<T, E>& G, MinSpanTree<T, E>& MST) {
	MSTEdgeNode<T, E> ed;
	int u, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumberOfEdges();
	MinHeap<E, MSTEdgeNode<T, E>> H(m);
	UFSets F(n);

	for (int u = 0; u < n; u++)
		for (int v = n + 1; v < n; v++)
			if (G.getWeight(u, v) != maxValue) {
				ed.tail = u, ed.head = v, ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}

	count = 1;
	while (count < n) {
		H.RemoveMin(ed);
		u = F.Find(ed.tail);
		v = F.Find(ed.head);
		if (u != v) {
			F.Union(u, v);
			MST.Insert(ed);
			count++;
		}
	}
}

template <class T, class E>
void Prim(Graphmtx<T, E>& G, MinSpanTree<T, E>& MST) {} // Ê¡ÂÔ...




# endif