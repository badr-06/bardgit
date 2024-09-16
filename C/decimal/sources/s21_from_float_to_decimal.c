#include "../headers/secondary.h"
#include "../s21_decimal.h"


int s21_from_float_to_decimal(float src, s21_decimal *dst)  {
  if (dst == NULL) return NULL_PTR;
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_float_to_decimal(src, &big_result);
  *dst = big_to_decimal(big_result);
  return code;
}

int calculate_scale(const char *str_src, int scale_tmp, char str_digit_sign,
                    int *count) {
  int scale = 0;
  for (int i = 7; i >= 0; i--) {
    if (str_src[i] == '0')
      continue;
    else if (str_src[i] == '.')
      break;
    else {
      *count = i - 1;
      if (scale_tmp < 6 && str_digit_sign == '+')
        scale = i - 1 - scale_tmp;
      else if (str_digit_sign == '-')
        scale = scale_tmp + i - 1;
      break;
    }
  }
  return scale;
}

int s21_big_float_to_decimal(float src, s21_big_decimal *dst) {
  int res = 0;
  const double MAX_DECIMAL = 79228162514264337593543950335.0;
  const double MIN_DECIMAL = 1e-28;
  int scale_tmp = 0;
  int scale = 0;
  if ((src < MIN_DECIMAL && src > 0) || !dst) {
    res = 1;
  } else if (fabs(src) > MAX_DECIMAL || isinf(src) || isnan(src)) {
    res = 1;
  } else {
   dst->bits[0] = dst->bits[1] = dst->scale = dst->sign = 0;
    if (src < 0) {
      src = -src;
      dst->sign = 1;
    }
    char str_src[100];
    sprintf(str_src, "%E", src);
    char string_digit[3];
    int count = 0;
    string_digit[0] = str_src[10];
    string_digit[1] = str_src[11];
    string_digit[2] = '\0';
    scale_tmp = strtol(string_digit, NULL, 10);
    char str_digit_sign = str_src[9];
    scale = calculate_scale(str_src, scale_tmp, str_digit_sign, &count);
    str_src[8] = '\0';
    double result_src = strtod(str_src, NULL);
    for (int i = 0; i < count && i < 6; i++) {
      result_src *= 10;
    }
    unsigned long int num = (int)result_src;
    if (scale > 28) scale = 28;
    dst->scale = scale;
    dst->bits[1] = num;

  }
  return res;
}