/*
** mrb_crypto.c - Crypto class
**
** Copyright (c) yang 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_crypto.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_crypto_data;

static const struct mrb_data_type mrb_crypto_data_type = {
  "mrb_crypto_data", mrb_free,
};

static mrb_value mrb_crypto_init(mrb_state *mrb, mrb_value self)
{
  mrb_crypto_data *data;
  char *str;
  int len;

  data = (mrb_crypto_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_crypto_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_crypto_data *)mrb_malloc(mrb, sizeof(mrb_crypto_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_crypto_hello(mrb_state *mrb, mrb_value self)
{
  mrb_crypto_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_crypto_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_crypto_gem_init(mrb_state *mrb)
{
  struct RClass *crypto;
  crypto = mrb_define_class(mrb, "Crypto", mrb->object_class);
  mrb_define_method(mrb, crypto, "initialize", mrb_crypto_init, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, crypto, "hello", mrb_crypto_hello, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, crypto, "hi", mrb_crypto_hi, MRB_ARGS_NONE());
  DONE;
}

void mrb_mruby_crypto_gem_final(mrb_state *mrb)
{
}

