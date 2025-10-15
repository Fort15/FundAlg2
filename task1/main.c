#include <stdio.h>
#include <stdarg.h>
#include "functions.h"

int main() {
    double a = 0.5, b = 0.1, c = 0.25, d = 0.3333333, e = 0.166;
    int n = 5;
    int base = 10;
    printf("==============TASK1==============\n\n");
    printf("base = %d, n = %d, a = %lf, b = %lf, c = %lf, d = %lf, e = %lf\n", base, n, a, b, c, d, e);
    printf("Количество чисел с конечной записью в base = %d\n\n", count_infinity_presentation(base, n, a, b, c, d, e));

    base = 2;
    n = 3;
    printf("base = %d, n = %d, b = %lf, d = %lf, e = %lf\n", base, n, b, d, e);
    printf("Количество чисел с конечной записью в base = %d\n\n", count_infinity_presentation(base, n, b, d, e));

    // a2 = 0.1, b2 = 0.0(0011), c2 = 0.01, d2 = 0.(01), e2 inf

    base = 8;
    n = 4;
    printf("base = %d, n = %d, a = %lf, b = %lf, d = %lf, e = %lf\n", base, n, a, b, d, e);
    printf("Количество чисел с конечной записью в base = %d\n\n", count_infinity_presentation(base, n, a, b, d, e));

    // a8 = 0.4, b8 = 0.(6314) , c8 = 0.2, d8 = 0.2(5217), e8 = 0.1(2473) 

    base = 16;
    n = 5;
    printf("base = %d, n = %d, a = %lf, b = %lf, c = %lf, d = %lf, e = %lf\n", base, n, a, b, c, d, e);
    printf("Количество чисел с конечной записью в base = %d\n\n", count_infinity_presentation(base, n, a, b, c, d, e));

    // a16 = 0.8, b16 = 0.(19), c16 = 0.4, d16 = 0.5(5A), e16 = 0.2(A7)
    return 0;
}