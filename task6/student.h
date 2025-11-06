#ifndef STUDENT_H
#define STUDENT_H

#include <stddef.h>

typedef struct {
    unsigned int id;
    char name[128];
    char surname[128];
    char group[64];
    unsigned char scores[5];
} Student;

typedef enum {
    STATUS_OK,
    STATUS_SAME_FILES,
    STATUS_FILE_ERROR,
    STATUS_INVALID_INPUT_FILE,
    STATUS_MEMORY_ERROR,
    STATUS_INVALID_INPUT,
    STATUS_INVALID_NUMBER,
    STATUS_TOO_BIG_INT,
} Status;

Status stroka_to_uint(const char *stroka, unsigned int *chislo);
Status same_files(const char *file1, const char *file2);
Status load_students(const char *filename, Student **students, size_t *count);
int is_valid_name(const char *name);
Student* find_student_by_id(Student *students, size_t count, unsigned int id);
Student* find_students_by_string(Student *students, size_t count, const char *string, const char *value, size_t *matches_count, Student **results);
int compare_by_id(const void *s1, const void *s2);
int compare_by_name(const void *s1, const void *s2);
int compare_by_surname(const void *s1, const void *s2);
int compare_by_group(const void *s1, const void *s2);
Status write_info_to_trace_file(const Student *student, const char *trace_filename);
Status write_score_info_to_trace_file(Student *students, size_t count, const char *trace_filename);


#endif 