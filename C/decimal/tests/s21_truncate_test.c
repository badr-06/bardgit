#include "../headers/main_test.h"
#include "../s21_decimal.h"

START_TEST(test_s21_truncate_1) {
  s21_decimal exept = {{63, 0, 0, -2147483648}};

  s21_decimal src_1 = {{32444, 100, 343253, -2145976320}};
  
  s21_decimal result = {0};

  s21_truncate(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}

START_TEST(test_s21_truncate_2) {
  s21_decimal exept = {{184467, 0, 0, 0}};

  s21_decimal src_1 = {{1, 1, 1, 917504}};
  
  s21_decimal result = {0};

  s21_truncate(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}

START_TEST(test_s21_truncate_3) {
  s21_decimal exept = {{0, 0, 0, 0}};

  s21_decimal src_1 = {{0, 0, 0, 851968}};
  
  s21_decimal result = {0};

  s21_truncate(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}

TCase *tcase_s21_truncate(void) {
  TCase *tc = tcase_create("s21_truncate");

  tcase_add_test(tc, test_s21_truncate_1);
  tcase_add_test(tc, test_s21_truncate_2);
  tcase_add_test(tc, test_s21_truncate_3);

  return tc;
}