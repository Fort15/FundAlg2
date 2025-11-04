#include "foo.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("=== OVERSPRINTF ===\n\n");
    printf("=== TEST Ro ===\n");
    char buffer[256];
    if (oversprintf(buffer, "1999 (MCMXCIX) = %Ro, 0 = %Ro, 49 (XLIX) = %Ro", 1999, 0, 49)) {
        printf("%s\n\n", buffer);
    }

    printf("=== TEST Zr ===\n");
    char buffer2[256];
    if (oversprintf(buffer2, "100 (00101000011) = %Zr, 50 (001001011) = %Zr, 77 (1000001011) = %Zr", 100u, 50u, 77u)) {
        printf("%s\n\n", buffer2);
    }

    printf("=== TEST Cv ===\n");
    char buffer3[256];
    if (oversprintf(buffer3, "255 in 16 (ff) = %Cv, 15 in 2 (1111) = %Cv, 1234 in 37 (1234) = %Cv", 255, 16, 15, 2, 1234, 37)) {
        printf("%s\n\n", buffer3);
    }

    printf("=== TEST CV ===\n");
    char buffer4[256];
    if (oversprintf(buffer4, "255 in 16 (FF) = %CV, 15 in 2(1111) = %CV, 1234 in 37 (1234) = %CV", 255, 16, 15, 2, 1234, 37)) {
        printf("%s\n\n", buffer4);
    }

    printf("=== TEST to ===\n");
    char buffer5[256];
    if (oversprintf(buffer5, "123 in 8 (83) = %to, ff in 16 (255) = %to, 221 in 3 (25) = %to", "123", 8, "ff", 16, "221", 3)) {
        printf("%s\n\n", buffer5);
    }

    printf("=== TEST TO ===\n");
    char buffer6[256];
    if (oversprintf(buffer6, "AAA in 16 (2730) = %TO, FF in 16 (255) = %TO, ABC in 13 (1845) = %TO", "AAA", 16, "FF", 16, "ABC", 13)) {
        printf("%s\n\n", buffer6);
    }

    printf("=== TEST mi/md/mf/mu ===\n");
    int i = 42;
    unsigned int u = 123;
    float f = 3.14f;
    double d = 3.1415;
    char buffer7[256];
    if (oversprintf(buffer7, "i42 = %mi, u123 = %mu, f3.14 = %mf, d3.1415 = %md", i, u, f, d)) {
        printf("%s\n\n", buffer7);
    }


    printf("=== OVERFPRINTF ===\n\n");
    printf("=== TEST Ro ===\n");
    overfprintf(stdout, "1999 (MCMXCIX) = %Ro, 0 = %Ro, 49 (XLIX) = %Ro\n", 1999, 0, 49); 

    printf("=== TEST Zr ===\n");
    overfprintf(stdout, "100 (00101000011) = %Zr, 50 (001001011) = %Zr, 77 (1000001011) = %Zr\n", 100u, 50u, 77u);

    printf("=== TEST Cv ===\n");
    overfprintf(stdout, "255 in 16 (ff) = %Cv, 15 in 2 (1111) = %Cv, 1234 in 37 (1234) = %Cv\n", 255, 16, 15, 2, 1234, 37);

    printf("=== TEST CV ===\n");
    overfprintf(stdout, "255 in 16 (FF) = %CV, 15 in 2(1111) = %CV, 1234 in 37 (1234) = %CV\n", 255, 16, 15, 2, 1234, 37);

    printf("=== TEST to ===\n");
    overfprintf(stdout, "123 in 8 (83) = %to, ff in 16 (255) = %to, 221 in 3 (25) = %to\n", "123", 8, "ff", 16, "221", 3);

    printf("=== TEST TO ===\n");
    overfprintf(stdout, "AAA in 16 (2730) = %TO, FF in 16 (255) = %TO, ABC in 13 (1845) = %TO\n", "AAA", 16, "FF", 16, "ABC", 13);

    printf("=== TEST mi/md/mf/mu ===\n");
    overfprintf(stdout, "i42 = %mi, u123 = %mu, f3.14 = %mf, d3.1415 = %md\n", i, u, f, d);

    return 0;
}