#include "../headers/secondary.h"
#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_value = decimal_to_big(value);
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_floor(big_value, &big_result);
  *result = big_to_decimal(big_result);
  return code;
}

int s21_big_floor(s21_big_decimal value, s21_big_decimal *result) {
  enum ErrCode code = SUCCESS;

  if (!result) {
    code = CALC_ERROR;
  } else {
    result->bits[0] = result->bits[1] = 0;
    result->scale = 0;
    byte sign = value.sign;
    result->sign = value.sign = 0;

    if (value.scale == 0) {
      result->bits[0] = value.bits[0];
      result->bits[1] = value.bits[1];
      result->sign = sign;
    } else {
      while (value.scale != 0) {
        value = div_by_ten(value);
        value.scale--;
      }

      result->bits[0] = value.bits[0];
      result->bits[1] = value.bits[1];

      if (sign) {
        s21_big_decimal one = {{0, 1}, 0, 0};
        s21_big_add(*result, one, result);
      }

      result->sign = sign;
    }
  }

  return code;
}