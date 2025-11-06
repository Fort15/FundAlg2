#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "foo.h"


int main() {
    char input_file[256];
    printf("Введите путь к входному файлу:\n");
    if (!fgets(input_file, sizeof(input_file), stdin)) {
        printf("Не удалось считать строку\n");
        return 0;
    }
    input_file[strcspn(input_file, "\n")] = '\0';


    char output_file[256];
    printf("Введите путь к выходному файлу:\n");
    if (!fgets(output_file, sizeof(output_file), stdin)) {
        printf("Не удалось считать строку\n");
        return 0;
    }
    output_file[strcspn(output_file, "\n")] = '\0';


    FILE *in = fopen(input_file, "r");
    if (!in) {
        printf("Не удалось открыть входной файл\n");
        return 0;
    }

    int output_exists = (access(output_file, F_OK) == 0);
    if (output_exists) {
        Status same_status = same_files(input_file, output_file);
        if (same_status == STATUS_SAME_FILES) {
            printf("Ошибка: входной и выходной файлы совпадают, риск затирания данных.\n");
            return 0;
        }
    }

    FILE *out = fopen(output_file, "w");
    if (!out) {
        printf("Не удалось открыть выходной файл\n");
        fclose(in);
        return 0;
    }

    Status status = copy_file1_to_file2(in, out);

    fclose(in);
    fclose(out);
    return 0;
}