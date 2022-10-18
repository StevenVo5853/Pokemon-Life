
#include "cselife.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - ensure that no border cells are set to alive
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){

	FILE *fp;
	boards_t * board = (boards_t *) malloc(sizeof(boards_t));
	if (board == NULL) {
		printf("ERROR : malloc failed !\n");
		exit(1);
	}

       	if ((fp = fopen(initFileName, "r")) == NULL) {
		free(board);
	      	return NULL;//No file to open
    	}

	int rowSize;
	fscanf(fp, "%d\n", &rowSize);
	board->numRows = rowSize;
	
	int colSize;
	fscanf(fp, "%d\n", &colSize);
	board->numCols = colSize;	

	//Creates space in memory for both buffers
	int size = (board->numRows * board->numCols);
	board->bufferA = malloc(sizeof(belem) * size);
	board->bufferB = malloc(sizeof(belem) * size);

	board->currentBuffer = board->bufferA;
	board->nextBuffer = board->bufferB;
	//initializes board
	clearBoards(board);

	uint32_t rows;
	uint32_t cols;
    	while (fscanf(fp, "%d %d", &rows, &cols) > 0) {
    		
		//sets up the board of dead and alive cells
		if ((rows != 0) && (rows != (board->numRows - 1)) &&
		   (rows != (board->numRows)) && (cols != 0)  && 
		   (cols != (board->numCols - 1)) && cols != (board->numCols)) { 
			int index = 0;
			index = getIndex(board, rows, cols);
			board->currentBuffer[index] = 1;
		}
		else {
			int deadIndex = 0;
			deadIndex = getIndex(board, rows, cols);
			board->currentBuffer[deadIndex] = 0;
		}
    	}
	board->gen = 0;
	fclose(fp);
	return board;
}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){
	
	//check if freeing on an empty memory
	if ((*bptrPtr) == NULL) {
		return;
	}		

	//Free the memory allocated
	free((*bptrPtr)->bufferA);
	(*bptrPtr)->bufferA = NULL;

	free((*bptrPtr)->bufferB);
	(*bptrPtr)->bufferB = NULL;
	
	free((*bptrPtr));
	(*bptrPtr) = NULL;
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
	
	int boardSize = (self->numRows * self->numCols);
	int loop = 0;

	//initializes all board elements to 0
	while (loop != boardSize) {
		self->bufferA[loop] = 0;
		self->bufferB[loop] = 0;
		loop++;
	}
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){

	//swaps the current and next buffer	
	belem *tempBuffer;
	tempBuffer = self->currentBuffer;
	self->currentBuffer = self->nextBuffer;
	self->nextBuffer = tempBuffer;
}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
	
	int index = 0;
    	index = (row * self->numCols) + col;
    	return index;
}
  
