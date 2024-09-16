#include "../s21_decimal.h"
#include "../headers/secondary.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_int_to_decimal(src, &big_result);
  *dst = big_to_decimal(big_result);
  return code;
}

int s21_big_int_to_decimal(int src, s21_big_decimal *dst) {
  int result = 1;
  if (dst) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->scale = 0;
    dst->sign = 0;
    if (src == -2147483648) {
      dst->bits[1] = 2147483648;
      dst->sign = 1;
    } else {
      if (src < 0) {
        src = -src;
        dst->sign = 1;
      }
      dst->bits[1] = src;
    }

    result = 0;
  }

  return result;
}
