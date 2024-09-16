#include "../headers/secondary.h"
#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return NULL_PTR;
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_mul(big_value_1, big_value_2, &big_result);
  *result = big_to_decimal(big_result);
  return code;
}

int s21_big_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result) {
  if (result == NULL) {
    return NULL_PTR;
  }
  enum ErrCode code = SUCCESS;
  result->bits[0] = result->bits[1] = result->scale = result->sign = 0;
  for (int i = 127; i >= 0; i--) {
    if ((value_2.bits[i / 64] >> (63 - i % 64)) & 1) {
      s21_big_add(*result, value_1, result);
    }
    value_1 = shift_decimal_left(value_1, 1);
  }
  result->scale = value_1.scale + value_2.scale;
  result->sign = 0;

  if (value_1.sign != value_2.sign) result->sign = 1;
  return code = overflow(*result);
}
