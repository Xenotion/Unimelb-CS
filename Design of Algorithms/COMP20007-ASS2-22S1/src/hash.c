/* 
hash.c

Driver function for hashing implementation.

Make using 
  make hash

Run in the form
  ./hash <digest length in bytes> <input file>

See specification for details of each argument.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick
*/
#include <assert.h>
#include <crypto.h>
#include <iohelpers.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  assert(argc == 3);

  uint64_t hash_len = atoll(argv[1]);

  uint8_t *file_buf;
  uint64_t file_len;
  {
    FILE *const file = fopen(argv[2], "rb");
    assert(file != NULL);
    io_file_to_mem(&file_buf, &file_len, file);
    fclose(file);
  }

  uint8_t *hash_buf = malloc(hash_len * sizeof(uint8_t));
  assert(hash_buf != NULL);
  hash(hash_buf, hash_len, file_buf, file_len);
  free(file_buf);

  char *output_buf = malloc((2 * hash_len + 1) * sizeof(char));
  assert(output_buf != NULL);
  io_convert_byte_to_hex(output_buf, hash_buf, hash_len);

  printf("%s\n", output_buf);

  return 0;
}
