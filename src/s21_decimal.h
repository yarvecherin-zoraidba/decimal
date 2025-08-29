#ifndef __S21_DECIMAL_H__
#define __S21_DECIMAL_H__

#include <math.h>
#include <stdio.h>

#define SIGNBIT 0x80000000U
#define MAX_INT 0x7FFFFFFF
#define MIN_INT -2147483648

#define EXBITS 0x00FF0000U
#define NOT_VALIDBITS 0x7F00FFFFU

#define LONG_BITS 192

enum { S21_OK = 0, S21_INF_POS = 1, S21_INF_NEG = 2, S21_DIV_BY_ZERO = 3 };
enum { S21_LIMB_COUNT_192 = 6 };
enum { S21_96_LIMBS = 3 };

typedef struct s21_decimal {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  char bits[LONG_BITS];
  char floa;
  char sign;
} s21_long_decimal;

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_is_less(s21_decimal v1, s21_decimal v2);
int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2);
int s21_is_greater(s21_decimal v1, s21_decimal v2);
int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2);
int s21_is_equal(s21_decimal v1, s21_decimal v2);
int s21_is_not_equal(s21_decimal v1, s21_decimal v2);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Dmitry
unsigned int s21_get_exp(s21_decimal src);
int s21_get_sign(s21_decimal src);
void s21_set_sign(s21_decimal *src, int sign);
void s21_init(s21_decimal *dst);

// karkaror
_Bool is_OK_input_bits_data(const s21_decimal *v);
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

// mushroot
void s21_long_add(s21_long_decimal value1, s21_long_decimal value2,
                  s21_long_decimal *result);
void s21_long_sub(s21_long_decimal value1, s21_long_decimal value2,
                  s21_long_decimal *result);
s21_decimal s21_decimal_init();
s21_long_decimal s21_long_init();
void s21_decimal_to_long_decimal(s21_decimal value, s21_long_decimal *result);
void s21_long_float_check(s21_long_decimal *value_1, s21_long_decimal *value_2);
int s21_long_comparison(s21_long_decimal value_1, s21_long_decimal value_2);
void s21_long_add(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal *result);
void s21_long_sub(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal *result);
s21_long_decimal s21_long_ten_init();
void s21_long_to_decimal(s21_long_decimal value, s21_decimal *result);
void s21_long_mul(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal *result);
int s21_long_size_check(s21_long_decimal *value);
s21_long_decimal s21_long_div(s21_long_decimal value_1,
                              s21_long_decimal value_2,
                              s21_long_decimal *result);
int s21_long_size(s21_long_decimal value);
void s21_long_bank_round(s21_long_decimal value, s21_long_decimal mod,
                         s21_long_decimal *result);
int s21_long_to_int(s21_long_decimal value);
void s21_long_shift(s21_long_decimal *value);

// charlesj
int s21_is_zero96(const s21_decimal *d);
void s21_zero_decimal(s21_decimal *d);
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_is_zero96(const s21_decimal *d);
void s21_big_zero(unsigned big[], int n);
unsigned s21_big_inc(unsigned big[], int n);
unsigned s21_big_div10(unsigned big[], int n);
unsigned s21_big_mod10_const(const unsigned big[], int n);
int s21_big_fits_96(const unsigned big[]);
void s21_mul_96x96_to_192(const s21_decimal *x, const s21_decimal *y,
                          unsigned out[], int n);
void s21_big_round_div10_bankers(unsigned big[], int n, unsigned rem,
                                 int sticky);

// zoraidba
_Bool add_digit(s21_decimal *value, unsigned digit);
void s21_set_exp(s21_decimal *src, unsigned int exp);

#endif
