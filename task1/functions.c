#include "functions.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>


long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int find_denominator(double number, double eps, long long *denominator, long long *numerator) {
    if (number <= 0 || number >= 1) return 1;

    double tmp = number;
    int n = 0;

    while (fabs(tmp - round(tmp)) >= eps) {
        if (n == 20) return 1;
        tmp *= 10;
        ++n;
    }

    long long power = 1;
    for (int i = 0; i < n; i++) {
        power *= 10;
    }

    *denominator = power;
    *numerator = (long long)round(number * power);
    return 0;
}

int have_infinity_presentation(int base, double number) {
    long long denominator, numerator;
    int status = find_denominator(number, EPS, &denominator, &numerator);
    if (status) return 0;
    // printf("%lld / %lld\t", numerator, denominator);
    long long nod = gcd(numerator, denominator);
    // printf("%lld\n", nod);
    denominator /= nod;
    long long tmp = denominator;
    for (long long i = 2; i * i <= tmp; ++i) {
        if (tmp % i == 0) {
            if (base % i == 0) {
                while (tmp % i == 0) tmp /= i;
            } else return 0;
        }
    } 
    
    if (tmp > 1) {
        if (base % tmp != 0) {
            return 0;
        }
    }
    
    return 1;
}

int count_infinity_presentation(int base, int n, ...) {
    va_list factor;
    va_start(factor, n);
    int a = 0;
    while (n--) {
        double temp = va_arg(factor, double);
        a += have_infinity_presentation(base, temp);
    }
    va_end(factor);
    return a;
}