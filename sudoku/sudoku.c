#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void printBoard(int* board){
	printf("\n--------- board_temp -------\n");
	int i;
	for(i = 0; i < 81; i++){
		if( i%9 == 0)
			printf("\n");
		printf(" %d" , board[i]);
	}
}

int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

void solveSudoku(char** board, int boardRowSize, int boardColSize) {
	int space_row[81] = {-1};
	int space_col[81] = {-1};
	int buddy_row[81][20] = {-1};
	int buddy_col[81][20] = {-1};
	int nspaces = 0;
	int stack[81] = {0};
	int i,j;
	int row,col;
	for(row=0;row<boardRowSize;row++){
		for(col = 0;col<boardColSize;col++){
			int temp = row * 9 + col;
			if(board[row][col] == '.'){
				space_row[nspaces] = row;
				space_col[nspaces] = col;
				int row_start = (row / 3 * 3); // end + 3
				int col_start = (col / 3 * 3);  // end + 3
				int counter = 0;
				for(i = 0;i<boardColSize;i++){
					if(i != col){				
						buddy_row[nspaces][counter] = row;
						buddy_col[nspaces][counter] = i;
						counter++;
					}
				}
				for(j = 0;j<boardRowSize;j++){
					if(j != row){
						buddy_row[nspaces][counter] = j;
						buddy_col[nspaces][counter] = col;
						counter++;					
					}
				}
				for(i = row_start; i < row_start + 3; i++){
					for(j = col_start; j < col_start + 3; j++){
						if(i!= row && j!= col){
							buddy_row[nspaces][counter] = i;
							buddy_col[nspaces][counter] = j;
							counter++;
						}
					}		
				}
				if(counter != 20)
					printf("counter != 20\n");				
				nspaces++;
			}				
		}
	}


	int k = 0;
	int guess = 0;
	while(k < nspaces){
		int temp_row = space_row[k];//index / 9;
		int temp_col = space_col[k];//index % 9;
		int flag = 0;
		for(guess=stack[k] + 1;guess<=9;guess++){
			// check available
			int in = 1;
			for(i = 0;i < 20;i++){
				int temp_buddy_row = buddy_row[k][i];
				int temp_buddy_col = buddy_col[k][i];
				if( guess == board[temp_buddy_row][temp_buddy_col] - '0'){
					in = 0;	 // not available				
					break;
				}
			}
			
			if(in == 1){
				flag = 1;
				stack[k] = guess; // record check number 1 - 9
				board[temp_row][temp_col] = guess + '0';
				break;
			}
		}
		if(flag == 1){
			k++;
			continue;
		}
		else{ // 1 - 9 not available , then back step
			board[temp_row][temp_col] = '.';
			stack[k] = 0;
			k--;
			if(k < 0){
				printf("No solution\n");
				break;
			}		
		}
	}
}

void printArr(char** board, int boardRowSize, int boardColSize){
	int row = 0;
	int col = 0;	
	for(row = 0; row < boardRowSize; row++){
		char* row_index = board[row];
		for(col = 0; col < boardColSize; col++){
			if(row_index[col] == '5')
				row_index[col] = '0';
			printf("%c , ", row_index[col]);
		}
		printf("\n");
	}
}

void testPrint(char** board, int boardRowSize, int boardColSize){
	int row = 0;
	int col = 0;	
	for(row = 0; row < boardRowSize; row++){
		for(col = 0; col < boardColSize; col++){
			printf("%c |  ", board[row][col]);
		}
		printf("\n");
	}
}


void main(){
	char** problem = (char**)malloc(9 * 9);
	char row_1[9] = {'5','3','.','.','7','.','.','.','.'};
	char row_2[9] = {'6','.','.','1','9','5','.','.','.'};
	char row_3[9] = {'.','9','8','.','.','.','.','6','.'};
	char row_4[9] = {'8','.','.','.','6','.','.','.','3'};
	char row_5[9] = {'4','.','.','8','.','3','.','.','1'};
	char row_6[9] = {'7','.','.','.','2','.','.','.','6'};
	char row_7[9] = {'.','6','.','.','.','.','2','8','.'};
	char row_8[9] = {'.','.','.','4','1','9','.','.','5'};
	char row_9[9] = {'.','.','.','.','8','.','.','7','9'};
	problem[0] = row_1; problem[1] = row_2; problem[2] = row_3; 
	problem[3] = row_4; problem[4] = row_5; problem[5] = row_6;
	problem[6] = row_7; problem[7] = row_8; problem[8] = row_9;
	testPrint(problem,9,9);
	int64_t start = now();
	solveSudoku(problem,9,9);
	int64_t end = now();
	double sec = (end-start)/1000000.0;
	printf("%f sec %f ms \n", sec, 1000*sec);
	testPrint(problem,9,9);
	//printArr(problem,9,9);
	//testPrint(problem,9,9);
}


