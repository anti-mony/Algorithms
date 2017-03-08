/* Sushant bansal 1410110454
 * February 22, 2017
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CAPACITY 40
#define MAX_ITEMS 10

typedef struct i{
	int value;
	int weight;
}item;

void printSack(item *arr, int n);
void fillBag(int max_weight,item *arr, int noOfItems);

int main(){
	srand(time(NULL));
	int k = MAX_CAPACITY; //Weight capacity of Knapsack
	int n = MAX_ITEMS; //Number of items

	item setOfItems[n];
	for(int i=0;i<n;i++){
		setOfItems[i].value = rand()%20 + 1;
		setOfItems[i].weight = rand()%20 + 1;
	}
	printSack(setOfItems,n);
	fillBag(MAX_CAPACITY,setOfItems,n);
}

void printSack(item *arr, int n){
	for(int i = 0;i<n ;i++){
		printf("Item Number:%2d  Weight:%2d Value:%2d \n",i+1,arr[i].weight,arr[i].value);
	}
}

void sortSack(item *arr, int n){
	item temp;
	for(int i = 0;i<n ;i++){
		for(int j = i;j<n-1;j++){
			if((double)arr[j].value/(double)arr[j].weight<(double)arr[j+1].value/(double)arr[j+1].weight){
				temp.value = arr[j].value;
				temp.weight =  arr[j].weight;
				arr[j].weight = arr[j+1].weight;
				arr[j].value =  arr[j+1].value;
				arr[j+1].value = temp.value;
				arr[j+1].weight = temp.weight;
			}
		}
	}
}

void fillBag(int max_weight,item *arr, int noOfItems){
	sortSack(arr,noOfItems);
	printf("\nItems in Knapsack: \n");
	double currentWeight = 0;
	double currentValue = 0;
	int leftOff = 0;
	for(int i=0;i<noOfItems;i++){
		if(currentWeight + arr[i].weight <= max_weight){
			currentWeight += arr[i].weight;
			currentValue += arr[i].value;
			printf("Weight:%2d Value:%2d \n",arr[i].weight,arr[i].value);		
		}
		else{
			leftOff = max_weight - currentWeight;
			currentValue += leftOff *  (double)arr[i].value/(double)arr[i].weight ;
			printf("Weight:%2d Value:%2.2f \n",leftOff,leftOff *  (double)arr[i].value/(double)arr[i].weight);
			break;
		}
	}
	printf("\n***** Maximum Value in Knapsack is :%2.2f *****\n\n",currentValue);

}

