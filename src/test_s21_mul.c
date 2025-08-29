#include <check.h>
#include <string.h>

#include "s21_decimal.h"

static s21_decimal make_dec(unsigned lo, unsigned mid, unsigned hi,
                            unsigned scale, int sign) {
  s21_decimal d = {{0, 0, 0, 0}};
  d.bits[0] = lo;
  d.bits[1] = mid;
  d.bits[2] = hi;
  s21_set_exp(&d, scale);
  s21_set_sign(&d, sign ? 1 : 0);
  return d;
}

static int dec_eq(s21_decimal a, s21_decimal b) {
  return a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
         a.bits[2] == b.bits[2] && a.bits[3] == b.bits[3];
}

START_TEST(test_mul_basic_small_ints) {
  s21_decimal a = make_dec(2u, 0u, 0u, 0u, 0);
  s21_decimal b = make_dec(3u, 0u, 0u, 0u, 0);
  s21_decimal got;
  int rc = s21_mul(a, b, &got);
  ck_assert_int_eq(rc, S21_OK);
  s21_decimal exp = make_dec(6u, 0u, 0u, 0u, 0);
  ck_assert(dec_eq(got, exp));
}
END_TEST

START_TEST(test_mul_zero_left) {
  s21_decimal a = make_dec(0u, 0u, 0u, 0u, 0);
  s21_decimal b = make_dec(123456u, 0u, 0u, 0u, 0);
  s21_decimal got;
  int rc = s21_mul(a, b, &got);
  ck_assert_int_eq(rc, S21_OK);
  s21_decimal exp1 = make_dec(0u, 0u, 0u, 0u, 0);
  ck_assert(dec_eq(got, exp1));
}
END_TEST

START_TEST(test_mul_zero_right) {
  s21_decimal a = make_dec(987u, 0u, 0u, 0u, 0);
  s21_decimal b = make_dec(0u, 0u, 0u, 0u, 0);
  s21_decimal got;
  int rc = s21_mul(a, b, &got);
  ck_assert_int_eq(rc, S21_OK);
  s21_decimal exp1 = make_dec(0u, 0u, 0u, 0u, 0);
  ck_assert(dec_eq(got, exp1));
}
END_TEST

START_TEST(test_mul_signs) {
  s21_decimal a = make_dec(2u, 0u, 0u, 0u, 1);
  s21_decimal b = make_dec(3u, 0u, 0u, 0u, 0);
  s21_decimal got;
  ck_assert_int_eq(s21_mul(a, b, &got), S21_OK);
  s21_decimal exp_neg = make_dec(6u, 0u, 0u, 0u, 1);
  ck_assert(dec_eq(got, exp_neg));

  a = make_dec(2u, 0u, 0u, 0u, 1);
  b = make_dec(3u, 0u, 0u, 0u, 1);
  ck_assert_int_eq(s21_mul(a, b, &got), S21_OK);
  s21_decimal exp_pos = make_dec(6u, 0u, 0u, 0u, 0);
  ck_assert(dec_eq(got, exp_pos));
}
END_TEST

START_TEST(test_mul_scales_simple) {
  s21_decimal a = make_dec(123u, 0u, 0u, 2u, 0);
  s21_decimal b = make_dec(45u, 0u, 0u, 1u, 0);
  s21_decimal got;
  ck_assert_int_eq(s21_mul(a, b, &got), S21_OK);

  ck_assert_uint_eq((unsigned)s21_get_exp(got), 3u);
  ck_assert_int_eq(s21_get_sign(got), 0);

  s21_decimal exp1 = make_dec(5535u, 0u, 0u, 3u, 0);
  ck_assert(dec_eq(got, exp1));
}
END_TEST

START_TEST(test_mul_scale_clamp_to_28_with_round) {
  s21_decimal a = make_dec(123456789u, 0u, 0u, 20u, 0);
  s21_decimal b = make_dec(987654321u, 0u, 0u, 20u, 0);
  s21_decimal got;
  ck_assert_int_eq(s21_mul(a, b, &got), S21_OK);

  ck_assert_uint_eq((unsigned)s21_get_exp(got), 28u);
  ck_assert_int_eq(s21_get_sign(got), 0);

  ck_assert(!(got.bits[0] == 0u && got.bits[1] == 0u && got.bits[2] == 0u));
}
END_TEST

START_TEST(test_mul_shrink_to_fit_by_div10) {
  s21_decimal a = make_dec(0xFFFFFFFFu, 0xFFFFFFFFu, 0x1u, 5u, 0);
  s21_decimal b = make_dec(0xFFFFFFFFu, 0x0u, 0x1u, 5u, 0);

  s21_decimal got;
  ck_assert_int_eq(s21_mul(a, b, &got), S21_OK);

  ck_assert((unsigned)s21_get_exp(got) <= 10u);
  ck_assert((unsigned)s21_get_exp(got) <= 28u);
}
END_TEST

START_TEST(test_mul_overflow_no_scale) {
  s21_decimal a = make_dec(0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0);
  s21_decimal b = make_dec(0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0u, 0);

  s21_decimal got;
  int rc = s21_mul(a, b, &got);
  ck_assert_int_eq(rc, S21_INF_POS);
}
END_TEST

START_TEST(test_mul_null_result_ptr) {
  s21_decimal a = make_dec(1u, 0u, 0u, 0u, 0);
  s21_decimal b = make_dec(1u, 0u, 0u, 0u, 0);
  int rc = s21_mul(a, b, NULL);
  ck_assert_int_eq(rc, S21_INF_POS);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s = suite_create("s21_mul");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_mul_basic_small_ints);
  tcase_add_test(tc, test_mul_zero_left);
  tcase_add_test(tc, test_mul_zero_right);
  tcase_add_test(tc, test_mul_signs);
  tcase_add_test(tc, test_mul_scales_simple);
  tcase_add_test(tc, test_mul_scale_clamp_to_28_with_round);
  tcase_add_test(tc, test_mul_shrink_to_fit_by_div10);
  tcase_add_test(tc, test_mul_overflow_no_scale);
  tcase_add_test(tc, test_mul_null_result_ptr);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  Suite *s = s21_mul_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 0 : 1;
}
