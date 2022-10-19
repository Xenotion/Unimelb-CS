/* 
encr.c

Driver function for authenticated encryption 
  implementation.

Make using 
  make encr

Run in the form
  ./encr <tag length in bytes> <key file> <plaintext file> <optional: concatenated tag+ciphertext file to write>

Where the final argument is optional.

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
  assert(argc == 4 || argc == 5);

  uint64_t tag_len = atoll(argv[1]);

  uint8_t key[CRYPTO_KEY_SIZE];
  {
    FILE *const key_file = fopen(argv[2], "rb");
    assert(key_file != NULL);
    fread(key, sizeof(uint8_t), CRYPTO_KEY_SIZE, key_file);
    fclose(key_file);
  }

  uint8_t *i_file_buf;
  uint64_t file_len;
  {
    FILE *const file = fopen(argv[3], "rb");
    assert(file != NULL);
    io_file_to_mem(&i_file_buf, &file_len, file);
    fclose(file);
  }

  uint8_t *encr_buf = malloc(file_len * sizeof(uint8_t));
  uint8_t *tag_buf = malloc(tag_len * sizeof(uint8_t));
  assert(encr_buf != NULL && tag_buf != NULL);
  auth_encr(encr_buf, tag_buf, tag_len, key, i_file_buf, file_len);
  free(i_file_buf);

  char *encr_ascii_buf = malloc((2 * file_len + 1) * sizeof(char));
  char *tag_ascii_buf = malloc((2 * tag_len + 1) * sizeof(char));
  assert(encr_ascii_buf != NULL && tag_ascii_buf != NULL);
  io_convert_byte_to_hex(encr_ascii_buf, encr_buf, file_len);
  io_convert_byte_to_hex(tag_ascii_buf, tag_buf, tag_len);

  printf("%s:%s\n", tag_ascii_buf, encr_ascii_buf);

  if (argc == 5) {
    FILE *const o_file = fopen(argv[4], "wb");
    assert(o_file != NULL);
    fwrite(tag_buf, sizeof(uint8_t), tag_len, o_file);
    fwrite(encr_buf, sizeof(uint8_t), file_len, o_file);
    fclose(o_file);
  }

  free(encr_buf);
  free(tag_buf);

  return 0;
}
