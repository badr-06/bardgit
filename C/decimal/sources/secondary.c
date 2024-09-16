#include "../headers/secondary.h"

#include "../s21_decimal.h"

s21_decimal big_to_decimal(s21_big_decimal value) {
  s21_decimal result = {{0, 0, 0, 0}};
  result.bits[0] = value.bits[1];
  result.bits[1] = value.bits[1] >> 32;
  result.bits[2] = value.bits[0];
  set_scale(value.scale, &result);
  set_sign(value.sign, &result);
  return result;
}

s21_big_decimal decimal_to_big(s21_decimal value) {
  s21_big_decimal result = {{0, 0}, 0, 0};
  result.bits[1] =
      (unsigned)value.bits[0] | ((unsigned long)value.bits[1] << 32);
  result.bits[0] = (unsigned)value.bits[2];
  result.scale = get_scale(value);
  result.sign = get_sign(value);
  return result;
}

byte get_scale(s21_decimal value) { return (value.bits[3] >> 16) & UCHAR_MAX; }

void set_scale(byte scale, s21_decimal *value) {
  value->bits[3] = (get_sign(*value) << 31) | ((int)scale << 16);
}

byte get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }

void set_sign(byte sign, s21_decimal *value) {
  value->bits[3] = ((int)sign << 31) | (get_scale(*value) << 16);
}

// Возвращает копию decimal смещённую вправо
s21_big_decimal shift_decimal_right(s21_big_decimal decimal, int shift) {
  if (shift > 0) {
    unsigned long *bits = decimal.bits;
    bits[1] = shift < 64 ? bits[1] >> shift : 0;
    if (shift < 64)
      bits[1] = bits[1] | bits[0] << (64 - shift);
    else if (shift < 128)
      bits[1] = bits[0] >> (shift - 64);
    else
      bits[1] = 0;

    bits[0] = shift < 64 ? bits[0] >> shift : 0;
  } else if (shift < 0)
    decimal = shift_decimal_left(decimal, -shift);
  return decimal;
}

// Возвращает копию decimal смещённую влево
s21_big_decimal shift_decimal_left(s21_big_decimal decimal, int shift) {
  if (shift > 0) {
    unsigned long *bits = decimal.bits;
    bits[0] = shift < 64 ? bits[0] << shift : 0;
    if (shift < 64)
      bits[0] = bits[0] | bits[1] >> (64 - shift);
    else if (shift < 128)
      bits[0] = bits[1] << (shift - 64);
    else
      bits[0] = 0;

    bits[1] = shift < 64 ? bits[1] << shift : 0;
  } else if (shift < 0) {
    decimal = shift_decimal_right(decimal, -shift);
  }
  return decimal;
}

void dec_copy(s21_big_decimal *dest, s21_big_decimal src) {
  if (dest == NULL) return;

  dest->bits[0] = src.bits[0];
  dest->bits[1] = src.bits[1];
  dest->scale = src.scale;
  dest->sign = src.sign;
}

// Выравнивание коэффициента
int scale_alignment(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  if (value_1->scale == value_2->scale) return SUCCESS;
  enum ErrCode code = SUCCESS;
  unsigned diff = value_1->scale > value_2->scale
                      ? value_1->scale - value_2->scale
                      : value_2->scale - value_1->scale;
  s21_big_decimal temp = value_1->scale < value_2->scale ? *value_1 : *value_2;
  temp.scale = 0;
  while (diff) {
    code = mul_by_ten(temp, &temp);
    diff--;
  }
  if (value_1->scale < value_2->scale) {
    dec_copy(value_1, temp);
    value_1->scale = value_2->scale;
  } else {
    dec_copy(value_2, temp);
    value_2->scale = value_1->scale;
  }
  return code;
}

int mul_by_ten(s21_big_decimal value_1, s21_big_decimal *result) {
  byte scale = value_1.scale;
  byte sign = value_1.sign;
  value_1.scale = 0;
  value_1.sign = 0;
  int code = s21_big_add(shift_decimal_left(value_1, 1),
                         shift_decimal_left(value_1, 3), result);
  result->scale = scale;
  result->sign = sign;
  return code;
}

static int greater_than_zero(s21_big_decimal value) {
  return value.sign == 0 && (value.bits[0] > 0 || value.bits[1] > 0);
}

s21_big_decimal div_by_ten(s21_big_decimal value) {
  byte tempSign = value.sign;
  byte tempScale = value.scale;
  value.sign = 0;
  value.scale = 0;
  s21_big_decimal result = {{0, 0}, 0, 0};
  s21_big_decimal tempRes = shift_decimal_right(value, 3);
  s21_big_decimal forCheck = {{0, 0}, 0, 0};
  s21_big_decimal adjustment = {{0, 0}, 0, 0};
  mul_by_ten(tempRes, &forCheck);
  s21_big_sub(forCheck, value, &adjustment);
  if (greater_than_zero(adjustment)) {
    adjustment = div_by_ten(adjustment);
    s21_big_sub(tempRes, adjustment, &tempRes);
  }
  mul_by_ten(tempRes, &forCheck);
  s21_big_sub(forCheck, value, &adjustment);
  value.bits[0] = 0;
  value.bits[1] = 1;
  value.sign = 0;
  value.scale = 0;
  if (greater_than_zero(adjustment)) s21_big_sub(tempRes, value, &tempRes);

  dec_copy(&result, tempRes);
  result.sign = tempSign;
  result.scale = tempScale;
  return result;
}

// Убрать незначащие нули
s21_big_decimal trim_insig_zero(s21_big_decimal value) {
  byte sign = value.sign;
  value.sign = 0;
  static int block = 0;
  if (block == 0) {
    block = 1;
    s21_big_decimal divVal = value;
    while (value.scale > 0) {
      divVal = value;
      divVal = div_by_ten(divVal);
      mul_by_ten(divVal, &divVal);
      if (!s21_big_is_equal(value, divVal)) break;
      value = div_by_ten(value);
      value.scale--;
    }
    block = 0;
  }
  value.sign = sign;
  return value;
}

int overflow(s21_big_decimal result) {
  int flag = 0;
  for (int i = 32; i < 64; i++) {
    if ((result.bits[0] >> i) & 1) {
      if (result.sign == 1)
        flag = 2;
      else
        flag = 1;
    }
  }
  return flag;
}
