#include "s21_decimal.h"

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
    unsigned int scale = s21_get_exponent(src);
    
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
    
    int overflow = (sign == 1 && values[0] > MAX_INT) || (sign == -1 && values[0] > SIGNBIT);

    if (has_overflow != 0 || overflow != 0) {
        *dst = 0;
    } else if (is_min_int != 0) {
        *dst = MIN_INT;
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
    unsigned int scale = s21_get_exponent(src);
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
    
    if (isinf(src) || isnan(src) || (src > 0 && src < 1e-28) || (src < 0 && src > -1e-28)) {
        s21_init(dst);
        return 1;
    }
    
    if (src < 0) {
        dst->bits[3] |= SIGNBIT;
        src = -src;
    }
    
    unsigned int scale = 0;
    while (src > 0 && src < 1000000.0 && scale < 28) {
        src *= 10.0;
        scale++;
    }
    
    unsigned int float_bits = *(unsigned int *)&src;
    int float_exponent = ((float_bits >> 23) & 0xFF) - 127;
    unsigned int mantissa = float_bits & 0x7FFFFF; //0-22
    
    if (float_exponent >= 0) {
        mantissa |= 0x800000;
    }
    if (mantissa != 0) {
        for (int bit_pos = 23; bit_pos >= 0; bit_pos--) {
            if (mantissa & (1U << bit_pos)) {
                int target_pos = float_exponent - (23 - bit_pos);
                if (target_pos >= 0 && target_pos < 96) {
                    int block = target_pos / 32;
                    int bit = target_pos % 32;
                    if (block < 3) {
                        dst->bits[block] |= (1U << bit);
                    }
                }
            }
        }
    }
    
    dst->bits[3] |= (scale << 16);
    
    return 0;
}

unsigned int s21_get_exponent(s21_decimal src)
{
    src.bits[3] &= ~SIGNBIT; 
    return src.bits[3] >> 16; 
}
