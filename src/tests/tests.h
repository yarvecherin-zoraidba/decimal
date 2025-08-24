#ifndef TEST_ME_H
#define TEST_ME_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../s21_decimal.h"
#include "../s21_decimal_functions.h"

Suite *s21_add_test(void);
Suite *s21_sub_test(void);
Suite *s21_mul_test(void);

#endif