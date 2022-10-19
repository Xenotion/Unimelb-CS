/*
utils.h

Visible structs and functions for helper functions to do with 
reading and writing.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2022
*/
/* Because we use FILE in this file, we should include stio.h here. */
#include <stdio.h>
/* Because we use enum problemPart in this file, we should include leap.h here. */
#include "leap.h"
/* The problem specified. */
struct dictProblem;

/* Reads the data from the given file pointer and returns a pointer to this 
information. */
struct dictProblem *readProblem(FILE *file, enum problemPart part);

/* Finds a solution for a given problem. */
struct solution *findSolution(struct dictProblem *problem, enum problemPart part);

/* Prints a given solution. */
void printSolution(struct dictProblem *problem, struct solution *solution, enum problemPart part);

/* Frees all data used by problem. */
void freeProblem(struct dictProblem *problem);

