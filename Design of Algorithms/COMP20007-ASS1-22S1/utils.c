/*
utils.c

Implementations for helper functions to do with reading and writing.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "leap.h"
#include "utils.h"

struct dictProblem {
    unsigned int seed;
    int length;
    int queryLength;
    int height;
    double p;
    int *elements;
    int *queryElements;
    /* Used in Part B */
    int deleteLength;
    int *deleteElements;
    enum problemPart part;
};

/* Helper function, returns "not found" if the result is not found 
and "present" otherwise */
const char *getResultString(int result);

/* Reads the data from the given file pointer and returns a pointer to this 
information. */
struct dictProblem *readProblem(FILE *file, enum problemPart part){
    struct dictProblem *problem;
    problem = (struct dictProblem *) malloc(sizeof(struct dictProblem));
    assert(problem);
    /* 
    Read in input in form:
    <random seed>
    <length> <query length>
    <height> <p>
    <elements>
    <query elements>
    -- Part B only --
    <delete length>
    <delete elements>
    */
    assert(fscanf(file, "%u ", &(problem->seed)) > 0);
    assert(fscanf(file, "%d ", &(problem->length)) > 0);
    assert(fscanf(file, "%d ", &(problem->queryLength)) > 0);
    assert(fscanf(file, "%d ", &(problem->height)) > 0);
    assert(fscanf(file, "%lf ", &(problem->p)) > 0);
    assert(problem->length > 0);
    problem->elements = (int *) malloc(sizeof(int) * problem->length);
    assert(problem->elements);
    int i;
    for(i = 0; i < problem->length; i++){
        assert(fscanf(file, "%d", &((problem->elements)[i])) == 1);
    }
    assert(problem->queryLength > 0);
    problem->queryElements = (int *) malloc(sizeof(int) * problem->queryLength);
    assert(problem->queryElements);
    for(i = 0; i < problem->queryLength; i++){
        assert(fscanf(file, "%d", &((problem->queryElements)[i])) == 1);
    }
    if(part == PART_B){
        assert(fscanf(file, "%d ", &(problem->deleteLength)) > 0);
        /* Allow for no deletions to help with easier debugging. */
        if(problem->deleteLength > 0){
            problem->deleteElements = (int *) malloc(sizeof(int) * problem->deleteLength);
            assert(problem->deleteElements);
            for(i = 0; i < problem->deleteLength; i++){
                assert(fscanf(file, "%d", &((problem->deleteElements)[i])) == 1);
            }
        }
    }

    problem->part = part;

    return problem;
}

/* Finds a solution for a given problem. */
struct solution *findSolution(struct dictProblem *problem, enum problemPart part){
    struct solution *solution = (struct solution *) malloc(sizeof(struct solution));
    assert(solution);

    solution->queries = 0;
    solution->queryResults = NULL;
    solution->queryElements = NULL;
    solution->baseAccesses = NULL;
    solution->requiredAccesses = NULL;

    struct leapList *list = newList(problem->height, problem->p, part);
    solution->list = list;

    /* Set random seed. */
    srand(problem->seed);

    switch(part){
        case PART_A:
            for(int i = 0; i < problem->length; i++){
                insertKey((problem->elements)[i], list, problem->p, problem->height);
            }

            for(int i = 0; i < problem->queryLength; i++){
                findKey(problem->queryElements[i], list, part, solution, problem->height);
            }

            break;

        case PART_B:
            for(int i = 0; i < problem->length; i++){
                insertKey((problem->elements)[i], list, problem->p, problem->height);
            }

            for(int i = 0; i < problem->deleteLength; i++){
                deleteKey(problem->deleteElements[i], list, part, problem->height);
            }

            for(int i = 0; i < problem->queryLength; i++){
                findKey(problem->queryElements[i], list, part, solution, problem->height);
            }

            break;
    }

    return solution;
}

const char *getResultString(int result){
    if(result == NOTFOUND){
        return "not found";
    } else {
        return "present";
    }
}

void printSolution(struct dictProblem *problem, struct solution *solution, 
    enum problemPart part){
    int i;
    switch(part){
        case PART_A:
            for(i = 0; i < solution->queries; i++){
                printf("%d (%s): %d %d\n", 
                    solution->queryElements[i], getResultString(solution->queryResults[i]), 
                    solution->baseAccesses[i], solution->requiredAccesses[i]);
            }

            break;

        case PART_B:
            /* Print from the top down. */
            for(i = problem->height - 1; i >= 0; i--){
                printLevel(solution->list, i);
            }

            /* Print the same output as Part A. */
            for(i = 0; i < solution->queries; i++){
                printf("%d (%s): %d %d\n", 
                    solution->queryElements[i], getResultString(solution->queryResults[i]), 
                    solution->baseAccesses[i], solution->requiredAccesses[i]);
            }
            break;
    }
}

/* Frees all data used by problem. */
void freeProblem(struct dictProblem *problem){
    if(!problem){
        return;
    }

    if(problem->elements){
        free(problem->elements);
    }
    if(problem->queryElements){
        free(problem->queryElements);
    }
    
    if(problem->part == PART_B){
        if(problem->deleteElements){
            free(problem->deleteElements);
        }
    }
    free(problem);
    
}

