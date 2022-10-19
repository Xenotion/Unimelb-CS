/* 
permutation.h

Definitions and prototypes for Gimli 384-bit permutation.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick
*/
#ifndef __PERMUTATION_H__
#define __PERMUTATION_H__

#include <stdint.h>

// Applies an in-place bijective transformation to an input array of 384 bits.
void permute_384(uint8_t *state);

#endif
