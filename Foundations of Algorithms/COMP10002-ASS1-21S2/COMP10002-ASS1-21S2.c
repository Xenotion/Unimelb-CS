/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Jung-Hyun An  1277954
   Dated:     15/09/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 }, //set[0]  rowstart
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 }, //set[8] rowend
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 }, //set[9] colstart
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 }, //set[17] colend
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 }, //set[18] sqrstart
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 }, 
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 }, //set[26] sqrend
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/

/****************************************************************/

#define FIRST_SQR_HYPEN 6           // number of hyphens required as a border for the first square
#define SECOND_SQR_HYPEN 7          // number of hyphens required as a border for the second square
#define THIRD_SQR_HYPEN 6           // number of hyphens required as a border for the thirs square
#define MAX_SET_NO_FOR_ROW 9        // biggest set number for the row
#define MAX_SET_NO_FOR_COL 18       // biggest set number for the column
#define DIFF_FOR_SET_ROW 1          // numerical difference between row and set
#define DIFF_FOR_SET_COL 8          // numerical difference between row and column
#define DIFF_FOR_SET_SQR 17         // numerical difference between row and square

void checkGrid(int a[]);
void read_print_sudoku(int a[]);
void find_cell_mates(int a[], int b[]);
void sort_int_array(int a[]);
int groupfind(int n);
int set_to_row(int n);
int set_to_col(int n);
int set_to_sqr(int n);

/****************************************************************/

/* main program controls all the action
*/
int main(int argc, char *argv[]) {
    int data[NCLL], cellmates[NSET];
    // function required to find out set numbers that a cell is in
    fill_c2s();

    // function for reading and printing the sudoku in a correct format off a txt file
    read_print_sudoku(data);

    // function for checking a valid sudoku
    checkGrid(data);

    // function for finding cellmates for a cell
    find_cell_mates(data, cellmates);
    
}

void read_print_sudoku(int a[]) {

    int i, j, count_0 = 0;

    printf("\n");
    
    // for loop to scan the txt file and print out the sudoku values 
    for (i=0;i<NCLL;i++) {
    
        scanf("%d,", &(a[i]));

        // separating the sudoku 1d array into a 9x9 grid
        // create a new line after the 9th item in the array
        if (i > 0 && (i+1) % NDIG == 0) {

            // if a number is 0, replace with '.'
            if (a[i] == 0) {
                printf(".\n");

                // counting number of unknown values in the sudoku
                count_0++;
            } else {
                printf("%d\n", a[i]);
            }
        } else {

            // if a number is 0, replace with '.'
            if (a[i] == 0) {
                printf(". ");
                count_0++;
            } else {
                printf("%d ", a[i]);
            }
        }

        // creating borders for the sudoku for 3x3 squares
        // create a horizontal line after every 27th element excluding the 81st
        if ((i+1) != NCLL && (i+1) % (NCLL/NDIM) == 0) {
            for (j = 0; j < FIRST_SQR_HYPEN; j++) {
                printf("-");
            }
            printf("+");
            for (j = 0; j < SECOND_SQR_HYPEN; j++) {
                printf("-");
            }
            printf("+");
            for (j = 0; j < THIRD_SQR_HYPEN; j++) {
                printf("-");
            }
            printf("\n");
        }

        // create a vertical line after 3rd element except the multiples of 9
        if ((i+1) % NDIG != 0 && (i+1) % NDIM == 0) {
            printf("| ");
        }
        

    }
    printf("\n%d cells are unknown\n\n", count_0);
}

void checkGrid(int a[]) {

    int i, j, k, count, viol = 0, count_dup = 0;
    int refarray[NDIG], recur[NDIG], setarray[NCLL];

    // loop through the sodoku and double loop through every 9 element within
    for (i=0; i<NSET; i++) {
        for (j=0; j<NDIG; j++) {
            // create a reference array to store all the row, col and sqr arrays 
            refarray[j] = a[s2c[i][j]];
        }

    // function to sort the array created
    sort_int_array(refarray);

        // frequency counter
        for (j=0; j<NDIG; j++) {
            count = 1;
            for (k=j+1; k<NDIG; k++) {

                // if duplicate element is found
                if (refarray[j] == refarray[k]) {
                    count++;

                    // make sure to not count the same element again
                    refarray[k]=-1;
                }
            }

            // if the current element is not counted
            if (recur[j] != -1) {
                recur[j] = count; 
            }
        }

        for (j=0; j<NDIG; j++) {

            // if there are more than 1 frequency of a value that is bigger than 0
            if (refarray[j] != -1 && recur[j] > 1 && refarray[j] > 0) {         

                if (i < MAX_SET_NO_FOR_ROW) {
                    printf("set %2d (row %d): %d instances of %d\n", i, groupfind(i), recur[j], refarray[j]);

                    // counting total number of violation
                    viol++;
                } 
                
                else if (i >= MAX_SET_NO_FOR_ROW && i < MAX_SET_NO_FOR_COL) {
                    printf("set %2d (col %d): %d instances of %d\n", i, groupfind(i), recur[j], refarray[j]);
                    viol++;
                } 

                else {
                    printf("set %2d (sqr %d): %d instances of %d\n", i, groupfind(i), recur[j], refarray[j]);
                    viol++;
                
                }

                // assign every set number with violation into a separate array
                setarray[i] = i;
    
            }
        }
    }
    
    // loop through without duplicates 
    for (i = 1; i < NSET; i++) {
        if (i == setarray[i]) {

            // count number of elements after alteration
            count_dup++;
        }
    }
    
    // if there is violation
    if (viol != 0) {
        printf("\n%d different sets have violations\n", count_dup);
        printf("%d violations in total\n", viol);

        // exit function to stop the program from running
        exit(-1);
    } 
}

int groupfind(int n) {

    // function to conver set number to row, column or square number
    if (n < MAX_SET_NO_FOR_ROW) {
        return set_to_row(n);
    } 

    else if (n >= MAX_SET_NO_FOR_ROW && n < MAX_SET_NO_FOR_COL) {
        return set_to_col(n);
    }

    else {
        return set_to_sqr(n);
    }
    return 0;
}

int set_to_row(int n) {

    return n + DIFF_FOR_SET_ROW;
}

int set_to_col(int n) {

    return n - DIFF_FOR_SET_COL;
}

int set_to_sqr(int n) {

    return n - DIFF_FOR_SET_SQR;
}

void sort_int_array(int a[]) {

    int temp = 0;  
    
    // sort the array in an ascending order
    for (int i = 0; i < NSET; i++) {     
        for (int j = i+1; j < NDIG; j++) {     
           if(a[i] > a[j]) {   

               temp = a[i];    
               a[i] = a[j];    
               a[j] = temp;    

            }     
        }     
    }   
} 

void find_cell_mates(int a[], int b[]) {

    // triple nested for loop to find cellmates of a particular cell given 
    for (int i = 0; i<NCLL; i++) {
        if (a[i] == 0) {
            for(int j=0; j<NGRP; j++) {
                for (int k=0; k<NDIG; k++) {

                    // utilising c2s, s2c function to gain cell mates
                    b[(j*NDIG)+k] = a[s2c[c2s[i][j]][k]];
                }
            }
        }
    }  
}

// algorithms are fun



/****************************************************************/