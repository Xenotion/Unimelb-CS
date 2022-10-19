/* 
iohelpers.c

Implementations for various io helpers for reading files
and writing outputs.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick
*/
#include <iohelpers.h>
#include <stdlib.h>

void io_file_to_mem(uint8_t **buf, uint64_t *len, FILE *file) {
  fseek(file, 0, SEEK_END);
  *len = ftell(file);
  fseek(file, 0, SEEK_SET);
  *buf = malloc(*len * sizeof(uint8_t));
  fread(*buf, sizeof(uint8_t), *len, file);
}

void io_convert_byte_to_hex(char *ascii, uint8_t const *byte_buf,
                            uint64_t len) {
  for (int i = 0; i < len; i++) {
    sprintf(ascii + 2 * i, "%02x", byte_buf[i]);
  }
}
