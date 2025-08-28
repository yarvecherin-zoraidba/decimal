#include "s21_round.h"
#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;

  if (result == NULL || s21_get_exp(*result) > 28) error = 1;
  else {
    int largest_fractional_part = 0;
    *result = value;
    unsigned int scale = s21_get_exp(value);
    remove_zero_if_div_10(result, scale);
    scale = s21_get_exp(*result);
    s21_truncate(*result, result);
    if (s21_get_sign(*result) != 0) {
      if (scale > 0) {
        add_digit(result, 1);
        s21_set_exp(result, 0);
      }
    }
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  unsigned int scale = s21_get_exp(value);

  if (result == NULL || s21_get_exp(*result) > 28) error = 1;
  else {
    int largest_fractional_part = 0;
    *result = value;

    while ((scale--) != 0) {
      largest_fractional_part = divide_by_10(result);
    }
      s21_set_exp(result, 0);
      if (largest_fractional_part >= 5) add_digit(result, 1);
    }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  int scale = s21_get_exp(value);

  if (result == NULL || s21_get_exp(*result) > 28) error = 1;  
  else {
    *result = value;

    while ((scale--) != 0) {
      divide_by_10(result);
    }
    s21_set_exp(result, 0);
  }

  return error;
}

int divide_by_10(s21_decimal *value) {
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
        overflow = overflow >> UINT_SIZE;
    }
    return (overflow != 0ULL);
}

int remove_zero_if_div_10(s21_decimal *v, int delta_ex) {
    int ex_v = -1;
    if (v != NULL) {
        ex_v = (int)((v->bits[3] & EXBITS) >> 16);
        unsigned long long remainder = 0ULL;
        while (delta_ex-- > 0 && ex_v > 0 && remainder == 0ULL) {
            s21_decimal v_temp = *v;
            remainder = (unsigned long long)divide_by_10(&v_temp);
            if (remainder == 0ULL) {
                *v = v_temp;
                ex_v--;
            }
        }
        v->bits[3] &= SIGNBIT;
        v->bits[3] |= (ex_v << 16);
    }
    return ex_v;
}
