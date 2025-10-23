#include <stdio.h>
#include "foo.h"

int main(void) {
    // memchr
    const char data[] = "Hello, world!";
    void *p = memchr(data, 'w', sizeof(data));
    if (p) {
        printf("memchr: найден символ 'w' по адресу %p\n", p);
    } else {
        printf("memchr: символ не найден\n");
    }

    // memcmp
    const char a[] = "abc";
    const char b[] = "abd";
    int cmp = memcmp(a, b, 3);
    printf("memcmp(\"abc\", \"abd\", 3) = %d\n", cmp);

    // memcpy
    char dest[20];
    memcpy(dest, "Hello, world!", 8);
    printf("memcpy: %s\n", dest);

    // memset
    memset(dest, '-', 5);
    printf("memset: %s\n", dest);

    // strncat
    char buf[50] = "Hello";
    strncat(buf, " World", 6);
    printf("strncat: %s\n", buf);

    // strchr
    char *pos = strchr("GoodBye, World!", ',');
    if (pos) {
        printf("strchr: первый ',' найден, остаток строки: %s\n", pos);
    }

    // strncmp
    int scmp = strncmp("apple", "apples", 5);
    printf("strncmp(\"apple\", \"apples\", 5) = %d\n", scmp);

    // strncpy
    char dst[10];
    strncpy(dst, "123456789", 9);
    dst[9] = '\0';
    printf("strncpy: %s\n", dst);

    // strcspn
    size_t span = strcspn("hello123", "0123456789");
    printf("strcspn: длина до цифры = %zu\n", span);

    // strlen
    size_t len = strlen("example");
    printf("strlen(\"example\") = %zu\n", len);

    // strpbrk
    char *brk = strpbrk("hello world", "owr");
    if (brk) {
        printf("strpbrk: первый совпадающий символ -> '%c'\n", *brk);
    }

    // strrchr
    char *str = "banana";
    char *last = strrchr(str, 'a');
    if (last) {
        printf("strrchr: последний 'a' -> позиция %ld\n", last - str);
    }

    // strstr
    char *found = strstr("hello goodbye privet poka", "privet");
    if (found) {
        printf("strstr: %s\n", found);
    }

    // strtok
    char text[] = "red,green;blue";
    char *token = strtok(text, ",;");
    printf("strtok: токены -> ");
    while (token) {
        printf("[%s] ", token);
        token = strtok(NULL, ",;");
    }
    printf("\n");

    return 0;
}