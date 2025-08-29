enum { S21_OK = 0, S21_INF_POS = 1, S21_INF_NEG = 2, S21_DIV_BY_ZERO = 3 };

enum { S21_LIMB_COUNT_192 = 6 };
enum { S21_96_LIMBS = 3 };

void s21_zero_decimal(s21_decimal *d);
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_is_zero96(const s21_decimal *d);
void s21_big_zero(unsigned big[], int n);
unsigned s21_big_inc(unsigned big[], int n);
unsigned s21_big_div10(unsigned big[], int n);
unsigned s21_big_mod10_const(const unsigned big[], int n);
int s21_big_fits_96(const unsigned big[]);
void s21_mul_96x96_to_192(const s21_decimal *x, const s21_decimal *y, unsigned out[], int n);
void s21_big_round_div10_bankers(unsigned big[], int n, unsigned rem, int sticky);
