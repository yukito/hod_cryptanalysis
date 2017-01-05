#include <stdlib.h>
#include "poly_operation.c"
//#include "extend_euc.c"
poly *lagrangePolynomial(int *point, int numofpoint, int q)
{
	int x,j;
	unsigned sum, jx;
	poly *px=setpoly(0,0);
	poly *form;
	poly *tmp;

	for(j=0;j<numofpoint;j++){
		sum=1;
		form=setpoly(1,0);
		for(x=0;x<numofpoint;x++){
			if(x==j) x++;
			if(x==numofpoint) break;
			if(j-x<0) jx=(q+(j-x))%q;
			else jx=j-x;
			sum=(sum*jx)%q;
			tmp=setpoly(1,1);
			exorpoly(tmp,setpoly(q-1*x,0));
			form=mulpoly(form,tmp,q);
			sortpoly(form);
			unipoly(form);
		}
		ntimepoly(point[j]*Ex_Euc(sum%q,q),form);
		modpoly(form,q);
		exorpoly(px,form);
		sortpoly(px);
		unipoly(px);
		modpoly(px,q);
	}
	return px;
}
