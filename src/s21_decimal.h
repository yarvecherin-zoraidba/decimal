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
int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal *result);

#endif