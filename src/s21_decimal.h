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
int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal *result);

#endif