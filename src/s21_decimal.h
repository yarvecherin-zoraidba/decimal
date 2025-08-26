#include <stdint.h>

#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define SIGNBIT 0x80000000

typedef struct {
  uint32_t bits[3];
  uint32_t sign : 1;
  uint32_t exp : 8;
  uint32_t empty : 23;
} s21_decimal;

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result);
s21_decimal s21_decimal_init();
void s21_align_exponents(s21_decimal *a, s21_decimal *b);
int s21_multiply_by_10_power(s21_decimal *value, int power);
int s21_div_by_10(s21_decimal *value, s21_decimal *result);
int s21_compare_absolute(s21_decimal a, s21_decimal b);
unsigned int s21_get_exponent(s21_decimal src);
void s21_set_exponent(s21_decimal *src, unsigned int exp);
void s21_shift_left(s21_decimal *value, int shift);

#endif