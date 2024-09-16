#include <limits.h>

#include "../headers/main_test.h"

START_TEST(s21_decimal_to_float_test_1) {
  float answer = -8.765;
  s21_decimal src = {.bits = {8765, 0, 0, 0b10000000000000110000000000000000}};
  float res;
  s21_from_decimal_to_float(src, &res);
  ck_assert_float_eq(answer, res);
}
END_TEST

START_TEST(s21_decimal_to_float_test_2) {
  float answer = 1.254;
  s21_decimal src = {
      .bits = {1254, 0, 0, 196608}};
  float res;
  s21_from_decimal_to_float(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

START_TEST(s21_decimal_to_float_test_3) {
  float answer = -12;
  s21_decimal src = {.bits = {12, 0, 0, 0b10000000000000000000000000000000}};
  float res;
  s21_from_decimal_to_float(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

START_TEST(s21_decimal_to_float_test_4) {
  float answer = 12345;
  s21_decimal src = {.bits = {12345, 0, 0, 0}};
  float res;
  s21_from_decimal_to_float(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

START_TEST(s21_decimal_to_float_test_5) {
  float answer = -54.321;
  s21_decimal src = {.bits = {54321, 0, 0, -2147287040}};
  float res;
  s21_from_decimal_to_float(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

TCase *tcase_s21_from_decimal_to_float(void) {
  TCase *tc = tcase_create("s21_decimal_to_float");

  tcase_add_test(tc, s21_decimal_to_float_test_1);
  tcase_add_test(tc, s21_decimal_to_float_test_2);
  tcase_add_test(tc, s21_decimal_to_float_test_3);
  tcase_add_test(tc, s21_decimal_to_float_test_4);
  tcase_add_test(tc, s21_decimal_to_float_test_5);

  return tc;
}
