#include "foo.h"
#include <stdio.h>

int main() {
    // OVERSSCANF STANDARD FLAGS
    char in[] = "25 3.141592 IV zxcghoul     ffff   23423432423";
    int x1, y1, tmp;
    long long l1;
    double f1;
    char xd[12];
    oversscanf(in, "%d %lf %Ro %s %Cv %lld", &x1, &f1, &y1, xd, &tmp, 16, &l1);
    printf("25 = %d, 3.141592 = %f, 4 = %d, zxcghoul = %s, 65535 = %d,23423432423 = %lld\n", x1, f1, y1, xd, tmp, l1);


    // OVERFSCANF STANDARD FLAGS
    int xx, yy, ttmp;
    long long l2;
    double f2;
    char xd2[12];
    int cntt;
    printf("int double Roman string Cv(ff) long long\n");
    cntt = overfscanf(stdin, "%d %lf %Ro %s %Cv %lld", &xx, &f2, &yy, xd2, &ttmp, 16, &l2);
    if (cntt != 6) {
        printf("Неправильный ввод, очистка буфера\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    else {
        printf("xx = %d, f2 = %f, yy = %d, xd2 = %s, ttmp = %d, l2 = %lld\n", xx, f2, yy, xd2, ttmp, l2);
    }


    // OVERSSCANF
    printf("=== TESTING OVERSSCANF ===\n\n");
    char input[] = "  MMMCMXCIX    III IX ";
    int x, y, z;
    oversscanf(input, "%Ro %Ro %Ro", &x, &y, &z);
    printf("3999 = %d, 3 = %d, 9 = %d\n", x, y, z);

    unsigned int ux, uy, uz;
    oversscanf("00101000011 001001011 1000001011", "%Zr %Zr %Zr", &ux, &uy, &uz);
    printf("100 = %u, 50 = %u, 77 = %u\n", ux, uy, uz);

    int a, b, c, d;
    oversscanf("123 ff 221 FFA", "%Cv %Cv %Cv %CV", &a, 8, &b, 16, &c, 3, &d, 16);
    printf("83 = %d, 255 = %d, 25 = %d, 4090 = %d\n", a, b, c, d);
    putchar('\n');


    // OVERFSCANF

    // XIII = 13 XLI = 41 DXXX = 530
    printf("=== TESTING OVERFSCANF===\n\n");
    int x2, y2, z2;
    int cnt;
    cnt = overfscanf(stdin, "%Ro %Ro %Ro", &x2, &y2, &z2);
    if (cnt != 3) {
        printf("Неправильный ввод, очистка буфера\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    else {
        printf("x2 = %d, y2 = %d, z2 = %d\n", x2, y2, z2);
    }

    // 00101000011 = 100 001001011 = 50 1000001011 = 77
    unsigned int ux2, uy2, uz2;
    cnt = overfscanf(stdin, "%Zr %Zr %Zr", &ux2, &uy2, &uz2);
    if (cnt != 3) {
        printf("Неправильный ввод, очистка буфера\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    else {
        printf("ux2 = %u, uy2 = %u, uz2 = %u\n", ux2, uy2, uz2);
    }

    // 123 = 83 ff = 255 221 = 25 FFA = 4090
    int a2, b2, c2, d2;
    cnt = overfscanf(stdin, "%Cv %Cv %Cv %CV", &a2, 8, &b2, 16, &c2, 3, &d2, 16);
    if (cnt != 4) {
        printf("Неправильный ввод, очистка буфера\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    else {
        printf("a2 = %d, b2 = %d, c2 = %d, d2 = %d\n", a2, b2, c2, d2);
    }
    putchar('\n');
    return 0;
}