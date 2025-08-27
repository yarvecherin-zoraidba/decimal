#include "s21_decimal.h"

s21_another_decimal s21_decimal_init() {
  s21_another_decimal result = {0};
  return result;
}

int s21_add(s21_another_decimal value1, s21_another_decimal value2, s21_another_decimal *result) {
  *result = s21_decimal_init();
  int error = 0;
  if (value1.sign ^ value2.sign) {
    if (value1.sign) {
      value1.sign = 0;
      return s21_sub(value2, value1, result);
    } else {
      value2.sign = 0;
      return s21_sub(value1, value2, result);
    }
  }
  int exp1 = s21_get_exponent(value1);
  int exp2 = s21_get_exponent(value2);

  int max_exp = (exp1 > exp2) ? exp1 : exp2;
  s21_another_decimal aligned1 = value1;
  s21_another_decimal aligned2 = value2;

  s21_align_exponents(&aligned1, &aligned2);

  unsigned long long sum = ( unsigned long long)aligned1.bits[0] + ( unsigned long long)aligned2.bits[0];
   unsigned long long carry = sum >> 32;
  result->bits[0] = (unsigned int)sum;

  sum = ( unsigned long long)aligned1.bits[1] + ( unsigned long long)aligned2.bits[1] + carry;
  carry = sum >> 32;
  result->bits[1] = (unsigned int)sum;

  sum = ( unsigned long long)aligned1.bits[2] + ( unsigned long long)aligned2.bits[2] + carry;
  carry = sum >> 32;
  result->bits[2] = (unsigned int)sum;

  if (carry > 0) {
    if (max_exp > 0) {
      s21_another_decimal temp = *result;
      s21_set_exponent(result, max_exp - 1);
      error = s21_div_by_10(&temp, result);
    } else {
      error = 1;
    }
  } else {
    s21_set_exponent(result, max_exp);
  }
  result->sign = value1.sign;
  return error;
}

int s21_sub(s21_another_decimal value1, s21_another_decimal value2, s21_another_decimal *result) {
  *result = s21_decimal_init();
  int error = 0;
  if (value1.sign ^ value2.sign) {
    if (value1.sign) {
      value1.sign = 0;
      error = s21_add(value1, value2, result);
      result->sign = 1;
    } else {
      value2.sign = 0;
      error = s21_add(value1, value2, result);
    }
    return error;
  }

  s21_align_exponents(&value1, &value2);
  int comparison = s21_compare_absolute(value1, value2);
  if (comparison == 0) {
    *result = s21_decimal_init();
    return 0;
  }
  s21_another_decimal *larger = {0};
  s21_another_decimal *smaller = {0};
  int result_sign = 0;

  if (comparison > 0) {
    larger = &value1;
    smaller = &value2;
    result_sign = value1.sign;
  } else {
    larger = &value2;
    smaller = &value1;
    result_sign = !value1.sign;
  }
   unsigned long long borrow = 0;

  for (int i = 0; i < 3; i++) {
     unsigned long long larger_val = ( unsigned long long)larger->bits[i];
     unsigned long long smaller_val = ( unsigned long long)smaller->bits[i] + borrow;

    if (larger_val < smaller_val) {
      result->bits[i] = (unsigned int)((UINT_MAX + 1) + larger_val - smaller_val);
      borrow = 1;
    } else {
      result->bits[i] = (unsigned int)(larger_val - smaller_val);
      borrow = 0;
    }
  }

  s21_set_exponent(result, s21_get_exponent(value1));
  result->sign = result_sign;

  return error;
}

void s21_align_exponents(s21_another_decimal *a, s21_another_decimal *b) {
  int exp1 = s21_get_exponent(*a);
  int exp2 = s21_get_exponent(*b);

  if (exp1 < exp2) {
    s21_multiply_by_10_power(a, exp2 - exp1);
    s21_set_exponent(a, exp2);
  } else if (exp2 < exp1) {
    s21_multiply_by_10_power(b, exp1 - exp2);
    s21_set_exponent(b, exp1);
  }
}

int s21_multiply_by_10_power(s21_another_decimal *value, int power) {
  for (int i = 0; i < power; i++) {
    s21_another_decimal temp = *value;
    s21_another_decimal temp2 = *value;
    s21_shift_left(&temp, 3);
    s21_shift_left(&temp2, 1);
    return s21_add(temp, temp2, value);
  }
  return 0;
}

int s21_div_by_10(s21_another_decimal *value, s21_another_decimal *result) {
   unsigned long long remainder = 0;
  for (int i = 2; i >= 0; i--) {
     unsigned long long current = (( unsigned long long)remainder << 32) | value->bits[i];
    result->bits[i] = (unsigned int)(current / 10);
    remainder = current % 10;
  }

  return (remainder == 0) ? 0 : 1;
}

int s21_compare_absolute(s21_another_decimal a, s21_another_decimal b) {
  s21_align_exponents(&a, &b);
  for (int i = 2; i >= 0; i--) {
    if (a.bits[i] > b.bits[i])
      return 1;
    if (a.bits[i] < b.bits[i])
      return -1;
  }
  return 0;
}

unsigned int s21_get_exponent(s21_another_decimal src) {
  src.bits[3] &= ~SIGNBIT;
  return src.bits[3] >> 16;
}

void s21_set_exponent(s21_another_decimal *src, unsigned int exp) {
  if (!src || exp > 28)
    return;
  src->bits[3] = (exp << 16) | (src->bits[3] & SIGNBIT);
}

void s21_shift_left(s21_another_decimal *value, int shift) {
  for (int s = 0; s < shift; s++) {
    unsigned int carry_prev = 0;
    for (int i = 0; i < 3; i++) {
      unsigned int current = value->bits[i];
      value->bits[i] = (current << 1) | carry_prev;
      carry_prev = (current >> 31) & 1;
    }
    if (carry_prev != 0) {
      break;
    }
  }
}
