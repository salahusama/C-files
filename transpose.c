/*
 * This program calculates and displays the transpose of a matrix entered by the user
 * Salaheldin Akl
 * 16 April 2016
 */

#include <stdlib.h>
#include <stdio.h>

main()
{
	int size;
	
	printf("Please enter the size of the matrix:  ");
	scanf("%d", &size);

	int original[size][size];
	int transpose[size][size];
	int i, j;

	// take original matrix as input
	for (i = 0; i < size; ++i)
	{
		printf("Enter Row %d separated by a space:  ", i+1);
		for (j = 0; j < size; ++j)
		{
			scanf("%d", &original[i][j]);
		}
	}


	// print original matrix
	printf("\nOriginal Matrix:\n");
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			printf("%d ", original[i][j]);
			// at end of row
			if ( (j+1) % size == 0 )
			{
				printf("\n");
			}//end if
		}//end for j
	}//end for i

	// copy original to transpose in order needed
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			transpose[j][i] = original[i][j];
		}//end for j
	}//end for i

	// print transpose matrix
	printf("\nTranspose Matrix:\n");
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			printf("%d ", transpose[i][j]);
			// at end of row
			if ( (j+1) % size == 0 )
			{
				printf("\n");
			}//end if
		}//end for j
	}//end for i
	printf("\n\n");

	//keep terminal open
	getchar();
	getchar();
}//end main
