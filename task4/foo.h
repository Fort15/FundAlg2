#ifndef FOO_H
#define FOO_H

#include <stdio.h>

int oversscanf(const char *str, const char *format, ...);
int overfscanf(FILE *stream, const char *format, ...);

int roman_to_int(const char *roman, int *result);
int zeckendorff(const char *string, size_t len, unsigned int *result);
int str_to_int_base(const char *str, int base, int *result, int upper);

#endif 