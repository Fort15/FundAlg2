#ifndef FOO_H
#define FOO_H

#include <stdio.h>

#define BUF_SIZE 256

typedef enum {
    STATUS_OK,
    STATUS_SAME_FILES,
    STATUS_ERROR_MEMORY,
} Status;


Status same_files(const char *file1, const char *file2);
Status copy_file1_to_file2(FILE *in, FILE *out);


#endif