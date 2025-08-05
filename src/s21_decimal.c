#include "s21_decimal.h"
#include <assert.h>


#define SIGNBIT 0x80000000 

void print_decimal(s21_decimal d) {
    printf("bits[0]: %u\n", d.bits[0]);
    printf("bits[1]: %u\n", d.bits[1]);
    printf("bits[2]: %u\n", d.bits[2]);
    printf("bits[3]: %u\n", d.bits[3]);
    printf("Знак: %s\n", (d.bits[3] & SIGNBIT) ? "Отрицательный" : "Положительный");
}

int main() {
    s21_decimal result;
    int boom = 6789;
    int status = s21_from_int_to_decimal(boom, &result);

    printf("%d\n", result.bits[0]);
    printf("%d\n", result.bits[3]);
    print_decimal(result);


    s21_decimal decimal = {0}; 
    float res = 0.0;
    decimal.bits[0] = 1234;
    decimal.bits[1] = 0;  
    decimal.bits[2] = 0;
    decimal.bits[3] = 0; 
    s21_from_decimal_to_float(decimal, &res);
    printf("%f\n", res);
    return 0;
};

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

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int status = 0;
    double res = 0.0;
    double factor = 1.0;
    unsigned scale;
    int exp;

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
