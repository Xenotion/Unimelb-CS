/* 
leap.h

Visible structs and functions for leap list construction and manipulation.

Skeleton written by Grady Fitzaptrick for COMP20007 Assignment 1 2022
*/
struct leapList;

enum problemPart;

/* A particular solution to an leapList problem. */
#ifndef SOLUTION_STRUCT
#define SOLUTION_STRUCT
struct solution {
    int queries;
    int *queryResults;
    int *queryElements;
    int *baseAccesses;
    int *requiredAccesses;
    /* Required for part B */
    struct leapList *list;
};
#endif

/* Which part the program should find a solution for. */
#ifndef PART_ENUM
#define PART_ENUM
enum problemPart {
    PART_A=0,
    PART_B=1
};
#endif

/* Value indicating the item is not found. */
#define NOTFOUND (-1)

/* Creates an empty leap list with the given max height and probability. */
struct leapList *newList(int maxHeight, double p, enum problemPart part);

/* Prints the given level of the list. */
void printLevel(struct leapList *list, int level);

/* Adds a new key to the leap list. */
void insertKey(int key, struct leapList *list, double p, int maxHeight);
int requiredAccesses(int key, struct leapList *list, int maxHeight);
/* Queries the leap list for the given key and places the result in the solution structure. */
int findKey(int key, struct leapList *list, enum problemPart part, struct solution *solution, int maxHeight);
/* Deletes a value from the leap list. */
void deleteKey(int key, struct leapList *list, enum problemPart part, int maxHeight);

/* Frees all memory associated with the leap list. */
void freeList(struct leapList *list);

/* Frees all memory associated with the solution. */
void freeSolution(struct solution *solution);

