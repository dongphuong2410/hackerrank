#ifndef __PMATH_H__
#define __PMATH_H__

/**
  * @brief Calculate least common multiple of two integers
  * @param a First integer
  * @param b Second integer
  * @return Least common multiple
  */
int lcm(int a, int b);

/**
  * @brief Calculate greatest common factor of two integers
  * @param a First integer
  * @param b Second integer
  * @return Greatest common factor
  */
int gcf(int a, int b);

/**
  * @brief Factorize number n into a1^p1*a2^p2*a3^p3 
  * @param n Number to be factorized
  * @param p Array of prime numbers pi
  * @param a Array of ai
  * @param n max_len Maximum len of p and a
  * @return Number of factors
  */
int factorize(int n, int *p, int *a, int max_len);

/**
  * @brief Get number of divisors of an integer
  * @param n Number
  * @return Number of divisors
  */
int count_divisors(int n);

#endif
