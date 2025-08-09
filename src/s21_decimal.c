#include "s21_decimal.h"
#include <math.h>


#define SIGNBIT 0x80000000 

void s21_print_decimal(s21_decimal dec) {
    printf("Decimal: [");
    for (int i = 0; i < 4; i++) {
        printf("0x%08X", dec.bits[i]);
        if (i < 3) printf(", ");
    }
    printf("]\n");
}

// int main() {
//     // s21_decimal result;
//     // int boom = 6789;
//     // int status = s21_from_int_to_decimal(boom, &result);

//     // printf("%d\n", result.bits[0]);
//     // printf("%d\n", result.bits[3]);
//     // print_decimal(result);


//     s21_decimal decimal = {0}; 
//     float res = 0.0;
//     // decimal.bits[0] = 1234;
//     // decimal.bits[1] = 0;  
//     // decimal.bits[2] = 0;
//     // decimal.bits[3] = 0; 
    
//     int stat;
//     float num = 1234.56;
//     stat = s21_from_float_to_decimal(num, &decimal);
//     printf("Test 1: %f -> status: %d\n", num, stat);
//     s21_print_decimal(decimal); 


//     s21_from_decimal_to_float(decimal, &res);
//     printf("%f\n", res);
//     s21_print_decimal(decimal);

//     return 0;
// };

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

void s21_zero_to_hero(s21_decimal *dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int status = 1;
    if (dst != NULL) {
        s21_zero_to_hero(dst);  
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
    int status = 0;
    
    if (!dst) {
        status = 1;
    } else {
        unsigned long long int_part = 0;
        for (int i = 0; i < 96; i++) {
            if (src.bits[i / 32] & (1U << (i % 32))) {
                int_part += (1ULL << i);
            }
        }
        unsigned int scale = s21_get_exp(src);
        for (unsigned int i = 0; i < scale; i++) {
            int_part /= 10;
        }
        int sign = s21_get_sign(src);
        
        if (sign) {
            if (int_part > SIGNBIT) { 
                status = 1;  
            } else if (int_part == SIGNBIT) {
                *dst = -2147483648;
            } else {
                *dst = -(int)int_part;
            }
        } else {
            if (int_part > 0x7FFFFFFF) { 
                status = 1; 
            } else {
                *dst = (int)int_part;
            }
        }
    }
    
    return status;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int status = 0;
    double res = 0.0;
    double factor = 1.0;

    if (!dst) {
        status = 1;
    } else { 
        for (int i = 0; i < 96; i++) {
            if (src.bits[i / 32] & (1 << (i % 32))) {
                res += factor;
            }
            factor *= 2.0;
        }
        unsigned scale = (src.bits[3] & 0x00FF0000) >> 16;
        int exp = (int)scale;
    
        for (int i = 0; i < exp; i++) {
            res /= 10.0;
        }

        *dst = (float)res;
        if (src.bits[3] & SIGNBIT) {
            *dst = -(*dst);
        }
    }

    return status;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    s21_zero_to_hero(dst);
    int status = 0;

    if ((src == 1.0 / 0.0) || (src == -1.0 / 0.0) || (src != src) || (!dst)) {
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
        int exp = ((float_bits >> 23) & 0xFF) - 127;
        if (exp >= -1 && exp < 96) {
            dst->bits[exp / 32] |= (1U << (exp % 32));
        }

        unsigned int mask = 0x400000;
        for (int i = exp; i > 0 && mask; i--) {
            if (i <= 96) { 
                int pos = i - 1;
                int block= pos / 32;
                int bit = pos % 32;
                
                if (block < 3) {
                    if (float_bits & mask) {
                        dst->bits[block] |= (1U << bit);
                    } else {
                        dst->bits[block] &= ~(1U << bit);
                    }
                }
            }
            mask >>= 1;
        }
        dst->bits[3] |= (scale << 16);
    }
    
    return status;
  }


unsigned int s21_get_exp(s21_decimal src)
{
    src.bits[3] &= ~SIGNBIT; 
    return src.bits[3] >> 16; 
}

void s21_set_exp(s21_decimal *src, unsigned int exp) {
    if (!src || exp > 28) return;
    src->bits[3] = (exp << 16) | (src->bits[3] & SIGNBIT);
}
