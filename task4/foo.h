#ifndef FOO_H
#define FOO_H

#include <stdio.h>

int _vsscanf_one(const char *s, const char *fmt, ...);
int vsscanf_one_arg(const char *s, const char *fmt, void *arg);
int oversscanf(const char *str, const char *format, ...);
int overfscanf(FILE *stream, const char *format, ...);

int roman_to_int(const char *roman, int *result);
int zeckendorff(const char *string, size_t len, unsigned int *result);
int str_to_int_base(const char *str, int base, int *result, int upper);

#endif 