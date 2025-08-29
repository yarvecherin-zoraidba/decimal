#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define LONG_BITS 192

typedef struct
{
    unsigned int bits[4];
} s21_decimal;

typedef struct
{
    int bits[LONG_BITS];
    char floa;
    char sign;
} s21_long_decimal;

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal *result);

void s21_long_add(s21_long_decimal value1, s21_long_decimal value2,
    s21_long_decimal *result);
void s21_long_sub(s21_long_decimal value1, s21_long_decimal value2,
    s21_long_decimal *result);
void s21_long_mul(s21_long_decimal value1, s21_long_decimal value2,
    s21_long_decimal *result);
s21_decimal s21_decimal_init();
s21_long_decimal s21_long_init();
void s21_decimal_to_long_decimal(s21_decimal value, s21_long_decimal *result);
void s21_long_float_check(s21_long_decimal *value_1, s21_long_decimal *value_2);
int s21_long_comparison(s21_long_decimal value_1, s21_long_decimal value_2);
void s21_long_add(s21_long_decimal value_1, s21_long_decimal value_2,
    s21_long_decimal *result);
void s21_long_sub(s21_long_decimal value_1, s21_long_decimal value_2,
    s21_long_decimal *result);
s21_long_decimal s21_long_ten_init();
void s21_long_to_decimal(s21_long_decimal value, s21_decimal *result);
void s21_long_mul(s21_long_decimal value_1, s21_long_decimal value_2,
    s21_long_decimal *result);
int s21_long_size_check(s21_long_decimal *value);
s21_long_decimal s21_long_div(s21_long_decimal value_1,
                s21_long_decimal value_2,
                s21_long_decimal *result);
int s21_long_size(s21_long_decimal value);
void s21_long_bank_round(s21_long_decimal value, s21_long_decimal mod,
           s21_long_decimal *result);
int s21_long_to_int(s21_long_decimal value);
void s21_long_shift(s21_long_decimal *value);
#endif



