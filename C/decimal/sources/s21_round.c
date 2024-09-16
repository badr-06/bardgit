#include "../headers/secondary.h"
#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_value = decimal_to_big(value);
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_round(big_value, &big_result);
  *result = big_to_decimal(big_result);
  return code;
}

int s21_big_round(s21_big_decimal value, s21_big_decimal *result) {
  int code = SUCCESS;
  if (!result)
    code = CALC_ERROR;
  else {
    int prov;
    s21_big_decimal temp = value;
    if (value.scale == 0) {
      result->bits[0] = value.bits[0];
      result->bits[1] = value.bits[1];

    } else {
      *result = div_by_ten(value);
      s21_big_decimal tp = {0};
      mul_by_ten(*result, &tp);
      s21_big_sub(value, tp, &temp);
      prov = temp.bits[1];
      value = *result;
      temp.bits[1] = 0;
      for (int i = 0; i < value.scale - 1; i++) {
        *result = div_by_ten(*result);
        mul_by_ten(*result, &tp);
        s21_big_sub(value, tp, &temp);
        prov = temp.bits[1];
        value = *result;
        temp.bits[1] = 0;
      }
      result->scale = 0;

      if (prov > 4) ++(result->bits[1]);
    }
  }
  return code;
}