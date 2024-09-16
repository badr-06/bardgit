#include "../headers/main_test.h"

START_TEST(test_s21_div_1) {
  s21_decimal exept = {{1, 0, 0, 0}};

  s21_decimal src_1 = {{1, 1, 1, 655360}};
  s21_decimal src_2 = {{1, 1, 1, 655360}};
  
  s21_decimal result = {0};

  s21_div(src_1, src_2, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_s21_div_2) {
  s21_decimal exept = {{100000, 0, 0, 0}};

  s21_decimal src_1 = {{1, 1, 1, 655360}};
  s21_decimal src_2 = {{1, 1, 1, 983040}};
  
  s21_decimal result = {0};

  s21_div(src_1, src_2, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_s21_div_3) {
  s21_decimal exept = {{1, 0, 0, -2147483648}};

  s21_decimal src_1 = {{1, 1, 1, 983040}};
  s21_decimal src_2 = {{1, 1, 1, -2146500608}};
  
  s21_decimal result = {0};

  s21_div(src_1, src_2, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal src_1 = {{1, 1, 1, 0}};
  s21_decimal src_2 = {{0, 0, 0, 0}};

  s21_decimal result = {0};

  int res = s21_div(src_1, src_2, &result);

  ck_assert_int_eq(3, res);
}
END_TEST

START_TEST(test_s21_div_5) {
  s21_decimal exept = {{1, 0, 0, 65536}};
  s21_decimal src_1 = {{1, 0, 0, 0}};
  s21_decimal src_2 = {{10, 0, 0, 0}};

  s21_decimal result = {0};
  
  s21_div(src_1, src_2, &result);

  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST


TCase *tcase_s21_div(void) {
  TCase *tc = tcase_create("s21_div");

  tcase_add_test(tc, test_s21_div_1);
  tcase_add_test(tc, test_s21_div_2);
  tcase_add_test(tc, test_s21_div_3);
  tcase_add_test(tc, test_s21_div_4);
  tcase_add_test(tc, test_s21_div_5);

  return tc;
}