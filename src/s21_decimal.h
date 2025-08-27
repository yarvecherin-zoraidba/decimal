#include <stdio.h>
#include <math.h>

#define SIGNBIT 0x80000000 
#define MIN_INT -2147483648

typedef struct {
    unsigned int bits[4]; 
} s21_decimal;


int s21_get_sign(s21_decimal src);
void s21_set_sign(s21_decimal *src, int sign);
int s21_negate(s21_decimal value, s21_decimal *result);
void s21_init(s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
unsigned int s21_get_exponent(s21_decimal src);
void s21_set_exponent(s21_decimal *src, unsigned int exponent);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_divide_by_10(s21_decimal *value);
