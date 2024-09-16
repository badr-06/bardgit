#include <limits.h>

#include "../headers/main_test.h"

START_TEST(s21_decimal_to_int_test_1) {
  int answer = 12;
  s21_decimal src = {.bits = {12, 0, 0, 0}};
  int res;
  s21_from_decimal_to_int(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

START_TEST(s21_decimal_to_int_test_2) {
  int answer = 1;
  s21_decimal src = {
      .bits = {1254, 0, 0, 196608}};
  int res;
  s21_from_decimal_to_int(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

START_TEST(s21_decimal_to_int_test_3) {
  int answer = -12;
  s21_decimal src = {.bits = {12, 0, 0, 0b10000000000000000000000000000000}};
  int res;
  s21_from_decimal_to_int(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

START_TEST(s21_decimal_to_int_test_4) {
  int answer = -7;
  s21_decimal src = {.bits = {UINT_MAX, UINT_MAX, UINT_MAX,
                              0b10000000000111000000000000000000}};
  int res;
  s21_from_decimal_to_int(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

START_TEST(s21_decimal_to_int_test_5) {
  int answer = -4;
  s21_decimal src = {
      .bits = {UINT_MAX, 0, 0, -2146893824}};
  int res;
  s21_from_decimal_to_int(src, &res);
  ck_assert_int_eq(answer, res);
}
END_TEST

TCase *tcase_s21_from_decimal_to_int(void) {
  TCase *tc = tcase_create("s21_decimal_to_int");

  tcase_add_test(tc, s21_decimal_to_int_test_1);
  tcase_add_test(tc, s21_decimal_to_int_test_2);
  tcase_add_test(tc, s21_decimal_to_int_test_3);
  tcase_add_test(tc, s21_decimal_to_int_test_4);
  tcase_add_test(tc, s21_decimal_to_int_test_5);

  return tc;
}