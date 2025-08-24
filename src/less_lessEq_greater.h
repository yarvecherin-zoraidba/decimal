#ifndef __less_lessEq_greater__
#define __less_lessEq_greater__

#include <stdio.h>

#define SIGNBIT 0x80000000U
#define EXBITS 0x00FF0000U

typedef struct {
    unsigned bits[4];
} s21_decimal;

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_less(s21_decimal v1, s21_decimal v2);
int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2);
int s21_is_greater(s21_decimal v1, s21_decimal v2);
int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2);
int s21_is_equal(s21_decimal v1, s21_decimal v2);
int s21_is_not_equal(s21_decimal v1, s21_decimal v2);
int get_res_of_comparison(s21_decimal v1, s21_decimal v2);
int compare_with_same_ex(s21_decimal v1, s21_decimal v2);
int make_num_v1_greater_v2(s21_decimal *v1, int *ex1, s21_decimal v2);
unsigned long long change_num_by_mul_10(s21_decimal *v, int delta_ex);
int remove_zero_if_div_10(s21_decimal *v, int delta_ex);
int divide_by_10(s21_decimal *v);

#endif