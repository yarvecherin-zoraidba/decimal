#include "s21_decimal.h"
#include "s21_decimal_functions.h"

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  *result = s21_decimal_init();
  int error = 0;
  s21_long_decimal longValue1;
  s21_long_decimal longValue2;
  s21_long_decimal longResult = s21_long_init();
  s21_decimal_to_long_decimal(value1, &longValue1);
  s21_decimal_to_long_decimal(value2, &longValue2);

  s21_long_float_check(&longValue1, &longValue2);

  if (longValue1.sign ^ longValue2.sign) {
    int comp = s21_long_comparison(longValue1, longValue2);
    if (comp == 1) {
      s21_long_sub(longValue1, longValue2, &longResult);
      longResult.sign = longValue1.sign;
    } else if (comp == 2) {
      s21_long_sub(longValue2, longValue1, &longResult);
      longResult.sign = longValue2.sign;
    } else {
      longResult = s21_long_init();
    }
  } else {
    s21_long_add(longValue1, longValue2, &longResult);
    longResult.sign = longValue1.sign;
  }
  error = s21_long_size_check(&longResult);
  s21_long_to_decimal(longResult, result);
  return error;
}

int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  *result = s21_decimal_init();
  int error = 0;
  s21_long_decimal longValue1;
  s21_long_decimal longValue2;
  s21_long_decimal longResult = s21_long_init();
  s21_decimal_to_long_decimal(value1, &longValue1);
  s21_decimal_to_long_decimal(value2, &longValue2);

  s21_long_float_check(&longValue1, &longValue2);

  if (longValue1.sign == longValue2.sign) {
    int comp = s21_long_comparison(longValue1, longValue2);
    if (comp == 1) {
      s21_long_sub(longValue1, longValue2, &longResult);
      longResult.sign = longValue1.sign;
    } else if (comp == 2) {
      s21_long_sub(longValue2, longValue1, &longResult);
      longResult.sign = longValue2.sign < 1;
    } else {
      longResult = s21_long_init();
    }
  } else {
    s21_long_add(longValue1, longValue2, &longResult);
    longResult.sign = longValue1.sign;
  }
  error = s21_long_size_check(&longResult);
  s21_long_to_decimal(longResult, result);
  return error;
}

int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  *result = s21_decimal_init();
  int error = 0;
  s21_long_decimal longValue1;
  s21_long_decimal longValue2;
  s21_long_decimal longResult = s21_long_init();
  s21_decimal_to_long_decimal(value1, &longValue1);
  s21_decimal_to_long_decimal(value2, &longValue2);
  int sign1 = longValue1.sign;
  int sign2 = longValue2.sign;

  if (s21_long_size(longValue1) && s21_long_size(longValue2)) {
    s21_long_mul(longValue1, longValue2, &longResult);
    longResult.sign = sign1 ^ sign2;
    error = s21_long_size_check(&longResult);
  }
  s21_long_to_decimal(longResult, result);
  return error;
}
