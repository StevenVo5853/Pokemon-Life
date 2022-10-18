/**
 * Assignment: life
 * Name: Steven Vo
 * PID: A15554478
 * Class: UCSD CSE30-sp20
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){
		
	while (srcStart != (srcEnd + 1)) {
	
		belem neighbor = 0;
		belem upCell = *(srcStart - cols);
		belem downCell = *(srcStart + cols);
		belem leftCell = *(srcStart - 1);
		belem rightCell = *(srcStart + 1);
		belem upRight = *(srcStart - cols + 1);
		belem upLeft = *(srcStart - cols - 1);
		belem downRight = *(srcStart + cols + 1);
		belem downLeft = *(srcStart + cols - 1);

		if (upCell == 1) {
			neighbor++;
		}
		if (downCell == 1) {
			neighbor++;
		}
		if (leftCell == 1) {
			neighbor++;
		}
		if (rightCell == 1) {
			neighbor++;
		}
		if (upRight == 1) {
			neighbor++;
		}
		if (upLeft == 1) {
			neighbor++;
		}
		if (downRight == 1) {
			neighbor++;
		}
		if (downLeft == 1) {
			neighbor++;
		}

		//Update next Buffer
		if (*srcStart >= 1) {

			if (neighbor <= 1) {
				*dest = 0;
			}
			if (neighbor == 2 || neighbor == 3) {
				*dest = 1;
			}
			if (neighbor >= 4) {
				*dest = 0;
			}
		}
		else if (*srcStart == 0) {

			if (neighbor == 3) {
				*dest = 1;
			}
			else {
				*dest = 0;
			}
		}
		srcStart++;
		dest++;
	}
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
	uint32_t i = 0;
 	uint32_t loops = 1;

 	belem *start = self->currentBuffer + self->numCols + 2;
  	belem *end = self->currentBuffer + self->numCols + self->numCols;
  	belem *destination = self->nextBuffer + self->numCols + 2;
 
	while (i < steps) {

		while (loops < self->numRows - 1) {

			start = self->currentBuffer + (loops * self->numCols) + 1;
			end = self->currentBuffer + ((loops + 1) * self->numCols) - 2;
			destination = self->nextBuffer + (loops * self->numCols) + 1;
	  		
			doRow(destination, start, end, self->numCols);	

			loops++;
		}

		loops = 1;
	  	swapBuffers(self);
	  	self->gen++;
	  	i++;
  	}

}




