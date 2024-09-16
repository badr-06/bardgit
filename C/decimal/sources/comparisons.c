#include "../headers/secondary.h"
#include "../s21_decimal.h"

//-//-//-//-//-//-//   comparison  <     //-//-//-//-//-//-//
int normalization(s21_big_decimal src_1, s21_big_decimal src_2) {
  int scale = 0;
  int result = 0;
  if (src_1.scale > src_2.scale) {
    scale = src_1.scale - src_2.scale;
    for (int i = 0; i < scale; i++) {
      mul_by_ten(src_2, &src_2);
    }
    if (src_1.bits[0] < src_2.bits[0])
      result = 1;
    else if(src_1.bits[0] == src_2.bits[0]){
      if(src_1.bits[1] < src_2.bits[1]) result = 1;
    }
  } else {
    scale = src_2.scale - src_1.scale;
    for (int i = 0; i < scale; i++) {
      mul_by_ten(src_1, &src_1);
    }
    if (src_1.bits[0] < src_2.bits[0])
      result = 1;
    else if(src_1.bits[0] == src_2.bits[0]){
      if(src_1.bits[1] < src_2.bits[1]) result = 1;
    }
  }

  return result;
}

int s21_is_less_scale(s21_big_decimal src_1, s21_big_decimal src_2) {
  int result = 0;
  s21_big_decimal src_int_1 = src_1;
  s21_big_decimal src_int_2 = src_2;

  for (int i = 0; i < src_int_1.scale; i++) {
    src_int_1 = div_by_ten(src_int_1);
  }
  for (int i = 0; i < src_int_2.scale; i++) {
    src_int_2 = div_by_ten(src_int_2);
  }
  if (src_int_1.bits[0] < src_int_2.bits[0])
    result = 1;
  else if (src_int_1.bits[1] < src_int_2.bits[1])
    result = 1;
  else {
    if (src_1.scale == src_2.scale) {
      if (src_1.bits[0] < src_2.bits[0])
        result = 1;
      else if (src_1.bits[1] < src_2.bits[1])
        result = 1;
    } else {
      result = normalization(src_1, src_2);
    }
  }

  return result;
}

int s21_big_is_less(s21_big_decimal src_1, s21_big_decimal src_2)
{
  int result = 0;
  unsigned long int *date_1;
  unsigned long int *date_2;

  if (src_1.sign && src_2.sign) {
    date_1 = src_2.bits;
    date_2 = src_1.bits;
    src_1.scale = src_1.scale - src_2.scale;
    src_2.scale = src_2.scale + src_1.scale;
    src_1.scale = src_2.scale - src_1.scale;
  } else {
    date_1 = src_1.bits;
    date_2 = src_2.bits;
  }

  if (date_1 == NULL || date_2 == NULL) return 0;
  if (src_1.sign && !src_2.sign)
    result = 1;

  else if (src_2.sign && !src_1.sign)
    result = 0;

  else {
    if (src_1.scale || src_2.scale) {
      result = s21_is_less_scale(src_1, src_2);
    } else {
      if (date_1[0] < date_2[0])
        result = 1;
      else if (date_1[0] == date_2[0]) {
        if (date_1[1] < date_2[1]){ result = 1; }
      }
    }
  }
  return result;
}

int s21_is_less(s21_decimal crs_1, s21_decimal crs_2) {
  int result = 0;
  s21_big_decimal src_1 = decimal_to_big(crs_1);
  s21_big_decimal src_2 = decimal_to_big(crs_2);
  unsigned long int *date_1;
  unsigned long int *date_2;

  if (src_1.sign && src_2.sign) {
    date_1 = src_2.bits;
    date_2 = src_1.bits;
    src_1.scale = src_1.scale - src_2.scale;
    src_2.scale = src_2.scale + src_1.scale;
    src_1.scale = src_2.scale - src_1.scale;
  } else {
    date_1 = src_1.bits;
    date_2 = src_2.bits;
  }

  if (date_1 == NULL || date_2 == NULL) return 0;
  if (src_1.sign && !src_2.sign)
    result = 1;

  else if (src_2.sign && !src_1.sign)
    result = 0;

  else {
    if (src_1.scale || src_2.scale) {
      result = s21_is_less_scale(src_1, src_2);
    } else {
      if (date_1[0] < date_2[0])
        result = 1;
      else if (date_1[0] == date_2[0]) {
        if (date_1[1] < date_2[1]){ result = 1; }
      }
    }
  }
  return result;
}

//-//-//-//-//-//-//   comparison  <=     //-//-//-//-//-//-//
int s21_big_is_less_or_equal(s21_big_decimal src_1, s21_big_decimal src_2)
{
  int code;
  s21_decimal crs_1 = big_to_decimal(src_1);
  s21_decimal crs_2 = big_to_decimal(src_2);

  code = s21_is_less_or_equal(crs_1, crs_2);

  return code;

}

int s21_is_less_or_equal(s21_decimal src_1, s21_decimal src_2) {

  int result = 0;
  if (s21_is_equal(src_1, src_2) || s21_is_less(src_1, src_2)) result = 1;

  return result;
}

//-//-//-//-//-//-//   comparison  >     //-//-//-//-//-//-//
int s21_big_is_geater(s21_big_decimal src_1, s21_big_decimal src_2)
{
  s21_decimal crs_1 = big_to_decimal(src_1);
  s21_decimal crs_2 = big_to_decimal(src_2);
  int result = 0;
  if (!s21_is_less_or_equal(crs_1, crs_2)) result = 1;

  return result;
}

int s21_is_greater(s21_decimal src_1, s21_decimal src_2) {
  int result = 0;
  if (!s21_is_less_or_equal(src_1, src_2)) result = 1;

  return result;
}

//-//-//-//-//-//-//   comparison  >=     //-//-//-//-//-//-//
int s21_big_is_greater_or_equal(s21_big_decimal src_1, s21_big_decimal src_2)
{
  s21_decimal crs_1 = big_to_decimal(src_1);
  s21_decimal crs_2 = big_to_decimal(src_2);

  int result = 0;
  if (!s21_is_less(crs_1, crs_2)) result = 1;

  return result;
  
}

int s21_is_greater_or_equal(s21_decimal src_1, s21_decimal src_2) {
  int result = 0;
  if (!s21_is_less(src_1, src_2)) result = 1;

  return result;
}

//-//-//-//-//-//-//   comparison  ==     //-//-//-//-//-//-//
int s21_big_is_equal(s21_big_decimal crs_1, s21_big_decimal crs_2)
{
  s21_decimal src_1 = big_to_decimal(crs_1);
  s21_decimal src_2 = big_to_decimal(crs_2);
  int code;

  code = s21_is_equal(src_1, src_2);

  return code;

}

int s21_is_equal(s21_decimal crs_1, s21_decimal crs_2) {

  s21_big_decimal src_1 = decimal_to_big(crs_1);
  s21_big_decimal src_2 = decimal_to_big(crs_2);
  
  int result = 1;
  unsigned long int *date_1 = src_1.bits;
  unsigned long int *date_2 = src_2.bits;

  if (date_1 == NULL || date_2 == NULL) return 0;
  if (src_1.sign && !src_2.sign)
    result = 0;

  else if (src_2.sign && !src_1.sign)
    result = 0;

  else if (src_1.scale != src_2.scale)
    result = 0;

  else {
    if (date_1[0] != date_2[0])
      result = 0;
    else {
      if (date_1[1] != date_2[1]) result = 0;
    }
  }
  return result;
}

//-//-//-//-//-//-//   comparison  !=     //-//-//-//-//-//-//
int s21_big_is_not_equal(s21_big_decimal crs_1, s21_big_decimal crs_2)
{
  s21_decimal src_1 = big_to_decimal(crs_1);
  s21_decimal src_2 = big_to_decimal(crs_2);
  int code;

   if (!s21_is_equal(src_1, src_2)) code = 1;

  return code;

}

int s21_is_not_equal(s21_decimal src_1, s21_decimal src_2) {
  int result = 0;
  if (!s21_is_equal(src_1, src_2)) result = 1;

  return result;
}