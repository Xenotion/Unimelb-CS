/* 
leap.c

Implementations for leap list construction and manipulation.

Skeleton written by Grady Fitzaptrick for COMP20007 Assignment 1 2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "leap.h"
#include "utils.h"

typedef struct node node;
typedef struct leapList leapList;

/* struct of node for every element in the leap list */
struct node {
    int val;
    node *next;
    node *down;
    node *up;
    node *prev;
};

/* struct of the entire leap list */
struct leapList {
    /* IMPLEMENT: Fill in structure. */
    int height;
    node **head;
};

struct leapList *newList(int maxHeight, double p, enum problemPart part) {
    /* IMPLEMENT: Set up list */

    /* create a new empty leap list */
    leapList *newList = malloc(sizeof(leapList));

    /* create an array of head nodes */
    node *head[maxHeight];
    newList->head = malloc(sizeof(node) * (maxHeight + 1));
    
    for (int i = 0; i < maxHeight; i++) {
        head[i] = malloc(sizeof(node));
        newList->head[i] = head[i];
        newList->head[i]->val = INT_MAX;
        newList->head[i]->next = NULL;
    }

    
    newList->head[0]->down = NULL;
    
    /* link all the heads from top to bottom */
    for (int i = maxHeight - 1; i > 0; i--) {
        newList->head[i]->down = newList->head[i-1];
    }
    
    return newList;
}

void printLevel(struct leapList *list, int level){
    if(! list){
        printf("\n");
        return;
    }
    /* IMPLEMENT (Part B): loop over list at given level, printing out each value. */
    /* Note: while additional next elements, print a space after the key. If no additional next elements, 
    print a new line and then return. */
    
    /* print function to print all the elements in an order of head level */
    node *current_node = list->head[level];
    while ( current_node->next != NULL) {
        printf("%d", current_node->next->val);
        if(current_node->next->next != NULL) {
            printf(" ");
        }
        current_node->next = current_node->next->next;
    }

    printf("\n");
    
    return;
}

void insertKey(int key, struct leapList *list, double p, int maxHeight){
    /* IMPLEMENT: Insert the key into the given leap list. */
    node *current;
    
    /* determine the height of the inseetion element using rand function */
    int height =  1;
    while ((double) rand() / RAND_MAX < p) {
        if (height == maxHeight - 1) {
            height++;
            break;
        } else {
            height++;
        }
    }
    
    /* create new nodes to be inserted into the leap list */
    node *newnode[height];
    for (int i = 0; i <= height; i++) {
        newnode[i] = malloc(sizeof(node));
        newnode[i]->val = key;
        newnode[i]->next = NULL;
        newnode[i]->prev = NULL;
    }

    for (int i = 0; i < height; i++) {
        newnode[i+1]->down = newnode[i];
        newnode[i]->up = newnode[i+1];
    }

    newnode[0]->down = NULL;
    
    /* connect all the nodes being inserted */
    for(int i = height - 1; i >= 0; i--) {
        if (list->head[i]->next == NULL || list->head[i]->next->val >= key) {
            newnode[i]->next = list->head[i]->next;
            list->head[i]->next = newnode[i];
        } else {
            current = list->head[i]->next;
            while (current->next != NULL && current->next->val < key) {
                current = current->next;
            }
            newnode[i]->next = current->next;
            current->next = newnode[i];
        }
    }

    
    
}

/* Queries the leap list for the given key and places the result in the solution structure. */
int findKey(int key, struct leapList *list, enum problemPart part, struct solution *solution, int maxHeight){
    int found = NOTFOUND;
    int element = key;
    int baseAccesses = 0;
    int requiredAccesses = 0;
    assert(solution);
    /* IMPLEMENT: Find the given key in the leap list. */
    
    node *current_node = list->head[0]->next;
    
    /* fucntion to determine which whether key is in the list and where it is */
    while (current_node != NULL) {
        baseAccesses++;
        if(current_node->val == element) {
            found = 1;
            break;
        } else if (current_node->val > element) {
            break;
        } 
        current_node = current_node->next;
    }
    
    /* function to locate an element using leap list search */
    node *current = list->head[maxHeight - 1];
    while(current != NULL) {
        if (current->next == NULL) {
            current = current->down;
        } else if (current->next->val < key) {
            requiredAccesses++;
            current = current->next;
        } else if (current->next->val > key) {
            int temp = current->next->val;
            requiredAccesses++;
            current = current->down;
            if(current == NULL) {
                break;
            }
            if(current->next && current->next->val == temp) {
                requiredAccesses--;
            }
        } else if (current->next->val == key) {
            requiredAccesses++;
            break;
        } 
    }
    
    /* Insert result into solution. */
    (solution->queries)++;
    solution->queryResults = (int *) realloc(solution->queryResults, sizeof(int) * solution->queries);
    assert(solution->queryResults);
    (solution->queryResults)[solution->queries - 1] = found;
    solution->queryElements = (int *) realloc(solution->queryElements, sizeof(int) * solution->queries);
    assert(solution->queryElements);
    solution->queryElements[solution->queries - 1] = element;
    solution->baseAccesses = (int *) realloc(solution->baseAccesses, sizeof(int) * solution->queries);
    assert(solution->baseAccesses);
    solution->baseAccesses[solution->queries - 1] = baseAccesses;
    solution->requiredAccesses = (int *) realloc(solution->requiredAccesses, sizeof(int) * solution->queries);
    assert(solution->requiredAccesses);
    solution->requiredAccesses[solution->queries - 1] = requiredAccesses;
    return found;
}

void deleteKey(int key, struct leapList *list, enum problemPart part, int maxHeight){
    /* IMPLEMENT: Remove the given key from the leap list. */
    
    /* function to loop through each level of the leap list and remove the key element */
    for (int i = maxHeight - 1; i >= 0; i--) {
        node *temp = list->head[i], *prev;
        while (temp != NULL && temp->val != key) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) {
            continue;
        }
        prev->next = temp->next;
    }
}

void freeList(struct leapList *list){
    /* IMPLEMENT: Free all memory used by the list. */

}

void freeSolution(struct solution *solution){
    if(! solution){
        return;
    }
    freeList(solution->list);
    if(solution->queries > 0){
        free(solution->queryResults);
        free(solution->queryElements);
        free(solution->baseAccesses);
        free(solution->requiredAccesses);
    }
    free(solution);
}

