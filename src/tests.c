#include "s21_decimal.h"
#include <check.h>

Suite *s21_suite(void);

int main() {
  SRunner *sr = srunner_create(NULL);

  srunner_add_suite(sr, s21_suite());

  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed == 0 ? 0 : 1;
}

START_TEST(s21_add_1) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_2) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 2;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 2;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 4;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_3) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 2;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 2;
  value_2.bits[2] = 0;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 4;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_4) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 2;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 2;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 4;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_5) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 10;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 1;
  value_2.exp = 0;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_6) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 10;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 1;
  value_2.exp = 0;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 1;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_7) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 1;
  value_1.exp = 0;

  value_2.bits[0] = 10;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_8) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 10;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 1;
  value_1.exp = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 1;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_9) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 100;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 2;

  value_2.bits[0] = 55;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 0;
  value_2.exp = 2;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 155;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 2;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_10) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 10000;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 2;

  value_2.bits[0] = 55;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 0;
  value_2.exp = 4;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 1000055;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 4;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_11) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 10000;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 2;

  value_2.bits[0] = 55;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 1;
  value_2.exp = 4;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 999945;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 4;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_add_12) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  int error = 0;
  int exp_error = 1;

  value_1.bits[0] = 0xffffffff;
  value_1.bits[1] = 0xffffffff;
  value_1.bits[2] = 0xffffffff;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 1;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 0;
  value_2.exp = 0;

  error = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(error, exp_error);
}
END_TEST

START_TEST(s21_add_13) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.sign = 0;
  value_1.exp = 5;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.sign = 1;
  value_2.exp = 2;

  s21_add(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 0;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_1) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 0;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 0;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 1;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 2;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 1;
  exp_result.sign = 1;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 1;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 2;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 1;
  exp_result.sign = 1;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 1;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 2;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 0;
  exp_result.bits[1] = 0;
  exp_result.bits[2] = 1;
  exp_result.sign = 1;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 10;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 5;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 5;
  value_1.sign = 0;
  value_1.exp = 0;

  value_2.bits[0] = 10;
  value_2.sign = 0;
  value_2.exp = 0;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.sign = 1;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 5;
  value_1.sign = 1;
  value_1.exp = 0;

  value_2.bits[0] = 10;
  value_2.sign = 1;
  value_2.exp = 0;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.sign = 0;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_8) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 10;
  value_1.sign = 1;
  value_1.exp = 0;

  value_2.bits[0] = 5;
  value_2.sign = 1;
  value_2.exp = 0;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 5;
  exp_result.sign = 1;
  exp_result.exp = 0;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_9) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 100;
  value_1.sign = 0;
  value_1.exp = 2;

  value_2.bits[0] = 55;
  value_2.sign = 0;
  value_2.exp = 2;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 45;
  exp_result.sign = 0;
  exp_result.exp = 2;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_10) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 10000;
  value_1.sign = 0;
  value_1.exp = 2;

  value_2.bits[0] = 55;
  value_2.sign = 0;
  value_2.exp = 4;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 999945;
  exp_result.sign = 0;
  exp_result.exp = 4;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

START_TEST(s21_sub_11) {
  s21_another_decimal value_1 = {0};
  s21_another_decimal value_2 = {0};
  s21_another_decimal result = {0};
  s21_another_decimal exp_result = {0};

  value_1.bits[0] = 10000;
  value_1.sign = 0;
  value_1.exp = 2;

  value_2.bits[0] = 55;
  value_2.sign = 1;
  value_2.exp = 4;

  s21_sub(value_1, value_2, &result);

  exp_result.bits[0] = 1000055;
  exp_result.sign = 0;
  exp_result.exp = 4;

  ck_assert_int_eq(result.bits[0], exp_result.bits[0]);
  ck_assert_int_eq(result.bits[1], exp_result.bits[1]);
  ck_assert_int_eq(result.bits[2], exp_result.bits[2]);
  ck_assert_int_eq(result.sign, exp_result.sign);
  ck_assert_int_eq(result.exp, exp_result.exp);
}
END_TEST

Suite *s21_suite(void) {
  Suite *s = suite_create("s21_decimal");
  TCase *core = tcase_create("Core");

  tcase_add_test(core, s21_add_1);
  tcase_add_test(core, s21_add_2);
  tcase_add_test(core, s21_add_3);
  tcase_add_test(core, s21_add_4);
  tcase_add_test(core, s21_add_5);
  tcase_add_test(core, s21_add_6);
  tcase_add_test(core, s21_add_7);
  tcase_add_test(core, s21_add_8);
  tcase_add_test(core, s21_add_9);
  tcase_add_test(core, s21_add_10);
  tcase_add_test(core, s21_add_11);
  tcase_add_test(core, s21_add_12);
  tcase_add_test(core, s21_add_13);
  tcase_add_test(core, s21_sub_1);
  tcase_add_test(core, s21_sub_2);
  tcase_add_test(core, s21_sub_3);
  tcase_add_test(core, s21_sub_4);
  tcase_add_test(core, s21_sub_5);
  tcase_add_test(core, s21_sub_6);
  tcase_add_test(core, s21_sub_7);
  tcase_add_test(core, s21_sub_8);
  tcase_add_test(core, s21_sub_9);
  tcase_add_test(core, s21_sub_10);
  tcase_add_test(core, s21_sub_11);

  suite_add_tcase(s, core);

  return s;
}
