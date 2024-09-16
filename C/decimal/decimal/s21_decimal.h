#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Чтобы проверить на переполнение нужно просто вызвать сравнение
// bits[0] > BITS_0_MAX
// если больше, значит число занимает больше 96 бит
#define BITS_0_MAX 0xfffffffful

typedef char byte;

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  unsigned long int bits[2];
  byte sign;
  byte scale;
} s21_big_decimal;

// Коды возвращаемые ошибок:
enum ErrCode {
  SUCCESS = 0,  // Ошибок нет
  // Арифметических функций
  TOO_BIG = 1,  // Число слишком велико или стремится к бесконечности
  TOO_SMALL = 2,  // Число слишком мало или стремится к минус бесконечности
  DEVISION_BY_ZERO = 3,  // Деление на 0
  // Функций конвертации
  CONVERT_ERROR = 1,  //Ошибка конвертации
  // Доп. функций
  CALC_ERROR = 1,  //Ошибка вычисления

  NULL_PTR = -1  // Аргумент не инициализирован
};

// Арифметические операторы
// Сложение
int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);
int s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result);

// Вычитание
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);
int s21_big_sub(s21_big_decimal value_1, s21_big_decimal value_2,
            s21_big_decimal *result);

// Умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);
int s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result);

// Деление
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);
int s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result);


// Коды возвращаемые функциями сравнения:
enum CompareCode { FALSE = 0, TRUE = 1 };

// Операторы сравнения
int s21_is_less(s21_decimal, s21_decimal);           // Меньше
int s21_big_is_less(s21_big_decimal src_1, s21_big_decimal src_2);

int s21_is_less_or_equal(s21_decimal, s21_decimal);  // Меньше или равно
int s21_big_is_less_or_equal(s21_big_decimal src_1, s21_big_decimal src_2);

int s21_is_greater(s21_decimal, s21_decimal);        // Больше
int s21_big_is_geater(s21_big_decimal src_1, s21_big_decimal src_2);

int s21_is_greater_or_equal(s21_decimal, s21_decimal);  // Больше или равно
int s21_big_is_greater_or_equal(s21_big_decimal src_1, s21_big_decimal src_2);

int s21_is_equal(s21_decimal, s21_decimal);             // Равно
int s21_big_is_equal(s21_big_decimal crs_1, s21_big_decimal crs_2);

int s21_is_not_equal(s21_decimal, s21_decimal);  // Не равно
int s21_big_is_not_equal(s21_big_decimal crs_1, s21_big_decimal crs_2);

// Преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);      // Из int
int s21_big_int_to_decimal(int src, s21_big_decimal *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);      // В int

int s21_from_float_to_decimal(float src, s21_decimal *dst);  // Из float
int s21_big_float_to_decimal(float src, s21_big_decimal *dst);

int s21_from_decimal_to_float(s21_decimal src, float *dst);  // В float

// Другие функции
int s21_floor(s21_decimal value,
              s21_decimal *result);  // Округляет указанное Decimal число до
                                     // ближайшего целого числа в сторону
                                     // отрицательной бесконечности.
int s21_big_floor(s21_big_decimal value, s21_big_decimal *result);

int s21_round(
    s21_decimal value,
    s21_decimal *result);  // Округляет Decimal до ближайшего целого числа.
int s21_big_round(s21_big_decimal value, s21_big_decimal *result);

int s21_truncate(s21_decimal value,
                 s21_decimal *result);  // Возвращает целые цифры указанного
                                        // Decimal числа; любые дробные цифры
                                        // отбрасываются, включая конечные нули.
int s21_big_truncate(s21_big_decimal value, s21_big_decimal *result);

int s21_negate(s21_decimal value,
               s21_decimal *result);  // Возвращает результат умножения
                                      // указанного Decimal на -1.
int s21_big_negate(s21_big_decimal value, s21_big_decimal *result);

#endif  // S21_DECIMAL_H