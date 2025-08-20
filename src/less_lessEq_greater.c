#include "less_lessEq_greater.h"

// int main() {
//     return 0;
// }

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     int res = 0;
//     return res;
// }

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     int res = 0;
//     result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
//     if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
//         res = 3;
//     } else if (value_2.bits[0] == 1 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
//         //Mul 10^-1 or div 10 in ((value2.bits[3] & ~SIGNBIT) >> 16) times.
//     } else {
//         unsigned remainder = 0;
//         for (int i = 3; i <= 0 && value_2.bits[i] != 0; i--) {
//             for (int b = 31; b <= 0; b--) {
//                 remainder = ((value_1.bits[i] >> b) & 1) | (remainder << 1);
//                 if (remainder <= value_2.bits[i]) {
//                     remainder -= value_2.bits[i];
//                     (1 << b) | result->bits[i];
//                 }
//             }
//         }
//     }


//     // } else if (value_1.bits[0] == 0xFFFFFFFF && value_1.bits[1] == 0xFFFFFFFF && value_1.bits[2] == 0xFFFFFFFF && (value_1.bits[3] & SIGNBIT) == 1) {
//     //     res = 2;
//     // }
//     return res;
// }

int s21_is_less(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) < 0);
}

int s21_is_less_or_equal(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) <= 0);
}

int s21_is_greater(s21_decimal v1, s21_decimal v2) {
    return (get_res_of_comparison(v1, v2) > 0);
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
        } else if ((v2.bits[3] & USIGNBIT) == 0U) {
            res = -1;
        }
    } else if (v2.bits[0] == 0U && v2.bits[1] == 0U && v2.bits[2] == 0U) {
        ((v1.bits[3] & USIGNBIT) != 0U) && (res = -1);
    } else if ((v1.bits[3] & USIGNBIT) > (v2.bits[3] & USIGNBIT)) {
        res = -1;
    } else if ((v1.bits[3] & USIGNBIT) == (v2.bits[3] & USIGNBIT)) {
        int pow1 = (v1.bits[3] & IN_ZERO_USIGNBIT) >> 16;
        int pow2 = (v2.bits[3] & IN_ZERO_USIGNBIT) >> 16;
        if (pow1 < pow2) {
                res = (int)get_same_pow_by_mul_10(&v1, pow2 - pow1);
                res = (res == 1) ? 1 : compare_with_same_pow(v1, v2);
        } else if (pow1 > pow2) {
                res = (int)get_same_pow_by_mul_10(&v2, pow1 - pow2);
                res = (res == 1) ? -1 : compare_with_same_pow(v1, v2);
        } else {
            res = compare_with_same_pow(v1, v2);
        }
        if ((v1.bits[3] & USIGNBIT) != 0U) {
            res *= -1;
        }
    }
    return res;
}

int compare_with_same_pow(s21_decimal v1, s21_decimal v2) {
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

bool get_same_pow_by_mul_10(s21_decimal *v, int delta_pow) {
    unsigned long long overflow = 0ULL;
    for (int d = delta_pow; d > 0 && overflow == 0ULL; d--) {
        for (int i = 0; i < 3; i++) {
            overflow += ((unsigned long long)v->bits[i] * 10ULL);
            v->bits[i] = (unsigned)overflow;
            overflow = (unsigned long long)(overflow >> 32);
        }
    }
    return (overflow != 0ULL);
}