/* 
mac.c

Driver function for MAC implementation.

Make using 
  make mac

Run in the form
  ./mac <tag length in bytes> <key file> <message file>

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
  assert(argc == 4);

  uint64_t tag_len = atoll(argv[1]);

  uint8_t key[CRYPTO_KEY_SIZE];
  {
    FILE *const key_file = fopen(argv[2], "rb");
    assert(key_file != NULL);
    fread(key, sizeof(uint8_t), CRYPTO_KEY_SIZE, key_file);
    fclose(key_file);
  }

  uint8_t *file_buf;
  uint64_t file_len;
  {
    FILE *const file = fopen(argv[3], "rb");
    assert(file != NULL);
    io_file_to_mem(&file_buf, &file_len, file);
    fclose(file);
  }

  uint8_t *tag_buf = malloc(tag_len * sizeof(uint8_t));
  assert(tag_buf != NULL);
  mac(tag_buf, tag_len, key, file_buf, file_len);
  free(file_buf);

  char *output_buf = malloc((2 * tag_len + 1) * sizeof(char));
  assert(output_buf != NULL);
  io_convert_byte_to_hex(output_buf, tag_buf, tag_len);

  printf("%s\n", output_buf);

  return 0;
}
