/* 
sponge.h

Definitions and prototypes for sponge construction
  initialisation and manipulation.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick
*/
#ifndef __SPONGE_H__
#define __SPONGE_H__

#include <stdbool.h>
#include <stdint.h>

// The size of the sponge's state, in bytes
#define SPONGE_STATE_SIZE 48

typedef struct sponge {
  uint8_t state[SPONGE_STATE_SIZE];
} sponge_t;

// Initialises a sponge by zeroing its state.
void sponge_init(sponge_t *sponge);

// Reads num bytes from the sponge's state into the dest buffer.
void sponge_read(uint8_t *dest, sponge_t const *sponge, uint64_t num);
// Writes num bytes from the src buffer into the sponge's state, either by
// bit-wise XOR when bw_xor, else by overwriting.
void sponge_write(sponge_t *sponge, uint8_t const *src, uint64_t num,
                  bool bw_xor);
// Bit-wise XORs the delimiter into the i'th byte of the sponge's state.
void sponge_demarcate(sponge_t *sponge, uint64_t i, uint8_t delimiter);
// Applies the permutation to the sponge's state.
void sponge_permute(sponge_t *sponge);

#endif
