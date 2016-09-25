/*
** mrb_crypto.c - Crypto class
**
** Copyright (c) yang 2016
**
** See Copyright Notice in LICENSE
*/

#include <openssl/evp.h>

#include <string.h>
#include <stdio.h>

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "mruby/variable.h"
#include "mruby/array.h"

#include "mrb_crypto.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

// typedef struct {
//   char *str;
//   int len;
// } mrb_crypto_data;
//
// static const struct mrb_data_type mrb_crypto_data_type = {
//   "mrb_crypto_data", mrb_free,
// };

// static mrb_value mrb_crypto_init(mrb_state *mrb, mrb_value self)
// {
//   mrb_crypto_data *data;
//   char *str;
//   int len;
//
//   data = (mrb_crypto_data *)DATA_PTR(self);
//   if (data) {
//     mrb_free(mrb, data);
//   }
//   DATA_TYPE(self) = &mrb_crypto_data_type;
//   DATA_PTR(self) = NULL;
//
//   mrb_get_args(mrb, "s", &str, &len);
//   data = (mrb_crypto_data *)mrb_malloc(mrb, sizeof(mrb_crypto_data));
//   data->str = str;
//   data->len = len;
//   DATA_PTR(self) = data;
//
//   return self;
// }

static mrb_value mrb_encrypt(mrb_state *mrb, mrb_value self) {
  mrb_value method, source, key, iv;
  mrb_get_args(mrb, "SSSS", &method, &source, &key, &iv);

  const EVP_CIPHER *cipher;
	OpenSSL_add_all_algorithms();
	cipher = EVP_get_cipherbyname(RSTRING_PTR(method));
  if (!cipher) {
    return mrb_nil_value();
  }

  EVP_CIPHER_CTX ctx;
  mrb_int i, source_len, cipher_length, final_length;
  unsigned char *ciphertext;

  EVP_CIPHER_CTX_init(&ctx);
  EVP_EncryptInit_ex(&ctx, cipher, NULL, RSTRING_PTR(key), RSTRING_PTR(iv));

  source_len = RSTRING_LEN(source);
  cipher_length = source_len + EVP_MAX_BLOCK_LENGTH;
  ciphertext = (unsigned char *)malloc(cipher_length);

  EVP_EncryptUpdate(&ctx, ciphertext, &cipher_length, RSTRING_PTR(source), source_len);
  EVP_EncryptFinal_ex(&ctx, ciphertext + cipher_length, &final_length);

  EVP_CIPHER_CTX_cleanup(&ctx);

  return mrb_str_new(mrb, ciphertext, strlen(ciphertext));
}
static mrb_value mrb_decrypt(mrb_state *mrb, mrb_value self) {
  mrb_value method, source, key, iv;
  unsigned char *plaintext;
  mrb_get_args(mrb, "SSSS", &method, &source, &key, &iv);

  const EVP_CIPHER *cipher;
  OpenSSL_add_all_algorithms();
  cipher = EVP_get_cipherbyname(RSTRING_PTR(method));
  if (!cipher) {
    return mrb_nil_value();
  }

  EVP_CIPHER_CTX ctx;
  EVP_CIPHER_CTX_init(&ctx);

  int length_partial = 0, length = 0;
  mrb_int source_len = RSTRING_LEN(source);

  plaintext = (unsigned char *)malloc(source_len);

	EVP_DecryptInit_ex(&ctx, cipher, NULL, RSTRING_PTR(key), RSTRING_PTR(iv));
  EVP_DecryptUpdate(&ctx, plaintext, &length_partial, RSTRING_PTR(source), source_len);
  EVP_DecryptFinal_ex(&ctx, plaintext + length_partial, &length);

  EVP_CIPHER_CTX_cleanup(&ctx);

  return mrb_str_new(mrb, plaintext, strlen(plaintext));
}

static mrb_value mrb_crypto_key_iv_ary(mrb_state *mrb, mrb_value self)
{
  mrb_value result;
  mrb_value method;
  mrb_get_args(mrb, "S", &method);

  const EVP_CIPHER *cipher;
  OpenSSL_add_all_algorithms();
  cipher = EVP_get_cipherbyname(RSTRING_PTR(method));
  if (!cipher) {
    return mrb_nil_value();
  }

  mrb_int cipher_key_length, cipher_iv_length;
	cipher_key_length = EVP_CIPHER_key_length(cipher);
	cipher_iv_length = EVP_CIPHER_iv_length(cipher);

  result = mrb_ary_new(mrb);
  mrb_ary_push(mrb, result, mrb_fixnum_value(cipher_key_length));
  mrb_ary_push(mrb, result, mrb_fixnum_value(cipher_iv_length));

  return result;
}

// static mrb_value mrb_crypto_hello(mrb_state *mrb, mrb_value self)
// {
//   mrb_crypto_data *data = DATA_PTR(self);
//
//   return mrb_str_new(mrb, data->str, data->len);
// }

void mrb_mruby_crypto_gem_init(mrb_state *mrb)
{
  struct RClass *crypto;
  crypto = mrb_define_class(mrb, "Crypto", mrb->object_class);
  // mrb_define_method(mrb, crypto, "initialize", mrb_crypto_init, MRB_ARGS_REQ(1));
  // mrb_define_method(mrb, crypto, "hello", mrb_crypto_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, crypto, "encrypt", mrb_encrypt, MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb, crypto, "decrypt", mrb_decrypt, MRB_ARGS_REQ(4));
  mrb_define_class_method(mrb, crypto, "cipher_len", mrb_crypto_key_iv_ary, MRB_ARGS_REQ(1));
  DONE;
}

void mrb_mruby_crypto_gem_final(mrb_state *mrb)
{
}
