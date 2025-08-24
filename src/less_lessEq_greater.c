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
    result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
    result->bits[3] |= ((value_1.bits[3] ^ value_2.bits[3]) & SIGNBIT);
    int ex1 = (int)(value_1.bits[3] & EXBITS) >> 16;
    int ex2 = (int)(value_2.bits[3] & EXBITS) >> 16;
    ex2 = remove_zero_if_div_10(&value_2, ex2);
    int ex_result = 0;
    _Bool fl_num_v1_less_v2 = 0;
    if (value_2.bits[0] == 0U && value_2.bits[1] == 0U && value_2.bits[2] == 0U) {
        res = 3;
    } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
    } else if ((ex_result = make_ex_1_2_zero(&value_1, &value_2, &ex1, &ex2)) < 0) {
        res = ((result->bits[3] & SIGNBIT) == 0U) ? 1 : 2;
    } else if ((fl_num_v1_less_v2 = make_num_v1_greater_v2(&value_1, &ex_result, value_2)) == -1) {
        res = 0; // или res = 2 или res = 0 со значением result без изменений(0,0,0,res->bit[3]). Как понять фразу "Число слишком мало или равно отрицательной бесконечности". Число мало, это число близкое к нулю, но не ноль, или все же имеется ввиду значение MAX,MAX,MAX,28 cо знаком "-"?
    } else {
        unsigned long long remainder = 0U;
        unsigned long long overflow = 0ULL;
        _Bool fl_result_is_overflow = 0;
        _Bool fl_num_value_1_is_zero = 0;
        _Bool fl_num_result_is_zero = 1;

        if (value_2.bits[2] != 0U) {
            if (fl_num_v1_less_v2 == 1) {
                    overflow = change_num_by_mul_10(&value_1, 1);
                    ex_result++;
                }
            while (fl_num_value_1_is_zero == 0 && fl_result_is_overflow == 0) {
                overflow = (overflow << 32) | value_1.bits[2];
                unsigned quotient = (unsigned)(overflow / (unsigned long long)value_2.bits[2]);
                remainder = (unsigned long long)(overflow % (unsigned long long)value_2.bits[2]);
                unsigned long long over_remainder = ((unsigned long long)value_2.bits[0] * (unsigned long long)quotient) >> 32;
                over_remainder = ((unsigned long long)value_2.bits[1] * (unsigned long long)quotient + over_remainder) >> 32;
                if (over_remainder > remainder) {
                    quotient--;
                }
                //ф-я добалвения digit в result, включая проверку для fl_result_is_overflow:
                if (fl_num_result_is_zero == 1) {
                    result->bits[0] = quotient;
                    fl_num_result_is_zero = 0;
                } else if (ex_result < 28) {
                    s21_decimal temp_result = *result;
                    fl_result_is_overflow = (change_num_by_mul_10(&temp_result, 1) != 0ULL);
                    if (fl_result_is_overflow == 0) {
                        fl_result_is_overflow = add_digit(result, quotient);
                    }
                    if (fl_result_is_overflow == 0) {
                        *result = temp_result;
                        ex_result++;
                    } else {
                        //ф-я банковского округления:
                        

                    }
                } else {
                    fl_result_is_overflow = 1;
                }
                if (fl_result_is_overflow == 0) {
                //ф-я вычитания из value_1.bit[0], учитывая необходимость вычитания из bit[1], если вычитаемое больше bit[0]:
                    
                //ф-я вычитания из value_1.bit[1], учитывая необходимость вычитания из bit[2], если вычитаемое больше bit[1]:

                //ф-я вычитания из overflow, учитывая необходимость * 10 (ex_res++), если вычитаемое больше overflow:

                //ф-я провекри для fl_num_value_1_is_zero:
                
                }
            }
        } else if (value_2.bits[1] != 0U) {

        } else if (value_2.bits[0] != 0U) {
            
        }

            // unsigned long long temp = (remainder << 32) | value_1.bits[1];
            // if (temp != 0U) {
            //     result->bits[1] = (unsigned)(temp / (unsigned long long)value_2.bits[1]);
            //     remainder = (unsigned long long)(value_1.bits[2] % value_2.bits[2]);
            //     overflow = ((unsigned long long)value_2.bits[0] * (unsigned long long)result->bits[2]) >> 32;
            //     overflow = ((unsigned long long)value_2.bits[1] * (unsigned long long)result->bits[2] + overflow) >> 32;
            //     if (overflow > remainder) {
            //         result->bits[2]--;
            //         remainder += (unsigned long long)value_2.bits[2];
                // }
            // }
        result->bits[3] |= (ex_result << 16);
    }

            // for (int b = 31; b <= 0; b--) {
            //     remainder = ((value_1.bits[i] >> b) & 1) | (remainder << 1);
            //     if (remainder <= value_2.bits[i]) {
            //         remainder -= value_2.bits[i];
            //         (1 << b) | result->bits[i];
            //     }

    // if (value_2.bits[0] == 1 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    //     //Mul 10^-1 or div 10 in ((value2.bits[3] & ~SIGNBIT) >> 16) times.
    //     }
// s21_decimal v1_exp0 = {{value_1.bits[0], value_1.bits[1], value_1.bits[2], 0U}};
        // s21_decimal v2_exp0 = {{value_2.bits[0], value_2.bits[1], value_2.bits[2], 0U}};

        // remove_right_zeros(&value_2);

    // } else if (value_1.bits[0] == 0xFFFFFFFF && value_1.bits[1] == 0xFFFFFFFF && value_1.bits[2] == 0xFFFFFFFF && (value_1.bits[3] & SIGNBIT) == 1) {
    //     res = 2;
    // }
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
    if (v1 != NULL) {
        s21_decimal v1_temp = *v1;
        while ((compare_with_same_ex(v1_temp, v2) == -1) && (res == 0)) {
            if ((change_num_by_mul_10(&v1_temp, 1) == 0ULL) && (*ex_result < 28)) {
                *v1 = v1_temp;
                (*ex_result)++;
            } else {
                res = (*ex_result >= 28) ? -1 : 1;
            }
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

int s21_negate(s21_decimal value, s21_decimal *result) {
    int status = 0;
    if (result != NULL) {
        *result = value;
        result->bits[3] ^ SIGNBIT;
    } else {
        status = 1;
    }
    return status;
}

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
    int rem = -1;
    if (v != NULL) {
        unsigned long long remainder = 0ULL;
        for (int i = 2; i >= 0; i--) {
            unsigned long long temp = (remainder << 32) | v->bits[i];
            v->bits[i] = (unsigned)(temp / 10ULL);
            remainder = temp % 10; 
        }
        rem = (int)remainder;
    }
    return rem;
}

int make_ex_1_2_zero(s21_decimal *v1, s21_decimal *v2, int *ex1, int *ex2) {
    int ex_result = *ex1 - *ex2;
    _Bool fl_overflow_v1 = 0;
    if (ex_result < 0) {
        fl_overflow_v1 = (change_num_by_mul_10(v1, -ex_result) != 0ULL);
    }
    if (fl_overflow_v1 == 0) {
        ex_result = 0;
    }
    *ex1 = *ex2 = 0;
    v1->bits[3] &= (~EXBITS);
    v2->bits[3] &= (~EXBITS);
    return ex_result;
}

_Bool add_digit(s21_decimal *v, unsigned quotient) {
    unsigned long long overflow = 0ULL;
    for (int i = 0; i < 3; i++) {
        overflow += ((unsigned long long)v->bits[i] + (unsigned long long)quotient);
        v->bits[i] = (unsigned)overflow;
        overflow = overflow >> 32;
    }
    return (overflow != 0ULL);
}