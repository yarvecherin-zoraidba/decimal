enum { S21_OK = 0, S21_INF_POS = 1, S21_INF_NEG = 2, S21_DIV_BY_ZERO = 3 };

enum { S21_LIMB_COUNT_192 = 6 };
enum { S21_96_LIMBS = 3 };

int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result);
