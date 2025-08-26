#include "s21_decimal.h"

s21_decimal s21_decimal_init() {
  s21_decimal result;
  for (int i = 0; i < 4; i++) {
    result.bits[i] = 0;
  }
  return result;
}

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
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
  s21_decimal aligned1 = value1;
  s21_decimal aligned2 = value2;

  s21_align_exponents(&aligned1, &aligned2);

  uint64_t sum = (uint64_t)aligned1.bits[0] + (uint64_t)aligned2.bits[0];
  uint64_t carry = sum >> 32;
  result->bits[0] = (uint32_t)sum;

  sum = (uint64_t)aligned1.bits[1] + (uint64_t)aligned2.bits[1] + carry;
  carry = sum >> 32;
  result->bits[1] = (uint32_t)sum;

  sum = (uint64_t)aligned1.bits[2] + (uint64_t)aligned2.bits[2] + carry;
  carry = sum >> 32;
  result->bits[2] = (uint32_t)sum;

  if (carry > 0) {
    if (max_exp > 0) {
      s21_decimal temp = *result;
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

int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
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
  s21_decimal *larger, *smaller;
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
  uint64_t borrow = 0;

  for (int i = 0; i < 3; i++) {
    uint64_t larger_val = (uint64_t)larger->bits[i];
    uint64_t smaller_val = (uint64_t)smaller->bits[i] + borrow;

    if (larger_val < smaller_val) {
      result->bits[i] = (uint32_t)((UINT32_MAX + 1) + larger_val - smaller_val);
      borrow = 1;
    } else {
      result->bits[i] = (uint32_t)(larger_val - smaller_val);
      borrow = 0;
    }
  }

  s21_set_exponent(result, s21_get_exponent(value1));
  result->sign = result_sign;

  return error;
}

void s21_align_exponents(s21_decimal *a, s21_decimal *b) {
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

int s21_multiply_by_10_power(s21_decimal *value, int power) {
  for (int i = 0; i < power; i++) {
    s21_decimal temp = *value;
    s21_decimal temp2 = *value;
    s21_shift_left(&temp, 3);
    s21_shift_left(&temp2, 1);
    return s21_add(temp, temp2, value);
  }
  return 0;
}

int s21_div_by_10(s21_decimal *value, s21_decimal *result) {
  uint64_t remainder = 0;
  for (int i = 2; i >= 0; i--) {
    uint64_t current = ((uint64_t)remainder << 32) | value->bits[i];
    result->bits[i] = (uint32_t)(current / 10);
    remainder = current % 10;
  }

  return (remainder == 0) ? 0 : 1;
}

int s21_compare_absolute(s21_decimal a, s21_decimal b) {
  s21_align_exponents(&a, &b);
  for (int i = 2; i >= 0; i--) {
    if (a.bits[i] > b.bits[i])
      return 1;
    if (a.bits[i] < b.bits[i])
      return -1;
  }
  return 0;
}

unsigned int s21_get_exponent(s21_decimal src) {
  src.bits[3] &= ~SIGNBIT;
  return src.bits[3] >> 16;
}

void s21_set_exponent(s21_decimal *src, unsigned int exp) {
  if (!src || exp > 28)
    return;
  src->bits[3] = (exp << 16) | (src->bits[3] & SIGNBIT);
}

void s21_shift_left(s21_decimal *value, int shift) {
  for (int s = 0; s < shift; s++) {
    uint32_t carry_prev = 0;
    for (int i = 0; i < 3; i++) {
      uint32_t current = value->bits[i];
      value->bits[i] = (current << 1) | carry_prev;
      carry_prev = (current >> 31) & 1;
    }
    if (carry_prev != 0) {
      break;
    }
  }
}
