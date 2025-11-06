#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include "student.h"
#include <string.h>
#include <limits.h>

int validate_string(char *buf, size_t buf_size) {
    if (!fgets(buf, buf_size, stdin)) {
        printf("Ошибка чтения ввода.\n");
        return 0; 
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0'; 
    } else {
        printf("Ошибка: ввод слишком длинный.\n");
        int c;
        while ((c = fgetc(stdin)) != '\n' && c != EOF) {}
        return 0;
    }

    if (strlen(buf) == 0) {
        printf("Ошибка: строка пуста.\n");
        return 0;
    }

    return 1; 
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Неверное число аргументов.\n");
        return 0;
    }

    const char *input_file = argv[1];
    const char *trace_file = argv[2];

    int output_exists = (access(argv[2], F_OK) == 0);
    if (output_exists) {
        Status same_status = same_files(input_file, trace_file);
        if (same_status == STATUS_SAME_FILES) {
            printf("Ошибка: входной и выходной файлы совпадают, риск затирания данных.\n");
            return 0;
        }
    }

    Student *students = NULL;
    size_t count = 0;
    Status status = load_students(input_file, &students, &count);
    if (status != STATUS_OK) {
        printf("Проблема при чтении данных в файле.\n");
        return 0;
    }

    int choice = -1;
    do {
        printf("0.Выход, 1.Поиск по ID и вывод данных в трассировочный файл, 2.Поиск по имени/фамилии/группе, 3.Сортировка по ID, "
            "4.Сортировка по фамилии, 5.Сортировка по имени, 6.Сортировка по группе, " 
            "7.Вывести имена и фамилии студентов в трассировочный файл чей средний балл выше среднего по всем студентам\n");

        char input[16];
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Ошибка чтения ввода.\n");
            break;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) != 1) {
            printf("Неправильное число, попробуйте ещё раз.\n");
            continue;
        }
        else if (sscanf(input, "%d", &choice) != 1) {
            printf("Неверный ввод.\n");
            continue;
        }
        
        switch (choice) {
        case 1: {
            printf("Введите ID студента.\n");
            char input[32];
            if (!validate_string(input, sizeof(input))) {
                printf("Введено слишком большое число.\n");
                return 0; 
            }

            unsigned int id;
            Status status = stroka_to_uint(input, &id);
            if (status != STATUS_OK) {
                printf("Неправильно введено число.\n");
                return 0;
            }

            Student *student = find_student_by_id(students, count, id);
            if (student) {
                status = write_info_to_trace_file(student, trace_file);
                if (status == STATUS_OK) {
                    printf("Данные студента записаны в трассировочный файл.\n");
                } else {
                    printf("Ошибка записи в трассировочный файл.\n");
                }
            } else {
                printf("Студент с ID: %u не найден.\n", id);
            }
            break;
        }
        case 2: {
            printf("Введите поле для поиска (name/surname/group):\n");
            char field[10];
            if (!validate_string(field, sizeof(field))) {
                break;
            }

            if (strcmp(field, "name") != 0 && strcmp(field, "surname") != 0 && strcmp(field, "group") != 0) {
                printf("Разрешены: name, surname, group.\n");
                break;
            }

            char value[128];
            printf("Введите значение:\n");
            if (!validate_string(value, sizeof(value))) {
                printf("Неправильный ввод.\n");
                break;
            }

            Student *results = NULL;
            size_t needed_students = 0;
            find_students_by_string(students, count, field, value, &needed_students, &results);

            if (results) {
                printf("Найдено %zu студентов:\n", needed_students);
                for (size_t i = 0; i < needed_students; ++i) {
                    printf("ID: %u, Имя: %s, Фамилия: %s, Группа: %s\n",
                            results[i].id, results[i].name, results[i].surname, results[i].group);
                }
                free(results);
            } else {
                printf("Студенты не найдены.\n");
            }
            break;
        }
        case 3: {
            qsort(students, count, sizeof(Student), compare_by_id);
            printf("Отсортировано по ID.\n");
            break;
        }
        case 4: {
            qsort(students, count, sizeof(Student), compare_by_surname);
            printf("Отсортировано по фамилии.\n");
            break;
        }
        case 5: {
            qsort(students, count, sizeof(Student), compare_by_name);
            printf("Отсортировано по имени.\n");
            break;
        }
        case 6: {
            qsort(students, count, sizeof(Student), compare_by_group);
            printf("Отсортировано по группе.\n");
            break;
        }
        case 7: {
            status = write_score_info_to_trace_file(students, count, trace_file);
            if (status == STATUS_OK) {
                printf("Студенты с баллом выше среднего записаны в трассировочный файл.\n");
            } else {
                printf("Ошибка записи в трассировочный файл.\n");
            }
            break;
        }
        case 0: {
            printf("=== Завершение программы === \n");
            break;
        }
        default: {
            printf("Нет такого действия.\n");
            break;
        }
        }
    } while (choice);

    free(students);
    return 0;
}