#include "../headers/secondary.h"
#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_big_decimal big_value = decimal_to_big(value);
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_truncate(big_value, &big_result);
  *result = big_to_decimal(big_result);
  return code;
}

int s21_big_truncate(s21_big_decimal value, s21_big_decimal *result) {
  int code = overflow(value);
  while (value.scale > 0) {
    value = div_by_ten(value);
    value.scale--;
  }

  dec_copy(result, value);
  return code;
}