#include <stdio.h>
#include <stdlib.h>

int main(){
	int matA[2][2];
	int matB[2][2];
	int matC[2][2];
	int i,j,m1,m2,m3,m4,m5,m6,m7;
	
	printf("Enter the 4 elements of first matrix A: \n");
  	for(i=0;i<2;i++)
     	for(j=0;j<2;j++)
           scanf("%d",&matA[i][j]);

  	printf("\nThe first matrix is\n");
  	for(i=0;i<2;i++){
      	for(j=0;j<2;j++)
           printf("%d\t",matA[i][j]);
 	printf("\n");
 	}

  	printf("\nEnter the 4 elements of second matrix B: \n");
  	for(i=0;i<2;i++)
    	for(j=0;j<2;j++)
        	scanf("%d",&matB[i][j]);
 	

  	printf("\nThe second matrix is\n");
  	for(i=0;i<2;i++){
    	for(j=0;j<2;j++)
        	printf("%d\t",matB[i][j]);
  	printf("\n");
  	}

  m1= (matA[0][0] + matA[1][1])*(matB[0][0]+matB[1][1]);
  m2= (matA[1][0]+matA[1][1])*matB[0][0];
  m3= matA[0][0]*(matB[0][1]-matB[1][1]);
  m4= matA[1][1]*(matB[1][0]-matB[0][0]);
  m5= (matA[0][0]+matA[0][1])*matB[1][1];
  m6= (matA[1][0]-matA[0][0])*(matB[0][0]+matB[0][1]);
  m7= (matA[0][1]-matA[1][1])*(matB[1][0]+matB[1][1]);

  matC[0][0]=m1+m4-m5+m7;
  matC[0][1]=m3+m5;
  matC[1][0]=m2+m4;
  matC[1][1]=m1-m2+m3+m6;

   printf("\nMatrix C i.e. A X B is : \n");
   
   	for(i=0;i<2;i++){
   		for(j=0;j<2;j++)
           printf("%d\t",matC[i][j]);
   	printf("\n");
   }

   return 0;

}