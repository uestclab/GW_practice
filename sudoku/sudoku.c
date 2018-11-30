#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}

int buddy[81][20] = {-1};
int board_temp[81] = {0};

int quantum(int cell){
	int cache[10] = {0};
	int i , index;
	for(i=0;i<20;i++){
		index = buddy[cell][i];	
		cache[board_temp[index]] = 1;
	}
	int counter = 0;
	for(i=0;i<10;i++){
		if(cache[i] == 0)
			counter = counter + 1;
	}
	return counter;
}


int findLess(int space[], int nspaces, int depth){
	int cell = space[depth];
	int min_value = quantum(cell);
	int min_index = depth;
	int i;
	for(i=depth+1;i<nspaces&& min_value>1;i++){
		int temp_value = quantum(space[i]);
		if(temp_value < min_value){
			min_value = temp_value;
			min_index = i;
		}
	}
	if(min_index != depth){
		i = space[depth];
		space[depth] = space[min_index];
		space[min_index] = i;
	}
	return space[depth];
}



void solveSudoku(char** board, int boardRowSize, int boardColSize) {
    int space[81] = {-1};
	//int buddy[81][20] = {-1};
	int nspaces = 0;
	int stack[81] = {0};
	//int board_temp[81] = {0};
	int i,j;
	int row,col;
	for(row=0;row<boardRowSize;row++){
		for(col = 0;col<boardColSize;col++){
			int temp = row * 9 + col;
			if(board[row][col] == '.'){
				space[nspaces] = temp;
				board_temp[temp] = 0;
				int row_start = (row / 3 * 3); // end + 3
				int col_start = (col / 3 * 3);  // end + 3
				int counter = 0;
				for(i = 0;i<boardColSize;i++){
					if(i != col){			
						buddy[temp][counter] = row * 9 + i;					
						counter++;
					}
				}
				for(j = 0;j<boardRowSize;j++){
					if(j != row){
						buddy[temp][counter] = j * 9 + col;
						counter++;					
					}
				}
				for(i = row_start; i < row_start + 3; i++){
					for(j = col_start; j < col_start + 3; j++){
						if(i!= row && j!= col){
							buddy[temp][counter] = i * 9 + j;
							counter++;
						}
					}		
				}
				if(counter != 20)
					printf("counter != 20\n");				
				nspaces++;
			}else{
				board_temp[temp] = board[row][col] - '0';			
			}				
		}
	}

	int k = 0;
	int guess = 0;
	while(k < nspaces){
		// ---- find -----
		//int index = space[k];
		int index = findLess(space,nspaces,k);
		// ---------------
		int temp_row = index / 9;
		int temp_col = index % 9;
		int flag = 0;

		for(guess=stack[k] + 1;guess<=9;guess++){
			// check available
			int in = 1;
			for(i = 0;i < 20;i++){
				int temp_index = buddy[index][i];
				if( guess == board_temp[temp_index]){
					in = 0;	 // not available				
					break;
				}
			}
			
			if(in == 1){
				flag = 1;
				stack[k] = guess; // record check number 1 - 9
				board_temp[index] = guess;
				board[temp_row][temp_col] = guess + '0';
				break;
			}
		}
		if(flag == 1){
			k++;
			continue;
		}
		else{ // 1 - 9 not available , then back step
			board_temp[index] = 0;
			board[temp_row][temp_col] = '.';
			stack[k] = 0;
			k--;
			if(k < 0){
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
}


