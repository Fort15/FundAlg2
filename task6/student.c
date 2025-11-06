#include "student.h"
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


Status stroka_to_uint(const char *stroka, unsigned int *chislo) {
    if (!stroka || !chislo) return STATUS_INVALID_NUMBER;

    char *endptr = NULL;
    long long x = strtol(stroka, &endptr, 10);

    if (*endptr != '\0') return STATUS_INVALID_NUMBER;  
    if (stroka == endptr) return STATUS_INVALID_NUMBER; 
    if (x < 0 || x > UINT_MAX) return STATUS_TOO_BIG_INT; 

    *chislo = (unsigned int)x;
    return STATUS_OK;
}

int is_valid_name(const char *name) {
    if (!name || *name == '\0') return 0;
    const char *p = name;
    while (*p) {
        if (!((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z'))) return 0;
        p++;
    }

    return 1;
}


Status same_files(const char *file1, const char *file2) {
    struct stat st1, st2;
    if (stat(file1, &st1) != 0) return STATUS_OK;    
    if (stat(file2, &st2) != 0) return STATUS_OK;    
    
    if ((st1.st_dev == st2.st_dev) && (st1.st_ino == st2.st_ino)) {
        return STATUS_SAME_FILES;
    }
    return STATUS_OK;
}

Status load_students(const char *filename, Student **students, size_t *count) {
    FILE *in = fopen(filename, "r");
    if (!in) return STATUS_FILE_ERROR;

    char line[512];
    int line_count = 0;
    while (fgets(line, sizeof(line), in)) {
        line_count++;
    }
    rewind(in);

    if (line_count <= 1) {
        fclose(in);
        return STATUS_INVALID_INPUT_FILE;
    }

    if (!fgets(line, sizeof(line), in)) {
        fclose(in);
        return STATUS_INVALID_INPUT_FILE;
    }
    line_count--;

    Student *array_of_students = malloc(line_count * sizeof(Student));
    if (!array_of_students) {
        fclose(in);
        return STATUS_MEMORY_ERROR;
    }

    int index = 0;
    while (fgets(line, sizeof(line), in)) {
        unsigned int id;
        char name[128], surname[128], group[64];
        unsigned char score1, score2, score3, score4, score5;
        if (sscanf(line, "%u,%127[^,],%127[^,],%63[^,],%hhu,%hhu,%hhu,%hhu,%hhu", &id, name, surname, group, 
            &score1, &score2, &score3, &score4, &score5) != 9) {
                free(array_of_students);
                fclose(in);
                return STATUS_INVALID_INPUT_FILE;
        }
        if (!is_valid_name(name) || !is_valid_name(surname) || strlen(group) == 0) {
            free(array_of_students);
            fclose(in);
            return STATUS_INVALID_INPUT_FILE;
        }
        array_of_students[index].id = id;
        strcpy(array_of_students[index].name, name);
        strcpy(array_of_students[index].surname, surname);
        strcpy(array_of_students[index].group, group);
        array_of_students[index].scores[0] = score1;
        array_of_students[index].scores[1] = score2;
        array_of_students[index].scores[2] = score3;
        array_of_students[index].scores[3] = score4;
        array_of_students[index].scores[4] = score5;

        index++;
    }

    *students = array_of_students;
    *count = index;
    fclose(in);
    return STATUS_OK;
}

Student* find_student_by_id(Student *students, size_t count, unsigned int id) {
    for (size_t i = 0; i < count; i++) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

Student* find_students_by_string(Student *students, size_t count, const char *string, const char *value, size_t *needed_students, Student **results) {
    *needed_students = 0;
    for (size_t i = 0; i < count; i++) {
        const char *string_val = NULL;
        if (strcmp(string, "name") == 0) string_val = students[i].name;
        else if (strcmp(string, "surname") == 0) string_val = students[i].surname;
        else if (strcmp(string, "group") == 0) string_val = students[i].group;
        else return NULL;

        if (strcmp(string_val, value) == 0) {
            Student *temp = realloc(*results, (*needed_students + 1) * sizeof(Student));
            if (!temp) return NULL;
            *results = temp;
            (*results)[(*needed_students)++] = students[i];
        }
    }
    return *results;
}


int compare_by_id(const void *s1, const void *s2) {
    const Student *student1 = (const Student*)s1;
    const Student *student2 = (const Student*)s2;
    if (student1->id < student2->id) return -1;
    if (student1->id > student2->id) return 1;
    return 0;
}

int compare_by_name(const void *s1, const void *s2) {
    const Student *student1 = (const Student*)s1;
    const Student *student2 = (const Student*)s2;
    return strcmp(student1->name, student2->name);
}

int compare_by_surname(const void *s1, const void *s2) {
    const Student *student1 = (const Student*)s1;
    const Student *student2 = (const Student*)s2;
    return strcmp(student1->surname, student2->surname);
}

int compare_by_group(const void *s1, const void *s2) {
    const Student *student1 = (const Student*)s1;
    const Student *student2 = (const Student*)s2;
    return strcmp(student1->group, student2->group);
}

Status write_info_to_trace_file(const Student *student, const char *trace_filename) {
    if (!student || !trace_filename) return STATUS_INVALID_INPUT;

    FILE *file = fopen(trace_filename, "a");
    if (!file) return STATUS_FILE_ERROR;

    double avg = (student->scores[0] + student->scores[1] + student->scores[2] + student->scores[3] + student->scores[4]) / 5.0;

    fprintf(file, "ID: %u, Имя: %s, Фамилия: %s, Группа: %s, Средний балл: %.2f\n",
            student->id, student->name, student->surname, student->group, avg);

    fclose(file);
    return STATUS_OK;
}

Status write_score_info_to_trace_file(Student *students, size_t count, const char *trace_filename) {
    if (!students || !trace_filename || count == 0) return STATUS_INVALID_INPUT;

    FILE *file = fopen(trace_filename, "a");
    if (!file) return STATUS_FILE_ERROR;

    double total_avg = 0.0;
    for (size_t i = 0; i < count; i++) {
        total_avg += (students[i].scores[0] + students[i].scores[1] + students[i].scores[2] + students[i].scores[3] + students[i].scores[4]) / 5.0;
    }
    total_avg /= count;
    fprintf(file, "Общий средний балл: %lf\n", total_avg);
    for (size_t i = 0; i < count; i++) {
        double avg = (students[i].scores[0] + students[i].scores[1] + students[i].scores[2] + students[i].scores[3] + students[i].scores[4]) / 5.0;
        if (avg > total_avg) {
            fprintf(file, "%s %s, Средний балл: %lf\n", students[i].surname, students[i].name, avg);
        }
    }

    fclose(file);
    return STATUS_OK;
}