#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>


int int_to_roman(int n, char *roman) {
    if (n <= 0 || n > 3999 || !roman) return 1;
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
    if (!buf || buf_size == 0) return 1;


    unsigned int fib[100]; 
    fib[0] = 1; fib[1] = 2;
    int len = 2;
    while (len < 100 && fib[len - 1] <= n) {
        fib[len] = fib[len - 1] + fib[len - 2];
        if (fib[len] > n) break;
        len++;
    }

    char temp[100];
    char* tmp = temp + sizeof(temp) - 1;
    *tmp-- = '\0';
    *tmp-- = '1';
    for (int i = len - 1; i >= 0; --i) {
        if (n >= fib[i]) {
            *tmp-- = '1';
            n -= fib[i];
        } else {
            *tmp-- = '0';
        }
    }
    *tmp++;
    if (strlen(tmp) + 1 > buf_size) return 2;
    strcpy(buf, tmp);
    return 0;
}

int val_in_base(int number, int base, char* buf, size_t buf_size, int upper) {
    if (!buf || buf_size == 0) return 1;

    char *p = buf + buf_size - 1;
    int r;

    *p-- = '\0';
    while (number) {
        r = number % base;
        if (r > 9) *p-- = r - 10 + (upper ? 'A' : 'a');
        else *p-- = r + '0';
        number /= base;
    }

    *p++;
    strcpy(buf, p);
    return 0;
}

int val_to_10(const char *str, int base, char *buf, size_t buf_size, int upper) {
    if (!str || !buf) return 1;

    char *p = (char*)str;
    int sign = 1;
    long long result = 0;
    size_t count_digit = 0;
    if (*p == '-') {
        sign = -1;
        p++;
    }
    while (*p) {
        int digit;
        if (*p >= '0' && *p <= '9') digit = *p++ - '0';
        else if (*p >= 'A' && *p <= 'Z' && upper) digit = *p++ - 'A' + 10;
        else if (*p >= 'a' && *p <= 'z' && !upper) digit = *p++ - 'a' + 10;
        else return 2;
        if (result > (LLONG_MAX - (long long)digit) / (long long)base) return 3;
        result = result * (long long)base + (long long)digit;
        count_digit++;
    }

    if (count_digit + 1 > buf_size) return 4;
    snprintf(buf, buf_size, "%lld", result * sign);
    return 0;
}

int damp_memory(void *value, size_t val_size, char *buf, size_t buf_size) {
    if (!value || !buf || buf_size == 0) {
        return 1; 
    }

    unsigned char* bytes = (unsigned char*)value;
    for (size_t i = 0; i < val_size; ++i) {
        for (int bit = 7; bit >= 0; --bit) {
            *buf++ = ((bytes[i] >> bit) & 1) ? '1' : '0';
        }
        if (i < val_size - 1) *buf++ = ' ';
    }
    *buf = '\0';
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
            char buf[120] = {0};
            if (!zeckendorff(val, buf, sizeof(buf))) {
                strcpy(out_string, buf);
                out_string += strlen(buf);
            } else {
                strcpy(out_string, "?");
                out_string++;
            }
            f += 2;
        }
        else if (f[0] == 'C' && (f[1] == 'v' || f[1] == 'V')) {
            int val = va_arg(args, int);
            int base = va_arg(args, int);
            base = (base >= 2 && base <= 36) ? base : 10;
            int upper = (f[1] == 'v') ? 0 : 1;
            char buf[100];
            if (!val_in_base(val, base, buf, sizeof(buf), upper)) {
                strcpy(out_string, buf);
                out_string += strlen(buf);
            } else {
                strcpy(out_string, "?");
                out_string++;
            }
            f += 2;
        }
        else if ((f[0] == 't' && f[1] == 'o') || (f[0] == 'T' && f[1] == 'O')) {
            char *str_val = va_arg(args, char*);
            int base = va_arg(args, int);
            char buf[100];
            base = (base >= 2 && base <= 36) ? base : 10;
            int upper = (f[1] == 'o') ? 0 : 1;
            if (!val_to_10(str_val, base, buf, sizeof(buf), upper)) {
                strcpy(out_string, buf);
                out_string += strlen(buf);
            } else {
                strcpy(out_string, "?");
                out_string++;
            }
            f += 2;  
        }
        else if (f[0] == 'm' && (f[1] == 'i' || f[1] == 'u' || f[1] == 'd' || f[1] == 'f')) {
            char buf[256];

            if (f[1] == 'i') {
                int val = va_arg(args, int);
                damp_memory(&val, sizeof(val), buf, sizeof(buf));
            }
            else if (f[1] == 'u') {
                unsigned int val = va_arg(args, unsigned int);
                damp_memory(&val, sizeof(val), buf, sizeof(buf));
            }
            else if (f[1] == 'd') {
                double val = va_arg(args, double);
                damp_memory(&val, sizeof(val), buf, sizeof(buf));
            }
            else { 
            float val = (float)va_arg(args, double);
            damp_memory(&val, sizeof(val), buf, sizeof(buf));
            }

            strcpy(out_string, buf);
            out_string += strlen(buf);
            f += 2;
        }
        else {
            const char *spec_start = f - 1;
            const char *p = f;

            while (*p && !isalpha(*p) && *p != '%') p++;
            while (*p && strchr("diouxXfFeEgGaAcsSpn", *p)) {
                p++;
            }

            char spec_buf[64];
            size_t spec_len = p - spec_start;
            if (spec_len >= sizeof(spec_buf)) {
                *out_string++ = '%';
                f++;  
                continue;
            }
            memcpy(spec_buf, spec_start, spec_len);
            spec_buf[spec_len] = '\0';


            int n = vsprintf(out_string, spec_buf, args);
            if (n < 0) {
                *out_string = '\0';
                va_end(args);
                return -1;
            }

            out_string += n;
            f = p;
        }
    }
    va_end(args);
    *out_string = '\0';
    return (int)(out_string - str);
}

int overfprintf(FILE* stream, const char* format, ... ) {
    if (!stream || !format) return -1;

    va_list args;
    va_start(args, format);
    const char *f = format;
    int total_written = 0;

    while (*f) {
        if (*f != '%') {
            fputc(*f, stream);
            f++;
            continue;
        }

        f++;
        if (f[0] == 'R' && f[1] == 'o') {
            int val = va_arg(args, int);
            char roman[50] = {0};
            if (!int_to_roman(val, roman)) {
                int len = fprintf(stream, "%s", roman);
                if (len < 0) { va_end(args); return -1; }
                total_written += len;
            } else {
                fputc('?', stream);
                total_written++;
            }
            f += 2;
        } 
        else if (f[0] == 'Z' && f[1] == 'r') {
            unsigned int val = va_arg(args, unsigned int);
            char buf[120] = {0};
            if (!zeckendorff(val, buf, sizeof(buf))) {
                int len = fprintf(stream, "%s", buf);
                if (len < 0) { va_end(args); return -1; }
                total_written += len;
            } else {
                fputc('?', stream);
                total_written++;
            }
            f += 2;
        }
        else if (f[0] == 'C' && (f[1] == 'v' || f[1] == 'V')) {
            int val = va_arg(args, int);
            int base = va_arg(args, int);
            base = (base >= 2 && base <= 36) ? base : 10;
            int upper = (f[1] == 'v') ? 0 : 1;
            char buf[100];
            if (!val_in_base(val, base, buf, sizeof(buf), upper)) {
                int len = fprintf(stream, "%s", buf);
                if (len < 0) { va_end(args); return -1; }
                total_written += len;
            } else {
                fputc('?', stream);
                total_written++;
            }
            f += 2;
        }
        else if ((f[0] == 't' && f[1] == 'o') || (f[0] == 'T' && f[1] == 'O')) {
            char *str_val = va_arg(args, char*);
            int base = va_arg(args, int);
            char buf[100];
            base = (base >= 2 && base <= 36) ? base : 10;
            int upper = (f[1] == 'o') ? 0 : 1;
            if (!val_to_10(str_val, base, buf, sizeof(buf), upper)) {
                int len = fprintf(stream, "%s", buf);
                if (len < 0) { va_end(args); return -1; }
                total_written += len;
            } else {
                fputc('?', stream);
                total_written++;
            }
            f += 2;  
        }
        else if (f[0] == 'm' && (f[1] == 'i' || f[1] == 'u' || f[1] == 'd' || f[1] == 'f')) {
            char buf[256];

            if (f[1] == 'i') {
                int val = va_arg(args, int);
                damp_memory(&val, sizeof(val), buf, sizeof(buf));
            }
            else if (f[1] == 'u') {
                unsigned int val = va_arg(args, unsigned int);
                damp_memory(&val, sizeof(val), buf, sizeof(buf));
            }
            else if (f[1] == 'd') {
                double val = va_arg(args, double);
                damp_memory(&val, sizeof(val), buf, sizeof(buf));
            }
            else { 
            float val = (float)va_arg(args, double);
            damp_memory(&val, sizeof(val), buf, sizeof(buf));
            }

            int len = fprintf(stream, "%s", buf);
            if (len < 0) { va_end(args); return -1; }
            total_written += len;
            f += 2;
        }
        else {
            const char *spec_start = f - 1;
            const char *p = f;

            while (*p && !isalpha(*p) && *p != '%') p++;
            while (*p && strchr("diouxXfFeEgGaAcsSpn", *p)) {
                p++;
            }

            char spec_buf[64];
            size_t spec_len = p - spec_start;
            if (spec_len >= sizeof(spec_buf)) {
                fputc('%', stream);
                total_written++;
                f++;  
                continue;
            }
            memcpy(spec_buf, spec_start, spec_len);
            spec_buf[spec_len] = '\0';


            int n = vfprintf(stream, spec_buf, args);
            if (n < 0) {
                va_end(args);
                return -1;
            }

            total_written += n;
            f = p;
        }
    }
    va_end(args);
    return total_written;
}