/*
* Sushant Bansal 1410110454
* Matrix Multiplication Method
* 8th February, 2017 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

#define MAX 2

typedef struct { int ra, rb, ca, cb; } edges; // to tracking rows and columns.

void findedges(edges a, int i, int j, edges *b); // to help divide arrays
void matrixMultiplyRecursive(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], edges a, edges b, edges c);
void matrixMultiplyRecursiveStrassen(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], edges a, edges b, edges c);
void strassenCalc(int matA[MAX][MAX], int matB[MAX][MAX], int matC[MAX][MAX],edges a, edges b, edges c);
void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX], int c[MAX][MAX] );
void initiateArray(int arr[MAX][MAX],int range);
void printArray(int array[MAX][MAX], char NameOfArray);

int main(int argc, char *argv[]){
	int printChck;
	if(argc == 2){
		printChck = atoi(argv[1]);
	}
	else{
		printChck = 0;
	}
	clock_t start,end;
	double time_spent;
	int A[MAX][MAX];
	int B[MAX][MAX];
	int C[MAX][MAX];
 	edges a = {0,MAX,0,MAX};
 	edges b = {0,MAX,0,MAX};
 	edges c = {0,MAX,0,MAX};
	initiateArray(A,9);
	if(printChck == 1)
		printArray(A,'A');
	sleep(1);
	initiateArray(B,9);
	if(printChck == 1)
		printArray(B,'B');	
	initiateArray(C,0);
	
	// start = clock();
	// multiplyMatrix(A,B,C);
	// end = clock();
	// time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	// printf("Time Taken to Multiply Matrices is : %f\n\n",time_spent);
	// if(printChck == 1)
	// printArray(C,'C');
	// initiateArray(C,0);

	start = clock();
	matrixMultiplyRecursive(A,B,C,a,b,c);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printArray(C,'C');
	printf("Time Taken to Multiply Matrices Recursively is : %f\n\n",time_spent);

	// initiateArray(C,0);
	// start = clock();
	// matrixMultiplyRecursiveStrassen(A,B,C,a,b,c);
	// end = clock();
	// time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	// if(printChck == 1)
	// 	printArray(C,'C');
	// printf("Time Taken to Multiply Matrices via Strassen's Algo is : %f\n\n",time_spent);
	
	return 0;
}


void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX], int c[MAX][MAX]){
	for(int i=0;i<MAX;i++){
		for (int j = 0; j < MAX; j++)
		{
			for (int k = 0; k < MAX; k++)
			{
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
}


void initiateArray(int arr[MAX][MAX],int range){
	srand(time(NULL));
	if(range == 0){
		for(int i=0;i<MAX;i++){
		for (int j = 0; j < MAX; j++)
			arr[i][j] = 0;
		}	
	}
	else{
		for(int i=0;i<MAX;i++){
		for (int j = 0; j < MAX; j++)
			arr[i][j] = rand()%range;
		}	
	}
}

void printArray(int array[MAX][MAX], char NameOfArray){
	printf("Array %c\n",NameOfArray);
	for(int i=0;i<MAX;i++){
		//printf("%d. ",i+1);
	 	for(int j=0;j<MAX;j++){
	 		printf("%4d ",array[i][j]);
	 	}
	 	printf("\n\n");
	}	
	printf("\n");
}


void findedges(edges a, int i, int j, edges *b) {
  int rm = a.ra + (a.rb - a.ra)/2 ;
  int cm = a.ca + (a.cb - a.ca)/2 ;
  *b = a;
  if (i==0)  b->rb = rm;     // top rows
  else       b->ra = rm;     // bot rows
  if (j==0)  b->cb = cm;     // left cols
  else       b->ca = cm;     // right cols
}

// Naive Multiply: A[a] * B[b] => C[c], recursively.
void matrixMultiplyRecursive(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], edges a, edges b, edges c) {
  edges ai[2][2], bi[2][2], ci[2][2];
  int i, j, m, n, p;

  m = a.rb - a.ra; assert(m==(c.rb-c.ra));
  n = a.cb - a.ca; assert(n==(b.rb-b.ra));
  p = b.cb - b.ca; assert(p==(c.cb-c.ca));
  assert(m>0);

  if (n==1) {
    C[c.ra][c.ca] += A[a.ra][a.ca] * B[b.ra][b.ca];
    return;
  }

  // Creating the smaller matrices:
  for(i=0;i<2;i++) {
  for(j=0;j<2;j++) {
        findedges(a, i, j, &ai[i][j]);
        findedges(b, i, j, &bi[i][j]);
        findedges(c, i, j, &ci[i][j]);
      }
  }

  for(i=0;i<2;i++) {
  	for(j=0;j<2;j++){
        printf("i:%d j:%d =>> ra = %d rb = %d ca = %d cb = %d\n",i,j,ai[i][j].ra,ai[i][j].rb,ai[i][j].ca,ai[i][j].cb);
    }
  }

  // Now do the 8 sub matrix multiplications.
  // C00 = A00*B00 + A01*B10
  // C01 = A00*B01 + A01*B11
  // C10 = A10*B00 + A11*B10
  // C11 = A10*B01 + A11*B11

  matrixMultiplyRecursive( A, B, C, ai[0][0], bi[0][0], ci[0][0] );
  matrixMultiplyRecursive( A, B, C, ai[0][1], bi[1][0], ci[0][0] );

  matrixMultiplyRecursive( A, B, C, ai[0][0], bi[0][1], ci[0][1] );
  matrixMultiplyRecursive( A, B, C, ai[0][1], bi[1][1], ci[0][1] );

  matrixMultiplyRecursive( A, B, C, ai[1][0], bi[0][0], ci[1][0] );
  matrixMultiplyRecursive( A, B, C, ai[1][1], bi[1][0], ci[1][0] );

  matrixMultiplyRecursive( A, B, C, ai[1][0], bi[0][1], ci[1][1] );
  matrixMultiplyRecursive( A, B, C, ai[1][1], bi[1][1], ci[1][1] );

}

void matrixMultiplyRecursiveStrassen(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], edges a, edges b, edges c) {
  edges ai[2][2], bi[2][2], ci[2][2];
  int i, j, m, n, p;

  m = a.rb - a.ra; assert(m==(c.rb-c.ra));
  n = a.cb - a.ca; assert(n==(b.rb-b.ra));
  p = b.cb - b.ca; assert(p==(c.cb-c.ca));
  assert(m>0);

  if (n==1){
  	strassenCalc(A,B,C,a,b,c);
    return;
  }

  // Creating the smaller matrices:
  for(i=0;i<2;i++) {
  for(j=0;j<2;j++) {
        findedges(a, i, j, &ai[i][j]);
        findedges(b, i, j, &bi[i][j]);
        findedges(c, i, j, &ci[i][j]);
      }
  }

  // Now do the 8 sub matrix multiplications.
  // C00 = A00*B00 + A01*B10
  // C01 = A00*B01 + A01*B11
  // C10 = A10*B00 + A11*B10
  // C11 = A10*B01 + A11*B11

  matrixMultiplyRecursiveStrassen( A, B, C, ai[0][0], bi[0][0], ci[0][0] );
  matrixMultiplyRecursiveStrassen( A, B, C, ai[0][1], bi[1][0], ci[0][0] );

  matrixMultiplyRecursiveStrassen( A, B, C, ai[0][0], bi[0][1], ci[0][1] );
  matrixMultiplyRecursiveStrassen( A, B, C, ai[0][1], bi[1][1], ci[0][1] );

  matrixMultiplyRecursiveStrassen( A, B, C, ai[1][0], bi[0][0], ci[1][0] );
  matrixMultiplyRecursiveStrassen( A, B, C, ai[1][1], bi[1][0], ci[1][0] );

  matrixMultiplyRecursiveStrassen( A, B, C, ai[1][0], bi[0][1], ci[1][1] );
  matrixMultiplyRecursiveStrassen( A, B, C, ai[1][1], bi[1][1], ci[1][1] );

  // matrixMultiplyRecursiveStrassen( A, B, C, ai[0][0], bi[0][0], ci[0][0] );
  // matrixMultiplyRecursiveStrassen( A, B, C, ai[0][1], bi[0][1], ci[0][1] );
  // matrixMultiplyRecursiveStrassen( A, B, C, ai[1][0], bi[1][0], ci[1][0] );
  // matrixMultiplyRecursiveStrassen( A, B, C, ai[1][1], bi[1][1], ci[1][1] );
}

void strassenCalc(int matA[MAX][MAX], int matB[MAX][MAX], int matC[MAX][MAX],edges a, edges b, edges c){
	int m1,m2,m3,m4,m5,m6,m7;
	m1= (matA[a.ra][a.ca] + matA[a.rb][a.cb])*(matB[b.ra][b.ca]+matB[b.rb][b.cb]);
	m2= (matA[a.rb][a.ca]+matA[a.rb][a.cb])*matB[b.ra][b.ca];
	m3= matA[a.ra][a.ca]*(matB[b.ra][b.cb]-matB[b.rb][b.cb]);
	m4= matA[a.rb][a.cb]*(matB[b.rb][b.ca]-matB[b.ra][b.ca]);
	m5= (matA[a.ra][a.ca]+matA[a.ra][a.cb])*matB[b.rb][b.cb];
	m6= (matA[a.rb][a.ca]-matA[a.ra][a.ca])*(matB[b.ra][b.ca]+matB[b.ra][b.cb]);
	m7= (matA[a.ra][a.cb]-matA[a.rb][a.cb])*(matB[b.rb][b.ca]+matB[b.rb][b.cb]);

	matC[c.ra][c.ca]=m1+m4-m5+m7;
	matC[c.ra][c.cb]=m3+m5;
	matC[c.rb][c.ca]=m2+m4;
	matC[c.rb][c.cb]=m1-m2+m3+m6;
}