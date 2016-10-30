/*
 * Program to find TARGET in randomly generated matrix and change row and column of that position to 0
 * Salaheldin AKl
 * 16 April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
#define TARGET 3

// fxn prototypes
void change(int [][SIZE], int, int);
void display(int [][SIZE]);

int main(void)
{
	int matrix[SIZE][SIZE];
	int i, j; // index variabes

	while(1) {
		system("cls");
		// loop to add random numbers
		for (i = 0; i < SIZE; i++)
		{
			for (j = 0; j < SIZE; j++)
			{
				matrix[i][j] = rand() % 10; // random number from 0 - 9
			}// end for j
		}// end for i

		printf("Before Change:\n");
		display(matrix);

		// find if a unit in the matrix is TARGET
		for (i = 0; i < SIZE; i++)
		{
			for (j = 0; j < SIZE; j++)
			{
				if (matrix[i][j] == TARGET)
				{
					// if element is target, change that  row and coumn to 0s
					change(matrix, i, j);
				}
			}// end for j
		}// end for i

		printf("\nAfter Change:\n");
		display(matrix);
		
		// wait for input
		printf("\nPress Enter to generate another Matrix");
		getchar();
	}

	return 0;
}//end main

// implement fxn change
void change(int matrix[][SIZE], int row, int col)
{
	int i; // index variable

	// change row to 0s
	for (i = 0; i < SIZE; i++)
	{
		matrix[row][i] = 0;
	}

	// change column to 0s
	for (i = 0; i < SIZE; i++)
	{
		matrix[i][col] = 0;
	}
}// end change()

// implement display function
void display(int matrix[][SIZE])
{
	int i, j; // index

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			printf("%d ", matrix[i][j]);
		}//end for j
		printf("\n");
	}//end for i
}// end display()