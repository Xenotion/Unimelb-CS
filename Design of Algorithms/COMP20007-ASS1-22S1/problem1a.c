/*
problem1a.c

Driver function for Problem 1 Part A

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2022
*/
#include <stdio.h>
#include "utils.h"

int main(int argc, char **argv){
    /* Read the problem in from stdin. */
    struct dictProblem *problem = readProblem(stdin, PART_A);
    /* Find the solution to the problem. */
    struct solution *solution = findSolution(problem, PART_A);

    /* Report solution */
    printSolution(problem, solution, PART_A);

    freeProblem(problem);
    freeSolution(solution);

    return 0;
}


