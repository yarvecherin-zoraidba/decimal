#include "s21_decimal.h"

enum { S21_LIMB_COUNT_192 = 6 };
enum { S21_96_LIMBS = 3 };

static void s21_zero_decimal(s21_decimal *d) {
  d->bits[0] = d->bits[1] = d->bits[2] = d->bits[3] = 0u;
}

static int s21_is_zero96(const s21_decimal *d) {
  return d->bits[0] == 0u && d->bits[1] == 0u && d->bits[2] == 0u;
}

static void s21_big_zero(uint32_t big[], int n) {
  for (int i = 0; i < n; ++i) big[i] = 0u;
}

static uint32_t s21_big_inc(uint32_t big[], int n) {
  uint64_t carry = 1u;
  for (int i = 0; i < n; ++i) {
    uint64_t sum = (uint64_t)big[i] + carry;
    big[i] = (uint32_t)(sum & 0xFFFFFFFFu);
    carry = sum >> 32;
    if (!carry) break;
  }
  return (uint32_t)carry;
}

static uint32_t s21_big_div10(uint32_t big[], int n) {
  uint64_t rem = 0;
  for (int i = n - 1; i >= 0; --i) {
    uint64_t cur = (rem << 32) | big[i];
    big[i] = (uint32_t)(cur / 10u);
    rem = cur % 10u;
  }
  return (uint32_t)rem;
}

static uint32_t s21_big_mod10_const(const uint32_t big[], int n) {
  uint64_t rem = 0;
  for (int i = n - 1; i >= 0; --i) {
    uint64_t cur = (rem << 32) | big[i];
    rem = cur % 10u;
  }
  return (uint32_t)rem;
}

static int s21_big_fits_96(const uint32_t big[]) {
  return big[3] == 0u && big[4] == 0u && big[5] == 0u;
}

static void s21_mul_96x96_to_192(const s21_decimal *x, const s21_decimal *y,
                                 uint32_t out[], int n) {
  s21_big_zero(out, n);
  for (int i = 0; i < S21_96_LIMBS; ++i) {
    uint64_t carry = 0;
    for (int j = 0; j < S21_96_LIMBS; ++j) {
      uint64_t cur = (uint64_t)x->bits[i] * (uint64_t)y->bits[j];
      uint64_t sum = (uint64_t)out[i + j] + cur + carry;
      out[i + j] = (uint32_t)(sum & 0xFFFFFFFFu);
      carry = sum >> 32;
    }
    int k = i + S21_96_LIMBS;
    while (carry && k < n) {
      uint64_t sum = (uint64_t)out[k] + carry;
      out[k] = (uint32_t)(sum & 0xFFFFFFFFu);
      carry = sum >> 32;
      ++k;
    }
  }
}

static void s21_big_round_div10_bankers(uint32_t big[], int n, uint32_t rem,
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
  if (!result) return 1;

  s21_zero_decimal(result);

  if (s21_is_zero96(&a) || s21_is_zero96(&b)) {
    s21_set_exp(result, 0);
    s21_set_sign(result, 0);
    return 0;
  }

  int sign = s21_get_sign(a) ^ s21_get_sign(b);
  unsigned scale = (unsigned)s21_get_exp(a) + (unsigned)s21_get_exp(b);

  a.bits[3] = 0u;
  b.bits[3] = 0u;

  uint32_t big[S21_LIMB_COUNT_192];
  s21_mul_96x96_to_192(&a, &b, big, S21_LIMB_COUNT_192);

  if (scale > 28u) {
    unsigned drop = scale - 28u;
    int sticky = 0;
    for (unsigned t = 0; t < drop; ++t) {
      uint32_t rem = s21_big_div10(big, S21_LIMB_COUNT_192);
      s21_big_round_div10_bankers(big, S21_LIMB_COUNT_192, rem, sticky);
      if (rem != 0u) sticky = 1;
    }
    scale = 28u;
  }

  {
    int sticky = 0;
    while (!s21_big_fits_96(big)) {
      if (scale == 0u) {
        return sign ? 2 : 1;
      }
      uint32_t rem = s21_big_div10(big, S21_LIMB_COUNT_192);
      s21_big_round_div10_bankers(big, S21_LIMB_COUNT_192, rem, sticky);
      if (rem != 0u) sticky = 1;
      --scale;
    }
  }

  result->bits[0] = big[0];
  result->bits[1] = big[1];
  result->bits[2] = big[2];

  if (result->bits[0] == 0u && result->bits[1] == 0u && result->bits[2] == 0u) {
    s21_set_exp(result, 0);
    s21_set_sign(result, 0);
    return 0;
  }

  s21_set_exp(result, (int)scale);
  s21_set_sign(result, sign);

  return 0;
}
