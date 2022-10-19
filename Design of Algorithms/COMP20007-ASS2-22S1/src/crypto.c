/* 
crypto.c

Implementations for cryptography primatives and functions
  making use of them.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick
  implementation by <You>
*/
#include <crypto.h>
#include <sponge.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The sponge's rate, in bytes. This represents the maximum number of bytes
// which can be read from or written the start of the sponge's state before a
// permutation must occur.
#define RATE 16
// Delimiter byte value used after absorption of the message
#define DELIMITER_A 0xAD
// Delimiter byte used at the end of the last-used block
#define DELIMITER_B 0X77

// Helpful min function that might be useful.
uint64_t min(uint64_t a, uint64_t b) { return a < b ? a : b; }

void hash(uint8_t *output, uint64_t output_len, uint8_t const *msg,
          uint64_t msg_len) {
  sponge_t sponge;
  // initialising sponge state to 0
  sponge_init(&sponge);

  // calculating how many sets of RATE bytes there will be and remainder for 
  // both msg_len and output_len
  int input_int = msg_len / RATE;
  int input_rem = msg_len % RATE;
  int output_int = output_len / RATE;
  int output_rem = output_len % RATE;

  // looping through to write RATE sets of bytes into the sponge from the 
  // original msg
  int w = 0;
  while (w < input_int) {
    sponge_write(&sponge, msg + RATE * w, RATE, true);

    sponge_permute(&sponge);

    w++;
  }

  // writing the remainder bytes into the songe
  if (input_rem > 0 && input_rem < 16) {
    sponge_write(&sponge, msg + RATE * input_int, input_rem, true);
  }

  // demarcation phase
  sponge_demarcate(&sponge, input_rem, DELIMITER_A);

  sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);

  sponge_permute(&sponge);

  // looping through to read RATE sets of bytes into the output from the sponge
  int r = 0;
  while (r < output_int) {
    sponge_read(output + RATE * r, &sponge, RATE);

    sponge_permute(&sponge);

    r++;
  }
  
  // reading the remainder bytes into the songe
  if (output_rem > 0 && output_rem < 16) {
    sponge_read(output + RATE * output_int, &sponge, output_rem);
  }

  // TODO: fill the rest of this function.
  // Here are some examples of what sponge routines are called for various
  // invocations of this hash function:
  // hash(o, 5, m, 0) performs:
  //   sponge_write(&sponge, m, 0, true);

  //   sponge_demarcate(&sponge, 0, DELIMITER_A);
  //   sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);
  //   sponge_permute(&sponge);

  //   sponge_read(o, &sponge, 5);
  //
  // hash(o, 16, m, 7) performs:
  //   sponge_write(&sponge, m, 7, true);

  //   sponge_demarcate(&sponge, 7, DELIMITER_A);
  //   sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);
  //   sponge_permute(&sponge);

  //   sponge_read(o, &sponge, 16);
  //
  // hash(o, 23, m, 16) performs:
  //   sponge_write(&sponge, m, RATE, true);
  //   sponge_permute(&sponge);
  //   sponge_write(&sponge, m + RATE, 0, true);

  //   sponge_demarcate(&sponge, 0, DELIMITER_A);
  //   sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);
  //   sponge_permute(&sponge);

  //   sponge_read(o, &sponge, RATE);
  //   sponge_permute(&sponge);
  //   sponge_read(o + RATE, &sponge, 7);
  //
  // hash(o, 32, m, 23) performs:
  //   sponge_write(&sponge, m, RATE, true);
  //   sponge_permute(&sponge);
  //   sponge_write(&sponge, m + RATE, 7, true);

  //   sponge_demarcate(&sponge, 7, DELIMITER_A);
  //   sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);
  //   sponge_permute(&sponge);

  //   sponge_read(o, &sponge, RATE);
  //   sponge_permute(&sponge);
  //   sponge_read(o + RATE, &sponge, 16);
}

void mac(uint8_t *tag, uint64_t tag_len, uint8_t const *key, uint8_t const *msg,
         uint64_t msg_len) {
  sponge_t sponge;
  // initialisng songe state to 0
  sponge_init(&sponge);

  // TODO: fill the rest of this function.
  // Your implementation should like very similar to that of the hash
  // function's, but should include a keying phase before the absorbing phase.
  // If you wish, you may also treat this as calculating the hash of the key
  // prepended to the message.
  
  // turning the empty sponge into a key state
  sponge_write(&sponge, key, RATE, true);
  sponge_permute(&sponge);

  sponge_write(&sponge, key + RATE, RATE, true);
  sponge_permute(&sponge);
  
  // calculating how many sets of RATE bytes there will be and remainder for 
  // both msg_len and tag_len
  int input_int = msg_len / RATE;
  int input_rem = msg_len % RATE;
  int tag_int = tag_len / RATE;
  int tag_rem = tag_len % RATE;

  // looping through to write RATE sets of bytes into the sponge from the 
  // original msg
  int w = 0;
  while (w < input_int) {
    sponge_write(&sponge, msg + RATE * w, RATE, true);

    sponge_permute(&sponge);

    w++;
  }
  
  // write remainder bytes into the sponge from the original msg
  if (input_rem > 0 && input_rem < 16) {
    sponge_write(&sponge, msg + RATE * input_int, input_rem, true);
  }

  // demarcation phase
  sponge_demarcate(&sponge, input_rem, DELIMITER_A);

  sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);

  sponge_permute(&sponge);

  // looping through to write RATE sets of bytes into the tag from the sponge 
  int r = 0;
  while (r < tag_int) {
    sponge_read(tag + RATE * r, &sponge, RATE);

    sponge_permute(&sponge);

    r++;
  }
  

  // reading the remainder bytes into the tag from sponge
  if (tag_rem > 0 && tag_rem < 16) {
    sponge_read(tag + RATE * tag_int, &sponge, tag_rem);
  }

}

void auth_encr(uint8_t *ciphertext, uint8_t *tag, uint64_t tag_len,
               uint8_t const *key, uint8_t const *plaintext,
               uint64_t text_len) {
  sponge_t sponge;
  // initialising sponge state to 0
  sponge_init(&sponge);

  // TODO: fill the rest of this function.
  // Your implementation should like very similar to that of the mac function's,
  // but should after each write into the sponge's state, there should
  // immediately follow a read from the sponge's state of the same number of
  // bytes, into the ciphertext buffer.
  
  // writing key into the empty sponge state
  sponge_write(&sponge, key, RATE, true);
  sponge_permute(&sponge);

  sponge_write(&sponge, key + RATE, RATE, true);
  sponge_permute(&sponge);

  // calculating how many sets of RATE bytes there will be and remainder for 
  // both text_len and tag_len
  int input_int = text_len / RATE;
  int input_rem = text_len % RATE;
  int tag_int = tag_len / RATE;
  int tag_rem = tag_len % RATE;

  // looping through to write RATE sets of bytes into the sponge from the plain 
  // text and read the equivalent amount out to the ciphertext 
  int w = 0;
  while (w < input_int) {
    sponge_write(&sponge, plaintext + RATE * w, RATE, true);

    sponge_read(ciphertext + RATE * w, &sponge, RATE);

    sponge_permute(&sponge);

    w++;
  }

  // write remainder bytes into the sponge into plaintext to sponge and read the 
  // corresponding amount to ciphertext from sponge
  if (input_rem > 0 && input_rem < 16) {
    sponge_write(&sponge, plaintext + RATE * input_int, input_rem, true);

    sponge_read(ciphertext + RATE * tag_int, &sponge, input_rem);

  }

  // demarcatin phase
  sponge_demarcate(&sponge, input_rem, DELIMITER_A);

  sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);

  sponge_permute(&sponge);

  // looping through to write RATE sets of bytes into the tag from the sponge
  int r = 0;
  while (r < tag_int) {
    sponge_read(tag + RATE * r, &sponge, RATE);

    sponge_permute(&sponge);

    r++;
  }
  
  // reading the remainder bytes ito the tag from sponge
  if (tag_rem > 0 && tag_rem < 16) {
    sponge_read(tag + RATE * tag_int, &sponge, tag_rem);
  }

}

int auth_decr(uint8_t *plaintext, uint8_t const *key, uint8_t const *ciphertext,
              uint64_t text_len, uint8_t const *tag, uint64_t tag_len) {
  sponge_t sponge;
  // initialising sponge state to 0
  sponge_init(&sponge);
  
  // TODO: fill the rest of this function.
  // The implementation of this function is left as a challenge. It may assist
  // you to know that a ^ b ^ b = a. Remember to return 0 on success, and 1 on
  // failure.

  // writing key into the empty sponge state
  sponge_write(&sponge, key, RATE, true);
  sponge_permute(&sponge);

  sponge_write(&sponge, key + RATE, RATE, true);
  sponge_permute(&sponge);

  // calculating how many sets of RATE bytes there will be and remainder for 
  // both text_len and tag_len
  int input_int = text_len / RATE;
  int input_rem = text_len % RATE;
  int tag_int = tag_len / RATE;
  int tag_rem = tag_len % RATE;

  // looping through to write RATE sets of bytes into the sponge from the 
  // ciphertext and read the corresponding amount into the plaintext, whilst 
  // resetting the sponge with the ciphertext before another execution
  int w = 0;
  while (w < input_int) {
    sponge_write(&sponge, ciphertext + RATE * w, RATE, true);

    sponge_read(plaintext + RATE * w, &sponge, RATE);

    sponge_write(&sponge, ciphertext + RATE * w, RATE, false);

    sponge_permute(&sponge);

    w++;
  } 

  // writing the remainder bytes into the sponge from ciphertext and reading out 
  // the corresponding amount to the plaintext, whilst resetting the sponge with the ciphertext 
  if (input_rem > 0 && input_rem < 16) {
    sponge_write(&sponge, ciphertext + RATE * input_int, input_rem, true);

    sponge_read(plaintext + RATE * input_int, &sponge, input_rem);

    sponge_write(&sponge, ciphertext + RATE * w, RATE, false);
  }

  // demarcation phase
  sponge_demarcate(&sponge, input_rem, DELIMITER_A);

  sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);

  sponge_permute(&sponge);
  
  // initialise new array with size tag_len
  uint8_t new_tag[tag_len];

  // initialise sponge state to 0
  sponge_init(&sponge);

  // write key into the empty sponge state
  sponge_write(&sponge, key, RATE, true);
  sponge_permute(&sponge);

  sponge_write(&sponge, key + RATE, RATE, true);
  sponge_permute(&sponge);

  // write plaintext into the sponge to get ciphertext
  int d = 0;
  while (d < input_int) {
    sponge_write(&sponge, plaintext + RATE * d, RATE, true);

    sponge_permute(&sponge);

    d++;
  }

  // write plaintext into the songe to get ciphertext for the remainng bytes
  if (input_rem > 0 && input_rem < 16) {
    sponge_write(&sponge, plaintext + RATE * input_int, input_rem, true);

  }

  // demarcation phase
  sponge_demarcate(&sponge, input_rem, DELIMITER_A);

  sponge_demarcate(&sponge, RATE - 1, DELIMITER_B);

  sponge_permute(&sponge);

  // read into newly created tag array from sponge
  int r = 0;  
  while (r < tag_int) {
    sponge_read(new_tag + RATE * r, &sponge, RATE);

    sponge_permute(&sponge);

    r++;
  }

  // read into newly created tag array from sponge for the remaining bytes
  if (tag_rem > 0 && tag_rem < 16) {
    sponge_read(new_tag + RATE * tag_int, &sponge, tag_rem);
  }
  
  // compare the newly created tag and the original tag to check whether the 
  // decryption was carried out with the same key
  // if yes return the decrypted msg, if no null it
  for (int i = 0; i < tag_len; i++) {
    if (new_tag[i] != tag[i]) {
      return 1;
    } else {
      return 0;
    }
  }

  return 0;
}
