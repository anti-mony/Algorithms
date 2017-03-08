/*
 * Made by Sushant Bansal 1410110454 and Pragya Chaturvedi 1410110289
 * 8th Feb, LAB 6
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void initiate(int *arr, int num){
	for(int i=0;i<num;i++){
		arr[i] = -1;
	}
}

int returnSum(int *arr, int end){
	int sum = 0;
	for(int i=0;i<end;i++){
		sum += arr[i];
	}
	return sum;
}

void randomizePumps(int *arr, int num, int maxDist, int totalDistance){
	srand(time(NULL));
	arr[0]=0;
	int tmp;
	int chck = 1,i;
	while(chck == 1){
		for(i=1;i<num;i++){
			tmp = rand()%(maxDist+1);
			if(tmp == 0)
				tmp++;
			arr[i]= tmp + arr[i-1];
		}
		if(totalDistance-arr[num-1]<maxDist)
			chck = 0;	
	}
	if(arr[num-1]>100)
		arr[num-1]=100;
}

void printArray(int *arr, int num){
	for(int i=0;i<num;i++)
		printf("%d \t",arr[i]);
	printf("\n");
}

int main(){
	int distance = 100, 
	maxDist=20 ,
	capacity=10 ,
	noOfStations=8 ,
	rateOfFilling=1;
	int pumpDistance[noOfStations];
	
	initiate(pumpDistance,noOfStations);
	randomizePumps(pumpDistance,noOfStations,maxDist,distance);
	printf("Gas Pumps are positined at(kms from source)  : \n");
	printArray(pumpDistance,noOfStations);

	int k;
	int current_distance=distance - pumpDistance[0];
	int tempD;
	int diffBwPumps; double totalStoppageTime = 0;
	int i=0,j=0;
	while(current_distance>maxDist){
		current_distance = distance - pumpDistance[i];
		// printf(" Current Dist: %d \n",distance-current_distance );
		for(j=i+1;j<noOfStations;j++){
			tempD = pumpDistance[j]-pumpDistance[i];
			if(tempD<=maxDist){
				continue;
			}
			else
				break;
		}
		// printf("B Stoppage Time: %f \n",totalStoppageTime);
		
		if(pumpDistance[i]+maxDist >= distance){
			totalStoppageTime += (double)(distance - pumpDistance[i])/2;	
			// printf("if Stoppage Time: %f \n",(double)(distance - pumpDistance[i]));
		}
		else{
			totalStoppageTime += (double)(pumpDistance[j-1]-pumpDistance[i])/2;
			// printf("else Stoppage Time: %f \n",(double)(pumpDistance[j-1]-pumpDistance[i])/2);
		}
		i = j-1;
	}

	printf("Minimum Stoppage Time: %f minutes\n",totalStoppageTime );
}


