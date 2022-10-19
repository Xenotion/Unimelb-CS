/* 
permutation.c

Implementations for Gimli permutation.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick

Implementation fully from: 
  https://gimli.cr.yp.to/spec.html
*/
#include <permutation.h>

uint32_t rotate(uint32_t x, int bits) {
  if (bits == 0) return x;
  return (x << bits) | (x >> (32 - bits));
}

void permute_384(uint8_t *state8) {
  uint32_t *state = (uint32_t *)state8;

  int round;
  int column;
  uint32_t x;
  uint32_t y;
  uint32_t z;

  for (round = 24; round > 0; --round) {
    for (column = 0; column < 4; ++column) {
      x = rotate(state[column], 24);
      y = rotate(state[4 + column], 9);
      z = state[8 + column];

      state[8 + column] = x ^ (z << 1) ^ ((y & z) << 2);
      state[4 + column] = y ^ x ^ ((x | z) << 1);
      state[column] = z ^ y ^ ((x & y) << 3);
    }

    if ((round & 3) == 0) {
      x = state[0];
      state[0] = state[1];
      state[1] = x;
      x = state[2];
      state[2] = state[3];
      state[3] = x;
    }
    if ((round & 3) == 2) {
      x = state[0];
      state[0] = state[2];
      state[2] = x;
      x = state[1];
      state[1] = state[3];
      state[3] = x;
    }

    if ((round & 3) == 0) {
      state[0] ^= (0x9e377900 | round);
    }
  }
}
