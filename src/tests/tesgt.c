#ifndef TEST_ME_H
#define TEST_ME_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../s21_decimal.h"

Suite *test_to_decimal_add(void);
Suite *test_to_decimal_sub(void);
Suite *test_to_decimal_mul(void);

#endif