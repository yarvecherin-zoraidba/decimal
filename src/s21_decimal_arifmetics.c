#include "s21_decimal.h"

s21_another_decimal s21_decimal_init() {
  s21_another_decimal result = {0};
  return result;
}

int s21_add(s21_another_decimal value1, s21_another_decimal value2, s21_another_decimal *result) {
    *result = s21_decimal_init();
    int error = 0;
    if (value1.sign ^ value2.sign) {
        if (value1.sign) {
            value1.sign = 0;
            error = s21_sub(value2, value1, result);
        } else {
            value2.sign = 0;
            error = s21_sub(value1, value2, result);
        }
        return error; 
    }
    
    int exp1 = s21_get_exponent(value1);
    int exp2 = s21_get_exponent(value2);
    int max_exp = (exp1 > exp2) ? exp1 : exp2;
    
    s21_another_decimal aligned1 = value1;
    s21_another_decimal aligned2 = value2;
    s21_align_exponents(&aligned1, &aligned2);
    unsigned long long sum = 0;
    unsigned long long carry = 0;
    
    for (int i = 0; i < 3; i++) {
        sum = (unsigned long long)aligned1.bits[i] + 
              (unsigned long long)aligned2.bits[i] + 
              carry;
        carry = sum >> 32;
        result->bits[i] = (unsigned int)(sum & 0xFFFFFFFF);
    }
    if (carry > 0) {
        if (max_exp > 0) {
            s21_another_decimal temp = *result;
            s21_set_exponent(&temp, max_exp);
            error = s21_div_by_10(&temp, result);
            if (!error) {
                s21_set_exponent(result, max_exp - 1);
            }
        } else {
            error = 1; 
        }
    } else {
        s21_set_exponent(result, max_exp);
    }
    result->sign = value1.sign;
    return error;
}


int s21_sub(s21_another_decimal value1, s21_another_decimal value2, s21_another_decimal *result) {
    *result = s21_decimal_init();
    int error = 0;
    
    // Обрабатываем разные знаки - преобразуем в сложение
    if (value1.sign != value2.sign) {
        value2.sign = !value2.sign; // Меняем знак второго числа
        return s21_add(value1, value2, result);
    }

    // Выравниваем экспоненты
    s21_another_decimal aligned1 = value1;
    s21_another_decimal aligned2 = value2;
    
    error = s21_align_exponents(&aligned1, &aligned2);
    if (error) return error;
    
    int exp = s21_get_exponent(aligned1);
    int comparison = s21_compare_absolute(aligned1, aligned2);
    
    if (comparison == 0) {
        *result = s21_decimal_init(); // Результат 0
        return 0;
    }
    
    // Определяем большее и меньшее число (используем копии, а не указатели)
    s21_another_decimal larger, smaller;
    int result_sign = 0;
    
    if (comparison > 0) {
        larger = aligned1;
        smaller = aligned2;
        result_sign = value1.sign;
    } else {
        larger = aligned2;
        smaller = aligned1;
        result_sign = !value1.sign;
    }
    
    // Вычитание с заимствованием
    unsigned int borrow = 0;
    
    for (int i = 0; i < 3; i++) {
        unsigned long long larger_val = (unsigned long long)larger.bits[i];
        unsigned long long smaller_val = (unsigned long long)smaller.bits[i] + borrow;
        
        if (larger_val < smaller_val) {
            result->bits[i] = (unsigned int)(0x100000000ULL + larger_val - smaller_val);
            borrow = 1;
        } else {
            result->bits[i] = (unsigned int)(larger_val - smaller_val);
            borrow = 0;
        }
    }
    
    // Проверка на переполнение
    if (borrow != 0) {
        return 2; // Код ошибки для переполнения
    }
    
    // Устанавливаем экспоненту и знак
    s21_set_exponent(result, exp);
    result->sign = result_sign;
    
    return error;
}

int s21_align_exponents(s21_another_decimal *a, s21_another_decimal *b) {
    if (!a || !b) return 1;
    
    int exp1 = s21_get_exponent(*a);
    int exp2 = s21_get_exponent(*b);
    
    if (exp1 == exp2) return 0;
    
    int error = 0;
    
    if (exp1 < exp2) {
        error = s21_multiply_by_10_power(a, exp2 - exp1);
        if (!error) {
            s21_set_exponent(a, exp2);
        }
    } else {
        error = s21_multiply_by_10_power(b, exp1 - exp2);
        if (!error) {
            s21_set_exponent(b, exp1);
        }
    }
    
    return error;
}

int s21_multiply_by_10_power(s21_another_decimal *value, int power) {
    int error = 0;
    
    if (power < 0) {
        error = 1;
    } else if (power == 0) {
        error = 0; 
    } else {
        for (int i = 0; i < power && error == 0; i++) {
            s21_another_decimal temp = *value;
            s21_another_decimal temp2 = *value;
            s21_shift_left(&temp, 3);  
            s21_shift_left(&temp2, 1);
            error = s21_add(temp, temp2, value);
        }
    }
    
    return error;
}

int s21_div_by_10(s21_another_decimal *value, s21_another_decimal *result) {
   unsigned long long remainder = 0;
  for (int i = 2; i >= 0; i--) {
     unsigned long long current = (( unsigned long long)remainder << 32) | value->bits[i];
    result->bits[i] = (unsigned int)(current / 10);
    remainder = current % 10;
  }
  return (remainder == 0) ? 0 : 1;
}

int s21_compare_absolute(s21_another_decimal a, s21_another_decimal b) {
    // Сначала выравниваем экспоненты
    s21_align_exponents(&a, &b);
    
    // Сравниваем побитово
    for (int i = 2; i >= 0; i--) {
        if (a.bits[i] > b.bits[i]) return 1;
        if (a.bits[i] < b.bits[i]) return -1;
    }
    return 0;
}

int s21_is_zero(s21_another_decimal value) {
    return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}

int s21_get_exponent(s21_another_decimal src) {
    return src.exp; // Просто читаем битовое поле!
}

void s21_set_exponent(s21_another_decimal *src, unsigned int exp) {
    if (!src || exp > 28) return;
    src->exp = exp; // Просто устанавливаем битовое поле!
}


int s21_shift_left(s21_another_decimal *value, int shift) {
    int error = 0;
    if (!value || shift < 0) {
        error = 1;
    } else if (shift == 0) {
        error = 0;
    } else {
        for (int s = 0; s < shift && !error; s++) {
            unsigned int carry_prev = 0;
            
            for (int i = 0; i < 3; i++) {
                unsigned int current = value->bits[i];
                value->bits[i] = (current << 1) | carry_prev;
                carry_prev = (current >> 31) & 1;
            }
            if (carry_prev != 0) {
                error = 1;
            }
        }
    }
    
    return error;
}

