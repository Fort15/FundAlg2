#include <stdarg.h>
#include <string.h>


int int_to_roman(int n, char *roman) {
    if (n <= 0 || n > 3999) return 1;
    const int numbers[] = {
        1000, 900, 500, 400,
        100, 90, 50, 40,
        10, 9, 5, 4, 1
    };
    const char *roman_numbers[] = {
        "M", "CM", "D", "CD",
        "C", "XC", "L", "XL",
        "X", "IX", "V", "IV", "I"
    };

    int index = 0;
    int len_numbers = sizeof(numbers) / sizeof(numbers[0]);
    for(int i = 0; i < len_numbers; ++i) {
        while (n >= numbers[i]) {
            strcat(roman, roman_numbers[i]);
            n -= numbers[i];
        }
    }
    return 0;
}

int zeckendorff(unsigned int n, char *buf, size_t buf_size) {
    if (!buf || buf_size == 0) return -1;


    unsigned int fib[49]; 
    fib[0] = 0; fib[1] = 1;
    size_t len = 2;
    while (len < 49 && fib[len - 1] <= n) {
        fib[len] = fib[len - 1] + fib[len - 2];
        if (fib[len] > n) break;
        len++;
    }

    char temp[64];
    temp[63] = '\0';
    temp[62] = '1';
    size_t pos = 61;
    for (size_t i = len; i > 0; --i) {
        if (n >= fib[i]) {
            temp[pos--] = '1';
            n -= fib[i];
        } else {
            temp[pos--] = '0';
        }
    }
    strcpy(buf, temp);
    return 0;
}

int oversprintf(char *str, const char *format, ...) {
    if (!str || !format) return -1;

    va_list args;
    va_start(args, format);


    char *out_string = str;
    const char *f = format;

    while (*f) {
        if (*f != '%') {
            *out_string = *f;
            out_string++;
            f++;
            continue;
        }

        f++;

        if (f[0] == 'R' && f[1] == 'o') {
            int val = va_arg(args, int);
            char roman[50] = {0};
            if (!int_to_roman(val, roman)) {
                strcpy(out_string, roman);
                out_string += strlen(roman);
            } else {
                strcpy(out_string, "?");
                out_string++;
            }
            f += 2;
        } 
        else if (f[0] == 'Z' && f[1] == 'r') {
            unsigned int val = va_arg(args, unsigned int);
            char buf[100] = {0};
            if (!zeckendorff(val, buf, sizeof(buf)))
        }
    }
}