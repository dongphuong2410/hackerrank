#include <stdlib.h>
#include "pmath.h"

int lcm(int a, int b)
{
    if (a == 0 || b == 0)
        return 0;
    int their_gcf = gcf(a, b);
    return their_gcf * (a / their_gcf) * (b / their_gcf);
}

int gcf(int a, int b)
{
    while (a != b) {
        if (a > b) {
            a = a - b;
        }
        else {
            int tmp = a;
            a = b - a;
            b = tmp;
        }
    }
    return a;
}

int factorize(int n, int *p, int *a, int max_len) {
    int *sieve = (int *)calloc(max_len, sizeof(int));
    int i, j;
    int cnt = 0;
    for (i = 2; i <= max_len; i++) {
        if (!sieve[i]) {
            int is_factor = 0;
            int n1 = n;
            while (n1 % i == 0) {
                is_factor = 1;
                p[cnt] = i;
                a[cnt]++;
                n1 = n1 / i;
            }
            if (is_factor) cnt++;
            j = 1;
            while (i * j <= n) {
                sieve[i * j] = 1;
                j++;
            }
        }
    }
    return cnt;
}

int count_divisors(int n) {
    int size = sqrt(n) + 1;
    int *p = (int *)malloc(size * sizeof(size));
    int *a = (int *)malloc(size * sizeof(size));
    int fact_no = factorize(n, p, a, size);
    int i;
    int cnt = 1;
    for (i = 0; i < fact_no; i++) {
        cnt *= (a[i] + 1);  //https://www.quora.com/What-is-the-fastest-algorithm-to-get-the-number-of-divisors-of-number-x-limits-up-to-10-12
    }
    return cnt;
}

