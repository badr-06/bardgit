#include "../headers/secondary.h"
#include "../s21_decimal.h"

static s21_big_decimal pow_decimal(int degree);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_div(big_value_1, big_value_2, &big_result);
  *result = big_to_decimal(big_result);
  return code;
}

int s21_big_div(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
  enum ErrCode code = SUCCESS;
  int i;

  s21_big_decimal ten = {{0, 10}, 0, 0};
  s21_big_decimal zero = {0};

  if (s21_big_is_equal(value_2, zero)) {
    code = DEVISION_BY_ZERO;
  } else {
    byte sign;
    byte scale_tmp = value_1.scale - value_2.scale;
    if (value_1.sign != value_2.sign) sign = 1;
    else sign = 0;

    value_1.scale = value_2.scale = 0;
    value_1.sign = value_2.sign = 0;

    s21_big_decimal bits2_tmp = value_2;

    while (s21_big_is_not_equal(value_1, zero) && scale_tmp < 29) {
      while (s21_big_is_geater(value_2, value_1) && scale_tmp < 29) {
        s21_big_mul(value_1, ten, &value_1);
        s21_big_mul(*result, ten, result);
        scale_tmp = scale_tmp + 1;
      }
      i = 0;
      while (s21_big_is_less_or_equal(shift_decimal_left(value_2, 1), value_1)) {
        value_2 = shift_decimal_left(value_2, 1);
        i++;
      }
      s21_big_sub(value_1, value_2, &value_1);
      value_2 = bits2_tmp;
      s21_big_add(*result, pow_decimal(i), result);
    }

    while (scale_tmp < 0) {
      s21_big_mul(*result, ten, result);
      scale_tmp = scale_tmp + 1;
    }

    result->scale = scale_tmp;
    result->sign = sign;
  }

  if ((result->bits[0] > BITS_0_MAX) && !result->sign)
    code = TOO_BIG;
  else if ((result->bits[0] > BITS_0_MAX) && result->sign)
    code = TOO_SMALL;

  return code;
}

s21_big_decimal pow_decimal(int degree) {
  s21_big_decimal res = {{0, 1}, 0, 0};
  s21_big_decimal two = {{0, 2}, 0, 0};
  for (int i = 1; i <= degree; i++) {
    s21_big_mul(res, two, &res);
  }
  return res;
}