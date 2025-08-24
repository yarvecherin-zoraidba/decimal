#include <check.h>

#include "tests.h"

START_TEST(s21_add_1) {
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

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 2;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 2;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 4;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 0;
  value_1.bits[1] = 2;
  value_1.bits[2] = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 2;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 4;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 2;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 2;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 4;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 10;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 10;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 1;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 10;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 1;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 10;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 1;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 1;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_9) {
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

  value_2.bits[0] = 55;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 2;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 2;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 155;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 2;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 10000;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 55;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 2;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 4;  // Float
  *(v2_byte + 15) = 0;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 1000055;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 4;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_11) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  s21_decimal exp_result = s21_decimal_init();
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;
  char *exp_res_byte = (char *)exp_result.bits;

  value_1.bits[0] = 10000;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;

  value_2.bits[0] = 55;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 2;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 4;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 999945;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 4;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_12) {
  s21_decimal value_1 = s21_decimal_init();
  s21_decimal value_2 = s21_decimal_init();
  s21_decimal result;
  int error = 0;
  int exp_error = 0;
  char *v1_byte = (char *)value_1.bits;
  char *v2_byte = (char *)value_2.bits;

  value_1.bits[0] = 0xffffffff;
  value_1.bits[1] = 0xffffffff;
  value_1.bits[2] = 0xffffffff;

  value_2.bits[0] = 1;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 0;  // Float
  *(v2_byte + 15) = 0;  // Sign

  error = s21_add(value_1, value_2, &result);
  exp_error = 1;

  ck_assert_int_eq(error, exp_error);
}
END_TEST

START_TEST(s21_add_13) {
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

  value_2.bits[0] = 16;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 0;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 1;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0xfffffffd;
  exp_result.bits[1] = 0xffffffff;
  exp_result.bits[2] = 0xffffffff;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

START_TEST(s21_add_14) {
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

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;

  *(v1_byte + 14) = 5;  // Float
  *(v1_byte + 15) = 0;  // Sign

  *(v2_byte + 14) = 2;  // Float
  *(v2_byte + 15) = 1;  // Sign

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;

  *(exp_res_byte + 14) = 0;
  *(exp_res_byte + 15) = 0;

  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
  }
}
END_TEST

Suite *s21_add_test(void) {
  Suite *suite = suite_create("\033[33m--s21_add--\033[0m");
  TCase *tcase_core = tcase_create("add_tc");
  tcase_add_test(tcase_core, s21_add_1);
  tcase_add_test(tcase_core, s21_add_2);
  tcase_add_test(tcase_core, s21_add_3);
  tcase_add_test(tcase_core, s21_add_4);
  tcase_add_test(tcase_core, s21_add_5);
  tcase_add_test(tcase_core, s21_add_6);
  tcase_add_test(tcase_core, s21_add_7);
  tcase_add_test(tcase_core, s21_add_8);
  tcase_add_test(tcase_core, s21_add_9);
  tcase_add_test(tcase_core, s21_add_10);
  tcase_add_test(tcase_core, s21_add_11);
  tcase_add_test(tcase_core, s21_add_12);
  tcase_add_test(tcase_core, s21_add_13);
  tcase_add_test(tcase_core, s21_add_14);
  suite_add_tcase(suite, tcase_core);
  return suite;
}
