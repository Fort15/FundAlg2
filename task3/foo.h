#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>


int oversprintf(char *str, const char *format, ...);
int int_to_roman(int n, char *roman);
int zeckendorff(unsigned int n, char *buf, size_t buf_size);

#endif