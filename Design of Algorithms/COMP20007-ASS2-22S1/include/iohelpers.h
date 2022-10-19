/* 
iohelpers.h

Definitions and prototypes for various io helpers for 
    reading files and writing outputs.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick
*/
#ifndef __IOHELPERS_H__
#define __IOHELPERS_H__

#include <stdint.h>
#include <stdio.h>

void io_file_to_mem(uint8_t **buf, uint64_t *len, FILE *file);
void io_convert_byte_to_hex(char *ascii, uint8_t const *byte_buf, uint64_t len);

#endif
