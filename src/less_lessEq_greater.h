#ifndef __less_lessEq_greater__
#define __less_lessEq_greater__

#include <stdio.h>

#define SIGNBIT 0x80000000U
#define EXBITS 0x00FF0000U
#define LEFT_32_FOR_64_BITS 0xFFFFFFFF00000000ULL
#define ALL_64_BITS 0xFFFFFFFFFFFFFFFFULL

typedef struct {
    unsigned bits[4];
} s21_decimal;

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
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
int make_ex_1_2_zero(s21_decimal *v1, s21_decimal *v2, int *ex1, int *ex2);
_Bool add_digit(s21_decimal *v, unsigned digit);
void make_decimal_division(s21_decimal *v1, s21_decimal *v2, s21_decimal *result, int *ex_result, int fl_num_v1_less_v2);
void divide_by_96_bits(s21_decimal *v1, s21_decimal *v2, s21_decimal *result, int *ex_result, int fl_num_v1_less_v2);
void divide_by_64_bits(s21_decimal *v1, s21_decimal *v2, s21_decimal *result, int *ex_result);
void divide_by_32_bits(s21_decimal *v1, s21_decimal *v2, s21_decimal *result, int *ex_result);
_Bool add_quotient_in_result(s21_decimal *result, int *ex_result, unsigned quotient);
void round_banks_decimal(s21_decimal *v, unsigned digit);
void subtract_low_bits_from_96bits_divident(s21_decimal *v1, s21_decimal *v2, unsigned long long *overflow_v1, unsigned quotient);
void subtract_middle_bits_from_96bits_divident(s21_decimal *v1, s21_decimal *v2, unsigned long long *overflow_v1, unsigned quotient);
void subtract_high_bits_from_96bits_divident(s21_decimal *v1, s21_decimal *v2, unsigned long long *overflow_v1, unsigned quotient);
void subtract_low_bits_from_64bits_divident(s21_decimal *v1, s21_decimal *v2, unsigned long long *overflow_v1, unsigned quotient);

#endif