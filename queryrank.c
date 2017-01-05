#include "extend_euc.c"
void printmatrix(int **matrix, int line, int colmn);
void swapline(int **matrix, int x, int y, int sizeline );
void queryrank(int **matrix, int sizex, int sizey, const int q)
{
	int buf;
	int i,j,k;

	for(i=0;i<sizex;i++){
		for(j=i;j<sizey;j++){
			if(matrix[j][i]!=0){
				swapline(matrix,i,j,sizex);
				break;
			}
			if(j==sizey-1){
				printmatrix(matrix,sizex,sizey);
				printf("rank: %d\n", i);
				return;
			}
		}

		buf=Ex_Euc(matrix[i][i],q);
		for(j=0;j<sizex;j++){
			matrix[i][j]=matrix[i][j]*buf%q;
			if(matrix[i][j]<0) matrix[i][j]=q+matrix[i][j];
		}
		//printmatrix(matrix,sizex,sizey);
		for(j=0;j<sizey;j++){
			if(i==j) j++;
			if(j==sizey) break;
			buf=matrix[j][i];
			for(k=0;k<sizex;k++){
				matrix[j][k]=matrix[j][k]-matrix[i][k]*buf;
				matrix[j][k]=matrix[j][k]%q;
				if(matrix[j][k]<0) matrix[j][k]=q+matrix[j][k];
			}
		}
	}
	printmatrix(matrix,sizex,sizey);
	printf("rank: %d\n", i);
}

void swapline(int **matrix, int x, int y, int sizeline )
{
	int i;
	int temp;
	for(i=0;i<sizeline;i++){
		temp=matrix[x][i];
		matrix[x][i]=matrix[y][i];
		matrix[y][i]=temp;
	}
	return;
}

void printmatrix(int **matrix, int colmn, int line)
{
	int i,j;
	for(i=0;i<line;i++){
		for(j=0;j<colmn;j++){
			printf("%03d ",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}
