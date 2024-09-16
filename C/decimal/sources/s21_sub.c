#include "../headers/secondary.h"
#include "../s21_decimal.h"

static void simple_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                       s21_big_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return NULL_PTR;
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_sub(big_value_1, big_value_2, &big_result);
  *result = big_to_decimal(big_result);
  return code;
}

int s21_big_sub(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
  if (result == NULL) return NULL_PTR;
  enum ErrCode code = SUCCESS;

  if (value_1.sign == 0 && value_2.sign == 0) {
    if (!s21_big_is_less(value_1, value_2)) {
      simple_sub(value_1, value_2, result);
    } else {
      simple_sub(value_2, value_1, result);
      result->sign = 1;
    }
  } else if (value_1.sign == 1 && value_2.sign == 0) {
    value_1.sign = 0;
    code = s21_big_add(value_1, value_2, result);
    result->sign = 1;
  } else if (value_1.sign == 0 && value_2.sign == 1) {
    value_2.sign = 0;
    code = s21_big_add(value_1, value_2, result);
  } else {
    value_1.sign = 0;
    value_2.sign = 0;
    code = s21_big_sub(value_2, value_1, result);
  }

  *result = trim_insig_zero(*result);

  return code;
}

// Вычитание положительных 1-е больше 2-го
static void simple_sub(s21_big_decimal value_1, s21_big_decimal value_2,
                       s21_big_decimal *result) {
  scale_alignment(&value_1, &value_2);
  result->scale = value_1.scale;

  unsigned bits1[3];
  unsigned bits2[3];
  unsigned resbits[3];
  bits1[2] = (value_1.bits[1] << 32) >> 32;
  bits1[1] = value_1.bits[1] >> 32;
  bits1[0] = value_1.bits[0];
  bits2[2] = (value_2.bits[1] << 32) >> 32;
  bits2[1] = value_2.bits[1] >> 32;
  bits2[0] = value_2.bits[0];
  unsigned long long carryOne = 0;

  int isInDebt = 0;
  carryOne = bits1[2];
  if (carryOne < bits2[2]) {
    carryOne = carryOne | 1ull << 32;
    isInDebt = 1;
  }
  resbits[2] = carryOne - bits2[2];

  carryOne = bits1[1];
  if (isInDebt) {
    isInDebt = 0;
    if (carryOne < 1) {
      isInDebt = 1;
      carryOne = carryOne | 1ull << 32;
    }
    carryOne--;
  }
  if (carryOne < bits2[1]) {
    isInDebt = 1;
    carryOne = carryOne | 1ull << 32;
  }
  resbits[1] = carryOne - bits2[1];

  carryOne = bits1[0];
  if (isInDebt) {
    carryOne--;
  }
  resbits[0] = carryOne - bits2[0];
  result->bits[1] = resbits[2] | ((unsigned long long)resbits[1] << 32);
  result->bits[0] = resbits[0];
}
