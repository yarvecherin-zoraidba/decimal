#include <check.h>
#include "s21_decimal.h"
#include "s21_round.h"

Suite *s21_suite(void);

int main() {
    SRunner *sr = srunner_create(NULL);
  
    srunner_add_suite(sr, s21_suite());
  
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
  
    return failed == 0 ? 0 : 1;
}

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

Suite *s21_suite(void) {
    Suite *s = suite_create("s21_decimal");
    TCase *core = tcase_create("Core");
    
    tcase_add_test(core, test_s21_floor);
    tcase_add_test(core, test_s21_round);
    tcase_add_test(core, test_s21_truncate);
  
    suite_add_tcase(s, core);
  
    return s;
}
