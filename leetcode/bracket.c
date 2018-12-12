#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print(char* space,int n){
	int i = 0;
	for(i = 0 ;i<n;i++){
		printf("%c ,",space[i]);
	}
	printf("\n");
}

void printstack(int* stack , int n){
	int i = 0;
	for(i = 0;i<n;i++){
		printf("%d , " , stack[i]);
	}
	printf("\n");
}

int check(char* space , int n){
	int i = 0,j = 0,k;
	int compare = 0;
	char* temp = (char*)malloc(n);
	for(k=n-1;k>=0;k--){
		if(i == 0){
			temp[i] = space[k];
			i++;
			continue;
		}
		temp[i] = space[k];
		if(temp[i] == ')' && temp[i-1] == '('){
			i = i - 2;
		}
		i++;
	}
	free(temp);
	if(i < 1)
		return 0;
	else
		return 1;
}
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

char** generateParenthesis(int n,int* returnSize) {
    char* space=(char*)malloc(2*n);
    int* stack=(int*)malloc(2*n*sizeof(int));
    int counter1=0,counter2=0;
    memset(space,'0',2*n);
    memset(stack,-1,2*n*4);
	int number = 2*n;
    int index=0;
    int i,j;
    int valid = 0;
	*returnSize = 0;
	int size_container = 1;
	for(i = 0;i<number-1;i++){
		size_container = size_container * 2;
	} 
	char** str_container = (char**)malloc(sizeof(char*)*size_container);
    while(index<number){
    	valid = 0;
    	for(i=stack[index]+1;i<=1;i++){
    		if(i == 0 && counter1 < n){
    			space[index] = ')';
    			stack[index] = 0;
    			valid = 1;
    			counter1++;
    			break;
    		}
    		if(i == 1 && counter2 < n){
    			space[index] = '(';
    			if(stack[index] == 0)
    				counter1--;
    			stack[index] = 1;
    			valid = 1;
    			counter2++;
    			break;
    		}
    	}
    	
    	if(valid == 1){
    		if(index == 2 * n-1){
    			//check
    			if(check(space,number) == 0){
    				//print(space,number);
					char* str = (char*)malloc(number+1);
					i = 0;
					for(j=number-1;j>=0;j--,i++){
						str[i] = space[j];
					}
					str[i] = '\0';
					print(str,number);
					str_container[*returnSize] = str;
					*returnSize = *returnSize  + 1;
				}        		
    		}else{
    			index++;
    		}
    	}else{
    		if(stack[index]  == 0)
    			counter1--;
    		else if(stack[index] == 1)
    			counter2--;
    		stack[index] = -1;
    		index--;
    		if(index < 0)
    			break;  		
    	}
    }
    free(space);
	free(stack);
	return str_container;
}
void main(){
	int returnSize = 0;
	char** temp;
	temp = generateParenthesis(1,&returnSize);
/*
	printf("\n\n------------ returnSize = %d \n", returnSize);
	int i;
	for(i=0;i<returnSize;i++){
		printf("%s ,\n",temp[i]);
	}
*/
}






