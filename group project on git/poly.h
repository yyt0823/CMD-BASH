#ifndef POLYH
#define POLYH

struct PolyTerm {
	int coeff;
	int expo;
	struct PolyTerm *next;
};

extern struct PolyTerm *head;

int addPolyTerm(int coeff, int expo);
void displayPolynomial();
int evaluatePolynomial(int x);


#endif
