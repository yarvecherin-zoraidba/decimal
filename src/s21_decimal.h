#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdio.h>
#include <limits.h>

typedef struct {
    unsigned int bits[4]; 
} s21_decimal;


int s21_get_sign(s21_decimal src);
void s21_set_sign(s21_decimal *src, int sign);
int s21_negate(s21_decimal value, s21_decimal *result);
void s21_zero_to_hero(s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
unsigned int s21_get_exp(s21_decimal src);
void s21_set_exp(s21_decimal *src, unsigned int exp);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

#endif