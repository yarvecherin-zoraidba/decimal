#include "s21_decimal.h"

int s21_get_sign(s21_decimal src) { return (src.bits[3] & SIGNBIT) ? 1 : 0; }

void s21_set_sign(s21_decimal *src, int sign) {
  if (sign) {
    src->bits[3] |= SIGNBIT;
  } else {
    src->bits[3] &= ~SIGNBIT;
  }
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result == NULL || is_OK_input_bits_data(&value) == 0) {
    status = 1;
  } else {
    *result = value;
    s21_set_sign(result, !s21_get_sign(value));
  }
  return status;
}

void s21_init(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = 1;
  if (dst != NULL) {
    s21_init(dst);
    if (src < 0) {
      dst->bits[3] = SIGNBIT;
      dst->bits[0] = (unsigned int)(-src);
    } else {
      dst->bits[0] = (unsigned int)src;
    }
    status = 0;
  }
  return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL || is_OK_input_bits_data(&src) == 0) {
    return 1;
  }

  int sign = s21_get_sign(src) ? -1 : 1;
  unsigned int scale = s21_get_exp(src);

  unsigned int values[3] = {src.bits[0], src.bits[1], src.bits[2]};

  for (unsigned int s = 0; s < scale; s++) {
    unsigned int remainder = 0;
    for (int i = 2; i >= 0; i--) {
      unsigned long long temp =
          ((unsigned long long)remainder << 32) | values[i];
      values[i] = (unsigned int)(temp / 10);
      remainder = (unsigned int)(temp % 10);
    }
  }

  int has_overflow = (values[1] > 0 || values[2] > 0);

  if (values[1] > 0 || values[2] > 0) {
    has_overflow = 1;
  }

  int is_min_int =
      (sign == -1 && values[0] == SIGNBIT && values[1] == 0 && values[2] == 0);

  int overflow =
      (sign == 1 && values[0] > MAX_INT) || (sign == -1 && values[0] > SIGNBIT);

  if (has_overflow != 0 || overflow != 0) {
    *dst = 0;
  } else if (is_min_int != 0) {
    *dst = MIN_INT;
  } else {
    *dst = sign * (int)values[0];
  }

  return (has_overflow || overflow) ? 1 : 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL || is_OK_input_bits_data(&src) == 0) {
    return 1;
  }
  double res = 0.0;
  double factor = 1.0;

  for (int bit_block = 0; bit_block < 3; bit_block++) {
    for (int bit_pos = 0; bit_pos < 32; bit_pos++) {
      if (src.bits[bit_block] & (1U << bit_pos)) {
        res += factor;
      }
      factor *= 2.0;
    }
  }
  unsigned int scale = s21_get_exp(src);
  for (unsigned int i = 0; i < scale; i++) {
    res /= 10.0;
  }

  if (src.bits[3] & SIGNBIT) {
    res = -res;
  }

  *dst = (float)res;
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL) {
    return 1;
  }
  s21_init(dst);

  if (isinf(src) || isnan(src) || (src > 0 && src < 1e-28) ||
      (src < 0 && src > -1e-28)) {
    s21_init(dst);
    return 1;
  }

  if (src < 0) {
    dst->bits[3] |= SIGNBIT;
    src = -src;
  }

  unsigned int scale = 0;
  while (src > 0 && src < 1000000.0 && scale < 28) {
    src *= 10.0;
    scale++;
  }

  unsigned int float_bits = *(unsigned int *)&src;
  int float_exponent = ((float_bits >> 23) & 0xFF) - 127;
  unsigned int mantissa = float_bits & 0x7FFFFF;  // 0-22

  if (float_exponent >= 0) {
    mantissa |= 0x800000;
  }
  if (mantissa != 0) {
    for (int bit_pos = 23; bit_pos >= 0; bit_pos--) {
      if (mantissa & (1U << bit_pos)) {
        int target_pos = float_exponent - (23 - bit_pos);
        if (target_pos >= 0 && target_pos < 96) {
          int block = target_pos / 32;
          int bit = target_pos % 32;
          if (block < 3) {
            dst->bits[block] |= (1U << bit);
          }
        }
      }
    }
  }

  dst->bits[3] |= (scale << 16);
  remove_zero_if_div_10(dst, 28);

  return 0;
}

unsigned int s21_get_exp(s21_decimal src) {
  src.bits[3] &= EXBITS;
  return src.bits[3] >> 16;
}

// karkaror
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
  if (s21_is_zero96(&value_2) == 1) {
    res = 3;
  } else if (s21_is_zero96(&value_1) == 1) {
    s21_init(result);
    result->bits[3] |= sign;
  } else if ((ex_result = make_ex_1_2_zero(&value_1, &value_2, &ex1, &ex2)) <
             0) {
    res = (sign == 0U) ? 1 : 2;
  } else if (make_num_v1_greater_v2(&value_1, &ex_result, value_2) == -1) {
    res = 2;
  } else {
    s21_init(result);
    result->bits[3] |= sign;
    make_decimal_division(&value_1, &value_2, result, &ex_result);
    result->bits[3] |= (ex_result << 16);
  }
  return res;
}

int s21_is_less(s21_decimal v1, s21_decimal v2) {
  if (is_OK_input_bits_data(&v1) == 0 || is_OK_input_bits_data(&v2) == 0) {
    return -1;
  }
  return (get_res_of_comparison(v1, v2) < 0);
}

int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2) {
  if (is_OK_input_bits_data(&v1) == 0 || is_OK_input_bits_data(&v2) == 0) {
    return -1;
  }
  return (get_res_of_comparison(v1, v2) <= 0);
}

int s21_is_greater(s21_decimal v1, s21_decimal v2) {
  if (is_OK_input_bits_data(&v1) == 0 || is_OK_input_bits_data(&v2) == 0) {
    return -1;
  }
  return (get_res_of_comparison(v1, v2) > 0);
}

int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2) {
  if (is_OK_input_bits_data(&v1) == 0 || is_OK_input_bits_data(&v2) == 0) {
    return -1;
  }
  return (get_res_of_comparison(v1, v2) >= 0);
}

int s21_is_equal(s21_decimal v1, s21_decimal v2) {
  if (is_OK_input_bits_data(&v1) == 0 || is_OK_input_bits_data(&v2) == 0) {
    return -1;
  }
  return (get_res_of_comparison(v1, v2) == 0);
}

int s21_is_not_equal(s21_decimal v1, s21_decimal v2) {
  if (is_OK_input_bits_data(&v1) == 0 || is_OK_input_bits_data(&v2) == 0) {
    return -1;
  }
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

// mushroot
int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  if (result == NULL || is_OK_input_bits_data(&value1) == 0 ||
      is_OK_input_bits_data(&value2) == 0) {
    return -1;
  }
  *result = s21_decimal_init();
  int error = 0;
  s21_long_decimal longValue1 = {0};
  s21_long_decimal longValue2 = {0};
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

  if (error == 2 || error == 1) {
    s21_init(result);
  }

  return error;
}

int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  if (result == NULL || is_OK_input_bits_data(&value1) == 0 ||
      is_OK_input_bits_data(&value2) == 0) {
    return -1;
  }

  int error = 0;
  if (s21_is_equal(value1, value2) == 1) {
    s21_init(result);
    result->bits[3] = ((_Bool)s21_get_sign(value1) << 31);
  } else {
    *result = s21_decimal_init();
    s21_long_decimal longValue1 = {0};
    s21_long_decimal longValue2 = {0};
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

    if (error == 2 || error == 1) {
      s21_init(result);
    }
  }
  return error;
}

s21_decimal s21_decimal_init() {
  s21_decimal result = {0};
  return result;
}

s21_long_decimal s21_long_init() {
  s21_long_decimal value = {0};
  for (int i = 0; i < LONG_BITS; i++) {
    value.bits[i] = 0;
  }
  value.floa = 0;
  value.sign = 0;
  return value;
}

void s21_decimal_to_long_decimal(s21_decimal value, s21_long_decimal *result) {
  *result = s21_long_init();
  int counter = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      result->bits[counter++] = (value.bits[i] >> j) & 1;
    }
  }
  result->sign = (value.bits[3] & (1u << 31)) ? 1 : 0;
  result->floa = (value.bits[3] >> 16) & 0xFF;
}

void s21_long_float_check(s21_long_decimal *value_1,
                          s21_long_decimal *value_2) {
  s21_long_decimal value_ten = s21_long_ten_init();
  value_ten.floa = 1;
  int sign1 = value_1->sign;
  int sign2 = value_2->sign;
  while (value_1->floa != value_2->floa) {
    if (value_1->floa > value_2->floa)
      s21_long_mul(*value_2, value_ten, value_2);
    else
      s21_long_mul(*value_1, value_ten, value_1);
  }
  value_1->sign = sign1;
  value_2->sign = sign2;
}

int s21_long_comparison(s21_long_decimal value_1, s21_long_decimal value_2) {
  int result = 0;
  for (int i = LONG_BITS - 1; i >= 0 && !result; i--) {
    if (value_1.bits[i] ^ value_2.bits[i])
      result = value_1.bits[i] * 1 + value_2.bits[i] * 2;
  }
  return result;
}

void s21_long_add(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal *result) {
  *result = s21_long_init();
  int free_bit = 0;
  for (int i = 0; i < 192; i++) {
    result->bits[i] = value_1.bits[i] ^ value_2.bits[i] ^ free_bit;
    free_bit = (value_1.bits[i] + value_2.bits[i] + free_bit) > 1;
  }
  result->floa = value_1.floa;
}

void s21_long_sub(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal *result) {
  *result = s21_long_init();
  int debt_bit = 0;
  for (int i = 0; i < 192; i++) {
    result->bits[i] = value_1.bits[i] ^ value_2.bits[i] ^ debt_bit;
    if (!value_1.bits[i] && (value_2.bits[i] || debt_bit))
      debt_bit = 1;
    else if (value_1.bits[i] && value_2.bits[i] && debt_bit)
      debt_bit = 1;
    else
      debt_bit = 0;
  }
  result->floa = value_1.floa;
}

int s21_long_size_check(s21_long_decimal *value) {
  int error = 0;
  int val_sign = value->sign;
  s21_long_decimal value_ten = s21_long_ten_init();
  s21_long_decimal value_mod = s21_long_init();
  value_ten.floa = 1;

  while (s21_long_comparison(value_ten, *value) == 2 && value->floa > 28)
    value_mod = s21_long_div(*value, value_ten, value);

  while (s21_long_size(*value) > 96 && value->floa)
    value_mod = s21_long_div(*value, value_ten, value);

  if (s21_long_size(value_mod)) s21_long_bank_round(*value, value_mod, value);

  if (!s21_long_size(*value)) *value = s21_long_init();

  if (s21_long_size(*value) > 96)
    error = val_sign * 2 + !val_sign * 1;
  else if (value->floa > 28)
    error = 2;

  value->sign = val_sign;
  return error;
}

s21_long_decimal s21_long_ten_init() {
  s21_long_decimal value_ten = s21_long_init();
  value_ten.bits[1] = 1;
  value_ten.bits[3] = 1;
  return value_ten;
}

void s21_long_to_decimal(s21_long_decimal value, s21_decimal *result) {
  *result = s21_decimal_init();
  int counter = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      if (value.bits[counter++]) {
        result->bits[i] |= (1u << j);
      }
    }
  }
  result->bits[3] = 0;
  if (value.sign) {
    result->bits[3] |= (1u << 31);
  }
  result->bits[3] |= ((value.floa & 0xFF) << 16);
}

void s21_long_mul(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal *result) {
  *result = s21_long_init();
  int counter = 0;
  for (; counter < 192; counter++) {
    if (value_2.bits[counter]) s21_long_add(*result, value_1, result);
    s21_long_shift(&value_1);
  }
  result->floa = value_1.floa + value_2.floa;
}

int s21_long_size(s21_long_decimal value) {
  int long_size = 0;
  for (int i = LONG_BITS - 1; !long_size && i >= 0; i--)
    if (value.bits[i]) long_size = i + 1;
  return long_size;
}

void s21_long_bank_round(s21_long_decimal value, s21_long_decimal mod,
                         s21_long_decimal *result) {
  int val_mod = s21_long_to_int(mod);
  if (val_mod > 5 || (val_mod == 5 && value.bits[0])) {
    s21_long_decimal value_one = s21_long_init();
    value_one.bits[0] = 1;
    s21_long_add(value, value_one, result);
    result->sign = value.sign;
  } else
    *result = value;
}

int s21_long_to_int(s21_long_decimal value) {
  int num = 0;
  int counter = 0;
  for (int i = 0; i < 4; i++) {
    if (!i)
      counter = 1;
    else
      counter += counter;
    num += value.bits[i] * counter;
  }
  return num;
}

void s21_long_shift(s21_long_decimal *value) {
  for (int i = LONG_BITS - 1; i > 0; i--) value->bits[i] = value->bits[i - 1];
  value->bits[0] = 0;
}

s21_long_decimal s21_long_div(s21_long_decimal value_1,
                              s21_long_decimal value_2,
                              s21_long_decimal *result) {
  *result = s21_long_init();
  s21_long_decimal value_ten = s21_long_ten_init();
  s21_long_decimal temp_divider = {0};
  s21_long_decimal temp_result = {0};
  int floa_1 = value_1.floa;
  int floa_2 = value_2.floa;
  value_1.floa = 0;
  value_2.floa = 0;
  for (; s21_long_comparison(value_1, value_2) == 2; floa_1++)
    s21_long_mul(value_1, value_ten, &value_1);
  while (s21_long_comparison(value_1, value_2) < 2) {
    temp_divider = s21_long_init();
    int counter = 0;
    for (; s21_long_comparison(value_1, temp_result) < 2 && counter < 192;
         counter++) {
      temp_divider.bits[counter] = 1;
      s21_long_mul(value_2, temp_divider, &temp_result);
      temp_divider.bits[counter] = 0;
    }
    temp_divider.bits[counter - 2] = 1;
    s21_long_add(*result, temp_divider, result);
    s21_long_mul(value_2, temp_divider, &temp_result);
    s21_long_sub(value_1, temp_result, &value_1);
  }

  value_1.floa = floa_1;
  result->floa = floa_1 - floa_2;
  for (; result->floa < 0; result->floa += 1)
    s21_long_mul(*result, value_ten, result);
  return value_1;
}

// charlesj
int s21_is_zero96(const s21_decimal *d) {
  return d->bits[0] == 0u && d->bits[1] == 0u && d->bits[2] == 0u;
}

void s21_big_zero(unsigned big[], int n) {
  for (int i = 0; i < n; ++i) big[i] = 0u;
}

unsigned s21_big_inc(unsigned big[], int n) {
  unsigned long long carry = 1u;
  for (int i = 0; i < n && carry; ++i) {
    unsigned long long sum = (unsigned long long)big[i] + carry;
    big[i] = (unsigned)(sum & 0xFFFFFFFFu);
    carry = sum >> 32;
  }
  return (unsigned)carry;
}

unsigned s21_big_div10(unsigned big[], int n) {
  unsigned long long rem = 0;
  for (int i = n - 1; i >= 0; --i) {
    unsigned long long cur = (rem << 32) | (unsigned long long)big[i];
    big[i] = (unsigned)(cur / 10u);
    rem = cur % 10u;
  }
  return (unsigned)rem;
}

unsigned s21_big_mod10_const(const unsigned big[], int n) {
  unsigned long long rem = 0;
  for (int i = n - 1; i >= 0; --i) {
    unsigned long long cur = (rem << 32) | (unsigned long long)big[i];
    rem = cur % 10u;
  }
  return (unsigned)rem;
}

int s21_big_fits_96(const unsigned big[]) {
  return big[3] == 0u && big[4] == 0u && big[5] == 0u;
}

void s21_mul_96x96_to_192(const s21_decimal *x, const s21_decimal *y,
                          unsigned out[], int n) {
  s21_big_zero(out, n);
  for (int i = 0; i < S21_96_LIMBS; ++i) {
    unsigned long long carry = 0;
    for (int j = 0; j < S21_96_LIMBS; ++j) {
      unsigned long long cur =
          (unsigned long long)x->bits[i] * (unsigned long long)y->bits[j];
      unsigned long long sum = (unsigned long long)out[i + j] + cur + carry;
      out[i + j] = (unsigned)(sum & 0xFFFFFFFFu);
      carry = sum >> 32;
    }
    int k = i + S21_96_LIMBS;
    while (carry && k < n) {
      unsigned long long sum = (unsigned long long)out[k] + carry;
      out[k] = (unsigned)(sum & 0xFFFFFFFFu);
      carry = sum >> 32;
      ++k;
    }
  }
}

void s21_big_round_div10_bankers(unsigned big[], int n, unsigned rem,
                                 int sticky) {
  if (rem > 5u) {
    (void)s21_big_inc(big, n);
  } else if (rem == 5u) {
    if (sticky) {
      (void)s21_big_inc(big, n);
    } else {
      if (s21_big_mod10_const(big, n) & 1u) {
        (void)s21_big_inc(big, n);
      }
    }
  }
}

void s21_zero_decimal(s21_decimal *d) {
  d->bits[0] = d->bits[1] = d->bits[2] = d->bits[3] = 0u;
}

int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result) {
  if (result == NULL || is_OK_input_bits_data(&a) == 0 ||
      is_OK_input_bits_data(&b) == 0) {
    return -1;
  }
  int status = S21_OK;
  s21_zero_decimal(result);
  int sign = s21_get_sign(a) ^ s21_get_sign(b);
  if (s21_is_zero96(&a) || s21_is_zero96(&b)) {
    s21_set_exp(result, 0);
    s21_set_sign(result, sign);
  } else {
    unsigned scale = (unsigned)s21_get_exp(a) + (unsigned)s21_get_exp(b);
    a.bits[3] = 0u;
    b.bits[3] = 0u;
    unsigned big[S21_LIMB_COUNT_192];
    s21_mul_96x96_to_192(&a, &b, big, S21_LIMB_COUNT_192);
    if (scale > 28u) {
      unsigned drop = scale - 28u;
      int sticky = 0;
      for (unsigned t = 0; t < drop; ++t) {
        unsigned rem = s21_big_div10(big, S21_LIMB_COUNT_192);
        s21_big_round_div10_bankers(big, S21_LIMB_COUNT_192, rem, sticky);
        if (rem != 0u) sticky = 1;
      }
      scale = 28u;
    }
    int sticky = 0;
    while (!s21_big_fits_96(big) && status == S21_OK) {
      if (scale == 0u) {
        status = sign ? S21_INF_NEG : S21_INF_POS;
      } else {
        unsigned rem = s21_big_div10(big, S21_LIMB_COUNT_192);
        s21_big_round_div10_bankers(big, S21_LIMB_COUNT_192, rem, sticky);
        if (rem != 0u) sticky = 1;
        --scale;
      }
    }
    if (status == S21_OK) {
      result->bits[0] = big[0];
      result->bits[1] = big[1];
      result->bits[2] = big[2];
      if (result->bits[0] == 0u && result->bits[1] == 0u &&
          result->bits[2] == 0u) {
        s21_set_exp(result, 0);
        s21_set_sign(result, sign);
      } else {
        s21_set_exp(result, (int)scale);
        s21_set_sign(result, sign);
      }
    }
  }
  return status;
}

// zoraidba
int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;

  if (result == NULL || is_OK_input_bits_data(&value) == 0)
    error = 1;
  else {
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

  if (result == NULL || is_OK_input_bits_data(&value) == 0)
    error = 1;
  else {
    unsigned int scale = s21_get_exp(value);
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

  if (result == NULL || is_OK_input_bits_data(&value) == 0)
    error = 1;
  else {
    int scale = s21_get_exp(value);
    *result = value;

    while ((scale--) != 0) {
      divide_by_10(result);
    }
    s21_set_exp(result, 0);
  }

  return error;
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

void s21_set_exp(s21_decimal *src, unsigned int exp) {
  src->bits[3] = (exp << 16) | (src->bits[3] & SIGNBIT);
}