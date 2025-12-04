#include <stdio.h>
#include <stdlib.h>
#include "foo.h"  
#include <string.h>

int main() {
    FILE *f = fopen("test.txt", "r");
    if (!f) {
        perror("fopen test.txt");
        return 1;
    }

    int x;
    double d;
    int roman_val;
    char str[64];
    int base_val;
    unsigned int zeck_val;
    long long big;

    printf("Чтение из test.txt: ");
    int cnt = overfscanf(f, "%d %lf %Ro %s %Cv %Zr %lld",
                         &x, &d, &roman_val, str, &base_val, 16, &zeck_val, &big);

    fclose(f);

    printf("Прочитано %d аргументов\n", cnt);
    // if (cnt != 7) {
    //     printf("ОШИБКА: ожидалось 7 аргументов, получено %d\n", cnt);
    //     return 0;
    // }

    if (x != 25) {
        printf("x = %d, ожидалось 25\n", x);
        return 1;
    }
    if (d < 3.141591 || d > 3.141593) {
        printf("d = %.6f, ожидалось ~3.141592\n", d);
        return 1;
    }
    if (roman_val != 4) {
        printf("roman = %d (IV), ожидалось 4\n", roman_val);
        return 1;
    }
    if (strcmp(str, "zxcghoul") != 0) {
        printf("str = %s, ожидалось zxcghoul\n", str);
        return 1;
    }
    if (base_val != 255) {
        printf("base_val = %d, ожидалось 255\n", base_val);
        return 1;
    }
    if (zeck_val != 12) {
        printf("zeck = %u (101), ожидалось 12\n", zeck_val);
        return 1;
    }
    if (big != 123456789012345LL) {
        printf("big = %lld, ожидалось 123456789012345\n", big);
        return 1;
    }

    printf("x = %d\n", x);
    printf("d = %.6f\n", d);
    printf("roman (IV) = %d\n", roman_val);
    printf("str = %s\n", str);
    printf("base_val (16) = %d\n", base_val);
    printf("zeck = %u\n", zeck_val);
    printf("big = %lld\n", big);

    return 0;
}