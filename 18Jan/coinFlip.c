#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define HEADS 1
#define TAILS 0 
#define MAX_DIGITS 50
#define MAX_FLIPS 1000

void generateNumber(int *arr, int maxLen);
void printArray(int *arr, int len);
int calcDecVal(int *arr, int len);
void simulateNFlips(int *flipNumber, int noOfBits, int noOfFlips, int *flips, int max);
float calcProb(int *arr, int len,int n);

int main(){

	int max,noOfBits;
	int flipNumber[MAX_DIGITS];
	int flips[MAX_FLIPS];
	float noProbs[MAX_DIGITS];
	printf(" Enter the max value of coin i.e. n : ");
	scanf("%d",&max);
	noOfBits = ceil(log(max)/log(2));
	simulateNFlips(flipNumber,noOfBits,MAX_FLIPS,flips,max);
	
	// printArray(flips,MAX_FLIPS);

	for(int i = 0;i<max;i++){
		printf("\n Probablity of %d: %1.3f",i+1,calcProb(flips,MAX_FLIPS,i+1));
	}
	printf("\n");

}

void simulateNFlips(int *flipNumber, int noOfBits, int noOfFlips, int *flips, int max){
 	int tempStore;
 	srand(time(NULL));
 	for(int i=0;i<noOfFlips;i++){
 		// printf("%4d) ",i+1);
 		generateNumber(flipNumber,noOfBits);
 		// printArray(flipNumber,noOfBits);
 		// printf(" : ");
 		tempStore = calcDecVal(flipNumber,noOfBits);
 		if(tempStore > max || tempStore < 1){
 			// printf("INVALID \n");
 			i-- ;
 			continue;
 		}
 		else{
 			flips[i] = tempStore ;
 			// printf("%d\n",tempStore);
 		}
 	}
}

void generateNumber(int *arr, int maxLen){
	for(int i = 0; i < maxLen; i++){
		arr[i] = (rand())%2;
	}
}

void printArray(int *arr, int len){
	for(int i = 0;i < len ;i++)
		printf("%d\t",arr[i]);
}

int calcDecVal(int *arr, int len){
	int i,j,sum = 0;
	for(i=len-1,j=0;i>=0,j<len;i--,j++){
		sum += arr[i]*pow(2,j);
	}
	return sum;
}

float calcProb(int *arr, int len,int n){
	int count=0;
	for(int i=0; i<len; i++){
		if(arr[i] == n){
			count++;
		}
	}
	return (double)count/(double)len;
}