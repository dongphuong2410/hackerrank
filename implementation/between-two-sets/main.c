#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 1024

/* Struct to represent a factorized number as : p1^a1 * p2^a2*..*pn^an */
typedef struct {
    int no;
    int p[MAX];
    int a[MAX];
} factor_t;

void test_factor_lcm(void);
void test_factor_gcf(void);
void test_get_lcm_all();
void test_get_gcf_all();
void test_dividable();

void factorize(int n, factor_t *output) {
    output->no = 0;
    int *sieve = (int *)calloc(MAX, sizeof(int));
    int i, j;
    for (i = 2; i <= MAX; i++) {
        if (!sieve[i]) {
            int is_factor = 0;
            int n1 = n;
            while (n1 % i == 0) {
                if (!is_factor) {
                    is_factor = 1;
                    output->a[output->no] = 0;
                }
                output->p[output->no] = i;
                output->a[output->no]++;
                n1 = n1 / i;
            }
            if (is_factor) output->no++;
            j = 1;
            while (i * j <= n) {
                sieve[i * j] = 1;
                j++;
            }
        }
    }
}

void factor_lcm(factor_t *a, factor_t *b, factor_t *output)
{
    int index_a = 0;
    int index_b = 0;
    output->no = 0;
    while (index_a < a->no || index_b < b->no) {
        if (index_a >= a->no) {
            output->p[output->no] = b->p[index_b];
            output->a[output->no] = b->a[index_b];
            output->no++;
            index_b++;
        }
        else if (index_b >= b->no) {
            output->p[output->no] = a->p[index_a];
            output->a[output->no] = a->a[index_a];
            output->no++;
            index_a++;
        }
        else {
            if (a->p[index_a] < b->p[index_b]) {
                output->p[output->no] = a->p[index_a];
                output->a[output->no] = a->a[index_a];
                output->no++;
                index_a++;
            }
            else if (a->p[index_a] > b->p[index_b]) {
                output->p[output->no] = b->p[index_b];
                output->a[output->no] = b->a[index_b];
                output->no++;
                index_b++;
            }
            else {
                output->p[output->no] = a->p[index_a];
                output->a[output->no] = (a->a[index_a] >= b->a[index_b] ? a->a[index_a] : b->a[index_b]);
                output->no++;
                index_a++;
                index_b++;
            }
        }
    }

}

void factor_copy(factor_t *dest, factor_t *source)
{
    int i;
    dest->no = source->no;
    for (i = 0; i < dest->no; i++) {
        dest->p[i] = source->p[i];
        dest->a[i] = source->a[i];
    }
}

/**
  * Get lcm of an array of integers in form of factors p1^a1 * p2^a2 * ...
  * @return Number of factors
  */
void get_lcm_all(int n_size, int*  n, factor_t *output) {
    if (n_size == 0)
        return;
    int i;
    factor_t *a = (factor_t *)calloc(1, sizeof(factor_t));
    factor_t *b = (factor_t *)calloc(1, sizeof(factor_t));
    factorize(n[0], output);
    for (i = 1; i < n_size; i++) {
        factor_copy(a, output);
        factorize(n[i], b);
        factor_lcm(a, b, output);
    }
    free(a);
    free(b);
}

void factor_gcf(factor_t *a, factor_t *b, factor_t *output) {
    output->no = 0;
    int index_a = 0;
    int index_b = 0;
    int index_o = 0;
    while (index_a < a->no && index_b < b->no) {
        if (a->p[index_a] == b->p[index_b]) {
            output->p[index_o] = a->p[index_a];
            output->a[index_o] = (a->a[index_a] <= b->a[index_b] ? a->a[index_a] : b->a[index_b]);
            index_o++;
            index_a++;
            index_b++;
        }
        else if (a->p[index_a] < b->p[index_b]) {
            index_a++;
        }
        else if (a->p[index_a] > b->p[index_b]) {
            index_b++;
        }
    }
    output->no = index_o;
}

/**
  * Get lcm of an array of integers in form of factors p1^a1 * p2^a2 * ...
  * @return Number of factors
  */
void get_gcf_all(int n_size, int *n, factor_t *output) {
    if (n_size == 0)
        return;
    int i;
    factor_t *a = (factor_t *)calloc(1, sizeof(factor_t));
    factor_t *b = (factor_t *)calloc(1, sizeof(factor_t));
    factorize(n[0], output);
    for (i = 1; i < n_size; i++) {
        factor_copy(a, output);
        factorize(n[i], b);
        factor_gcf(a, b, output);
    }
    free(a);
    free(b);
}

/**
  * Does a % b == 0 or not
  * @return TRUE OR FALSE
  */
int dividable(factor_t *a, factor_t *b)
{
    int index_a = 0;
    int index_b = 0;
    while (index_b < b->no) {
        if (index_a < a->no)
            return 0;
        if (a->a[index_a] == b->a[index_b]) {
            if (a->p[index_a] < b->p[index_b]) {
                return 0;
            }
            else {
                index_a++;
                index_b++;
            }
        }
        else if (a->a[index_a] > b->a[index_b]) {
            return 0;
        }
        else if (a->a[index_a] < b->a[index_b]) {
            index_a++;
        }
    }
    return 1;
}

/**
  * Return a / b as a factorized number
  */
void factor_divide(factor_t *a, factor_t *b, factor_t *c)
{
    factor_copy(c, a);
    int index_b = 0;
    int index_c = 0;
    while (index_b < b->no) {
    }
    return NULL;
}

/**
  * Count number of divisors of a factorized number
  */
int count_divisor_no(factor_t *a)
{
    return 0;
}

int getTotalX(int a_size, int* a, int b_size, int* b) {
    int result = 0;
    factor_t *smaller = (factor_t *)calloc(1, sizeof(factor_t));
    factor_t *bigger = (factor_t *)calloc(1, sizeof(factor_t));
    get_lcm_all(a_size, a, smaller);
    get_gcf_all(b_size, b, bigger);
    if (!dividable(bigger, smaller)) {
        return 0;
    }
    factor_t *common = factor_divide(bigger, smaller);
    result = count_divisor_no(common);
    free(common);
done:
    free(smaller);
    free(bigger);
    return result;
}

int main() {
    test_factor_lcm();
    test_factor_gcf();
    test_get_lcm_all();
    test_get_gcf_all();
    test_dividable();

    ////Test main function
    //int n;
    //int m;
    //scanf("%i %i", &n, &m);
    //int *a = malloc(sizeof(int) * n);
    //for (int a_i = 0; a_i < n; a_i++) {
    //   scanf("%i",&a[a_i]);
    //}
    //int *b = malloc(sizeof(int) * m);
    //for (int b_i = 0; b_i < m; b_i++) {
    //   scanf("%i",&b[b_i]);
    //}
    //int total = getTotalX(n, a, m, b);
    //printf("%d\n", total);
    return 0;
}

void test_factor_lcm(void)
{
    factor_t *a = (factor_t *)calloc(1, sizeof(factor_t));
    factor_t *b = (factor_t *)calloc(1, sizeof(factor_t));
    factor_t *c = (factor_t *)calloc(1, sizeof(factor_t));

    /* a = 2^1, b = 3^1 */
    a->no = 1;
    a->p[0] = 2;
    a->a[0] = 1;
    b->no = 1;
    b->p[0] = 3;
    b->a[0] = 1;
    factor_lcm(a, b, c);
    assert(c->no == 2);
    assert(c->p[0] == 2);
    assert(c->a[0] == 1);
    assert(c->p[1] == 3);
    assert(c->a[1] == 1);

    /* a = 2^3*7^1, b = 2*3^1*11 */
    /* c should be 2^3*3^1*7^1*11^1 */
    a->no = 2;
    a->p[0] = 2;
    a->a[0] = 3;
    a->p[1] = 7;
    a->a[1] = 1;
    b->no = 3;
    b->p[0] = 2;
    b->a[0] = 1;
    b->p[1] = 3;
    b->a[1] = 1;
    b->p[2] = 11;
    b->a[2] = 1;
    factor_lcm(a, b, c);
    assert(c->no == 4);
    assert(c->p[0] == 2);
    assert(c->a[0] == 3);
    assert(c->p[1] == 3);
    assert(c->a[1] == 1);
    assert(c->p[2] == 7);
    assert(c->a[2] == 1);
    assert(c->p[3] == 11);
    assert(c->a[3] == 1);

    free(a);
    free(b);
    free(c);
}

void test_factor_gcf(void)
{
    factor_t *a = (factor_t *)calloc(1, sizeof(factor_t));
    factor_t *b = (factor_t *)calloc(1, sizeof(factor_t));
    factor_t *c = (factor_t *)calloc(1, sizeof(factor_t));

    /* a = 2^1, b = 3^1 */
    a->no = 1;
    a->p[0] = 2;
    a->a[0] = 1;
    b->no = 1;
    b->p[0] = 3;
    b->a[0] = 1;
    factor_gcf(a, b, c);
    assert(c->no == 0);

    /* a = 2^2*7^1, b = 2*3^1*11 */
    /* c should be 2^2 */
    a->no = 2;
    a->p[0] = 2;
    a->a[0] = 3;
    a->p[1] = 7;
    a->a[1] = 1;
    b->no = 3;
    b->p[0] = 2;
    b->a[0] = 2;
    b->p[1] = 3;
    b->a[1] = 1;
    b->p[2] = 11;
    b->a[2] = 1;
    factor_gcf(a, b, c);
    assert(c->no == 1);
    assert(c->p[0] == 2);
    assert(c->a[0] == 2);

    free(a);
    free(b);
    free(c);
}

void test_get_lcm_all()
{
    factor_t *result = (factor_t *)calloc(1, sizeof(factor_t));
    int n[] = {2, 10, 15, 7};
    get_lcm_all(4, n, result);
    assert(result->no == 4);
    assert(result->p[0] == 2);
    assert(result->a[0] == 1);
    assert(result->p[1] == 3);
    assert(result->a[1] == 1);
    assert(result->p[2] == 5);
    assert(result->a[2] == 1);
    assert(result->p[3] == 7);
    assert(result->a[3] == 1);
}

void test_get_gcf_all()
{
    factor_t *result = (factor_t *)calloc(1, sizeof(factor_t));
    int n[] = {30, 15, 45};
    get_gcf_all(3, n, result);
    assert(result->no == 2);
    assert(result->p[0] == 3);
    assert(result->a[0] == 1);
    assert(result->p[1] == 5);
    assert(result->a[1] == 1);
}

void test_dividable()
{
    int a, b;
    factor_t *fa = (factor_t *)calloc(1, sizeof(factor_t));
    factor_t *fb = (factor_t *)calloc(1, sizeof(factor_t));
    int divide;

    a = 20;
    b = 15;
    factorize(a, fa);
    factorize(b, fb);
    divide = dividable(fa, fb);
    assert(divide == 0);

    a = 20;
    b = 10;
    factorize(a, fa);
    factorize(b, fb);
    divide = dividable(fa, fb);
    assert(divide == 1);
}
