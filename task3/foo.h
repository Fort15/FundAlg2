#ifndef FOO_H
#define FOO_H

#include <stddef.h>
#include <stdio.h>


int overfprintf(FILE* stream, const char* format, ... );
int oversprintf(char *str, const char *format, ...);
int int_to_roman(int n, char *roman);
int zeckendorff(unsigned int n, char *buf, size_t buf_size);
int val_in_base(int number, int base, char* buf, size_t buf_size, int upper);
int val_to_10(const char *str, int base, char *buf, size_t buf_size, int upper);

#endif