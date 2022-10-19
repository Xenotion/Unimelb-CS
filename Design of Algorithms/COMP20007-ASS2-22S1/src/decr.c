/* 
decr.c

Driver function for authenticated decryption 
  implementation.

Make using 
  make decr

Run in the form
  ./decr <tag length in bytes: must match tag length used for encryption> <key file> <concatenated tag+ciphertext file>

See specification for details of each argument.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick
*/
#include <assert.h>
#include <crypto.h>
#include <iohelpers.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  uint8_t *tag_buf = malloc(tag_len * sizeof(uint8_t));
  assert(tag_buf != NULL);
  uint8_t *encr_buf;
  uint64_t file_len;
  {
    uint8_t *i_file_buf;
    FILE *const file = fopen(argv[3], "rb");
    assert(file != NULL);
    io_file_to_mem(&i_file_buf, &file_len, file);
    fclose(file);

    assert(file_len >= tag_len);
    file_len -= tag_len;
    memcpy(tag_buf, i_file_buf, tag_len);
    encr_buf = malloc(file_len * sizeof(uint8_t));
    assert(encr_buf != NULL);
    memcpy(encr_buf, i_file_buf + tag_len, file_len);
    free(i_file_buf);
  }

  uint8_t *decr_buf = malloc(file_len * sizeof(uint8_t));
  assert(decr_buf != NULL);
  int const res =
      auth_decr(decr_buf, key, encr_buf, file_len, tag_buf, tag_len);
  free(encr_buf);

  if (res == 0) {
    printf("Decryption successful. Printing decrypted file below dashes:\n");
    printf("----------------------------\n");
    printf("%s\n", decr_buf);
  } else {
    printf(
        "Error: invalid tag. Wrong decryption key used, or tampering or "
        "corruption has occurred.\n");
  }

  free(tag_buf);
  return res;
}
