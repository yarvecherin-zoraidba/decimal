#ifndef __less_lessEq_greater__
#define __less_lessEq_greater__

#include <stdio.h>
#include <stdbool.h>

#define USIGNBIT 0x80000000U
#define IN_ZERO_USIGNBIT 0x7FFFFFFFU

typedef struct {
    unsigned bits[4];
} s21_decimal;

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_less(s21_decimal v1, s21_decimal v2);
int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2);
int s21_is_greater(s21_decimal v1, s21_decimal v2);
int get_res_of_comparison(s21_decimal v1, s21_decimal v2);
int compare_with_same_pow(s21_decimal v1, s21_decimal v2);
bool get_same_pow_by_mul_10(s21_decimal *v, int delta_pow);

#endif