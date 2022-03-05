# ifndef _POLYNOMAL_H_
# define _POLYNIMAL_H_
# include <iostream>
using namespace std;

struct Term {
	float coef;
	int exp;
	Term* link;
	Term(float c, int e, Term* next = NULL) : coef(c), exp(e), link(next) {};
	Term* InsertAfter(float c, int e);
	friend ostream& operator << (ostream&, const Term&);
};

class Polynomal {
public:
	Polynomal() { first = new Term(0, -1); }
	Polynomal(Polynomal& R);
	int maxOrder();
	Term* getHead() const { return first; }
private:
	Term* first;
	friend ostream& operator << (ostream&, const Polynomal&);
	friend istream& operator >> (istream&, Polynomal&);
	friend Polynomal operator + (Polynomal&, Polynomal&);
	friend Polynomal operator * (Polynomal&, Polynomal&);
};

Term* Term::InsertAfter(float c, int e) {
	link = new Term(c, e, link);
	return link;
}

ostream& operator << (ostream& out, const Term& x) {
	if (x.coef == 0.0) return out;
	out << x.coef;
	switch (x.exp) {
	case 0: break;
	case 1: 
		out << "X";
		break;
	default:
		out << "X^" << x.exp;
		break;
	}
	return out;
}

Polynomal::Polynomal(Polynomal& R) {
	first = new Term(0, -1);
	Term* desptr = first, * srcptr = R.getHead()->link;
	while (srcptr != NULL) {
		desptr->InsertAfter(srcptr->coef, srcptr->exp);
		srcptr = srcptr->link;
		desptr = desptr->link;
	}
}

int Polynomal::maxOrder() {
	Term* current = first;
	while (current->link != NULL) current = current->link;
	return current->exp;
}

istream& operator >> (istream& in, Polynomal& x) {
	Term* rear = x.getHead();
	float c;
	int e;
	while (1) {
		cout << "Input a term(coef, exp): " << endl;
		in >> c >> e;
		if (e < 0) break;
		rear = rear->InsertAfter(c, e);
	}
	return in;
}

ostream& operator << (ostream& out, const Polynomal& x) {
	Term* current = x.getHead()->link;
	cout << "The polynomal is: " << endl;
	bool h = true;
	while (current != NULL) {
		if (!h && current->coef > 0.0) out << " + ";
		h = false;
		out << *current;
		current = current->link;
	}
	out << endl;
	return out;
}

Polynomal operator + (Polynomal& A, Polynomal& B) {
	Term* pa, * pb, * pc, * p;
	float temp;
	Polynomal C;
	pc = C.getHead();
	pa = A.getHead()->link, pb = B.getHead()->link;

	while (pa != NULL && pb != NULL) {
		if (pa->exp == pb->exp) {
			temp = pa->coef + pb->coef;
			if (fabs(temp) > 0.001) pc = pc->InsertAfter(temp, pa->exp);//防止浮点数的舍入误差带来影响
			pa = pa->link, pb = pb->link;
		}else if (pa->exp < pb->exp) {
			pc = pc->InsertAfter(pa->coef, pa->exp);
			pa = pa->link;
		}else {
			pc = pc->InsertAfter(pb->coef, pb->exp);
			pb = pb->link;
		}
	}
	if (pa != NULL) p = pa;
	else p = pb;
	while (p != NULL) {
		pc = pc->InsertAfter(p->coef, p->exp);
		p = p->link;
	}
	return C;
}

Polynomal operator * (Polynomal& A, Polynomal& B) {
	Term* pa, * pb, * pc;
	int AL, BL, k, maxExp;
	Polynomal C;
	pc = C.getHead();
	AL = A.maxOrder(), BL = B.maxOrder();
	if (AL != -1 && BL != -1) {
		maxExp = AL + BL;
		float* result = new float[maxExp + 1];
		for (int i = 0; i <= maxExp; i++) result[i] = 0.0;
		pa = A.getHead()->link;
		while (pa != NULL) {
			pb = B.getHead()->link;
			while (pb != NULL) {
				k = pa->exp + pb->exp;
				result[k] += pa->coef * pb->coef;
				pb = pb->link;
			}
			pa = pa->link;
		}
		for (int i = 0; i <= maxExp; i++)
			if (fabs(result[i]) > 0.001) pc = pc->InsertAfter(result[i], i);
		delete[] result;
	}
	pc->link = NULL;
	return C;
}


#endif