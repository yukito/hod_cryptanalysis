#include "poly_operation.h"

poly *initpoly(void)
{
	poly *term=(poly *)malloc(sizeof(poly));
	term->coef=0;
	term->degree=0;
	term->nextterm=NULL;
	return term;
}

poly *input_poly()
{
	poly *_poly=(poly *)malloc(sizeof(poly));
	poly *newPoly=_poly;
	int degree;
	int coef;
	
	while(1){
		printf("coef and degree:"); 
		scanf("%d %d", &coef, &degree);
		newPoly->degree=degree;
		newPoly->coef=coef;
		if(degree == 0 && coef == 0) break; 
		newPoly->nextterm=(poly *)malloc(sizeof(poly));
		newPoly=newPoly->nextterm;
	}

	return _poly;
}

poly *setpoly(int coef, int degree)
{
	poly *term=(poly *)malloc(sizeof(poly));
	term->coef=coef;
	term->degree=degree;
	term->nextterm=initpoly();
	return term;
}


void sortpoly(poly *form)
{
	poly *i, *j;
	int temp;


	for(i=form;i->nextterm!=NULL;i=i->nextterm){
		for(j=i->nextterm;j->nextterm!=NULL;j=j->nextterm){
			if(i->degree < j->degree){
				temp=i->degree;
				i->degree=j->degree;
				j->degree=temp;
				temp=i->coef;
				i->coef=j->coef;
				j->coef=temp;
			}
		}
	}
}

void ntimepoly(int num, poly *form)
{
	poly *i;
	for(i=form;i->nextterm!=NULL;i=i->nextterm)
		i->coef*=num;
}

poly *mulpoly(poly *form1, poly *form2, int q)
{
	poly *i, *j;
	poly *result=(poly *)malloc(sizeof(poly));
	poly *term=result;


	for(i=form1;i->nextterm!=NULL;i=i->nextterm){
		for(j=form2;j->nextterm!=NULL;j=j->nextterm){
			term->degree=i->degree+j->degree;
			term->coef=i->coef*j->coef%q;
			term->nextterm=initpoly();
			term=term->nextterm;
		}
//		sortpoly(result);
//		unipoly(result);
	}
	releasepoly(form1); releasepoly(form2);		
	return result;
}

void exorpoly(poly *form1, poly *form2)
{
	while(1){
		if(form1->nextterm->nextterm==NULL){
			form1->nextterm=form2;
			break;
		}
		form1=form1->nextterm;
	}
}

void unipoly(poly *form)
{
	poly *i=form;
	poly *temp;

	while(i->nextterm!=NULL){
		if(i->degree == i->nextterm->degree){
			i->coef += i->nextterm->coef;
			temp=i->nextterm;
			i->nextterm=temp->nextterm;
			free(temp);
		}else{
			i=i->nextterm;
		}
	}
	i->nextterm=initpoly();
}

void modpoly(poly *form, int q)
{
	poly *i;
	for(i=form;i->nextterm!=NULL;i=i->nextterm)
		i->coef=i->coef%q;
}

void dumpPoly(poly *form)
{
	poly *i;

	for(i=form;i->nextterm!=NULL;i=i->nextterm){
		printf("%dx^%d", i->coef, i->degree);
		if(i->nextterm->nextterm!=NULL) printf("+");
	}
	printf("\n");
	return;
}

void Poly2array(poly *form,int *array)
{
	poly *i;

	for(i=form;i->nextterm!=NULL;i=i->nextterm){
		array[i->degree]=i->coef;
	}
	return;
}

void releasepoly(poly *form)
{
	poly *i,*j;
	if(form==NULL) return;
	while(form->nextterm!=NULL){
		for(i=form;;i=i->nextterm){
			if(i->nextterm==NULL){
				free(i);
				j->nextterm=NULL;
				break;
			}
			j=i;
		}
	}		
	free(form);
	return;
}
