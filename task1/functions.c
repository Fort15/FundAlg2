#include "functions.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int find_denominator(double number, double eps, long long *denominator, long long *numerator) {
    if (!numerator || !denominator) {
        return 1;
    }


    long long a0 = floor(number);
    double frac = number - a0;

    if (fabs(frac) < eps) {
        *numerator = a0;
        *denominator = 1;
        return 0;
    }

    long long p0 = 1, q0 = 0;
    long long p1 = a0, q1 = 1;

    double x = number;
    const int k = 50;
    for (int i = 0; i < k; ++i) {
        x = 1.0 / (x - floor(x));
        long long a = floor(x);
        long long p2 = a * p1 + p0;
        long long q2 = a * q1 + q0;

        if (fabs(number - (double)p2 / q2) < eps || q2 > MAX_DEN) {
            *numerator = p2;
            *denominator = q2;
            return 0;
        }

        p0 = p1;
        q0 = q1;
        p1 = p2;
        q1 = q2;
    }
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
        if (temp <= 0 || temp >= 1.0) continue;
        a += have_infinity_presentation(base, temp);
    }
    va_end(factor);
    return a;
}