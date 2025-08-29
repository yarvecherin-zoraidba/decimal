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

  START_TEST(s21_sub_1) {
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
  
    s21_sub(value_1, value_2, &result);
  
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
  
  START_TEST(s21_sub_2) {
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
  
    value_2.bits[0] = 2;
    value_2.bits[1] = 0;
    value_2.bits[2] = 0;
  
    *(v1_byte + 14) = 0;  // Float
    *(v1_byte + 15) = 0;  // Sign
  
    *(v2_byte + 14) = 0;  // Float
    *(v2_byte + 15) = 0;  // Sign
  
    s21_sub(value_1, value_2, &result);
  
    exp_result.bits[0] = 1;
    exp_result.bits[1] = 0;
    exp_result.bits[2] = 0;
  
    *(exp_res_byte + 14) = 0;
    *(exp_res_byte + 15) = 1;
  
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
    }
  }
  END_TEST
  
  START_TEST(s21_sub_3) {
    s21_decimal value_1 = s21_decimal_init();
    s21_decimal value_2 = s21_decimal_init();
    s21_decimal result;
    s21_decimal exp_result = s21_decimal_init();
    char *v1_byte = (char *)value_1.bits;
    char *v2_byte = (char *)value_2.bits;
    char *exp_res_byte = (char *)exp_result.bits;
  
    value_1.bits[0] = 0;
    value_1.bits[1] = 1;
    value_1.bits[2] = 0;
  
    value_2.bits[0] = 0;
    value_2.bits[1] = 2;
    value_2.bits[2] = 0;
  
    *(v1_byte + 14) = 0;  // Float
    *(v1_byte + 15) = 0;  // Sign
  
    *(v2_byte + 14) = 0;  // Float
    *(v2_byte + 15) = 0;  // Sign
  
    s21_sub(value_1, value_2, &result);
  
    exp_result.bits[0] = 0;
    exp_result.bits[1] = 1;
    exp_result.bits[2] = 0;
  
    *(exp_res_byte + 14) = 0;
    *(exp_res_byte + 15) = 1;
  
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
    }
  }
  END_TEST
  
  START_TEST(s21_sub_4) {
    s21_decimal value_1 = s21_decimal_init();
    s21_decimal value_2 = s21_decimal_init();
    s21_decimal result;
    s21_decimal exp_result = s21_decimal_init();
    char *v1_byte = (char *)value_1.bits;
    char *v2_byte = (char *)value_2.bits;
    char *exp_res_byte = (char *)exp_result.bits;
  
    value_1.bits[0] = 0;
    value_1.bits[1] = 0;
    value_1.bits[2] = 1;
  
    value_2.bits[0] = 0;
    value_2.bits[1] = 0;
    value_2.bits[2] = 2;
  
    *(v1_byte + 14) = 0;  // Float
    *(v1_byte + 15) = 0;  // Sign
  
    *(v2_byte + 14) = 0;  // Float
    *(v2_byte + 15) = 0;  // Sign
  
    s21_sub(value_1, value_2, &result);
  
    exp_result.bits[0] = 0;
    exp_result.bits[1] = 0;
    exp_result.bits[2] = 1;
  
    *(exp_res_byte + 14) = 0;
    *(exp_res_byte + 15) = 1;
  
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
    }
  }
  END_TEST
  
  START_TEST(s21_sub_5) {
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
    *(v2_byte + 15) = 0;  // Sign
  
    s21_sub(value_1, value_2, &result);
  
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
  
  START_TEST(s21_sub_6) {
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
    *(v2_byte + 15) = 0;  // Sign
  
    s21_sub(value_1, value_2, &result);
  
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
  
  START_TEST(s21_sub_7) {
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
    *(v2_byte + 15) = 1;  // Sign
  
    s21_sub(value_1, value_2, &result);
  
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
  
  START_TEST(s21_sub_8) {
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
    *(v2_byte + 15) = 1;  // Sign
  
    s21_sub(value_1, value_2, &result);
  
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
  
  START_TEST(s21_sub_9) {
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
  
    s21_sub(value_1, value_2, &result);
  
    exp_result.bits[0] = 45;
    exp_result.bits[1] = 0;
    exp_result.bits[2] = 0;
  
    *(exp_res_byte + 14) = 2;
    *(exp_res_byte + 15) = 0;
  
    for (int i = 0; i < 4; i++) {
      ck_assert_int_eq(result.bits[i], exp_result.bits[i]);
    }
  }
  END_TEST
  
  START_TEST(s21_sub_10) {
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
  
    s21_sub(value_1, value_2, &result);
  
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
  
  START_TEST(s21_sub_11) {
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
  
    s21_sub(value_1, value_2, &result);
  
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
  
  START_TEST(s21_sub_12) {
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
    *(v1_byte + 15) = 1;  // Sign
  
    *(v2_byte + 14) = 0;  // Float
    *(v2_byte + 15) = 0;  // Sign
  
    error = s21_sub(value_1, value_2, &result);
    exp_error = 2;
  
    ck_assert_int_eq(error, exp_error);
  }
  END_TEST
  
  START_TEST(s21_sub_13) {
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
    *(v2_byte + 15) = 0;  // Sign
  
    s21_sub(value_1, value_2, &result);
  
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
  
  START_TEST(s21_sub_14) {
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
  
    s21_sub(value_1, value_2, &result);
  
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
    tcase_add_test(core, s21_add_14);
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
    tcase_add_test(core, s21_sub_13);
    tcase_add_test(core, s21_sub_14);
    suite_add_tcase(s, core);
  
    return s;
  }
