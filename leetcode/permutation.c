#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printarry(int a[],int length){
	int i;
	for(i=0;i<length;i++)
		printf("%d ",a[i]);

	printf("\n");
}

int permutation(int number){ // number = 4 --> 1,  2, 3, 4
	int* space = (int*)malloc(sizeof(int) * number);
	int* used  = (int*)malloc(sizeof(int) *number);
	int* stack = (int*)malloc(sizeof(int) *number);
	memset(space,0,4*number);
	memset(used,0,4*number);
	memset(stack,0,4*number);
	//int space[4] = {0};
	//int used[4] = {0};
	int k = 0;
	int valid = 0;
	//int stack[4] = {0};
	int counter = 0;
	while(k < number){
		int guess;
		valid = 0;
		for(guess=stack[k]+1;guess <=number;guess++){
			if(used[guess-1] == 0){
				space[k] = guess;
				used[guess-1] = 1;
				stack[k] = guess;
				valid = 1;
				break;
			}
		}
		if(valid == 1){
			if(k == number - 1){
				printarry(space,number);
				counter++;
				used[stack[k]-1] = 0;
				stack[k] = 0;
				k--;
				used[stack[k]-1]  = 0;
			}else{
				k++;
			}
		}else{
			used[stack[k]-1] = 0;
			stack[k] = 0;
			k--;
			used[stack[k]-1] = 0;
			if(k < 0)
				break;
		}
	}
	return counter;
}


void main(){
	int counter = permutation(9);
	printf("counter = %d \n" , counter);
}
