#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	clock_t begin = clock();
	int searchResult = 0;
	int searchKey = 0;
	char * line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char fileName[25];
	printf("Enter a fileName to open:\n");
	scanf("%s",fileName);
	printf("Enter a number to be searched:\n");
	scanf("%d",&searchKey);

	FILE *fp = fopen(fileName,"r");
	while((read = getline(&line,&len,fp))!= -1 && searchResult == 0){
		if(searchKey == atoi(line)){
			printf("FOUND!");
			searchResult = 1 ;	
		}
		
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Execution Time: %f\n",time_spent);
	close(fp);

}