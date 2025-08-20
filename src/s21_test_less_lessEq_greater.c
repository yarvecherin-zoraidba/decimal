#include <check.h>
#include "less_lessEq_greater.h"

static s21_decimal v1_0 = {{0, 0, 0, 0}};
static s21_decimal v2_0 = {{0, 0, 0, 0x80000000U}};
static s21_decimal v3_12_34_56_0_4 = {{12, 34, 56, 0x00040000U}};
static s21_decimal v4_16_34_56_0_4 = {{16, 34, 56, 0x00040000U}};
static s21_decimal v5_3_35_56_0_4 = {{3, 35, 56, 0x00040000U}};
static s21_decimal v6_2_3_58_0_4 = {{2, 3, 58, 0x00040000U}};
static s21_decimal v7_1_0_0_0_28 = {{1, 0, 0, 0x001C0000U}};
static s21_decimal v8_MAX_MAX_MAX_0_4 = {{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x00040000U}};
static s21_decimal v9_MAX_MAX_MAX_0_0 = {{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x00000000U}};
static s21_decimal v10_MAX_MAX_MAX_1_0 = {{0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0x80000000U}};
static s21_decimal v11_1_0_0_1_28 = {{1, 0, 0, 0x801C0000U}};
static s21_decimal v12_12_34_56_1_7 = {{12, 34, 56, 0x80070000U}};

Suite *s21_suite(void);

int main() {
    SRunner *sr = srunner_create(NULL);
    srunner_add_suite(sr, s21_suite());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return failed == 0 ? 0 : 1;
}

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
ck_assert_int_eq(s21_is_less_or_equal(v8_MAX_MAX_MAX_0_4, v9_MAX_MAX_MAX_0_0), 1);
ck_assert_int_eq(s21_is_less_or_equal(v11_1_0_0_1_28, v12_12_34_56_1_7), 0);
ck_assert_int_eq(s21_is_less_or_equal(v12_12_34_56_1_7, v11_1_0_0_1_28), 1);
ck_assert_int_eq(s21_is_less_or_equal(v10_MAX_MAX_MAX_1_0, v11_1_0_0_1_28), 1);
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


Suite *s21_suite(void) {
    Suite *s = suite_create("s21_decimal");
    TCase *core = tcase_create("Core");
    tcase_add_test(core, test_s21_less);
    tcase_add_test(core, test_s21_lessEq);
    tcase_add_test(core, test_s21_greater);
    suite_add_tcase(s, core);
    return s;
}