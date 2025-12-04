#include "foo.h"
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

int vsscanf_one_arg(const char *s, const char *fmt, void *arg) {
    return _vsscanf_one(s, fmt, arg);
}

int _vsscanf_one(const char *s, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int r = vsscanf(s, fmt, ap);
    va_end(ap);
    return r;
}

int roman_val(char c) {
    if (c == 'I') return 1;
    if (c == 'V') return 5;
    if (c == 'X') return 10;
    if (c == 'L') return 50;
    if (c == 'C') return 100;
    if (c == 'D') return 500;
    if (c == 'M') return 1000;

    return 0;
}

int roman_to_int(const char *roman, int *result) {
    if (!roman || !result) return 1;
    int res = 0;    
    int n = strlen(roman);
    for (int i = 0; i < n; ++i) {
        int s1 = roman_val(roman[i]);
        if (!s1) return 2;
        if (i + 1 < n) {
            int s2 = roman_val(roman[i + 1]);
            if (!s2) return 2;
            if (s1 >= s2) {
                res += s1;
            } else {
                res += s2 - s1;
                ++i;
            }
        } else {
            res += s1;
        }
    }
    *result = res;
    return 0;
}

int zeckendorff(const char *string, size_t len, unsigned int *result) {
    if (!string || !result || len == 0)  return 1;
    if (string[--len] != '1') return 2; 

    unsigned int res = 0;
    unsigned int fib[48];
    fib[0] = 1; fib[1] = 2;
    for (size_t i = 2; i < len; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    
    for (size_t index = 0; index < len; ++index) {
        if (string[index] == '1') {
            if (UINT_MAX - res < fib[index]) {
                return 3; 
            }
            res += fib[index];
        }
    }

    *result = res;
    return 0;
}

int str_to_int_base(const char *str, int base, int *result, int upper) {
    if (!str || !result) return 1;

    long long val = 0;
    int sign = 1;
    const char *p = str;

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
        if (digit >= base) return 4;
        if (val > (LLONG_MAX - (long long)digit) / (long long)base) return 3;
        val = val * (long long)base + (long long)digit;
    }

    long long final_val = val * sign;
    
    if (final_val > INT_MAX || final_val < INT_MIN) return 3;

    *result = (int)final_val;
    return 0; 
}


int oversscanf(const char *str, const char *format, ...) {
    if (!str || !format) return 0;

    va_list args;
    va_start(args, format);

    const char *s = str;          
    const char *f = format;  
    int count = 0;                

    while (*f) {
        if (*f != '%') {
            if (*f == *s) {
                s++;
                f++;
                continue;
            } else {
                break;
            }  
        }

        f++;

        if (f[0] == 'R' && f[1] == 'o') {
            int *ptr = va_arg(args, int*);
            if (!ptr) {
                break;
            }

            while (*s == ' ' || *s == '\t') s++;

            const char* start = s;
            while (*s && strchr("MDCLXVI", *s)) {
                s++;
            }

            if (start == s) {   
                break;
            }

            char buf[32];
            size_t len = s - start;
            if (len >= sizeof(buf)) {
                break; 
            }
            strncpy(buf, start, len);
            buf[len] = '\0';

            int value;
            if (roman_to_int(buf, &value) == 0) {
                *ptr = value; 
                count++;
            } else {
                break; 
            }

            f += 2;
        }
        else if (f[0] == 'Z' && f[1] == 'r') {
            unsigned int *ptr = va_arg(args, unsigned int*);
            if (!ptr) {
                break;
            }

            while (*s == ' ' || *s == '\t') s++;

            const char* start = s;
            while (*s && strchr("01", *s)) {
                s++;
            }

            if (start == s) {   
                break;
            }

            char buf[60];
            size_t len = s - start;
            if (len >= sizeof(buf)) {
                break; 
            }
            strncpy(buf, start, len);
            buf[len] = '\0';
            unsigned int value;
            if (zeckendorff(buf, strlen(buf), &value) == 0) {
                *ptr = value; 
                count++;
            } else {
                break; 
            }

            f += 2;
        }
        else if (f[0] == 'C' && (f[1] == 'V' || f[1] == 'v')) {
            int upper = (f[1] == 'v') ? 0 : 1;
            int *ptr = va_arg(args, int*);
            int base = va_arg(args, int);
            base = (base >= 2 && base <= 36) ? base : 10;
            if (!ptr) {
                break;
            }

            while (*s == ' ' || *s == '\t') s++;

            const char* start = s;
            while (*s && ((*s >= '0' && *s <= '9') || 
                  (*s >= 'a' && *s <= 'z' && !upper) || (*s >= 'A' && *s <= 'Z' && upper))) {
                    s++;
            }

            if (start == s) {   
                break;
            }
            
            char buf[100];
            size_t len = s - start;
            if (len >= sizeof(buf)) break;
            strncpy(buf, start, len);
            buf[len] = '\0';

            int value;
            if (str_to_int_base(buf, base, &value, upper) == 0) {
                *ptr = value;
                ++count;
            } else break;

            f += 2;
        }
        else {
            const char *spec_start = f - 1;
            const char *p = f;
            while (*p && !isspace(*p) && *p != '%') p++;

            while (*s && isspace(*s)) s++;
            const char *arg_start = s;
            while (*s && !isspace(*s)) s++;

            char spec_buf[32], arg_buf[128];
            int spec_len = p - spec_start;
            int arg_len = s - arg_start;
            if (spec_len < sizeof(spec_buf) && arg_len < sizeof(arg_buf)) {
                strncpy(spec_buf, spec_start, spec_len);
                spec_buf[spec_len] = '\0';
                strncpy(arg_buf, arg_start, arg_len);
                arg_buf[arg_len] = '\0';

                
                int matched = vsscanf(arg_buf, spec_buf, args);
                (void)va_arg(args, void*);

                if (matched > 0) count += matched;
            }

            f = p;
        }
    }
    va_end(args);
    return count;
}

int overfscanf(FILE *stream, const char *format, ...) {
    if (!stream || !format) {
        return 0;
    }

    va_list args;
    va_start(args, format);
    const char *f = format;
    int count = 0;

    while (*f) {
        if (*f != '%') {
            int c = fgetc(stream);
            if (c == EOF || c != (unsigned char)*f) {
                if (c != EOF) ungetc(c, stream);
                break;
            }
            f++;
            continue;
        }

        f++;

        if (f[0] == 'R' && f[1] == 'o') {
            int *ptr = va_arg(args, int*);
            if (!ptr) break;


            int c;
            while ((c = fgetc(stream)) != EOF && isspace(c)) {}


            char buf[32];
            int i = 0;
            while (c != EOF && i < 31) {
                if (c == 'M' || c == 'D' || c == 'C' ||
                    c == 'L' || c == 'X' || c == 'V' || c == 'I') {
                    buf[i++] = (char)c;
                } else {
                    if (c != EOF) ungetc(c, stream);
                    break;
                }
                c = fgetc(stream);
            }

            if (i == 0) break;

            buf[i] = '\0';
            int value;
            if (roman_to_int(buf, &value) == 0) {
                *ptr = value;
                count++;
            } else {
                break;
            }
            f += 2;
        }
        else if (f[0] == 'Z' && f[1] == 'r') {
            unsigned int *ptr = va_arg(args, unsigned int*);
            if (!ptr) break;

            int c;
            while ((c = fgetc(stream)) != EOF && isspace(c)) { }

            char buf[64];
            int i = 0;
            while (c != EOF && i < 63) {
                if (c == '0' || c == '1') {
                    buf[i++] = (char)c;
                } else {
                    if (c != EOF) ungetc(c, stream);
                    break;
                }
                c = fgetc(stream);
            }

            if (i == 0) break;

            buf[i] = '\0';
            unsigned int value;
            if (zeckendorff(buf, i, &value) == 0) {
                *ptr = value;
                count++;
            } else {
                break;
            }
            f += 2;
        }
        else if (f[0] == 'C' && (f[1] == 'V' || f[1] == 'v')) {
            int *ptr = va_arg(args, int*);
            int base = va_arg(args, int);
            base = (base >= 2 && base <= 36) ? base : 10;
            int upper = (f[1] == 'v') ? 0 : 1;

            int c;
            while ((c = fgetc(stream)) != EOF && isspace(c)) { }

            char buf[65];
            int i = 0;
            while (c != EOF && i < 64) {
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' && !upper)
                    || (c >= 'A' && c <= 'Z' && upper)) {
                    buf[i++] = (char)c;
                } else {
                    if (c != EOF) ungetc(c, stream);
                    break;
                }
                c = fgetc(stream);
            }

            if (i == 0) break;

            buf[i] = '\0';
            int value;
            if (str_to_int_base(buf, base, &value, upper) == 0) {
                *ptr = value;
                count++;
            } else {
                break;
            }
            f += 2;
        }
        else {
            const char *spec_start = f - 1;
            const char *p = f;

            while (*p && !isspace(*p) && *p != '%') p++;

            char spec_buf[32];
            size_t len = p - spec_start;
            if (len >= sizeof(spec_buf)) {
                f++;
                continue;
            }
            strncpy(spec_buf, spec_start, len);
            spec_buf[len] = '\0';

            int matched = vfscanf(stream, spec_buf, args);
            if (matched <= 0) break;
            count += matched;
            (void)va_arg(args, void*);
            f = p;
        }
    }

    va_end(args);
    return count;
}