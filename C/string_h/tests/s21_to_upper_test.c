#include "../headers/main_test.h"

START_TEST(test_s21_to_upper_1) {
  char str[] = "Hello, world!\n";
  char *result = s21_to_upper(str);
  char *expected = "HELLO, WORLD!\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_2) {
  char str[] = "HELLO\nMy name\tis Henry.\n";
  char *result = s21_to_upper(str);
  char *expected = "HELLO\nMY NAME\tIS HENRY.\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_3) {
  char str[] = "0123456789\t0123456789\v";
  char *result = s21_to_upper(str);
  char *expected = "0123456789\t0123456789\v";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_4) {
  char str[] = "";
  char *result = s21_to_upper(str);
  char *expected = "";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_5) {
  char str[] = "HELLO, WORLD!\n";
  char *result = s21_to_upper(str);
  char *expected = "HELLO, WORLD!\n";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_6) {
  char *str = S21_NULL;
  char *result = s21_to_upper(str);
  ck_assert_ptr_null(result);
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_7) {
  char *str = "qwertyuiop_lkjhgfdsaz_xcvbnm";
  char *result = s21_to_upper(str);
  char *expected = "QWERTYUIOP_LKJHGFDSAZ_XCVBNM";
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

TCase *tcase_s21_to_upper(void) {
  TCase *tcase = tcase_create("s21_to_upper");
  tcase_add_test(tcase, test_s21_to_upper_1);
  tcase_add_test(tcase, test_s21_to_upper_2);
  tcase_add_test(tcase, test_s21_to_upper_3);
  tcase_add_test(tcase, test_s21_to_upper_4);
  tcase_add_test(tcase, test_s21_to_upper_5);
  tcase_add_test(tcase, test_s21_to_upper_6);
  tcase_add_test(tcase, test_s21_to_upper_7);

  return tcase;
}