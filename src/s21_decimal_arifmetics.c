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

s21_decimal s21_decimal_init() {
  s21_decimal result;
  for (int i = 0; i < 4; i++) {
    result.bits[i] = 0;
  }
  return result;
}

s21_long_decimal s21_long_init() {
  s21_long_decimal value;
  for (int i = 0; i < LONG_BITS; i++) {
    value.bits[i] = 0;
  }
  value.floa = 0;
  value.sign = 0;
  return value;
}

void s21_decimal_to_long_decimal(s21_decimal value, s21_long_decimal *result) {
  *result = s21_long_init();
  char *val_byte = (char *)value.bits;
  result->floa = *(val_byte + 14);
  result->sign = *(val_byte + 15);
  int counter = 0;
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 8; j++) {
      if (*(val_byte + i) & (1 << j))
        result->bits[counter] = 1;
      counter++;
    }
  }
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

  if (s21_long_size(value_mod))
    s21_long_bank_round(*value, value_mod, value);

  if (!s21_long_size(*value))
    *value = s21_long_init();

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
  char *res_byte = (char *)result->bits;
  *(res_byte + 14) = value.floa;
  *(res_byte + 15) = value.sign;
  int counter = 0;
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 8; j++)
      if (value.bits[counter++])
        *(res_byte + i) += 1 << j;
  }
}

void s21_long_mul(s21_long_decimal value_1, s21_long_decimal value_2,
                  s21_long_decimal *result) {
  *result = s21_long_init();
  int counter = 0;
  for (; counter < 192; counter++) {
    if (value_2.bits[counter])
      s21_long_add(*result, value_1, result);
    s21_long_shift(&value_1);
  }
  result->floa = value_1.floa + value_2.floa;
}

s21_long_decimal s21_long_div(s21_long_decimal value_1,
                              s21_long_decimal value_2,
                              s21_long_decimal *result) {
  *result = s21_long_init();
  s21_long_decimal value_ten = s21_long_ten_init();
  s21_long_decimal temp_divider;
  s21_long_decimal temp_result;
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

int s21_long_size(s21_long_decimal value) {
  int long_size = 0;
  for (int i = LONG_BITS - 1; !long_size && i >= 0; i--)
    if (value.bits[i])
      long_size = i + 1;
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
  for (int i = LONG_BITS - 1; i > 0; i--)
    value->bits[i] = value->bits[i - 1];
  value->bits[0] = 0;
}