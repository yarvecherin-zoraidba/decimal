#include <check.h>
#include <limits.h>
#include <string.h>

#include "s21_decimal.h"

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

static tst lst_div[] = {{{{0x00000000U, 0x00000000U, 0x00000000U, 0x00000000U}},
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
                         1}};

s21_decimal make_dec(unsigned lo, unsigned mid, unsigned hi, unsigned scale,
                     int sign) {
  s21_decimal d = {{0, 0, 0, 0}};
  d.bits[0] = lo;
  d.bits[1] = mid;
  d.bits[2] = hi;
  s21_set_exp(&d, scale);
  s21_set_sign(&d, sign ? 1 : 0);
  return d;
}

int dec_eq(s21_decimal a, s21_decimal b) {
  return a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
         a.bits[2] == b.bits[2] && a.bits[3] == b.bits[3];
}

void s21_set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[3] &= 0x80000000;
  decimal->bits[3] |= (scale << 16);
}

Suite *s21_suite(void);

int main() {
  SRunner *sr = srunner_create(NULL);
  srunner_add_suite(sr, s21_suite());
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed == 0 ? 0 : 1;
}

// Dmitry
START_TEST(test_s21_form_int_to_decimal) {
  s21_decimal src;
  s21_from_int_to_decimal(0, &src);
  ck_assert_int_eq(src.bits[0], 0);
  ck_assert_int_eq(src.bits[1], 0);
  ck_assert_int_eq(src.bits[2], 0);
  ck_assert_int_eq(src.bits[3], 0);

  s21_decimal src1;
  s21_from_int_to_decimal(-1234567, &src1);
  ck_assert_int_eq(src1.bits[0], 1234567);
  ck_assert_int_eq(src1.bits[1], 0);
  ck_assert_int_eq(src1.bits[2], 0);
  ck_assert_int_eq(src1.bits[3], 0x80000000);

  s21_decimal src2;
  s21_from_int_to_decimal(12345678, &src2);
  ck_assert_int_eq(src2.bits[0], 12345678);
  ck_assert_int_eq(src2.bits[1], 0);
  ck_assert_int_eq(src2.bits[2], 0);
  ck_assert_int_eq(src2.bits[3], 0);

  s21_decimal src3;
  s21_from_int_to_decimal(0x80000000, &src3);
  ck_assert_int_eq(src3.bits[0], 2147483648);
  ck_assert_int_eq(src3.bits[1], 0);
  ck_assert_int_eq(src3.bits[2], 0);
  ck_assert_int_eq(src3.bits[3], 0x80000000);

  s21_decimal src4;
  s21_from_int_to_decimal(2147483647, &src4);
  ck_assert_int_eq(src4.bits[0], 2147483647);
  ck_assert_int_eq(src4.bits[1], 0);
  ck_assert_int_eq(src4.bits[2], 0);
  ck_assert_int_eq(src4.bits[3], 0);

  s21_decimal src5;
  s21_from_int_to_decimal(2147483648, &src5);
  ck_assert_int_eq(src5.bits[0], 2147483648);
  ck_assert_int_eq(src5.bits[1], 0);
  ck_assert_int_eq(src5.bits[2], 0);
  ck_assert_int_eq(src5.bits[3], 0x80000000);

  s21_decimal src6;
  s21_from_int_to_decimal(-2147483648, &src6);
  ck_assert_int_eq(src6.bits[0], 2147483648);
  ck_assert_int_eq(src6.bits[1], 0);
  ck_assert_int_eq(src6.bits[2], 0);
  ck_assert_int_eq(src6.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_decimal_to_int) {
  int number = 0;
  s21_decimal src = {{0, 0, 0, 0}};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);

  int number1 = 0;
  s21_decimal src1 = {{2147483647, 0, 0, 0}};
  s21_from_decimal_to_int(src1, &number1);
  ck_assert_int_eq(number1, 2147483647);

  int number2 = 0;
  s21_decimal src2 = {{1234567, 0, 0, 0x80000000}};
  s21_from_decimal_to_int(src2, &number2);
  ck_assert_int_eq(number2, -1234567);

  int number3 = 0;
  s21_decimal src3 = {{2147483648, 0, 0, 0x80000000}};
  s21_from_decimal_to_int(src3, &number3);
  ck_assert_int_eq(number3, -2147483648);

  int number4 = 0;
  s21_decimal src4 = {{0, 0, 0, 0x80000000}};
  s21_from_decimal_to_int(src4, &number4);
  ck_assert_int_eq(number4, 0);

  int number5 = 0;
  s21_decimal src5 = {{0, 1, 0, 0}};
  int status = s21_from_decimal_to_int(src5, &number5);
  s21_from_decimal_to_int(src5, &number5);
  ck_assert_int_eq(number5, 0);
  ck_assert_int_eq(status, 1);

  int number6 = 0;
  s21_decimal src6 = {{12345, 0, 0, (2 << 16)}};
  int status1 = s21_from_decimal_to_int(src6, &number6);
  s21_from_decimal_to_int(src6, &number6);
  ck_assert_int_eq(number6, 123);
  ck_assert_int_eq(status1, 0);
}
END_TEST

START_TEST(test_s21_decimal_to_float) {
  float number = 0.0;
  s21_decimal src = {{12345, 0, 0, 2147680256}};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -12.345);

  float number2 = 0.0;
  s21_decimal src2 = {{12345, 0, 0, 2147483648}};
  s21_from_decimal_to_float(src2, &number2);
  ck_assert_float_eq(number2, -12345);

  float number3 = 0.0;
  s21_decimal src3 = {{12345, 0, 0, 0}};
  s21_from_decimal_to_float(src3, &number3);
  ck_assert_float_eq(number3, 12345);

  float number4 = 0.0;
  s21_decimal src4 = {{12345678, 0, 0, 0}};
  s21_from_decimal_to_float(src4, &number4);
  ck_assert_float_eq(number4, 12345678);

  float number5 = 0.0;
  s21_decimal src5 = {{1234567, 0, 0, 0x80000000 | (2 << 16)}};
  s21_from_decimal_to_float(src5, &number5);
  ck_assert_float_eq(number5, -12345.67);

  float number6 = 0.0;
  s21_decimal src6 = {{1234567, 0, 0, (7 << 16)}};
  s21_from_decimal_to_float(src6, &number6);
  ck_assert_float_eq(number6, 0.1234567);

  float number7 = 0.0;
  s21_decimal src7 = {{4294967295, 4294967295, 0, 0}};
  s21_from_decimal_to_float(src7, &number7);
  ck_assert_float_eq(number7, 0xFFFFFFFFFFFFFFFF);

  float number8 = 0.0;
  s21_decimal src8 = {{1234567, 0, 0, (28 << 16)}};
  s21_from_decimal_to_float(src8, &number8);
  ck_assert_int_eq(number8, 0);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal) {
  s21_decimal src;
  float number = 0;
  s21_from_float_to_decimal(0, &src);
  s21_from_decimal_to_float(src, &number);
  ck_assert_int_eq(number, 0);

  s21_decimal src1;
  float number1 = 0;
  s21_from_float_to_decimal(0.123456, &src1);
  s21_from_decimal_to_float(src1, &number1);
  ck_assert_int_eq(number1, 0.123456);

  s21_decimal src2;
  ck_assert_int_eq(s21_from_float_to_decimal(NAN, &src2), 1);
  ck_assert_int_eq(s21_from_float_to_decimal(1.0 / 0.0, &src2), 1);
  ck_assert_int_eq(s21_from_float_to_decimal(-INFINITY, &src2), 1);

  s21_decimal src3;
  float number3 = 0;
  s21_from_float_to_decimal(-123456.78, &src3);
  s21_from_decimal_to_float(src3, &number3);
  ck_assert_int_eq(number3, -123456.78);

  s21_decimal src4;
  float number4 = 0;
  s21_from_float_to_decimal(0.000000005, &src4);
  s21_from_decimal_to_float(src4, &number4);
  ck_assert_int_eq(number4, 0.000000005);

  s21_decimal src5;
  float number5 = -123456.78;
  ck_assert_int_eq(s21_from_float_to_decimal(number5, &src5), 0);

  s21_decimal src6;
  s21_from_float_to_decimal(-1234567, &src6);
  ck_assert_int_eq(src6.bits[0], 1234567);
  ck_assert_int_eq(src6.bits[1], 0);
  ck_assert_int_eq(src6.bits[2], 0);
  ck_assert_int_eq(src6.bits[3], 0x80000000);

  s21_decimal src7;
  s21_from_float_to_decimal(-1234.567, &src7);
  ck_assert_int_eq(src7.bits[0], 1234567);
  ck_assert_int_eq(src7.bits[1], 0);
  ck_assert_int_eq(src7.bits[2], 0);
  ck_assert_int_eq(src7.bits[3], 0x80000000 | (3 << 16));
}
END_TEST

START_TEST(test_s21_negate) {
  s21_decimal src = {{12, 34, 56, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_negate(src, &res);
  ck_assert_int_eq(res.bits[0], 12);
  ck_assert_int_eq(res.bits[1], 34);
  ck_assert_int_eq(res.bits[2], 56);
  ck_assert_int_eq(res.bits[3], 0x80000000);

  s21_decimal src1 = {{12, 34, 56, 0x80000000}};
  s21_decimal res1 = {{0, 0, 0, 0}};
  s21_negate(src1, &res1);
  ck_assert_int_eq(res1.bits[0], 12);
  ck_assert_int_eq(res1.bits[1], 34);
  ck_assert_int_eq(res1.bits[2], 56);
  ck_assert_int_eq(res1.bits[3], 0);
}
END_TEST

// karkaror
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

// mushroot

START_TEST(s21_add_1) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal decimal1 = {{2, 0, 0, 0}};
  s21_decimal decimal2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{4, 0, 0, 0}};

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal decimal1 = {{0, 2, 0, 0}};
  s21_decimal decimal2 = {{0, 2, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 4, 0, 0}};

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal decimal1 = {{0, 0, 2, 0}};
  s21_decimal decimal2 = {{0, 0, 2, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 4, 0}};

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal decimal1 = {{10, 0, 0, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0}};
  s21_set_sign(&decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{5, 0, 0, 0}};

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal decimal1 = {{5, 0, 0, 0}};
  s21_decimal decimal2 = {{10, 0, 0, 0}};
  s21_set_sign(&decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{5, 0, 0, 0}};
  s21_set_sign(&check, 1);

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal decimal1 = {{5, 0, 0, 0}};
  s21_set_sign(&decimal1, 1);
  s21_decimal decimal2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{5, 0, 0, 0}};

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_8) {
  s21_decimal decimal1 = {{10, 0, 0, 0}};
  s21_set_sign(&decimal1, 1);
  s21_decimal decimal2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{5, 0, 0, 0}};
  s21_set_sign(&check, 1);

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_9) {
  s21_decimal decimal1 = {{100, 0, 0, 0}};
  s21_decimal decimal2 = {{55, 0, 0, 0}};
  s21_set_scale(&decimal1, 2);
  s21_set_scale(&decimal2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{155, 0, 0, 0}};
  s21_set_scale(&check, 2);

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_add_10) {
  s21_decimal decimal1 = {{10000, 0, 0, 0}};
  s21_decimal decimal2 = {{55, 0, 0, 0}};
  s21_set_scale(&decimal1, 2);
  s21_set_scale(&decimal2, 4);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000055, 0, 0, 0}};
  s21_set_scale(&check, 4);

  int res = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_1) {
  s21_decimal decimal1 = {{0, 1, 0, 0}};
  s21_decimal decimal2 = {{0, 2, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 1, 0, 0}};
  s21_set_sign(&check, 1);

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal decimal1 = {{0, 0, 1, 0}};
  s21_decimal decimal2 = {{0, 0, 2, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 1, 0}};
  s21_set_sign(&check, 1);

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal decimal1 = {{10, 0, 0, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{5, 0, 0, 0}};

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_4) {
  s21_decimal decimal1 = {{5, 0, 0, 0}};
  s21_decimal decimal2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{5, 0, 0, 0}};
  s21_set_sign(&check, 1);

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal decimal1 = {{5, 0, 0, 0}};
  s21_decimal decimal2 = {{10, 0, 0, 0}};
  s21_set_sign(&decimal1, 1);
  s21_set_sign(&decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{5, 0, 0, 0}};

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_6) {
  s21_decimal decimal1 = {{10, 0, 0, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0}};
  s21_set_sign(&decimal1, 1);
  s21_set_sign(&decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{5, 0, 0, 0}};
  s21_set_sign(&check, 1);

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal decimal1 = {{100, 0, 0, 0}};
  s21_decimal decimal2 = {{55, 0, 0, 0}};
  s21_set_scale(&decimal1, 2);
  s21_set_scale(&decimal2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{45, 0, 0, 0}};
  s21_set_scale(&check, 2);

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_8) {
  s21_decimal decimal1 = {{10000, 0, 0, 0}};
  s21_decimal decimal2 = {{55, 0, 0, 0}};
  s21_set_scale(&decimal1, 2);
  s21_set_scale(&decimal2, 4);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{999945, 0, 0, 0}};
  s21_set_scale(&check, 4);

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_9) {
  s21_decimal decimal1 = {{10000, 0, 0, 0}};
  s21_decimal decimal2 = {{55, 0, 0, 0}};
  s21_set_scale(&decimal1, 2);
  s21_set_scale(&decimal2, 4);
  s21_set_sign(&decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000055, 0, 0, 0}};
  s21_set_scale(&check, 4);

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_10) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal decimal2 = {{1, 0, 0, 0}};
  s21_set_sign(&decimal1, 1);
  s21_decimal result = {{0, 0, 0, 0}};

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_sub_11) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal decimal2 = {{16, 0, 0, 0}};
  s21_set_scale(&decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(s21_sub_12) {
  s21_decimal decimal1 = {{0, 0, 0, 0}};
  s21_decimal decimal2 = {{0, 0, 0, 0}};
  s21_set_scale(&decimal1, 5);
  s21_set_scale(&decimal2, 2);
  s21_set_sign(&decimal2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0, 0, 0, 0}};

  int res = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

// charlesj
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
  ck_assert_int_eq(rc, -1);
}
END_TEST

// zoraidba
START_TEST(test_s21_floor) {
  s21_decimal src = {0};
  s21_decimal result = {0};

  src.bits[0] = 0;
  src.bits[0] = 0;
  src.bits[0] = 0;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 5);
  src.bits[0] = 123456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&result, 0);

  s21_set_exp(&src, 5);
  s21_set_sign(&src, 1);
  src.bits[0] = 123456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 5);
  s21_set_sign(&src, 1);

  src.bits[0] = 1;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 28);
  s21_set_sign(&src, 1);

  src.bits[0] = 5;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 28);
  s21_set_sign(&src, 0);

  src.bits[0] = 5;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 5);
  s21_set_sign(&src, 0);

  src.bits[0] = 500000;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 5);
  s21_set_sign(&src, 1);

  src.bits[0] = 500000;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 0);
  s21_set_sign(&src, 0);

  src.bits[0] = 2147483647;
  src.bits[1] = 2147483647;
  src.bits[2] = 2147483647;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 2147483647);
  ck_assert_int_eq(result.bits[2], 2147483647);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 0);
  s21_set_sign(&src, 1);

  src.bits[0] = 2147483647;
  src.bits[1] = 2147483647;
  src.bits[2] = 2147483647;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 2147483647);
  ck_assert_int_eq(result.bits[2], 2147483647);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 0);

  src.bits[0] = 0x8BEFDD0F;
  src.bits[1] = 0x79E13C2C;
  src.bits[2] = 0x2FC2CC07;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 0xC64CFBD0);
  ck_assert_int_eq(result.bits[1], 0x14835E8B);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 1);

  src.bits[0] = 0x8BEFDD0F;
  src.bits[1] = 0x79E13C2C;
  src.bits[2] = 0x2FC2CC07;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 0xC64CFBD1);
  ck_assert_int_eq(result.bits[1], 0x14835E8B);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 0);

  src.bits[0] = 0x50000000;
  src.bits[1] = 0x36B90BE5;
  src.bits[2] = 0xA18F07D7;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 0x44F40000);
  ck_assert_int_eq(result.bits[1], 0x45639182);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 1);

  src.bits[0] = 0x50000000;
  src.bits[1] = 0x36B90BE5;
  src.bits[2] = 0xA18F07D7;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 0x44F40000);
  ck_assert_int_eq(result.bits[1], 0x45639182);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_round) {
  s21_decimal src = {0};
  s21_decimal result = {0};

  src.bits[0] = 0;
  src.bits[0] = 0;
  src.bits[0] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 5);
  src.bits[0] = 123456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 5);
  s21_set_sign(&src, 1);
  src.bits[0] = 123456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_sign(&src, 0);
  s21_set_exp(&src, 5);
  src.bits[0] = 163456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_sign(&src, 1);
  s21_set_exp(&src, 5);
  src.bits[0] = 163456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_sign(&src, 0);
  s21_set_exp(&src, 0);
  src.bits[0] = 163456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 163456);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_sign(&src, 1);
  s21_set_exp(&src, 0);
  src.bits[0] = 163456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 163456);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_sign(&src, 0);
  s21_set_exp(&src, 5);
  src.bits[0] = 100000;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_sign(&src, 1);
  s21_set_exp(&src, 5);
  src.bits[0] = 100000;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 0);
  s21_set_sign(&src, 0);

  src.bits[0] = 2147483647;
  src.bits[1] = 2147483647;
  src.bits[2] = 2147483647;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 2147483647);
  ck_assert_int_eq(result.bits[2], 2147483647);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 0);
  s21_set_sign(&src, 1);

  src.bits[0] = 2147483647;
  src.bits[1] = 2147483647;
  src.bits[2] = 2147483647;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 2147483647);
  ck_assert_int_eq(result.bits[2], 2147483647);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 0);

  src.bits[0] = 0x50000000;
  src.bits[1] = 0x36B90BE5;
  src.bits[2] = 0xA18F07D7;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0x44F40000);
  ck_assert_int_eq(result.bits[1], 0x45639182);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 1);

  src.bits[0] = 0x50000000;
  src.bits[1] = 0x36B90BE5;
  src.bits[2] = 0xA18F07D7;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0x44F40000);
  ck_assert_int_eq(result.bits[1], 0x45639182);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 0);

  src.bits[0] = 0x8BEFDD0F;
  src.bits[1] = 0x79E13C2C;
  src.bits[2] = 0x2FC2CC07;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0xC64CFBD0);
  ck_assert_int_eq(result.bits[1], 0x14835E8B);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 1);

  src.bits[0] = 0x8BEFDD0F;
  src.bits[1] = 0x79E13C2C;
  src.bits[2] = 0x2FC2CC07;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0xC64CFBD0);
  ck_assert_int_eq(result.bits[1], 0x14835E8B);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 1);

  src.bits[0] = 0x50000000;
  src.bits[1] = 0x36B90BE5;
  src.bits[2] = 0xA18F07D7;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0x44F40000);
  ck_assert_int_eq(result.bits[1], 0x45639182);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 8);
  s21_set_sign(&src, 0);

  src.bits[0] = 0x8B7AB89D;
  src.bits[1] = 0xFEF792BB;
  src.bits[2] = 0x2FEB13FD;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0x595DB3D2);
  ck_assert_int_eq(result.bits[1], 0x0A12FE09);
  ck_assert_int_eq(result.bits[2], 0x8);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 8);
  s21_set_sign(&src, 1);

  src.bits[0] = 0x8B7AB89D;
  src.bits[1] = 0xFEF792BB;
  src.bits[2] = 0x2FEB13FD;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0x595DB3D2);
  ck_assert_int_eq(result.bits[1], 0x0A12FE09);
  ck_assert_int_eq(result.bits[2], 0x8);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_truncate) {
  s21_decimal src = {0};
  s21_decimal result = {0};

  src.bits[0] = 0;
  src.bits[0] = 0;
  src.bits[0] = 0;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 5);
  src.bits[0] = 123456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 5);
  s21_set_sign(&src, 1);
  src.bits[0] = 123456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_sign(&src, 0);
  s21_set_exp(&src, 0);
  src.bits[0] = 163456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 163456);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_sign(&src, 1);
  s21_set_exp(&src, 0);
  src.bits[0] = 163456;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 163456);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_sign(&src, 0);
  s21_set_exp(&src, 5);
  src.bits[0] = 100000;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_sign(&src, 1);
  s21_set_exp(&src, 5);
  src.bits[0] = 100000;
  src.bits[1] = 0;
  src.bits[2] = 0;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 0);
  s21_set_sign(&src, 0);

  src.bits[0] = 2147483647;
  src.bits[1] = 2147483647;
  src.bits[2] = 2147483647;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 2147483647);
  ck_assert_int_eq(result.bits[2], 2147483647);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 0);
  s21_set_sign(&src, 1);

  src.bits[0] = 2147483647;
  src.bits[1] = 2147483647;
  src.bits[2] = 2147483647;

  s21_truncate(src, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 2147483647);
  ck_assert_int_eq(result.bits[2], 2147483647);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 0);

  src.bits[0] = 0x50000000;
  src.bits[1] = 0x36B90BE5;
  src.bits[2] = 0xA18F07D7;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 0x44F40000);
  ck_assert_int_eq(result.bits[1], 0x45639182);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 1);

  src.bits[0] = 0x50000000;
  src.bits[1] = 0x36B90BE5;
  src.bits[2] = 0xA18F07D7;

  s21_floor(src, &result);
  ck_assert_int_eq(result.bits[0], 0x44F40000);
  ck_assert_int_eq(result.bits[1], 0x45639182);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 0);

  src.bits[0] = 0x8BEFDD0F;
  src.bits[1] = 0x79E13C2C;
  src.bits[2] = 0x2FC2CC07;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0xC64CFBD0);
  ck_assert_int_eq(result.bits[1], 0x14835E8B);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);

  s21_set_exp(&src, 10);
  s21_set_sign(&src, 1);

  src.bits[0] = 0x8BEFDD0F;
  src.bits[1] = 0x79E13C2C;
  src.bits[2] = 0x2FC2CC07;

  s21_round(src, &result);
  ck_assert_int_eq(result.bits[0], 0xC64CFBD0);
  ck_assert_int_eq(result.bits[1], 0x14835E8B);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

Suite *s21_suite(void) {
  Suite *s = suite_create("s21_decimal");
  TCase *core = tcase_create("Core");

  tcase_add_test(core, test_s21_form_int_to_decimal);
  tcase_add_test(core, test_s21_decimal_to_float);
  tcase_add_test(core, test_s21_form_float_to_decimal);
  tcase_add_test(core, test_s21_decimal_to_int);
  tcase_add_test(core, test_s21_negate);

  tcase_add_test(core, test_s21_div);
  tcase_add_test(core, test_s21_less);
  tcase_add_test(core, test_s21_lessEq);
  tcase_add_test(core, test_s21_greater);
  tcase_add_test(core, test_s21_greaterEq);
  tcase_add_test(core, test_s21_equal);
  tcase_add_test(core, test_s21_notEqual);

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
  tcase_add_test(core, s21_sub_12);

  tcase_add_test(core, test_mul_basic_small_ints);
  tcase_add_test(core, test_mul_zero_left);
  tcase_add_test(core, test_mul_zero_right);
  tcase_add_test(core, test_mul_signs);
  tcase_add_test(core, test_mul_scales_simple);
  tcase_add_test(core, test_mul_scale_clamp_to_28_with_round);
  tcase_add_test(core, test_mul_shrink_to_fit_by_div10);
  tcase_add_test(core, test_mul_overflow_no_scale);
  tcase_add_test(core, test_mul_null_result_ptr);

  tcase_add_test(core, test_s21_floor);
  tcase_add_test(core, test_s21_round);
  tcase_add_test(core, test_s21_truncate);

  suite_add_tcase(s, core);
  return s;
}
