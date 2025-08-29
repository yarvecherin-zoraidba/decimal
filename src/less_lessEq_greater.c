#include "less_lessEq_greater.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL || is_OK_input_bits_data(&value_1) == 0 ||
      is_OK_input_bits_data(&value_2) == 0) {
    return -1;
  }
  int res = 0;
  unsigned sign = ((value_1.bits[3] ^ value_2.bits[3]) & SIGNBIT);
  int ex1 = (int)(value_1.bits[3] & EXBITS) >> 16;
  int ex2 = (int)(value_2.bits[3] & EXBITS) >> 16;
  ex2 = remove_zero_if_div_10(&value_2, ex2);
  int ex_result = 0;
  if (is_zero_num(&value_2) == 1) {
    res = 3;
  } else if (is_zero_num(&value_1) == 1) {
    set_zero_num(result);
    result->bits[3] |= sign;
  } else if ((ex_result = make_ex_1_2_zero(&value_1, &value_2, &ex1, &ex2)) <
             0) {
    res = (sign == 0U) ? 1 : 2;
  } else if (make_num_v1_greater_v2(&value_1, &ex_result, value_2) == -1) {
    res = 2;
  } else {
    set_zero_num(result);
    result->bits[3] |= sign;
    make_decimal_division(&value_1, &value_2, result, &ex_result);
    result->bits[3] |= (ex_result << 16);
  }
  return res;
}

int s21_is_less(s21_decimal v1, s21_decimal v2) {
  return (get_res_of_comparison(v1, v2) < 0);
}

int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2) {
  return (get_res_of_comparison(v1, v2) <= 0);
}

int s21_is_greater(s21_decimal v1, s21_decimal v2) {
  return (get_res_of_comparison(v1, v2) > 0);
}

int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2) {
  return (get_res_of_comparison(v1, v2) >= 0);
}

int s21_is_equal(s21_decimal v1, s21_decimal v2) {
  return (get_res_of_comparison(v1, v2) == 0);
}

int s21_is_not_equal(s21_decimal v1, s21_decimal v2) {
  return (get_res_of_comparison(v1, v2) != 0);
}

_Bool is_OK_input_bits_data(const s21_decimal *v) {
  _Bool fl_is_ok_input = 1;
  if (((v->bits[3] & NOT_VALIDBITS) != 0U) ||
      (((v->bits[3] & EXBITS) >> 16) > 28)) {
    fl_is_ok_input = 0;
  }
  return fl_is_ok_input;
}

_Bool is_zero_num(const s21_decimal *v) {
  return (v->bits[0] == 0U && v->bits[1] == 0U && v->bits[2] == 0U);
}

void set_zero_num(s21_decimal *v) { v->bits[0] = v->bits[1] = v->bits[2] = 0U; }

int get_res_of_comparison(s21_decimal v1, s21_decimal v2) {
  int res = 1;
  if (v1.bits[0] == 0U && v1.bits[1] == 0U && v1.bits[2] == 0U) {
    if (v2.bits[0] == 0U && v2.bits[1] == 0U && v2.bits[2] == 0U) {
      res = 0;
    } else if ((v2.bits[3] & SIGNBIT) == 0U) {
      res = -1;
    }
  } else if (v2.bits[0] == 0U && v2.bits[1] == 0U && v2.bits[2] == 0U) {
    ((v1.bits[3] & SIGNBIT) != 0U) && (res = -1);
  } else if ((v1.bits[3] & SIGNBIT) > (v2.bits[3] & SIGNBIT)) {
    res = -1;
  } else if ((v1.bits[3] & SIGNBIT) == (v2.bits[3] & SIGNBIT)) {
    int ex1 = (v1.bits[3] & EXBITS) >> 16;
    int ex2 = (v2.bits[3] & EXBITS) >> 16;
    if (ex1 < ex2) {
      res = (int)(change_num_by_mul_10(&v1, ex2 - ex1) != 0ULL);
      res = (res == 1) ? 1 : compare_with_same_ex(v1, v2);
    } else if (ex1 > ex2) {
      res = (int)(change_num_by_mul_10(&v2, ex1 - ex2) != 0ULL);
      res = (res == 1) ? -1 : compare_with_same_ex(v1, v2);
    } else {
      res = compare_with_same_ex(v1, v2);
    }
    if ((v1.bits[3] & SIGNBIT) != 0U) {
      res *= -1;
    }
  }
  return res;
}

int compare_with_same_ex(s21_decimal v1, s21_decimal v2) {
  int res = 1;
  if (v1.bits[2] < v2.bits[2]) {
    res = -1;
  } else if (v1.bits[2] == v2.bits[2]) {
    if (v1.bits[1] < v2.bits[1]) {
      res = -1;
    } else if (v1.bits[1] == v2.bits[1]) {
      if (v1.bits[0] < v2.bits[0]) {
        res = -1;
      } else if (v1.bits[0] == v2.bits[0]) {
        res = 0;
      }
    }
  }
  return res;
}

int make_num_v1_greater_v2(s21_decimal *v1, int *ex_result, s21_decimal v2) {
  int res = 0;
  s21_decimal v1_temp = *v1;
  while ((compare_with_same_ex(v1_temp, v2) == -1) && (res == 0)) {
    if ((change_num_by_mul_10(&v1_temp, 1) == 0ULL) && (*ex_result < 28)) {
      *v1 = v1_temp;
      (*ex_result)++;
    } else {
      res = (*ex_result >= 28) ? -1 : 1;
    }
  }
  return res;
}

unsigned long long change_num_by_mul_10(s21_decimal *v, int delta_ex) {
  unsigned long long overflow = 0ULL;
  for (int d = delta_ex; d > 0 && overflow == 0ULL; d--) {
    for (int i = 0; i < 3; i++) {
      overflow += ((unsigned long long)v->bits[i] * 10ULL);
      v->bits[i] = (unsigned)overflow;
      overflow = overflow >> 32;
    }
  }
  return overflow;
}

int remove_zero_if_div_10(s21_decimal *v, int delta_ex) {
  int ex_v = (int)((v->bits[3] & EXBITS) >> 16);
  int remainder = 0;
  while (delta_ex-- > 0 && ex_v > 0 && remainder == 0) {
    s21_decimal v_temp = *v;
    remainder = divide_by_10(&v_temp);
    if (remainder == 0) {
      *v = v_temp;
      ex_v--;
    }
  }
  v->bits[3] &= SIGNBIT;
  v->bits[3] |= (ex_v << 16);
  return ex_v;
}

int divide_by_10(s21_decimal *v) {
  unsigned long long remainder = 0ULL;
  for (int i = 2; i >= 0; i--) {
    unsigned long long temp = (remainder << 32) | v->bits[i];
    v->bits[i] = (unsigned)(temp / 10ULL);
    remainder = temp % 10;
  }
  return (int)remainder;
}

int make_ex_1_2_zero(s21_decimal *v1, s21_decimal *v2, int *ex1, int *ex2) {
  int ex_result = *ex1 - *ex2;
  if (ex_result < 0) {
    _Bool fl_overflow_v1 = (change_num_by_mul_10(v1, -ex_result) != 0ULL);
    if (fl_overflow_v1 == 0) {
      ex_result = 0;
    }
  }
  *ex1 = *ex2 = 0;
  v1->bits[3] &= (~EXBITS);
  v2->bits[3] &= (~EXBITS);
  return ex_result;
}

void make_decimal_division(const s21_decimal *v1, const s21_decimal *v2,
                           s21_decimal *result, int *ex_result) {
  unsigned quotient[7] = {0};
  unsigned v1_b_num[7] = {v1->bits[0], v1->bits[1], v1->bits[2], 0, 0, 0, 0};
  unsigned v2_b_num[7] = {v2->bits[0], v2->bits[1], v2->bits[2], 0, 0, 0, 0};
  change_b_num_by_mul_10(v1_b_num, 30);
  divide_b_nums(v1_b_num, v2_b_num, quotient);
  change_b_num_for_s21_decimal(quotient, result, ex_result);
}

void change_b_num_by_mul_10(unsigned *n, int delta_ex) {
  unsigned long long overflow = 0ULL;
  for (int d = delta_ex; d > 0 && overflow == 0ULL; d--) {
    for (int i = 0; i < 7; i++) {
      overflow += ((unsigned long long)n[i] * 10ULL);
      n[i] = (unsigned)overflow;
      overflow = overflow >> 32;
    }
  }
}

void divide_b_nums(const unsigned *dividend, const unsigned *divisor,
                   unsigned *quotient) {
  unsigned remainder[7] = {0};
  if (compare_b_num(divisor, dividend) == 1) {
    for (int i = 0; i < 7; i++) {
      remainder[i] = dividend[i];
    }
  } else {
    for (int i = 223; i >= 0; i--) {
      shift_left_b_num(remainder);
      if (check_bit_in_indx_b_num(dividend, i) != 0) {
        remainder[0] |= 1U;
      }
      if (compare_b_num(remainder, divisor) >= 0) {
        unsigned temp[7] = {0};
        substract_b_nums_by_bitwise(remainder, divisor, temp);
        for (int j = 0; j < 7; j++) {
          remainder[j] = temp[j];
        }
        set_bit_in_indx_b_num(quotient, i, 1);
      }
    }
  }
}

int compare_b_num(const unsigned *n1, const unsigned int *n2) {
  int res = 0;
  for (int i = 6; i >= 0 && res == 0; i--) {
    if (n1[i] < n2[i]) {
      res = -1;
    } else if (n1[i] > n2[i]) {
      res = 1;
    }
  }
  return res;
}

void shift_left_b_num(unsigned *n) {
  unsigned carry = 0;
  for (int i = 0; i < 7; i++) {
    unsigned int current = n[i];
    n[i] = (current << 1) | carry;
    carry = current >> 31;
  }
}

int check_bit_in_indx_b_num(const unsigned *num, int indx) {
  return (int)((num[indx / 32] >> (indx % 32)) & 1U);
}

void set_bit_in_indx_b_num(unsigned *n, int indx, int value) {
  (value == 0) ? (n[indx / 32] &= ~(1U << (indx % 32)))
               : (n[indx / 32] |= (1U << (indx % 32)));
}

int substract_b_nums_by_bitwise(const unsigned *n1, const unsigned *n2,
                                unsigned int *difference) {
  for (int i = 0; i < 7; i++) {
    difference[i] = 0;
  }
  int borrow = 0;
  for (int i = 0; i < 224; i++) {
    int bit_n1 = (n1[i / 32] >> (i % 32)) & 1U;
    int bit_n2 = (n2[i / 32] >> (i % 32)) & 1U;
    int delta = bit_n1 - bit_n2 - borrow;
    if (delta < 0) {
      delta += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }
    if (delta == 1) {
      difference[i / 32] |= (1U << (i % 32));
    }
  }
  return borrow;
}

void change_b_num_for_s21_decimal(unsigned *quotient, s21_decimal *result,
                                  int *ex_result) {
  int ex_current = *ex_result + 30;
  if (is_zero_high_blocks_of_b_num(quotient) == 0) {
    int remainder = 0;
    while (is_zero_high_blocks_of_b_num(quotient) == 0 || ex_current > 28) {
      remainder = divide_b_num_by_10(quotient);
      ex_current--;
    }
    round_banks_decimal(quotient, remainder, &ex_current);
  }
  remove_all_zeros_from_b_num_if_div_10(quotient, &ex_current);
  for (int i = 0; i < 3; i++) {
    result->bits[i] = quotient[i];
  }
  *ex_result = ex_current;
}

_Bool is_zero_high_blocks_of_b_num(const unsigned *n) {
  _Bool fl_is_zero_high_blocks = 0;
  if (n[3] == 0 && n[4] == 0 && n[5] == 0 && n[6] == 0) {
    fl_is_zero_high_blocks = 1;
  }
  return fl_is_zero_high_blocks;
}

int divide_b_num_by_10(unsigned *n) {
  unsigned long long remainder = 0ULL;
  for (int i = 6; i >= 0; i--) {
    unsigned long long temp = (remainder << 32) | n[i];
    n[i] = (unsigned)(temp / 10ULL);
    remainder = temp % 10;
  }
  return (int)remainder;
}

void round_banks_decimal(unsigned *n, int digit, int *ex_current) {
  unsigned temp_n[7] = {0};
  for (int i = 0; i < 3; i++) {
    temp_n[i] = n[i];
  }
  int remainder = divide_b_num_by_10(temp_n);
  remainder %= 2;
  if (digit > 5 || (digit == 5U && remainder == 1)) {
    for (int i = 0; i < 3; i++) {
      temp_n[i] = n[i];
    }
    if (add_digit_in_3_low_b_num(temp_n, 1) == 0) {
      for (int i = 0; i < 3; i++) {
        n[i] = temp_n[i];
      }
    } else {
      remainder = divide_b_num_by_10(n);
      (*ex_current)--;
      round_banks_decimal(n, remainder, ex_current);
    }
  }
}

_Bool add_digit_in_3_low_b_num(unsigned *n, int digit) {
  unsigned long long overflow = (unsigned long long)(digit);
  for (int i = 0; i < 3; i++) {
    overflow += (unsigned long long)n[i];
    n[i] = (unsigned)overflow;
    overflow = overflow >> 32;
  }
  return (overflow != 0ULL);
}

void remove_all_zeros_from_b_num_if_div_10(unsigned *n, int *ex_current) {
  int remainder = 0;
  while (*ex_current > 0 && remainder == 0) {
    unsigned temp_n[7] = {0};
    for (int i = 0; i < 3; i++) {
      temp_n[i] = n[i];
    }
    remainder = divide_b_num_by_10(temp_n);
    if (remainder == 0) {
      for (int i = 0; i < 3; i++) {
        n[i] = temp_n[i];
      }
      (*ex_current)--;
    }
  }
}