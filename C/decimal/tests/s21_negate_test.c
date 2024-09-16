#include "../headers/main_test.h"
#include "../s21_decimal.h"

START_TEST(negate_test_1) {
  s21_decimal exept = {{32444, 100, 343253, 1507328}};

  s21_decimal src_1 = {{32444, 100, 343253, -2145976320}};
  
  s21_decimal result = {0};

  s21_negate(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(negate_test_2) {
  s21_decimal exept = {{1, 1, 1, -2146566144}};

  s21_decimal src_1 = {{1, 1, 1, 917504}};
  
  s21_decimal result = {0};

  s21_negate(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

START_TEST(negate_test_3) {
  s21_decimal exept = {{0, 0, 0, -2146566144}};

  s21_decimal src_1 = {{0, 0, 0, 917504}};
  
  s21_decimal result = {0};

  s21_negate(src_1, &result);
  
  int res = s21_is_equal(result, exept);

  ck_assert_int_eq(1, res);
}
END_TEST

TCase *tcase_s21_negate(void) {
  TCase *tc = tcase_create("s21_negate");

  tcase_add_test(tc, negate_test_1);
  tcase_add_test(tc, negate_test_2);
  tcase_add_test(tc, negate_test_3);

  return tc;
}