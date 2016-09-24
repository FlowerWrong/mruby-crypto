#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/des.h>
#include <string.h>
#include <stdio.h>
#include "crypto.h"

#define SUCCESS 1
#define ERROR 0

void encrypt(const char *plain, int plain_size, const char *method, const char *pass, const char *salt) {
	const EVP_CIPHER *cipher;
	OpenSSL_add_all_algorithms();
	printf("method is %s\n", method);
	cipher = EVP_get_cipherbyname(method);
	if(!cipher) {
		fprintf(stderr, "no such cipher\n");
		exit;
	}

	int cipher_key_length, cipher_iv_length;
	cipher_key_length = EVP_CIPHER_key_length(cipher);
	cipher_iv_length = EVP_CIPHER_iv_length(cipher);
	unsigned char *key[EVP_MAX_KEY_LENGTH], *iv[EVP_MAX_IV_LENGTH];
	EVP_BytesToKey(cipher, EVP_md5(), salt, (unsigned char*)pass, strlen(pass), 1, key, iv);
	printf("key is %d, iv is %d\n", strlen(key), strlen(iv));

  if (strlen(key) != cipher_key_length) {
    fprintf(stderr, "Error: key length must be %d\n", cipher_key_length);
    exit;
  }
  if (strlen(iv) != cipher_iv_length) {
    fprintf(stderr, "Error: iv length must be %d\n", cipher_iv_length);
    exit;
  }
	printf("iv is %s\n", iv);

  EVP_CIPHER_CTX ctx;
  int i, cipher_length, final_length;
  unsigned char *ciphertext;

  EVP_CIPHER_CTX_init(&ctx);
  EVP_EncryptInit_ex(&ctx, cipher, NULL, key, iv);

  cipher_length = plain_size + EVP_MAX_BLOCK_LENGTH;
  ciphertext = (unsigned char *)malloc(cipher_length);

  EVP_EncryptUpdate(&ctx, ciphertext, &cipher_length, plain, plain_size);
  EVP_EncryptFinal_ex(&ctx, ciphertext + cipher_length, &final_length);

  for (i = 0; i < cipher_length + final_length; i++)
    printf("%02x", ciphertext[i]);
  printf("\n");

	int en_data_len = strlen(ciphertext);

  EVP_CIPHER_CTX_cleanup(&ctx);

	char *plaintext;
	plaintext = (unsigned char *)malloc(cipher_length);
	int length_partial, length = 0;
	EVP_CIPHER_CTX dectx;
  EVP_CIPHER_CTX_init(&dectx);
	EVP_DecryptInit_ex(&dectx, cipher, NULL, key, iv);
  EVP_DecryptUpdate(&dectx, plaintext, &length_partial, ciphertext, en_data_len);
  EVP_DecryptFinal_ex(&dectx, plaintext + length_partial, &length);
  printf("plaintext is %s\n", plaintext);

  EVP_CIPHER_CTX_cleanup(&dectx);
}
