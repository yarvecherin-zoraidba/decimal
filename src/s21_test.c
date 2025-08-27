#include <check.h>
#include "s21_decimal.h"
#include <limits.h>

Suite *s21_suite(void);


int main() {
    SRunner *sr = srunner_create(NULL);
  
    srunner_add_suite(sr, s21_suite());
  
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
  
    return failed == 0 ? 0 : 1;
  }

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
    s21_decimal src5 = {{1234567, 0, 0, 0x80000000 | (2<<16)}};
    s21_from_decimal_to_float(src5, &number5);
    ck_assert_float_eq(number5, -12345.67);

    float number6 = 0.0;
    s21_decimal src6 = {{1234567, 0, 0, (7<<16)}};
    s21_from_decimal_to_float(src6, &number6);
    ck_assert_float_eq(number6, 0.1234567);
  
    float number7 = 0.0;
    s21_decimal src7 = {{4294967295, 4294967295, 0, 0}};
    s21_from_decimal_to_float(src7, &number7);
    ck_assert_float_eq(number7, 0xFFFFFFFFFFFFFFFF);

    float number8 = 0.0;
    s21_decimal src8 = {{1234567, 0, 0, (28<<16)}};
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
    ck_assert_int_eq(src7.bits[3], 0x80000000 | (3<<16));

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

Suite *s21_suite(void) {
    Suite *s = suite_create("s21_decimal");
    TCase *core = tcase_create("Core");
    
    tcase_add_test(core, test_s21_form_int_to_decimal);
    tcase_add_test(core, test_s21_decimal_to_float);
    tcase_add_test(core, test_s21_form_float_to_decimal);
    tcase_add_test(core, test_s21_decimal_to_int);
    tcase_add_test(core, test_s21_negate);
    
  
    suite_add_tcase(s, core);
  
    return s;
  }


 
