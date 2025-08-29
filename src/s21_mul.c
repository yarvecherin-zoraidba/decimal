#include "s21_decimal.h"

void s21_zero_decimal(s21_decimal *d) {
  d->bits[0] = d->bits[1] = d->bits[2] = d->bits[3] = 0u;
}

int s21_is_zero96(const s21_decimal *d) {
  return d->bits[0] == 0u && d->bits[1] == 0u && d->bits[2] == 0u;
}

void s21_big_zero(unsigned big[], int n) {
  for (int i = 0; i < n; ++i) big[i] = 0u;
}

unsigned s21_big_inc(unsigned big[], int n) {
  unsigned long long carry = 1u;
  for (int i = 0; i < n; ++i) {
    unsigned long long sum = (unsigned long long)big[i] + carry;
    big[i] = (unsigned)(sum & 0xFFFFFFFFu);
    carry = sum >> 32;
    if (!carry) break;
  }
  return (unsigned)carry;
}

unsigned s21_big_div10(unsigned big[], int n) {
  unsigned long long rem = 0;
  for (int i = n - 1; i >= 0; --i) {
    unsigned long long cur = (rem << 32) | (unsigned long long)big[i];
    big[i] = (unsigned)(cur / 10u);
    rem = cur % 10u;
  }
  return (unsigned)rem;
}

unsigned s21_big_mod10_const(const unsigned big[], int n) {
  unsigned long long rem = 0;
  for (int i = n - 1; i >= 0; --i) {
    unsigned long long cur = (rem << 32) | (unsigned long long)big[i];
    rem = cur % 10u;
  }
  return (unsigned)rem;
}

int s21_big_fits_96(const unsigned big[]) {
  return big[3] == 0u && big[4] == 0u && big[5] == 0u;
}

void s21_mul_96x96_to_192(const s21_decimal *x, const s21_decimal *y,
                          unsigned out[], int n) {
  s21_big_zero(out, n);
  for (int i = 0; i < S21_96_LIMBS; ++i) {
    unsigned long long carry = 0;
    for (int j = 0; j < S21_96_LIMBS; ++j) {
      unsigned long long cur =
          (unsigned long long)x->bits[i] * (unsigned long long)y->bits[j];
      unsigned long long sum = (unsigned long long)out[i + j] + cur + carry;
      out[i + j] = (unsigned)(sum & 0xFFFFFFFFu);
      carry = sum >> 32;
    }
    int k = i + S21_96_LIMBS;
    while (carry && k < n) {
      unsigned long long sum = (unsigned long long)out[k] + carry;
      out[k] = (unsigned)(sum & 0xFFFFFFFFu);
      carry = sum >> 32;
      ++k;
    }
  }
}

void s21_big_round_div10_bankers(unsigned big[], int n, unsigned rem,
                                 int sticky) {
  if (rem > 5u) {
    (void)s21_big_inc(big, n);
  } else if (rem == 5u) {
    if (sticky) {
      (void)s21_big_inc(big, n);
    } else {
      if (s21_big_mod10_const(big, n) & 1u) {
        (void)s21_big_inc(big, n);
      }
    }
  }
}

int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result) {
  int status = S21_OK;

  if (!result) {
    status = S21_INF_POS;
  } else {
    s21_zero_decimal(result);

    if (s21_is_zero96(&a) || s21_is_zero96(&b)) {
      s21_set_exp(result, 0);
      s21_set_sign(result, 0);
    } else {
      int sign = s21_get_sign(a) ^ s21_get_sign(b);
      unsigned scale = (unsigned)s21_get_exp(a) + (unsigned)s21_get_exp(b);

      a.bits[3] = 0u;
      b.bits[3] = 0u;

      unsigned big[S21_LIMB_COUNT_192];
      s21_mul_96x96_to_192(&a, &b, big, S21_LIMB_COUNT_192);

      if (scale > 28u) {
        unsigned drop = scale - 28u;
        int sticky = 0;
        for (unsigned t = 0; t < drop; ++t) {
          unsigned rem = s21_big_div10(big, S21_LIMB_COUNT_192);
          s21_big_round_div10_bankers(big, S21_LIMB_COUNT_192, rem, sticky);
          if (rem != 0u) sticky = 1;
        }
        scale = 28u;
      }

      {
        int sticky = 0;
        while (!s21_big_fits_96(big) && status == S21_OK) {
          if (scale == 0u) {
            status = sign ? S21_INF_NEG : S21_INF_POS;
          } else {
            unsigned rem = s21_big_div10(big, S21_LIMB_COUNT_192);
            s21_big_round_div10_bankers(big, S21_LIMB_COUNT_192, rem, sticky);
            if (rem != 0u) sticky = 1;
            --scale;
          }
        }
      }

      if (status == S21_OK) {
        result->bits[0] = big[0];
        result->bits[1] = big[1];
        result->bits[2] = big[2];

        if (result->bits[0] == 0u && result->bits[1] == 0u &&
            result->bits[2] == 0u) {
          s21_set_exp(result, 0);
          s21_set_sign(result, 0);
        } else {
          s21_set_exp(result, (int)scale);
          s21_set_sign(result, sign);
        }
      }
    }
  }
  return status;
}
