#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define R				9
//#define PICKED_NUMBER	3

#define matrixRowLength		3
#define matrixColLength		5
#define rowLength			matrixRowLength*matrixColLength
#define rowCount			10

const int rows[rowCount][rowLength] = {
	{1,1,1,1,0,1,1,0,1,1,0,1,1,1,1},
	{0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
	{1,1,1,0,0,1,1,1,1,1,0,0,1,1,1},
	{1,1,1,0,0,1,1,1,1,0,0,1,1,1,1},
	{1,0,1,1,0,1,1,1,1,0,0,1,0,0,1},
	{1,1,1,1,0,0,1,1,1,0,0,1,1,1,1},
	{1,1,1,1,0,0,1,1,1,1,0,1,1,1,1},
	{1,1,1,0,0,1,0,0,1,0,0,1,0,0,1},
	{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,1,0,1,1,1,1,0,0,1,1,1,1}
};

void printWeights(const size_t length, const int* weights) {
	for (int i = 0; i < length; i++) {
		printf("%d ", weights[i]);
	}
	printf("\n");	
}

int calculateR(const size_t length, const int* digitRow, const int* weightsRow) {
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum += digitRow[i] * weightsRow[i];
	}
	return sum;
}
void add(const size_t length, const int* digitRow, int* weightsRow) {
	for (int i = 0; i < length; i++) {
		weightsRow[i]+=digitRow[i];
	}
}
void sub(const size_t length, const int* digitRow, int* weightsRow) {
	for (int i = 0; i < length; i++) {
		weightsRow[i]-=digitRow[i];
	}	
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: %s <0-9>\n", argv[0]);
		return 1;
	}

	int PICKED_NUMBER = atoi(argv[1]);
	if (PICKED_NUMBER < 0 || PICKED_NUMBER > 9) {
		printf("Incorrect input: %d",PICKED_NUMBER);
		return 1;
	}

	int weights[rowLength] = {0};
	uint rowIndex = 0;

	const int overloopConstant = 2;
	int overloop = overloopConstant;
	while (overloop) {
		if (calculateR(rowLength,rows[rowIndex],weights) >= R) {
			if (rowIndex != PICKED_NUMBER) {
				sub(rowLength,rows[rowIndex],weights);
				overloop = overloopConstant;
				goto finally;
			}
		}
		else {
			if (rowIndex == PICKED_NUMBER) {
				add(rowLength,rows[rowIndex],weights);
				overloop = overloopConstant;
				goto finally;
			}
		}
		rowIndex++;
		if (rowIndex >= rowCount) {
			rowIndex = 0;
			overloop--;
		}

		finally:
		//printWeights(rowLength,weights);
		;
	}
	printWeights(rowLength,weights);
	return 0;
}
