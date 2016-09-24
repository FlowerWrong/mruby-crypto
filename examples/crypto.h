#ifndef __CRYPTO__
#define __CRYPTO__

#define FILE_LENGTH_SIZE 4

// https://github.com/epintos/stenography/blob/master/src/crypto.c
int encrypt(const char *plain, int plain_size, char **encrypted, char **return_iv, const char *method, const char *pass, const char *salt);

#endif
