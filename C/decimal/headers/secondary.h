#ifndef SECONDARY_H
#define SECONDARY_H

#include "../s21_decimal.h"

s21_decimal big_to_decimal(s21_big_decimal value);
s21_big_decimal decimal_to_big(s21_decimal value);

byte get_scale(s21_decimal value);
void set_scale(byte scale, s21_decimal *value);
byte get_sign(s21_decimal value);
void set_sign(byte scale, s21_decimal *value);

// Возвращает копию смещённой decimal
s21_big_decimal shift_decimal_right(s21_big_decimal decimal, int shift);
s21_big_decimal shift_decimal_left(s21_big_decimal decimal, int shift);

// Выравнивание коэффициента
int scale_alignment(s21_big_decimal *value_1, s21_big_decimal *value_2);

int mul_by_ten(s21_big_decimal value_1, s21_big_decimal *result);
void dec_copy(s21_big_decimal *dest, s21_big_decimal src);
s21_big_decimal div_by_ten(s21_big_decimal value);

// Убрать незначащие нули
s21_big_decimal trim_insig_zero(s21_big_decimal value);

int overflow(s21_big_decimal);

#endif  // SECONDARY_H
