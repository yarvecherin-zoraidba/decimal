#ifndef S21_ROUND_H
#define S21_ROUND_H

#include "s21_decimal.h"
#include <string.h>

#define UINT_SIZE 32

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_divide_by_10(s21_decimal *value);

#endif