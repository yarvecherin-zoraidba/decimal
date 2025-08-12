#include "s21_round.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int scale = s21_get_exp(value);
  if (scale > 28) return 1;

  if (!result) return 1;

  *result = value;

  while (scale-- > 0) {
    s21_divide_by_10(result);
  }

  s21_set_exp(result, 0);
  return 0;
}

int s21_divide_by_10(s21_decimal *value) {
  if (value == NULL) return 1;

  unsigned long long buff = 0;

  for (int i = 2; i >= 0; i--) {
    unsigned long long temp = (buff << UINT_SIZE) | value->bits[i];
    value->bits[i] = (unsigned)(temp / 10);
    buff = temp % 10;
  }

  return 0;
}