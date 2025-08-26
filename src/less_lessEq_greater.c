#include "less_lessEq_greater.h"

// int main() {
//     return 0;
// }

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     int res = 0;
//     return res;
// }

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    if (result == NULL) { 
        return 0;  //или нужно выделить память?
    }
    int res = 0;
    result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0U;
    result->bits[3] |= ((value_1.bits[3] ^ value_2.bits[3]) & SIGNBIT);
    int ex1 = (int)(value_1.bits[3] & EXBITS) >> 16;
    int ex2 = (int)(value_2.bits[3] & EXBITS) >> 16;
    ex2 = remove_zero_if_div_10(&value_2, ex2);
    int ex_result = 0;
    int fl_num_v1_less_v2 = 0;
    if (value_2.bits[0] == 0U && value_2.bits[1] == 0U && value_2.bits[2] == 0U) {
        res = 3;
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
    } else if ((ex_result = make_ex_1_2_zero(&value_1, &value_2, &ex1, &ex2)) < 0) {
        res = ((result->bits[3] & SIGNBIT) == 0U) ? 1 : 2;
    } else if ((fl_num_v1_less_v2 = make_num_v1_greater_v2(&value_1, &ex_result, value_2)) == -1) {
        res = 0; // или res = 2 или res = 0 со значением result без изменений(0,0,0,res->bit[3]). Как понять фразу "Число слишком мало или равно отрицательной бесконечности". Число мало, это число близкое к нулю, но не ноль, или все же имеется ввиду значение MAX,MAX,MAX,28 cо знаком "-"?
    } else {
        make_decimal_division(&value_1, &value_2, result, &ex_result, fl_num_v1_less_v2);
        result->bits[3] |= (ex_result << 16);
    }
    return res;
}

int s21_is_less(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) < 0);
}

int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) <= 0);
}

int s21_is_greater(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) > 0);
}

int s21_is_greater_or_equal(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) >= 0);
}

int s21_is_equal(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) == 0);
}

int s21_is_not_equal(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) != 0);
}

/*
-1 - less (v1 < v2);
 0 - equal (v1 == v2);
+1 - greater (v1 > v2);
*/
int get_res_of_comparison(s21_decimal v1, s21_decimal v2) {
    int res = 1;
    if (v1.bits[0] == 0U && v1.bits[1] == 0U && v1.bits[2] == 0U) {
        if (v2.bits[0] == 0U && v2.bits[1] == 0U && v2.bits[2] == 0U) {
            res = 0;
        } else if ((v2.bits[3] & SIGNBIT) == 0U) {
            res = -1;
        }
    } else if (v2.bits[0] == 0U && v2.bits[1] == 0U && v2.bits[2] == 0U) {
        ((v1.bits[3] & SIGNBIT) != 0U) && (res = -1);
    } else if ((v1.bits[3] & SIGNBIT) > (v2.bits[3] & SIGNBIT)) {
        res = -1;
    } else if ((v1.bits[3] & SIGNBIT) == (v2.bits[3] & SIGNBIT)) {
        int ex1 = (v1.bits[3] & EXBITS) >> 16;
        int ex2 = (v2.bits[3] & EXBITS) >> 16;
        if (ex1 < ex2) {
                res = (int)(change_num_by_mul_10(&v1, ex2 - ex1) != 0ULL);
                res = (res == 1) ? 1 : compare_with_same_ex(v1, v2);
        } else if (ex1 > ex2) {
                res = (int)(change_num_by_mul_10(&v2, ex1 - ex2) != 0ULL);
                res = (res == 1) ? -1 : compare_with_same_ex(v1, v2);
        } else {
            res = compare_with_same_ex(v1, v2);
        }
        if ((v1.bits[3] & SIGNBIT) != 0U) {
            res *= -1;
        }
    }
    return res;
}

int compare_with_same_ex(s21_decimal v1, s21_decimal v2) {
    int res = 1;
    if (v1.bits[2] < v2.bits[2]) {
        res = -1;
    } else if (v1.bits[2] == v2.bits[2]) {
        if (v1.bits[1] < v2.bits[1]) {
            res = -1;
        } else if (v1.bits[1] == v2.bits[1]) {
            if (v1.bits[0] < v2.bits[0]) {
                res = -1;
            } else if (v1.bits[0] == v2.bits[0]) {
                res = 0;
            }
        }
    }
    return res;
}

int make_num_v1_greater_v2(s21_decimal *v1, int *ex_result, s21_decimal v2) {
    int res = 0;
    s21_decimal v1_temp = *v1;
    while ((compare_with_same_ex(v1_temp, v2) == -1) && (res == 0)) {
        if ((change_num_by_mul_10(&v1_temp, 1) == 0ULL) && (*ex_result < 28)) {
            *v1 = v1_temp;
            (*ex_result)++;
        } else {
            res = (*ex_result >= 28) ? -1 : 1;
        }
    }
    return res;
}

unsigned long long change_num_by_mul_10(s21_decimal *v, int delta_ex) {
    unsigned long long overflow = 0ULL;
    for (int d = delta_ex; d > 0 && overflow == 0ULL; d--) {
        for (int i = 0; i < 3; i++) {
            overflow += ((unsigned long long)v->bits[i] * 10ULL);
            v->bits[i] = (unsigned)overflow;
            overflow = overflow >> 32;
        }
    }
    return overflow;
}

// int s21_negate(s21_decimal value, s21_decimal *result) {
//     int status = 0;
//     if (result != NULL) {
//         *result = value;
//         result->bits[3] ^ SIGNBIT;
//     } else {
//         status = 1;
//     }
//     return status;
// }

int remove_zero_if_div_10(s21_decimal *v, int delta_ex) {
    int ex_v = -1;
    if (v != NULL) {
        ex_v = (int)((v->bits[3] & EXBITS) >> 16);
        unsigned long long remainder = 0ULL;
        while (delta_ex-- > 0 && ex_v > 0 && remainder == 0ULL) {
            s21_decimal v_temp = *v;
            remainder = (unsigned long long)divide_by_10(&v_temp);
            if (remainder == 0ULL) {
                *v = v_temp;
                ex_v--;
            }
        }
        v->bits[3] &= SIGNBIT;
        v->bits[3] |= (ex_v << 16);
    }
    return ex_v;
}

int divide_by_10(s21_decimal *v) {
    if (v == NULL) {
        return -1;
    }
    unsigned long long remainder = 0ULL;
    for (int i = 2; i >= 0; i--) {
        unsigned long long temp = (remainder << 32) | v->bits[i];
        v->bits[i] = (unsigned)(temp / 10ULL);
        remainder = temp % 10; 
    }
    return (int)remainder;
}

int make_ex_1_2_zero(s21_decimal *v1, s21_decimal *v2, int *ex1, int *ex2) {
    int ex_result = *ex1 - *ex2;
    _Bool fl_overflow_v1 = 0;
    if (ex_result < 0) {
        fl_overflow_v1 = (change_num_by_mul_10(v1, -ex_result) != 0ULL);
        if (fl_overflow_v1 == 0) {
            ex_result = 0;
        }
    }
    *ex1 = *ex2 = 0;
    v1->bits[3] &= (~EXBITS);
    v2->bits[3] &= (~EXBITS);
    return ex_result;
}

_Bool add_digit(s21_decimal *v, unsigned digit) {
    unsigned long long overflow = (unsigned long long)(digit);
    for (int i = 0; i < 3; i++) {
        overflow += (unsigned long long)v->bits[i];
        v->bits[i] = (unsigned)overflow;
        overflow = overflow >> 32;
    }
    return (overflow != 0ULL);
}

void make_decimal_division(s21_decimal *v1, s21_decimal *v2, s21_decimal *result, int *ex_result, int fl_num_v1_less_v2) {
    if (v2->bits[2] != 0U) {
        divide_by_96_bits(v1, v2, result, ex_result, fl_num_v1_less_v2);
    } else if (v2->bits[1] != 0U) {
        divide_by_64_bits(v1, v2, result, ex_result);
    } else if (v2->bits[0] != 0U) {
        divide_by_32_bits(v1, v2, result, ex_result);
    }
}

void divide_by_96_bits(s21_decimal *v1, s21_decimal *v2, s21_decimal *result, int *ex_result, int fl_num_v1_less_v2) {
    unsigned long long overflow_v1 = 0ULL;
    _Bool fl_result_is_overflow = 0;
    _Bool fl_num_result_is_zero = 1;
    _Bool fl_num_value_1_is_zero = 0;
    if (fl_num_v1_less_v2 == 1) {
        overflow_v1 = change_num_by_mul_10(v1, 1);
        overflow_v1 = overflow_v1 << 32;
        (*ex_result)++;
    }
    while (fl_num_value_1_is_zero == 0 && fl_result_is_overflow == 0) {
        overflow_v1 = (overflow_v1 | (unsigned long long)v1->bits[2]);
        unsigned quotient = (unsigned)(overflow_v1 / (unsigned long long)v2->bits[2]);
        unsigned long long remainder = (unsigned long long)(overflow_v1 % (unsigned long long)v2->bits[2]);
        unsigned long long over_remainder = ((unsigned long long)v2->bits[0] * (unsigned long long)quotient) >> 32;
        over_remainder = ((unsigned long long)v2->bits[1] * (unsigned long long)quotient + over_remainder) >> 32;
        if (over_remainder > remainder) {
            quotient--;
        }
        if (fl_num_result_is_zero == 1) {
            result->bits[0] = quotient;
            fl_num_result_is_zero = 0;
        } else {
            fl_result_is_overflow = add_quotient_in_result(result, ex_result, quotient);
        }
        if (fl_result_is_overflow == 0) {
            if (quotient != 0) {
                subtract_low_bits_from_96bits_divident(v1, v2, &overflow_v1, quotient);
                subtract_middle_bits_from_96bits_divident(v1, v2, &overflow_v1, quotient);
                subtract_high_bits_from_96bits_divident(v1, v2, &overflow_v1, quotient);
            }
            fl_num_value_1_is_zero = (v1->bits[0] == 0U && v1->bits[1] == 0U && v1->bits[2] == 0U);
            if (fl_num_value_1_is_zero == 0) {
                overflow_v1 = change_num_by_mul_10(v1, 1);
                overflow_v1 = overflow_v1 << 32;
            }
        }
    }
}

void divide_by_64_bits(s21_decimal *v1, s21_decimal *v2, s21_decimal *result, int *ex_result) {
    unsigned long long overflow_v1 = (unsigned long long)(((unsigned long long)v1->bits[2] << 32) | (unsigned long long)v1->bits[1]);
    unsigned long long overflow_v2 = (unsigned long long)(((unsigned long long)v2->bits[1] << 32) | (unsigned long long)v2->bits[0]);
    _Bool fl_result_is_overflow = 0;
    result->bits[1] = (unsigned)(overflow_v1 / overflow_v2);
    overflow_v1 -= (unsigned long long)(overflow_v2 * (unsigned long long)result->bits[1]);
    overflow_v1 = (unsigned long long)((overflow_v1 << 32) | (unsigned long long)v1->bits[0]);
    result->bits[0] = (unsigned)(overflow_v1 / overflow_v2);
    overflow_v1 -= (unsigned long long)(overflow_v2 * (unsigned long long)result->bits[0]);
    v1->bits[2] = 0U;
    v1->bits[1] = (unsigned)(overflow_v1 >> 32);
    v1->bits[0] = (unsigned)overflow_v1;
    _Bool fl_num_value_1_is_zero = (v1->bits[1] == 0U && v1->bits[0] == 0U);
    if (fl_num_value_1_is_zero == 0) {
        change_num_by_mul_10(v1, 1);
    }
    while (fl_num_value_1_is_zero == 0 && fl_result_is_overflow == 0) {
        overflow_v1 = (unsigned long long)(((unsigned long long)v1->bits[2] << 32) | (unsigned long long)v1->bits[1]);
        unsigned quotient = (unsigned)(overflow_v1 / (unsigned long long)v2->bits[1]);
        unsigned long long remainder = (unsigned long long)(overflow_v1 % (unsigned long long)v2->bits[1]);
        unsigned long long over_remainder = ((unsigned long long)v2->bits[0] * (unsigned long long)quotient) >> 32;
        if (over_remainder > remainder) {
            quotient--;
        }
        fl_result_is_overflow = add_quotient_in_result(result, ex_result, quotient);
        if (fl_result_is_overflow == 0) {
            if (quotient != 0) {
                subtract_low_bits_from_96bits_divident(v1, v2, &overflow_v1, quotient);
                subtract_middle_bits_from_96bits_divident(v1, v2, &overflow_v1, quotient);
            }
            fl_num_value_1_is_zero = (v1->bits[0] == 0U && v1->bits[1] == 0U && v1->bits[2] == 0U);
            if (fl_num_value_1_is_zero == 0) {
                change_num_by_mul_10(v1, 1);
            }
        }
    }
}

void divide_by_32_bits(s21_decimal *v1, s21_decimal *v2, s21_decimal *result, int *ex_result) {
    unsigned long long overflow_v1 = 0ULL;
    _Bool fl_result_is_overflow = 0;
    for (int i = 2; i >= 0; i--) {
        overflow_v1 = overflow_v1 << 32;
        overflow_v1 |= (unsigned long long)v1->bits[i];
        result->bits[i] = (unsigned)(overflow_v1 / (unsigned long long)v2->bits[0]);
        overflow_v1 -= (unsigned long long)((unsigned long long)v2->bits[0] * (unsigned long long)result->bits[i]);
    }
    v1->bits[2] = v1->bits[1] = 0U;
    v1->bits[0] = (unsigned)overflow_v1;
    _Bool fl_num_value_1_is_zero = (v1->bits[0] == 0U);
    if (fl_num_value_1_is_zero == 0) {
        change_num_by_mul_10(v1, 1);
    }
    while (fl_num_value_1_is_zero == 0 && fl_result_is_overflow == 0) {
        overflow_v1 = (unsigned long long)(((unsigned long long)v1->bits[1] << 32) | (unsigned long long)v1->bits[0]);
        unsigned quotient = (unsigned)(overflow_v1 / (unsigned long long)v2->bits[0]);
        fl_result_is_overflow = add_quotient_in_result(result, ex_result, quotient);
        if (fl_result_is_overflow == 0) {
            if (quotient != 0) {
                subtract_low_bits_from_64bits_divident(v1, v2, &overflow_v1, quotient);
            }
            fl_num_value_1_is_zero = (v1->bits[0] == 0U && v1->bits[1] == 0U && v1->bits[2] == 0U);
            if (fl_num_value_1_is_zero == 0) {
                change_num_by_mul_10(v1, 1);
            }
        }
    }
}

_Bool add_quotient_in_result(s21_decimal *result, int *ex_result, unsigned quotient) {
    _Bool fl_result_is_overflow = 0;
    if (*ex_result < 28) {
        s21_decimal temp_result = *result;
        fl_result_is_overflow = (change_num_by_mul_10(&temp_result, 1) != 0ULL);
        if (fl_result_is_overflow == 1) {
            round_banks_decimal(result, quotient);
        } else {
            fl_result_is_overflow = add_digit(&temp_result, quotient);
            if (fl_result_is_overflow == 0) {
                *result = temp_result;
                (*ex_result)++;
            }
        }
    } else {
        fl_result_is_overflow = 1;
    }
    return fl_result_is_overflow;
}

void round_banks_decimal(s21_decimal *v, unsigned digit) {
    s21_decimal temp_v = *v;
    int remainder = divide_by_10(&temp_v);
    remainder %= 2;
    if (digit > 5 || (digit == 5U && remainder == 1)) {
        temp_v = *v;
        if (add_digit(&temp_v, 1) == 0) {
            *v = temp_v;
        }
    }
}

void subtract_low_bits_from_96bits_divident(s21_decimal *v1, s21_decimal *v2, unsigned long long *overflow_v1, unsigned quotient) {
    unsigned long long minuend_v1 = (unsigned long long)((unsigned long long)v1->bits[1] << 32) | (unsigned long long)v1->bits[0];
    unsigned long long subtrahend = (unsigned long long)((unsigned long long)v2->bits[0] * (unsigned long long)quotient);
    if (minuend_v1 < subtrahend) {
        subtrahend -= minuend_v1;
        (*overflow_v1)--;
        v1->bits[2] = (unsigned)(*overflow_v1);
        unsigned long long extra_minuend_v1 = ALL_64_BITS;
        extra_minuend_v1 -= (subtrahend - 1ULL);
        v1->bits[0] = (unsigned)extra_minuend_v1;
        v1->bits[1] = (unsigned)(extra_minuend_v1 >> 32);
    } else {
        minuend_v1 -= subtrahend;
        v1->bits[0] = (unsigned)minuend_v1;
        v1->bits[1] = (unsigned)(minuend_v1 >> 32);
    }
}

void subtract_middle_bits_from_96bits_divident(s21_decimal *v1, s21_decimal *v2, unsigned long long *overflow_v1, unsigned quotient) {
    unsigned long long minuend_v1 = (unsigned long long)((unsigned long long)v1->bits[2] << 32) | (unsigned long long)v1->bits[1];
    unsigned long long subtrahend = (unsigned long long)((unsigned long long)v2->bits[1] * (unsigned long long)quotient);
    if (minuend_v1 < subtrahend) {
        subtrahend -= minuend_v1;
        *overflow_v1 = (*overflow_v1 >> 32) - 1ULL;
        unsigned long long extra_minuend_v1 = ALL_64_BITS;
        extra_minuend_v1 -= (subtrahend - 1ULL);
        v1->bits[1] = (unsigned)extra_minuend_v1;
        v1->bits[2] = (unsigned)(extra_minuend_v1 >> 32);
        *overflow_v1 = (*overflow_v1 & LEFT_32_FOR_64_BITS) | (unsigned long long)v1->bits[2];
    } else {
        minuend_v1 -= subtrahend;
        v1->bits[1] = (unsigned)minuend_v1;
        v1->bits[2] = (unsigned)(minuend_v1 >> 32);
    }
}
    
void subtract_high_bits_from_96bits_divident(s21_decimal *v1, s21_decimal *v2, unsigned long long *overflow_v1, unsigned quotient) {
    unsigned long long subtrahend = (unsigned long long)((unsigned long long)v2->bits[2] * (unsigned long long)quotient);
    (*overflow_v1) -= subtrahend;
    v1->bits[2] = (unsigned)(*overflow_v1);
}

void subtract_low_bits_from_64bits_divident(s21_decimal *v1, s21_decimal *v2, unsigned long long *overflow_v1, unsigned quotient) {
    unsigned long long subtrahend = (unsigned long long)((unsigned long long)v2->bits[0] * (unsigned long long)quotient);
    (*overflow_v1) -= subtrahend;
    v1->bits[1] = (unsigned)(*overflow_v1 >> 32);
    v1->bits[0] = (unsigned)(*overflow_v1);
}