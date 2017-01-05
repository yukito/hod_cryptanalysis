typedef struct term{
	int degree;
	int coef;
	struct term *nextterm;
} poly;

poly *initpoly(void);
poly *input_poly(void);
poly *setpoly(int coef, int degree);
void sortpoly(poly *form);
void ntimepoly(int num,  poly *form);
poly *mulpoly(poly *form1, poly *form2, int q);
void exorpoly(poly *form1, poly *form2);
void unipoly(poly *form);
void modpoly(poly *form, int q);
void dumpPoly(poly *form);
void Poly2array(poly *form, int *array);
void releasepoly(poly *form);
