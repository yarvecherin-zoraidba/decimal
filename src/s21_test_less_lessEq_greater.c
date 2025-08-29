#include <check.h>

#include "less_lessEq_greater.h"

typedef struct tst {
  s21_decimal v1;
  s21_decimal v2;
  s21_decimal ve;
  int res_e;
} tst;

static s21_decimal v1_0 = {{0, 0, 0, 0}};
static s21_decimal v2_0 = {{0, 0, 0, 0x80000000U}};
static s21_decimal v3_12_34_56_0_4 = {{12, 34, 56, 0x00040000U}};
static s21_decimal v4_16_34_56_0_4 = {{16, 34, 56, 0x00040000U}};
static s21_decimal v5_3_35_56_0_4 = {{3, 35, 56, 0x00040000U}};
static s21_decimal v6_2_3_58_0_4 = {{2, 3, 58, 0x00040000U}};
static s21_decimal v7_1_0_0_0_28 = {{1, 0, 0, 0x001C0000U}};
static s21_decimal v8_MAX_MAX_MAX_0_4 = {
    {0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x00040000U}};
static s21_decimal v9_MAX_MAX_MAX_0_0 = {
    {0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x00000000U}};
static s21_decimal v10_MAX_MAX_MAX_1_0 = {
    {0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x80000000U}};
static s21_decimal v11_1_0_0_1_28 = {{1, 0, 0, 0x801C0000U}};
static s21_decimal v12_12_34_56_1_7 = {{12, 34, 56, 0x80070000U}};

static tst lst_div[] = {
    {{{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     3},
    {{{0x00000000U, 0x00000000U, 0x00000000U, 0x11000000U}},
     {{0x00000001U, 0x00000000U, 0x00000000U, 0x00000000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     -1},
    {{{0x00000000U, 0x00000000U, 0x00000000U, 0x00000011U}},
     {{0x00000001U, 0x00000000U, 0x00000000U, 0x80000000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     -1},
    {{{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     {{0x00000001U, 0x00000000U, 0x00000000U, 0x80000000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x80000000U}},
     0},
    {{{0x00000000U, 0x00000000U, 0x00000000U, 0x80000000U}},
     {{0x00000001U, 0x00000000U, 0x00000000U, 0x80000000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     0},
    {{{0x00000028U, 0x00000001U, 0x00000000U, (14U << 16)}},
     {{0x00001000U, 0x00000000U, 0x00000000U, 0x80040000U}},
     {{0xA09502F9U, 0x0003B9ACU, 0x00000000U, 0x80130000U}},
     0},
    {{{0x00000028U, 0x00000000U, 0xFFFFFFFFU, (00U << 16)}},
     {{0x00000011U, 0x00000000U, 0x00000000U, (28U << 16)}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     1},
    {{{0x00000028U, 0x00000000U, 0xFFFFFFFFU, 0x80000000U}},
     {{0x00000011U, 0x00000000U, 0x00000000U, (28U << 16)}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     2},
    {{{0x00000028U, 0x00000000U, 0x00000000U, (28U << 16)}},
     {{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x80000000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     2},
    {{{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFF22U, (00U << 16)}},
     {{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, (00U << 16)}},
     {{0x6A0CF235U, 0x593FDB05U, 0x204FCE42U, 0x001C0000U}},
     0},
    {{{12, 34, 56, 0x00040000U}},
     {{12, 34, 56, 0x00040000U}},
     {{0x00000001U, 0x00000000U, 0x00000000U, 0x00000000U}},
     0},
    {{{12, 34, 56, 0x000E0000U}},
     {{16, 34, 56, 0x00040000U}},
     {{0x00000001U, 0x00000000U, 0x00000000U, 0x000A0000U}},
     0},
    {{{12, 34, 56, 0x00040000U}},
     {{03, 35, 56, 0x00020000U}},
     {{0x201CEE39U, 0xDCC692AFU, 0x0052B7D2U, 0x001C0000U}},
     0},
    {{{12, 34, 56, 0x000A0000U}},
     {{02, 03, 58, 0x00040000U}},
     {{0x5311E633U, 0x573E4F9EU, 0x00000034U, 0x001B0000U}},
     0},
    {{{12, 34, 56, 0x00040000U}},
     {{16, 34, 56, 0x00040000U}},
     {{0x0DB1281EU, 0x3E250261U, 0x204FCE5EU, 0x001C0000U}},
     0},
    {{{12, 34, 56, 0x00040000U}},
     {{3, 35, 56, 0x00040000U}},
     {{0x8B4D0E49U, 0x3D914C68U, 0x204FCE5EU, 0x001C0000U}},
     0},
    {{{12, 34, 56, 0x00040000U}},
     {{2, 3, 58, 0x00040000U}},
     {{0xB41E1F8AU, 0x67CFE676U, 0x1F329249U, 0x001C0000U}},
     0},
    {{{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x00040000U}},
     {{1, 0, 0, 0x001C0000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     1},
    {{{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x00040000U}},
     {{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x00000000U}},
     {{0x00000001U, 0x00000000U, 0x00000000U, 0x00040000U}},
     0},
    {{{1, 0, 0, 0x801C0000U}},
     {{12, 34, 56, 0x80070000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     2},
    {{{12, 34, 56, 0x80070000U}},
     {{1, 0, 0, 0x801C0000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     1},
    {{{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x80000000U}},
     {{1, 0, 0, 0x801C0000U}},
     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
     1},
    //    {{{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     0}
    //    {{{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     0},
    //    {{{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     {{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
    //     0}

};

Suite *s21_suite(void);

int main() {
  SRunner *sr = srunner_create(NULL);
  srunner_add_suite(sr, s21_suite());
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed == 0 ? 0 : 1;
}

START_TEST(test_s21_div) {
  for (int i = 0; i < (int)(sizeof(lst_div) / sizeof(*lst_div)); i++) {
    s21_decimal vr = {0};
    ck_assert_int_eq(s21_div(lst_div[i].v1, lst_div[i].v2, &vr),
                     lst_div[i].res_e);
    ck_assert_mem_eq(&vr, &lst_div[i].ve, sizeof(s21_decimal));
  }
}
END_TEST

START_TEST(test_s21_less) {
  ck_assert_int_eq(s21_is_less(v1_0, v2_0), 0);
  ck_assert_int_eq(s21_is_less(v1_0, v3_12_34_56_0_4), 1);
  ck_assert_int_eq(s21_is_less(v1_0, v11_1_0_0_1_28), 0);
  ck_assert_int_eq(s21_is_less(v12_12_34_56_1_7, v2_0), 1);
  ck_assert_int_eq(s21_is_less(v3_12_34_56_0_4, v2_0), 0);
  ck_assert_int_eq(s21_is_less(v11_1_0_0_1_28, v7_1_0_0_0_28), 1);
  ck_assert_int_eq(s21_is_less(v3_12_34_56_0_4, v3_12_34_56_0_4), 0);
  ck_assert_int_eq(s21_is_less(v3_12_34_56_0_4, v4_16_34_56_0_4), 1);
  ck_assert_int_eq(s21_is_less(v3_12_34_56_0_4, v5_3_35_56_0_4), 1);
  ck_assert_int_eq(s21_is_less(v3_12_34_56_0_4, v6_2_3_58_0_4), 1);
  ck_assert_int_eq(s21_is_less(v8_MAX_MAX_MAX_0_4, v7_1_0_0_0_28), 0);
  ck_assert_int_eq(s21_is_less(v8_MAX_MAX_MAX_0_4, v9_MAX_MAX_MAX_0_0), 1);
  ck_assert_int_eq(s21_is_less(v11_1_0_0_1_28, v12_12_34_56_1_7), 0);
  ck_assert_int_eq(s21_is_less(v12_12_34_56_1_7, v11_1_0_0_1_28), 1);
  ck_assert_int_eq(s21_is_less(v10_MAX_MAX_MAX_1_0, v11_1_0_0_1_28), 1);
}
END_TEST

START_TEST(test_s21_lessEq) {
  ck_assert_int_eq(s21_is_less_or_equal(v1_0, v2_0), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v1_0, v3_12_34_56_0_4), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v1_0, v11_1_0_0_1_28), 0);
  ck_assert_int_eq(s21_is_less_or_equal(v12_12_34_56_1_7, v2_0), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v3_12_34_56_0_4, v2_0), 0);
  ck_assert_int_eq(s21_is_less_or_equal(v11_1_0_0_1_28, v7_1_0_0_0_28), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v3_12_34_56_0_4, v3_12_34_56_0_4), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v3_12_34_56_0_4, v4_16_34_56_0_4), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v3_12_34_56_0_4, v5_3_35_56_0_4), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v3_12_34_56_0_4, v6_2_3_58_0_4), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v8_MAX_MAX_MAX_0_4, v7_1_0_0_0_28), 0);
  ck_assert_int_eq(s21_is_less_or_equal(v8_MAX_MAX_MAX_0_4, v9_MAX_MAX_MAX_0_0),
                   1);
  ck_assert_int_eq(s21_is_less_or_equal(v11_1_0_0_1_28, v12_12_34_56_1_7), 0);
  ck_assert_int_eq(s21_is_less_or_equal(v12_12_34_56_1_7, v11_1_0_0_1_28), 1);
  ck_assert_int_eq(s21_is_less_or_equal(v10_MAX_MAX_MAX_1_0, v11_1_0_0_1_28),
                   1);
}
END_TEST

START_TEST(test_s21_greater) {
  ck_assert_int_eq(s21_is_greater(v1_0, v2_0), 0);
  ck_assert_int_eq(s21_is_greater(v1_0, v3_12_34_56_0_4), 0);
  ck_assert_int_eq(s21_is_greater(v1_0, v11_1_0_0_1_28), 1);
  ck_assert_int_eq(s21_is_greater(v12_12_34_56_1_7, v2_0), 0);
  ck_assert_int_eq(s21_is_greater(v3_12_34_56_0_4, v2_0), 1);
  ck_assert_int_eq(s21_is_greater(v11_1_0_0_1_28, v7_1_0_0_0_28), 0);
  ck_assert_int_eq(s21_is_greater(v3_12_34_56_0_4, v3_12_34_56_0_4), 0);
  ck_assert_int_eq(s21_is_greater(v3_12_34_56_0_4, v4_16_34_56_0_4), 0);
  ck_assert_int_eq(s21_is_greater(v3_12_34_56_0_4, v5_3_35_56_0_4), 0);
  ck_assert_int_eq(s21_is_greater(v3_12_34_56_0_4, v6_2_3_58_0_4), 0);
  ck_assert_int_eq(s21_is_greater(v8_MAX_MAX_MAX_0_4, v7_1_0_0_0_28), 1);
  ck_assert_int_eq(s21_is_greater(v8_MAX_MAX_MAX_0_4, v9_MAX_MAX_MAX_0_0), 0);
  ck_assert_int_eq(s21_is_greater(v11_1_0_0_1_28, v12_12_34_56_1_7), 1);
  ck_assert_int_eq(s21_is_greater(v12_12_34_56_1_7, v11_1_0_0_1_28), 0);
  ck_assert_int_eq(s21_is_greater(v10_MAX_MAX_MAX_1_0, v11_1_0_0_1_28), 0);
}
END_TEST

START_TEST(test_s21_greaterEq) {
  ck_assert_int_eq(s21_is_greater_or_equal(v1_0, v2_0), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(v1_0, v3_12_34_56_0_4), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(v1_0, v11_1_0_0_1_28), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(v12_12_34_56_1_7, v2_0), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(v3_12_34_56_0_4, v2_0), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(v11_1_0_0_1_28, v7_1_0_0_0_28), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(v3_12_34_56_0_4, v3_12_34_56_0_4),
                   1);
  ck_assert_int_eq(s21_is_greater_or_equal(v3_12_34_56_0_4, v4_16_34_56_0_4),
                   0);
  ck_assert_int_eq(s21_is_greater_or_equal(v3_12_34_56_0_4, v5_3_35_56_0_4), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(v3_12_34_56_0_4, v6_2_3_58_0_4), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(v8_MAX_MAX_MAX_0_4, v7_1_0_0_0_28),
                   1);
  ck_assert_int_eq(
      s21_is_greater_or_equal(v8_MAX_MAX_MAX_0_4, v9_MAX_MAX_MAX_0_0), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(v11_1_0_0_1_28, v12_12_34_56_1_7),
                   1);
  ck_assert_int_eq(s21_is_greater_or_equal(v12_12_34_56_1_7, v11_1_0_0_1_28),
                   0);
  ck_assert_int_eq(s21_is_greater_or_equal(v10_MAX_MAX_MAX_1_0, v11_1_0_0_1_28),
                   0);
}
END_TEST

START_TEST(test_s21_equal) {
  ck_assert_int_eq(s21_is_equal(v1_0, v2_0), 1);
  ck_assert_int_eq(s21_is_equal(v1_0, v3_12_34_56_0_4), 0);
  ck_assert_int_eq(s21_is_equal(v1_0, v11_1_0_0_1_28), 0);
  ck_assert_int_eq(s21_is_equal(v12_12_34_56_1_7, v2_0), 0);
  ck_assert_int_eq(s21_is_equal(v3_12_34_56_0_4, v2_0), 0);
  ck_assert_int_eq(s21_is_equal(v11_1_0_0_1_28, v7_1_0_0_0_28), 0);
  ck_assert_int_eq(s21_is_equal(v3_12_34_56_0_4, v3_12_34_56_0_4), 1);
  ck_assert_int_eq(s21_is_equal(v3_12_34_56_0_4, v4_16_34_56_0_4), 0);
  ck_assert_int_eq(s21_is_equal(v3_12_34_56_0_4, v5_3_35_56_0_4), 0);
  ck_assert_int_eq(s21_is_equal(v3_12_34_56_0_4, v6_2_3_58_0_4), 0);
  ck_assert_int_eq(s21_is_equal(v8_MAX_MAX_MAX_0_4, v7_1_0_0_0_28), 0);
  ck_assert_int_eq(s21_is_equal(v8_MAX_MAX_MAX_0_4, v9_MAX_MAX_MAX_0_0), 0);
  ck_assert_int_eq(s21_is_equal(v11_1_0_0_1_28, v12_12_34_56_1_7), 0);
  ck_assert_int_eq(s21_is_equal(v12_12_34_56_1_7, v11_1_0_0_1_28), 0);
  ck_assert_int_eq(s21_is_equal(v10_MAX_MAX_MAX_1_0, v11_1_0_0_1_28), 0);
}
END_TEST

START_TEST(test_s21_notEqual) {
  ck_assert_int_eq(s21_is_not_equal(v1_0, v2_0), 0);
  ck_assert_int_eq(s21_is_not_equal(v1_0, v3_12_34_56_0_4), 1);
  ck_assert_int_eq(s21_is_not_equal(v1_0, v11_1_0_0_1_28), 1);
  ck_assert_int_eq(s21_is_not_equal(v12_12_34_56_1_7, v2_0), 1);
  ck_assert_int_eq(s21_is_not_equal(v3_12_34_56_0_4, v2_0), 1);
  ck_assert_int_eq(s21_is_not_equal(v11_1_0_0_1_28, v7_1_0_0_0_28), 1);
  ck_assert_int_eq(s21_is_not_equal(v3_12_34_56_0_4, v3_12_34_56_0_4), 0);
  ck_assert_int_eq(s21_is_not_equal(v3_12_34_56_0_4, v4_16_34_56_0_4), 1);
  ck_assert_int_eq(s21_is_not_equal(v3_12_34_56_0_4, v5_3_35_56_0_4), 1);
  ck_assert_int_eq(s21_is_not_equal(v3_12_34_56_0_4, v6_2_3_58_0_4), 1);
  ck_assert_int_eq(s21_is_not_equal(v8_MAX_MAX_MAX_0_4, v7_1_0_0_0_28), 1);
  ck_assert_int_eq(s21_is_not_equal(v8_MAX_MAX_MAX_0_4, v9_MAX_MAX_MAX_0_0), 1);
  ck_assert_int_eq(s21_is_not_equal(v11_1_0_0_1_28, v12_12_34_56_1_7), 1);
  ck_assert_int_eq(s21_is_not_equal(v12_12_34_56_1_7, v11_1_0_0_1_28), 1);
  ck_assert_int_eq(s21_is_not_equal(v10_MAX_MAX_MAX_1_0, v11_1_0_0_1_28), 1);
}
END_TEST

Suite *s21_suite(void) {
  Suite *s = suite_create("s21_decimal");
  TCase *core = tcase_create("Core");
  tcase_add_test(core, test_s21_div);
  tcase_add_test(core, test_s21_less);
  tcase_add_test(core, test_s21_lessEq);
  tcase_add_test(core, test_s21_greater);
  tcase_add_test(core, test_s21_greaterEq);
  tcase_add_test(core, test_s21_equal);
  tcase_add_test(core, test_s21_notEqual);
  suite_add_tcase(s, core);
  return s;
}