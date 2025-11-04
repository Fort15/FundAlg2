#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define EPS 1e-12
#define MAX_DEN 1e+12

// typedef enum {
//     STATUS_OK,
//     STATUS_INVALID_NUMBER,
//     STATUS_TOO_BIG_DENOMINATOR,
// } Status;


long long gcd(long long a, long long b);
int count_infinity_presentation(int base, int n, ...);
int have_infinity_presentation(int base, double number);
int find_denominator(double number, double eps, long long *denominator, long long *numerator);

#endif