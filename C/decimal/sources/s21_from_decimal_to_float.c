#include "../s21_decimal.h"
#include "../headers/secondary.h"

int s21_from_decimal_to_float(s21_decimal crs, float *dst) {
  int result = 0;
  s21_big_decimal src = decimal_to_big(crs);
  unsigned long int *bits = src.bits;
  if (dst) {
    double tmp;
    for (int i = 0, j = 127; i < 96; i++, j--) {
      if (((bits[j / 64] >> i % 64) & 1) != 0) tmp += pow(2, i);
    }

    if (src.scale != 0 && src.scale <= 28) {
      for (int i = 0; i < src.scale; i++, tmp /= 10.0)
        ;
    }

    *dst = (float)tmp;
    if (src.sign) *dst *= -1;
  } else
    result = 1;

  return result;
}