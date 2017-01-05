#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queryrank.c"
#include "katan64.c"
#include "lagrangePolynomial.c"

#define ORDER 512
#define POINT 256

int main()
{
	int **matrix=(int **)malloc(sizeof(int)*ORDER);
	int *lagarray=(int *)malloc(sizeof(int)*POINT);
	int i,j;
	int hextext[4];
	poly *form;
	int q=257;
	unsigned char ptext[64], mkey[80];

	srand(time(NULL));
	for(i=0;i<ORDER;i++) matrix[i]=(int *)malloc(sizeof(int)*POINT);
	for(i=0;i<80;i++) mkey[i]=rand()&1;
	for(j=0;j<ORDER;j++){
		for(i=0;i<POINT;i++){
			initPlaintext(hextext);
			hextext[2]^=i;
			hexa_to_bin(hextext,ptext);
			katan64_encrypt(ptext,mkey);
			lagarray[i]=ptext[25];
		}
		form=lagrangePolynomial(lagarray,POINT,q);
		printf("%d\n",j);
		for(i=0;i<80;i++)
			mkey[i]=rand()&1;
		Poly2array(form,matrix[j]);
		releasepoly(form);
	}
	queryrank(matrix,POINT,ORDER,q);
}
