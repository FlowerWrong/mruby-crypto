#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/des.h>

int main(int argc, char const *argv[]) {
  char *msg = "hello world";
  int ml = strlen(msg);
  char *method = "AES-256-CFB";
  int encrypted_size = 0;
  unsigned char *key[EVP_MAX_KEY_LENGTH], *iv[EVP_MAX_IV_LENGTH];
  char *encrypted;
  encrypt(msg, ml, "aes-256-cfb", "pass", NULL);

  return 0;
}
