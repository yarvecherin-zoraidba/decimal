#ifndef __less_lessEq_greater__
#define __less_lessEq_greater__

#include <stdio.h>

#define SIGNBIT 0x80000000U
#define EXBITS 0x00FF0000U
#define NOT_VALIDBITS 0x7F00FFFFU

typedef struct s21_decimal {
  unsigned bits[4];
} s21_decimal;

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_less(s21_decimal v1, s21_decimal v2);
int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2);
int s21_is_greater(s21_decimal v1, s21_decimal v2);
int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2);
int s21_is_equal(s21_decimal v1, s21_decimal v2);
int s21_is_not_equal(s21_decimal v1, s21_decimal v2);
_Bool is_OK_input_bits_data(const s21_decimal *v);
_Bool is_zero_num(const s21_decimal *v);
void set_zero_num(s21_decimal *v);
int get_res_of_comparison(s21_decimal v1, s21_decimal v2);
int compare_with_same_ex(s21_decimal v1, s21_decimal v2);
int make_num_v1_greater_v2(s21_decimal *v1, int *ex1, s21_decimal v2);
unsigned long long change_num_by_mul_10(s21_decimal *v, int delta_ex);
int remove_zero_if_div_10(s21_decimal *v, int delta_ex);
int divide_by_10(s21_decimal *v);
int make_ex_1_2_zero(s21_decimal *v1, s21_decimal *v2, int *ex1, int *ex2);
void make_decimal_division(const s21_decimal *v1, const s21_decimal *v2,
                           s21_decimal *result, int *ex_result);
void change_b_num_by_mul_10(unsigned *n, int delta_ex);
void divide_b_nums(const unsigned *dividend, const unsigned *divisor,
                   unsigned *quotient);
int compare_b_num(const unsigned *n1, const unsigned int *n2);
void shift_left_b_num(unsigned *n);
int check_bit_in_indx_b_num(const unsigned *num, int indx);
void set_bit_in_indx_b_num(unsigned *n, int indx, int value);
int substract_b_nums_by_bitwise(const unsigned *n1, const unsigned *n2,
                                unsigned int *difference);
void change_b_num_for_s21_decimal(unsigned *quotient, s21_decimal *result,
                                  int *ex_result);
_Bool is_zero_high_blocks_of_b_num(const unsigned *n);
int divide_b_num_by_10(unsigned *n);
void round_banks_decimal(unsigned *n, int digit, int *ex_current);
_Bool add_digit_in_3_low_b_num(unsigned *n, int digit);
void remove_all_zeros_from_b_num_if_div_10(unsigned *n, int *ex_current);

#endif