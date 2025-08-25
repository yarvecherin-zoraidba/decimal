#include "s21_round.h"
#include  <stdbool.h>

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int largest_fractional_part = 0;
  unsigned int scale = s21_get_exp(value);

  if (scale != 0) {
    *result = value;
    remove_leading_zeros(result);
    scale = s21_get_exp(*result);
    if (s21_get_sign(*result) == 0) {
      s21_truncate(*result, result);
    } else {
      while ((scale--) != 0) {
      largest_fractional_part = s21_divide_by_10(result);
      }
      add_digit(result, 1);
    }
  }
  
  return error;
}


int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  unsigned int scale = s21_get_exp(value);
  int largest_fractional_part = 0;
  *result = value;

  while ((scale--) != 0) {
    largest_fractional_part = s21_divide_by_10(result);
  }
  s21_set_exp(result, 0);
  if (largest_fractional_part >= 5) add_digit(result, 1);

  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int scale = s21_get_exp(value);
  if (scale > 28) return 1;

  if (!result) return 1;

  *result = value;

  while ((scale--) != 0) {
    s21_divide_by_10(result);
  }

  s21_set_exp(result, 0);
  return 0;
}

int s21_divide_by_10(s21_decimal *value) {
  if (value == NULL) return -1;

  unsigned long long buff = 0;

  for (int i = 2; i >= 0; i--) {
    unsigned long long temp = (buff << UINT_SIZE) | value->bits[i];
    value->bits[i] = (unsigned)(temp / 10);
    buff = temp % 10;
  }

  return (int)buff;
}

_Bool add_digit(s21_decimal *value, unsigned digit) {
    unsigned long long overflow = (unsigned long long)digit;
    for (int i = 0; i < 3; i++) {
        overflow += (unsigned long long)value->bits[i];
        value->bits[i] = (unsigned)overflow;
        overflow = overflow >> 32;
    }
    return (overflow != 0ULL);
}

void remove_leading_zeros(s21_decimal *value) {
  int scale = s21_get_exp(*value);
  while ((scale != 0) && (value->bits[0] % 10 == 0)) {
    s21_divide_by_10(value);
    scale--;
  };
  s21_set_exp(value, scale);
}