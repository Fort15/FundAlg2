#include "foo.h"
#include <stdio.h>

int main() {
    printf("=== TESTING OVERSSCANF ===\n\n");
    char input[] = "  MMMCMXCIX    III IX ";
    int x, y, z;
    oversscanf(input, "%Ro %Ro %Ro %Ro", &x, &y, &z);
    printf("3999 = %d, 3 = %d, 9 = %d\n", x, y, z);

    unsigned int ux, uy, uz;
    oversscanf("00101000011 001001011 1000001011", "%Zr %Zr %Zr", &ux, &uy, &uz);
    printf("100 = %u, 50 = %u, 77 = %u\n", ux, uy, uz);

    int a, b, c, d;
    oversscanf("123 ff 221 FFA", "%Cv %Cv %Cv %CV", &a, 8, &b, 16, &c, 3, &d, 16);
    printf("83 = %d, 255 = %d, 25 = %d, 4090 = %d\n", a, b, c, d);
    putchar('\n');

    printf("=== TESTING OVERFSCANF===\n\n");
    int x2, y2, z2;
    int cnt;
    cnt = overfscanf(stdin, "%Ro %Ro %Ro", &x2, &y2, &z2);
    if (cnt != 3) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    printf("x2 = %d, y2 = %d, z2 = %d\n", x2, y2, z2);

    unsigned int ux2, uy2, uz2;
    cnt = overfscanf(stdin, "%Zr %Zr %Zr", &ux2, &uy2, &uz2);
    if (cnt != 3) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    printf("ux2 = %u, uy2 = %u, uz2 = %u\n", ux2, uy2, uz2);

    int a2, b2, c2, d2;
    cnt = overfscanf(stdin, "%Cv %Cv %Cv %CV", &a2, 8, &b2, 16, &c2, 3, &d2, 16);
    if (cnt != 4) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    printf("a2 = %d, b2 = %d, c2 = %d, d2 = %d\n", a2, b2, c2, d2);
    putchar('\n');
    return 0;
}