#include "../headers/secondary.h"
#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_value = decimal_to_big(value);
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_negate(big_value, &big_result);
  *result = big_to_decimal(big_result);
  return code;
}

int s21_big_negate(s21_big_decimal value, s21_big_decimal *result) {
  *result = value;
  result->sign = !value.sign;
  return overflow(value);
}