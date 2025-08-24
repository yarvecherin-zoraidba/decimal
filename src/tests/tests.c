#include "tests.h"

int main(void) {
  int fail = 0;
  Suite *s21_decimal_test[] = {s21_add_test(),
    s21_sub_test(),
    s21_mul_test(),
                               NULL};
  for (int i = 0; s21_decimal_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_decimal_test[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    fail += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  if (fail > 0)
    printf("Failed: \033[31m%d\033[0m\n", fail);
  else
    printf("Failed: \033[32m%d\033[0m\n", fail);
  return fail ? 1 : 0;
}
