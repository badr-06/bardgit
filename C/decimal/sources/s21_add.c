#include "../headers/secondary.h"
#include "../s21_decimal.h"

static int simple_add(s21_big_decimal value_1, s21_big_decimal value_2,
                      s21_big_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return NULL_PTR;
  s21_big_decimal big_value_1 = decimal_to_big(value_1);
  s21_big_decimal big_value_2 = decimal_to_big(value_2);
  s21_big_decimal big_result = {{0, 0}, 0, 0};
  int code = s21_big_add(big_value_1, big_value_2, &big_result);
  *result = big_to_decimal(big_result);
  return code;
}

int s21_big_add(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result) {
  if (result == NULL) return NULL_PTR;
  enum ErrCode code = SUCCESS;
  if (value_1.bits[0] > BITS_0_MAX || value_2.bits[0] > BITS_0_MAX)
    code = TOO_BIG;

  if (value_1.sign == 0 && value_2.sign == 0) {
    code = simple_add(value_1, value_2, result);
  } else if (value_1.sign == 0 && value_2.sign == 1) {
    value_2.sign = 0;
    code = s21_big_sub(value_1, value_2, result);
  } else if (value_1.sign == 1 && value_2.sign == 0) {
    value_1.sign = 0;
    code = s21_big_sub(value_2, value_1, result);
  } else {
    code = simple_add(value_1, value_2, result);
    result->sign = 1;
  }

  *result = trim_insig_zero(*result);

  return code;
}

// Сумма двух положительных
static int simple_add(s21_big_decimal value_1, s21_big_decimal value_2,
                      s21_big_decimal *result) {
  enum ErrCode сode = SUCCESS;  // Возвращаемый код

  scale_alignment(&value_1, &value_2);
  result->scale = value_1.scale;

  unsigned bits1[3];
  unsigned bits2[3];
  unsigned resbits[3];
  bits1[2] = (value_1.bits[1] << 32) >> 32;
  bits1[1] = value_1.bits[1] >> 32;
  bits1[0] = value_1.bits[0];
  bits2[2] = (value_2.bits[1] << 32) >> 32;
  bits2[1] = value_2.bits[1] >> 32;
  bits2[0] = value_2.bits[0];

  // Переменная для хранения числа в уме большего диапазона, потому что она и
  // пригождается только при переполнении исходного типа
  unsigned long long carryOne = 0;  // В уме
  for (int i = 2; i >= 0; i--) {
    carryOne += (unsigned long long)bits1[i] + bits2[i];
    resbits[i] = carryOne;  // Запишет первые 32 бита
    // Сместим число на 32 бита влево, 32 крайних бита будут потеряны,
    // что нам и нужно, эти биты уже записаны в первую часть результата
    carryOne = carryOne >> 32;
  }
  // Если после суммирования всех 3-х частей и отброса записанных знаков из
  // числа в уме, оно не равно 0, значит результирующее число больше диапазона
  // (либо меньше, но я пока что не реализовал работу с отрицательными числами),
  // нужно вернуть соответствующий код ошибки.
  // if (carryOne != 0) сode = TOO_BIG;

  carryOne <<= 32;
  carryOne += ((value_1.bits[0] >> 32) << 32) + ((value_2.bits[0] >> 32) << 32);
  if (carryOne != 0) сode = TOO_BIG;

  result->bits[1] = resbits[2] | ((unsigned long long)resbits[1] << 32);
  result->bits[0] = carryOne | resbits[0];
  return сode;
}