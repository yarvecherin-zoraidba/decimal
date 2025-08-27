#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) return 1;

  int scale = s21_get_exponent(value);
  if (scale > 28) return 1;

  if (!result) return 1;

  *result = value;

  while ((scale--) != 0) {
    s21_divide_by_10(result);
  }

  s21_set_exponent(result, 0);
  return 0;
}

int s21_divide_by_10(s21_decimal *value) {
  if (value == NULL) return -1;

  unsigned long long buff = 0;

  for (int i = 2; i >= 0; i--) {
    unsigned long long temp = (buff << 32) | value->bits[i];
    value->bits[i] = (unsigned)(temp / 10);
    buff = temp % 10;
  }

  return (int)buff;
}


int s21_get_sign(s21_decimal src) {
    return (src.bits[3] & SIGNBIT) ? 1 : 0;
}

void s21_set_sign(s21_decimal *src, int sign) {
    if (sign) {
        src->bits[3] |= SIGNBIT;
    }
    else {
        src->bits[3] &= ~SIGNBIT;
    } 
}

int s21_negate(s21_decimal value, s21_decimal *result) {
    int status = 0;

    if (result) {
        *result = value;
        s21_set_sign(result, !s21_get_sign(value));
    } else {
        status = 1;
    }

    return status;
}

void s21_init(s21_decimal *dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int status = 1;
    if (dst != NULL) {
        s21_init(dst);
        if (src < 0) {
            dst->bits[3] = SIGNBIT;       
            dst->bits[0] = (unsigned int)(-src);
        } else {
            dst->bits[0] = (unsigned int)src;
        }
        status = 0;
    }
    return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    if (!dst) return 1;
    
    int sign = s21_get_sign(src) ? -1 : 1;
    unsigned int scale = (src.bits[3] & 0x00FF0000) >> 16;
    
    int has_overflow = (src.bits[1] > 0 || src.bits[2] > 0);
    
    unsigned int values[3] = {src.bits[0], src.bits[1], src.bits[2]};
    
    for (unsigned int s = 0; s < scale; s++) {
        unsigned int remainder = 0;
        for (int i = 2; i >= 0; i--) {
            unsigned long long temp = ((unsigned long long)remainder << 32) | values[i];
            values[i] = (unsigned int)(temp / 10);
            remainder = (unsigned int)(temp % 10);
        }
    }
    
    if (values[1] > 0 || values[2] > 0) {
        has_overflow = 1;
    }
    
    int is_min_int = (sign == -1 && values[0] == SIGNBIT && values[1] == 0 && values[2] == 0);
    
    int overflow = (sign == 1 && values[0] > 0x7FFFFFFF) || (sign == -1 && values[0] > SIGNBIT);

    if (has_overflow != 0 || overflow != 0) {
        *dst = 0;
    } else if (is_min_int != 0) {
        *dst = -2147483648;
    } else {
        *dst = sign * (int)values[0];
    }
    
    return (has_overflow || overflow) ? 1 : 0;
}


int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    if (!dst) return 1;
    
    double res = 0.0;
    double factor = 1.0;
    
    for (int bit_block = 0; bit_block < 3; bit_block++) {
        for (int bit_pos = 0; bit_pos < 32; bit_pos++) {
            if (src.bits[bit_block] & (1U << bit_pos)) {
                res += factor;
            }
            factor *= 2.0;
        }
    } 
    unsigned int scale = (src.bits[3] & 0x00FF0000) >> 16;
    for (unsigned int i = 0; i < scale; i++) {
        res /= 10.0;
    }
    
    if (src.bits[3] & SIGNBIT) {
        res = -res;
    }
    
    *dst = (float)res;
    return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    s21_init(dst);
    int status = 0;

    if (isinf(src) || isnan(src)) {
    status = 1;
    } else {
        if (src < 0) {
            dst->bits[3] |= SIGNBIT;
            src = -src;
        }
        unsigned int scale = 0;
        while ((scale < 28) && ((int)src == 0 || src < 1000000)) {
            src *= 10; 
            scale++;
        }
        
        unsigned int float_bits = *(unsigned int *)&src;
        int exponent = ((float_bits >> 23) & 0xFF) - 127;
        if (exponent >= 0 && exponent < 96) {
            dst->bits[exponent / 32] |= (1U << (exponent % 32));
        }

        unsigned int mask = 0x400000; //23 бит
        for (int i = exponent; i > 0 && mask != 0; i--) {
            if (i <= 96) { 
                int pos = i - 1; 
                int block= pos / 32;
                int bit = pos % 32;
                
                if (block < 3) {
                    if ((float_bits & mask) != 0) {
                        dst->bits[block] |= (1U << bit);
                    }
                }
            }
            mask >>= 1;
        }
        dst->bits[3] |= (scale << 16);
    }
    
    return status;
  }

unsigned int s21_get_exponent(s21_decimal src)
{
    src.bits[3] &= ~SIGNBIT; 
    return src.bits[3] >> 16; 
}

void s21_set_exponent(s21_decimal *src, unsigned int exponent) {
    if (!src || exponent > 28) return;
    src->bits[3] = (exponent << 16) | (src->bits[3] & SIGNBIT);
}
