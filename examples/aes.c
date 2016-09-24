// #include "crypto.h"
//
// int main(int argc, char const *argv[]) {
//   char *msg = "hello world";
//   int size = *((int*) msg);
//   char *algorithm = "AES-256";
//   char *mode = "CFB";
//   int encrypted_size = 0;
//   char * encrypted = (unsigned char*)encrypt(msg, &encrypted_size, algorithm, mode, "aa", size);
//   return 0;
// }




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
  int dlen = encrypt(msg, ml, encrypted, iv, "aes-256-cfb", "pass", NULL);
  printf("en data is %s\n", encrypted);
  printf("iv is %s\n", iv);
  printf("dlen is %d en data len is %d\n", dlen, strlen(encrypted));


  // const unsigned char *salt = NULL;
  // const unsigned char *pass = "pass";
	// const EVP_CIPHER *cipher;
	// OpenSSL_add_all_algorithms();
	// cipher = EVP_get_cipherbyname("aes-256-cfb");
	// printf("EVP_MAX_KEY_LENGTH %d EVP_MAX_IV_LENGTH %d\n", EVP_MAX_KEY_LENGTH, EVP_MAX_IV_LENGTH);
	// unsigned char *key[EVP_MAX_KEY_LENGTH], *iv[EVP_MAX_IV_LENGTH];
	// EVP_BytesToKey(cipher, EVP_md5(), salt, (unsigned char*)pass, strlen(pass), 1, key, iv);
  //
	// printf("key is %d, iv is %d\n", strlen(key), strlen(iv));

  return 0;
}

// int main(int argc, const char* argv[])
// {
//   if (argc <= 3) {
//     fprintf(stderr, "Usage: %s <key> <iv> <data>\n", argv[0]);
//     exit(EXIT_FAILURE);
//   }
//
//   const char *key, *iv, *data;
//   int key_length, iv_length, data_length;
//   key = argv[1];
//   key_length = strlen(key);
//   iv = argv[2];
//   iv_length = strlen(iv);
//   data = argv[3];
//   data_length = strlen(data);
//
//   const EVP_CIPHER *cipher;
//   OpenSSL_add_all_algorithms();
//   int cipher_key_length, cipher_iv_length;
//   // cipher = EVP_aes_256_cfb();
//   cipher = EVP_get_cipherbyname("aes-256-cfb");
//   if(!cipher) {
//     fprintf(stderr, "no such cipher\n");
//     return 1;
//   }
//   cipher_key_length = EVP_CIPHER_key_length(cipher);
//   cipher_iv_length = EVP_CIPHER_iv_length(cipher);
//
//   if (key_length != cipher_key_length) {
//     fprintf(stderr, "Error: key length must be %d\n", cipher_key_length);
//     exit(EXIT_FAILURE);
//   }
//   if (iv_length != cipher_iv_length) {
//     fprintf(stderr, "Error: iv length must be %d\n", cipher_iv_length);
//     exit(EXIT_FAILURE);
//   }
//
//   EVP_CIPHER_CTX ctx;
//   int i, cipher_length, final_length;
//   unsigned char *ciphertext;
//
//   EVP_CIPHER_CTX_init(&ctx);
//   EVP_EncryptInit_ex(&ctx, cipher, NULL, (unsigned char *)key, (unsigned char *)iv);
//
//   cipher_length = data_length + EVP_MAX_BLOCK_LENGTH;
//   ciphertext = (unsigned char *)malloc(cipher_length);
//
//   EVP_EncryptUpdate(&ctx, ciphertext, &cipher_length, (unsigned char *)data, data_length);
//   EVP_EncryptFinal_ex(&ctx, ciphertext + cipher_length, &final_length);
//
//   for (i = 0; i < cipher_length + final_length; i++)
//     printf("%02x", ciphertext[i]);
//   printf("\n");
//
//   free(ciphertext);
//
//   EVP_CIPHER_CTX_cleanup(&ctx);
//
//   return 0;
// }
