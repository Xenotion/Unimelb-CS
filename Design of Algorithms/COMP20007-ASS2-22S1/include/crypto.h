/* 
crypto.h

Definitions and prototypes for cryptography primatives 
    and functions making use of them.

Skeleton written by Aidan Dang for COMP20007 Assignment 2 2022
  with Minor modifications by Grady Fitzpatrick
*/
#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <stdint.h>

// The size of the keys used for the MAC system and authenticated encryption and
// decryption schemes, in bytes
#define CRYPTO_KEY_SIZE 32

// Hashes an input msg of size msg_len bytes to the output of size output_len
// bytes.
void hash(uint8_t *output, uint64_t output_len, uint8_t const *msg,
          uint64_t msg_len);

// Creates authentication tag of size tag_len bytes from key of size
// CRYPTO_KEY_SIZE bytes and an input msg of size msg_len bytes.
void mac(uint8_t *tag, uint64_t tag_len, uint8_t const *key, uint8_t const *msg,
         uint64_t msg_len);

// Encrypts plaintext of size text_len bytes into ciphertext, using key of
// length CRYPTO_KEY_SIZE bytes and produces authentication tag of size tag_len
// bytes.
void auth_encr(uint8_t *ciphertext, uint8_t *tag, uint64_t tag_len,
               uint8_t const *key, uint8_t const *plaintext, uint64_t text_len);

// Decrypts ciphertext of size text_len bytes into plaintext, using key of
// length CRYPTO_KEY_SIZE bytes and verifies authentication tag of size tag_len
// bytes. Returns 1 on invalid tag, else 0.
int auth_decr(uint8_t *plaintext, uint8_t const *key, uint8_t const *ciphertext,
              uint64_t text_len, uint8_t const *tag, uint64_t tag_len);

#endif
