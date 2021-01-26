////////////////////////////////////////////////////////////////////////////////
// Main File:        check_queens.c
// This File:        check_queens.c
// Other Files:      none
// Semester:         CS 354 Fall 2018
//
// Author:           David Zhu
// Email:            dzhu46@wisc.edu
// CS Login:         zhu
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          N/A
//
//
// Online sources:   TutorialsPoint, StackExchange
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>   

char *COMMA = ",";

/* COMPLETED:
 * Retrieves from the first line of the input file,
 * the number of rows and columns for the board.
 * 
 * fp: file pointer for input file
 * rows: pointer to number of rows
 * cols: pointer to number of columns
 */
void get_dimensions(FILE *fp, int *rows, int *cols) {     
	char *line = NULL; 
	size_t len = 0;
	if (getline(&line, &len, fp) == -1) { 
		printf("Error in reading the file\n");
		exit(1); 
	}

	char *token = NULL; 
	token = strtok(line, COMMA);
	*rows = atoi(token); 

	token = strtok(NULL, COMMA); 
	*cols = atoi(token);
}      

/*
 * Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other.
 * Otherwise returns 0.
 *
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns
 */
int check_queens(int **board, int rows, int cols) {           

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			// if there is a queen, check that queen's row, col,
			// first diagonal, second diagonal
			if (*(*(board + i) + j) == 1) {

				// check for queens along cols
				for (int c = i + 1; c < rows; c++) {
					if (*(*(board + c) + j) == 1) {
						return 1;
					}
				}

				// check for queens along rows
				for (int r = j + 1; r < cols; r++) {
					if ((*(*(board) + i) + r) == 1) {
						return 1;
					}
				}

				// check for queens along first diagonal
				int i1 = 1;
				int j1 = 1;
				while (((i + i1) < rows) && ((j - j1) >= 0)) {

					if (*(*(board + (i + i1)) + (j - j1)) == 1) {
						return 1;
					}
					i1++;
					j1++;
				}

				// check for queens along second diagonal
				int i2 = 1;
				int j2 = 1;
				while (((i + i2) < rows) && ((j + j2) < cols)) {

					if (*(*(board + (i + i2)) + (j + j2)) == 1) {
						return 1;
					}
					i2++;
					j2++;
				}
			}
		}
	}

	// if code reaches here, there are other queens in same row,
	// col, or either diagonal, meaning that there is no other
	// attacking queen.
	return 0;
}     

/* PARTIALLY COMPLETED:
 * This program prints true if the input file has any pair
 * of queens that can attack each other, and false otherwise
 * 
 * argc: CLA count
 * argv: CLA value 
 */
int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("Wrong number of command line args\n");
		exit(1);
	}

	//Open the file and check if it opened successfully.
	FILE *fp = fopen(*(argv + 1), "r");
	if (fp == NULL) {
		printf("Cannot open file for reading\n");
		exit(1);
	}

	//Declare local variables.
	int rows, cols;
	get_dimensions(fp, &rows, &cols);

	// allocate memory for chessboard (2D array)
	int **chessptr;
		chessptr = malloc(sizeof(int *) * rows);

	if (chessptr != NULL) {
		for (int i = 0; i < rows; i++) {
			(*(chessptr + i)) = malloc(sizeof(int) * cols);
		}
	}

	//Read the file line by line.
	//Tokenize each line wrt comma to store the values in your 2D array.
	char *line = NULL;
	size_t len = 0;
	char *token = NULL;
	for (int i = 0; i < rows; i++) {

		if (getline(&line, &len, fp) == -1) {
			printf("Error while reading the file\n");
			exit(1);	
		}

		token = strtok(line, COMMA);
		for (int j = 0; j < cols; j++) {
			*(*(chessptr + i) + j) = atoi(token);
			token = strtok(NULL, COMMA);	
		}
	}

 	//output depending on the function's return value.
	int state = check_queens(chessptr, rows, cols);
	if (state == 0) {
		printf("false\n");
	}
	else if (state == 1) {
		printf("true\n");
	}
	else {
		printf("error, check_queens returned incorrect value!\n");
		exit(1);
	}
        
	for (int i = 0; i < rows; i++) {
		free(*(chessptr + i));
	}
	free(chessptr);
	chessptr = NULL;

	//Close the file.
	if (fclose(fp) != 0) {
		printf("Error while closing the file\n");
		exit(1);	
	}

	return 0;
}    
