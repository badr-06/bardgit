#include "../headers/secondary.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal crs, int *dst) {
  int result;
  s21_big_decimal src = decimal_to_big(crs);

  if (src.scale != 0) {
    for (int i = 0; i < src.scale; i++) {
      src = div_by_ten(src);
    }
  }

  if (src.bits[0] == 0 && src.bits[1] < UINT_MAX) {
    *dst = 0;
    *dst |= (int)src.bits[1];
    result = 0;

    if (src.sign) *dst *= -1;

  } else
    result = 1;

  return result;
}

