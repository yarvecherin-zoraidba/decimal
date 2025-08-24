#include <stdio.h>

#include "tests.h"

START_TEST(s21_mul_1) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 1;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 1;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_2) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_3) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 1;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_4) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 1;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 1;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 1;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 1;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_5) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 1;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 1;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 1;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_6) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 1000;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 8;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 1;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 8000;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_7) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 0;
  value_1.bits[1] = 1000;
  value_1.bits[2] = 0;

  value_2.bits[0] = 8;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 1;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 8000;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_8) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 1000;

  value_2.bits[0] = 8;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 1;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 8000;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_9) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 1000;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 100;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 2;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 100000;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 2;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_10) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 100;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 100;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 2;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 2;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = 10000;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 4;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_11) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;
  value_1.bits[0] = 0xffffffff;
  value_1.bits[1] = 0xffffffff;
  value_1.bits[2] = 0xffffffff;

  value_2.bits[0] = 0xffffffff;
  value_2.bits[1] = 0xffffffff;
  value_2.bits[2] = 0xffffffff;

  *(v1_byte + 14) = 15;  // Float
  *(v1_byte + 15) = 0;   // Sign

  *(v2_byte + 14) = 15;  // Float
  *(v2_byte + 15) = 0;   // Sign

  s21_mul(value_1, value_2, &result);

  exp_result.bits[0] = -1670508211;
  exp_result.bits[1] = -1018700142;
  exp_result.bits[2] = 1020847100;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
}
END_TEST

START_TEST(s21_mul_12) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  int exp_res = 1;

  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;

  value_1.bits[0] = 0xffffffff;
  value_1.bits[1] = 0xffffffff;
  value_1.bits[2] = 0xffffffff;

  value_2.bits[0] = 3;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  int res = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(res, exp_res);
}
END_TEST

START_TEST(s21_mul_13) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  int exp_res = 2;

  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;

  value_1.bits[0] = 0xffffffff;
  value_1.bits[1] = 0xffffffff;
  value_1.bits[2] = 0xffffffff;

  value_2.bits[0] = 3;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 1;  // Sign

  int res = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(res, exp_res);
}
END_TEST

START_TEST(s21_mul_14) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  int exp_res = 2;

  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;

  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 1;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 28;  // Float
  *(v1_byte + 15) = 0;   // Sign

  *(v2_byte + 14) = 5;  // Float
  *(v2_byte + 15) = 0;  // Sign

  int res = s21_mul(value_1, value_2, &result);

  ck_assert_int_eq(res, exp_res);
}
END_TEST

Suite *s21_mul_test(void) {
  Suite *suite = suite_create("\033[33m--s21_mul--\033[0m");
  TCase *tcase_core = tcase_create("mul_tc");
  tcase_add_test(tcase_core, s21_mul_1);
  tcase_add_test(tcase_core, s21_mul_2);
  tcase_add_test(tcase_core, s21_mul_3);
  tcase_add_test(tcase_core, s21_mul_4);
  tcase_add_test(tcase_core, s21_mul_5);
  tcase_add_test(tcase_core, s21_mul_6);
  tcase_add_test(tcase_core, s21_mul_7);
  tcase_add_test(tcase_core, s21_mul_8);
  tcase_add_test(tcase_core, s21_mul_9);
  tcase_add_test(tcase_core, s21_mul_10);
  tcase_add_test(tcase_core, s21_mul_11);
  tcase_add_test(tcase_core, s21_mul_12);
  tcase_add_test(tcase_core, s21_mul_13);
  tcase_add_test(tcase_core, s21_mul_14);
  suite_add_tcase(suite, tcase_core);
  return suite;
}
