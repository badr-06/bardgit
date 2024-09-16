#include "../headers/main_test.h"


START_TEST(from_int_to_decimal_test_1) {
    s21_decimal exept = {{12, 0, 0, 0}};
    s21_decimal result = {0};
    int num = 12;
    s21_from_int_to_decimal(num, &result);
    int res = s21_is_equal(exept, result);

    ck_assert_int_eq(1, res);
} 
END_TEST

START_TEST(from_int_to_decimal_test_2) {
    s21_decimal exept = {{36, 0, 0, 0}};
    s21_decimal result = {0};
    int num = 36;
    s21_from_int_to_decimal(num, &result);
    int res = s21_is_equal(exept, result);

    ck_assert_int_eq(1, res);
} 
END_TEST

START_TEST(from_int_to_decimal_test_3) {
    s21_decimal exept = {{36, 0, 0, 0}};
    s21_decimal result = {0};
    int num = 36;
    s21_from_int_to_decimal(num, &result);
    int res = s21_is_equal(exept, result);

    ck_assert_int_eq(1, res);
} 
END_TEST

START_TEST(from_int_to_decimal_test_4) {
    s21_decimal exept = {{999, 0, 0, 0}};
    s21_decimal result = {0};
    int num = 999;
    s21_from_int_to_decimal(num, &result);
    int res = s21_is_equal(exept, result);

    ck_assert_int_eq(1, res);
} 
END_TEST

START_TEST(from_int_to_decimal_test_5) {
    s21_decimal exept = {{1999, 0, 0, 0}};
    s21_decimal result = {0};
    int num = 1999;
    s21_from_int_to_decimal(num, &result);
    int res = s21_is_equal(exept, result);

    ck_assert_int_eq(1, res);
} 
END_TEST

TCase *tcase_s21_from_int_to_decimal(void) {
  TCase *tc = tcase_create("s21_from_to_decimal");

  tcase_add_test(tc, from_int_to_decimal_test_1);
  tcase_add_test(tc, from_int_to_decimal_test_2);
  tcase_add_test(tc, from_int_to_decimal_test_3);
  tcase_add_test(tc, from_int_to_decimal_test_4);
  tcase_add_test(tc, from_int_to_decimal_test_5);

  return tc;
}
